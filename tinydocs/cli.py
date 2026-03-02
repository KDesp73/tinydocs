#!/usr/bin/env python3

import argparse
from pathlib import Path
from .ignore import IgnoreChecker

def parse_arguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("-F", "--files", type=str, help="Provide files (comma separated)")
    parser.add_argument("-D", "--dirs", type=str, default=".", help="Provide directories (comma separated)")
    parser.add_argument("-I", "--ignore", type=str, default=".gitignore", help="Paths to ignore files (comma seperated)")

    return parser.parse_args()

def main():
    args = parse_arguments()
    ignore_checker = IgnoreChecker([".git/"])
    ignore_checker.load_ignore_files(args.ignore.split(","))

    all_files = []
    
    # Process explicit files
    if args.files:
        for f in args.files.split(","):
            f_path = f.strip()
            if not ignore_checker.is_ignored(f_path):
                all_files.append(f_path)

    # Process directories
    if args.dirs:
        dirs = [d.strip() for d in args.dirs.split(",")]
        for d_path in dirs:
            path_obj = Path(d_path)
            if path_obj.is_dir():
                for item in path_obj.rglob("*"):
                    # Check if file AND ensure no part of its path is ignored
                    if item.is_file() and not ignore_checker.is_ignored(item):
                        all_files.append(str(item))

    # Output results
    for f in sorted(set(all_files)):
        print(f)

if __name__ == "__main__":
    main()
