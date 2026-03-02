# @module parser
from pathlib import Path
from typing import List, Dict, Any
from .markers import Marker, Argument
import re


# @class Parser
# @desc This class is responsible for reading
# and parsing the doc attributes from a file
class Parser:
    # @constructor
    # @param file The file to parse
    # @param comment The comment prefix (#, //, etc). Defaults to `#`
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
        # Track entries that need their names inferred from the next code line
        pending_inference = []

        for line_number, line in enumerate(lines, start=1):
            raw_line = line.strip()
            is_comment = re.match(comment_prefix, raw_line)

            if not is_comment:
                if pending_inference and raw_line:
                    self._infer_names(pending_inference, raw_line)
                    pending_inference = []
                
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
                        argc = getattr(marker, 'argc', 1)
                        arg_str = match.group("arg").strip()
                        entry["args"] = arg_str.split(" ", maxsplit=argc-1)

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
