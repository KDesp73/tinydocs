# @module docs

from pathlib import Path
from typing import List, Dict, Any
from .markers import Marker, Argument
import re


# @class Docs
# @desc This class is responsible for reading and parsing the doc attributes
# from a file
class Docs:
    # @constructor
    # @param file The file to parse
    def __init__(self, file: Path, comment: str = "#"):
        self.file = file
        self.comment = comment

    # @method parse
    # @param markers The list of markers to look for while parsing
    def parse(self, markers: List[Marker]) -> List[Dict[str, Any]]:
        text = self.file.read_text()
        lines = text.split("\n")
        results = []

        comment_prefix = rf'^{re.escape(self.comment)}'
        marker_prefixes = list(set(m.prefix for m in markers))
        prefix_pattern = rf"^\s*[{re.escape(''.join(marker_prefixes))}]"

        current_entry = None

        for line_number, line in enumerate(lines, start=1):
            raw_line = line.strip()
            
            is_comment = re.match(comment_prefix, raw_line)
            
            if not is_comment:
                current_entry = None
                continue

            content = re.sub(rf'^{re.escape(self.comment)}\s*', '', raw_line).strip()
            
            found_new_marker = False
            for marker in markers:
                pattern = marker.pattern()
                match = re.search(pattern, content)

                if match:
                    found_new_marker = True
                    entry = {
                        "marker": marker.name,
                        "type": marker.type.value,
                        "raw": [line],
                        "file": str(self.file),
                        "line": line_number,
                        "args": []
                    }

                    if marker.arg != Argument.NONE:
                        try:
                            argc = getattr(marker, 'argc', 1)
                            arg_str = match.group("arg").strip()
                            entry["args"] = arg_str.split(" ", maxsplit=argc-1)
                        except (IndexError, AttributeError):
                            entry["args"] = []

                    results.append(entry)
                    current_entry = entry
                    break

            if not found_new_marker and current_entry:
                if re.match(prefix_pattern, content):
                    current_entry = None
                else:
                    if current_entry["args"]:
                        current_entry["args"][-1] += f" {content}"
                    else:
                        current_entry["args"] = [content]

                    current_entry["raw"].append(line)

        for res in results:
            res["raw"] = "\n".join(res["raw"])

        return results
