#!/usr/bin/env python3

import json
import argparse
from pathlib import Path
from .ignore import IgnoreChecker
from .parser import Parser
from .markers import Marker, MarkerType, Argument


def parse_arguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("-F", "--files", type=str, help="Provide files (comma separated)")
    parser.add_argument("-D", "--dirs", type=str, help="Provide directories (comma separated)")
    parser.add_argument("-I", "--ignore", type=str, default=".gitignore", help="Paths to ignore files (comma seperated)")
    parser.add_argument("--list-files", action="store_true", help="List the files included in the documentation generation")
    parser.add_argument("--comment-style", type=str, default="#", help="Specify the comment style (#, //, etc)")

    return parser.parse_args()


def main():
    args = parse_arguments()
    ignore_checker = IgnoreChecker([".git/"])
    ignore_checker.load_ignore_files(args.ignore.split(","))

    files = ignore_checker.filter(args.dirs)
    if args.files:
        files.extend(args.files.split(","))

    if args.list_files:
        for f in files:
            print(f)
        return

    markers = [
        Marker(
            name="module",
            arg=Argument.REQUIRED,
            type=MarkerType.MODULE
        ),
        Marker(
            name="class",
            arg=Argument.REQUIRED,
            type=MarkerType.CLASS
        ),
        Marker(
            name="method",
            arg=Argument.REQUIRED,
            type=MarkerType.FUNCTION
        ),
        Marker(
            name="desc",
            arg=Argument.REQUIRED,
            type=MarkerType.DESCRIPTION,
            argc=1
        ),
        Marker(
            name="param",
            arg=Argument.REQUIRED,
            argc=2,
            type=MarkerType.PARAMETER
        ),
        Marker(
            name="constructor",
            arg=Argument.NONE,
            type=MarkerType.ANY
        )
    ]

    docs = []
    for i, file in enumerate(files, start=1):
        print(f"[{i}/{len(files)}] Parsing {file}...")
        parser = Parser(Path(file), prefix="@", comment="#")
        docs.extend(parser.parse(markers))

    json_output = json.dumps(docs, indent=2, ensure_ascii=False)

    with open("tinydocs.json", "w") as file:
        file.write(json_output)


if __name__ == "__main__":
    main()
