# @module parser
from pathlib import Path
from typing import List, Dict, Any, Optional
from .markers import Marker, Argument
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
        for marker in markers:
            if not marker.prefix:
                if self.prefix:
                    marker.prefix = self.prefix
                else:
                    raise ValueError("You should specify a global prefix or assing one to each marker")

        text = self.file.read_text()
        lines = text.split("\n")
        
        all_blocks = []
        current_block = None
        module_node = None

        for line_number, line in enumerate(lines, start=1):
            raw_line = line.strip()
            is_comment = re.match(rf'^{re.escape(self.comment)}', raw_line)

            if not is_comment:
                current_block = None
                continue

            content = re.sub(rf'^{re.escape(self.comment)}\s*', '', raw_line).strip()
            
            found_new_marker = False
            for marker in markers:
                match = re.search(marker.pattern(), content)
                if match:
                    found_new_marker = True

                    args = []
                    if marker.arg != Argument.NONE:
                        raw_args = match.group("arg").strip()
                        argc = getattr(marker, 'argc', 1)
                        args = raw_args.split(" ", maxsplit=argc - 1)

                    entry = {
                        "marker": marker.name,
                        "args": args,
                        "line": line_number,
                        "children": []
                    }

                    if marker.name in ["param", "desc", "arg", "returns"]:
                        if current_block:
                            current_block["children"].append(entry)
                        else:
                            all_blocks.append(entry) # Fallback if no parent
                    else:
                        if marker.name == "module":
                            module_node = entry
                        
                        all_blocks.append(entry)
                        current_block = entry
                    break

            if not found_new_marker and current_block:
                if current_block["args"]:
                    current_block["args"][-1] += f" {content}"
                else:
                    current_block["args"] = [content]

        if module_node:
            others = [b for b in all_blocks if b is not module_node]
            module_node["children"].extend(others)
            return [module_node]

        return all_blocks
