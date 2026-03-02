#!/usr/bin/env python3

import json
import argparse
from pathlib import Path
from .ignore import IgnoreChecker
from .parser import Parser
from .markers import Marker
from .generator import SiteGenerator
from datetime import datetime


def parse_arguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("-F", "--files", type=str, help="Provide files (comma separated)")
    parser.add_argument("-D", "--dirs", type=str, help="Provide directories (comma separated)")
    parser.add_argument("-I", "--ignore", type=str, help="Paths to ignore files (comma seperated)")
    parser.add_argument("--list-files", action="store_true", help="List the files included in the documentation generation")
    parser.add_argument("--comment-style", type=str, default="#", help="Specify the comment style (#, //, etc)")
    parser.add_argument("--markers", type=str, default="tiny.markers.json", help="Provide the marker definition json file")
    parser.add_argument("-o", "--output", type=str, default="docs", help="Specify the output directory")
    parser.add_argument("--generate", action="store_true", help="Generate a static documentation site")
    parser.add_argument("--name", type=str, help="Specify the name of the project")

    return parser.parse_args()


def main():
    args = parse_arguments()

    ignore_files = args.ignore.split(",") if args.ignore else []

    ignore_checker = IgnoreChecker([".git/"])
    ignore_checker.load_ignore_files(ignore_files)

    files = ignore_checker.filter(args.dirs.split(","))
    if args.files:
        files.extend(args.files.split(","))

    if args.list_files:
        for f in files:
            print(f)
        return

    with open(args.markers, "r") as file:
        markers = Marker.parse(file.read())

    docs = []
    for i, file in enumerate(files, start=1):
        print(f"[{i}/{len(files)}] Parsing {file}...")
        parser = Parser(Path(file), prefix="@", comment="#")
        docs.extend([
            {
                "file": file,
                "docs": doc
            } 
            for doc in parser.parse(markers)
        ])


    output = {
        "name": args.name or "TinyDocs", 
        "timestamp": str(datetime.now()).split(".")[0],
        "docs": docs
    }

    json_output = json.dumps(output, indent=4, ensure_ascii=False)

    output_file = f"{args.output}/tiny.docs.json"
    with open(output_file, "w") as file:
        file.write(json_output)

    if args.generate:
        gen = SiteGenerator(json_path=output_file, output_dir=args.output)
        gen.generate()


if __name__ == "__main__":
    main()
