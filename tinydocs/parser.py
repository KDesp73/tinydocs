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
    # @returns List[Dict[str, Any]]
    def parse(self, markers: List[Marker]) -> List[Dict[str, Any]]:
        # Ensure all markers have a prefix
        for marker in markers:
            if not marker.prefix:
                marker.prefix = self.prefix

        text = self.file.read_text()
        lines = text.split("\n")

        all_blocks = []
        current_block = None  # Structural parent (Module, Class, Function)
        module_node = None

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
            if not content: continue

            found_new_marker = False
            for marker in markers:
                match = re.match(marker.pattern(), content)
                if not match: continue

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

                # Hierarchy Logic
                if marker.type.value in METADATA_MARKERS:
                    if current_block:
                        current_block["children"].append(entry)
                    else:
                        all_blocks.append(entry)
                else:
                    # This is a structural marker (Module, Class, Function, etc.)
                    if marker.name == "module":
                        module_node = entry
                    
                    all_blocks.append(entry)
                    current_block = entry # New context for subsequent metadata markers
                break

            # Multiline Handling
            if not found_new_marker and current_block:
                # Target: the specific metadata item or the block itself
                target = current_block["children"][-1] if current_block["children"] else current_block
                
                if target["type"] in MULTILINE_TYPES:
                    if target["args"]:
                        # Join with newline or space depending on preference
                        # Newline is usually better for @example
                        joiner = "\n" if target["type"] == MarkerType.EXAMPLE.value else " "
                        target["args"][-1] += f"{joiner}{content}"
                    else:
                        target["args"] = [content]

        # Nest everything under module if found
        if module_node:
            others = [b for b in all_blocks if b is not module_node]
            module_node["children"].extend(others)
            return [module_node]

        return all_blocks
