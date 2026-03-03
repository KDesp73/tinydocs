# @module parser
from pathlib import Path
from typing import List, Dict, Any, Optional
from .markers import Marker, Argument, MarkerType
import re


# @class Parser
# @desc This class is responsible for reading
# and parsing the doc attributes from a file
class Parser:
    # @constructor
    # @param file The file to parse
    # @param comment The comment prefix (#, //, etc). Defaults to `#`
    def __init__(self, file: Path, comment: Optional[str] = "#", prefix: Optional[str] = "@"):
        if not comment:
            raise ValueError("comment should be defined")
        if not prefix:
            raise ValueError("prefix should be defined")

        self.file = file
        self.comment = comment
        self.prefix = prefix

    # @method parse
    # @param markers The list of markers to look for while parsing 
    # @returns List[Dict[str,Any]] The resulting documentation from each file
    def parse(self, markers: List[Marker]) -> List[Dict[str, Any]]:
        # Ensure all markers have a prefix
        for marker in markers:
            if not marker.prefix:
                marker.prefix = self.prefix

        text = self.file.read_text()
        lines = text.split("\n")

        final_modules = []    # List of all modules found in the file
        active_module = None  # The current module scope
        current_block = None  # The specific item (Class/Method) for metadata

        METADATA_MARKERS = {
            MarkerType.PARAMETER.value,
            MarkerType.DESCRIPTION.value,
            MarkerType.RETURN.value,
            MarkerType.EXAMPLE.value,
            MarkerType.AUTHOR.value,
            MarkerType.LICENSE.value
        }
        MULTILINE_TYPES = {
            MarkerType.DESCRIPTION.value,
            MarkerType.RETURN.value,
            MarkerType.EXAMPLE.value,
            MarkerType.ANY.value
        }

        for line_number, line in enumerate(lines, start=1):
            raw_line = line.strip()

            # Check if line starts with comment prefix
            if not raw_line.startswith(self.comment):
                current_block = None
                continue

            # Strip comment and whitespace
            content = re.sub(rf"^{re.escape(self.comment)}\s*", "", raw_line).strip()
            if not content:
                continue

            found_new_marker = False
            for marker in markers:
                match = re.match(marker.pattern(), content)
                if not match:
                    continue

                found_new_marker = True
                args = []
                if marker.arg != Argument.NONE:
                    raw_args = match.group("arg").strip()
                    if not raw_args:
                        raise ValueError(f"Marker @{marker.name} requires args at line {line_number}")

                    argc = getattr(marker, "argc", 1)
                    split_args = raw_args.split(" ", maxsplit=argc - 1)
                    if len(split_args) < argc:
                        raise ValueError(f"@{marker.name} expected {argc} args at line {line_number}")
                    args = split_args

                entry = {
                    "marker": marker.name,
                    "type": marker.type.value,
                    "args": args,
                    "line": line_number,
                    "children": []
                }

                # --- Hierarchy Logic ---
                if marker.type.value in METADATA_MARKERS:
                    # Metadata always belongs to the last defined structural block
                    if current_block:
                        current_block["children"].append(entry)
                    elif active_module:
                        # Fallback: if no class/method is active, it belongs to the module
                        active_module["children"].append(entry)
                    else:
                        # Orphan metadata at top of file
                        final_modules.append(entry)
                
                elif marker.name == "module":
                    # A new module starts a new scope for everything below it
                    active_module = entry
                    final_modules.append(active_module)
                    current_block = active_module
                
                else:
                    # This is a structural marker (Class, Function, Struct, etc.)
                    if active_module:
                        # Nest this block inside the current active module
                        active_module["children"].append(entry)
                    else:
                        # If no module defined yet, it's a top-level block
                        final_modules.append(entry)
                    
                    # Update current_block so subsequent metadata belongs here
                    current_block = entry
                break

            # --- Multiline Handling ---
            if not found_new_marker and current_block:
                # Find the target for the text: either the block itself or its last child
                target = current_block["children"][-1] if current_block["children"] else current_block
                
                if target["type"] in MULTILINE_TYPES:
                    if target["args"]:
                        joiner = "\n" if target["type"] == MarkerType.EXAMPLE.value else " "
                        target["args"][-1] += f"{joiner}{content}"
                    else:
                        target["args"] = [content]

        return final_modules
