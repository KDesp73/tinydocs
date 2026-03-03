#!/usr/bin/env python3

import json
import argparse
import sys
import logging
from pathlib import Path
from datetime import datetime

from .ignore import IgnoreChecker
from .parser import Parser
from .markers import Marker, MarkerType
from .generator import SiteGenerator

logging.basicConfig(level=logging.INFO, format="%(levelname)s: %(message)s")
logger = logging.getLogger("tinydocs")

def parse_arguments():
    parser = argparse.ArgumentParser(description="TinyDocs: Minimalist documentation generator.")
    parser.add_argument("-F", "--files", type=str, help="Comma separated files")
    parser.add_argument("-D", "--dirs", type=str, help="Comma separated directories")
    parser.add_argument("-I", "--ignore", type=str, help="Comma separated ignore files")
    parser.add_argument("--list-files", action="store_true", help="List included files and exit")
    parser.add_argument("--list-marker-types", action="store_true", help="List all available marker types and exit")
    parser.add_argument("--comment-style", type=str, default="#", help="Comment style (default: #)")
    parser.add_argument("--markers", type=str, default="tiny.markers.json", help="Markers definition JSON")
    parser.add_argument("-o", "--output", type=str, default="docs", help="Output directory")
    parser.add_argument("--generate", action="store_true", help="Generate static HTML site")
    parser.add_argument("--name", type=str, help="Project name")

    return parser.parse_args()

def main():
    args = parse_arguments()

    if args.list_marker_types:
        [print(type.value) for type in MarkerType]
        return
    
    # 1. Initialize Ignore Checker
    ignore_files = args.ignore.split(",") if args.ignore else []
    ignore_checker = IgnoreChecker([".git/", "__pycache__/", ".venv/", "node_modules/"])
    try:
        ignore_checker.load_ignore_files(ignore_files)
    except Exception as e:
        logger.warning(f"Could not load some ignore files: {e}")

    # 2. Collect and Validate Files
    files = []
    if args.dirs:
        dir_paths = [d.strip() for d in args.dirs.split(",") if d.strip()]
        files.extend(ignore_checker.filter(dir_paths))
    
    if args.files:
        extra_files = [f.strip() for f in args.files.split(",") if f.strip()]
        files.extend(extra_files)

    # Remove duplicates and filter non-existent files
    files = list(dict.fromkeys(files)) 
    files = [f for f in files if Path(f).exists()]

    if not files:
        logger.error("No valid files found to document. Check your --dirs or --files arguments.")
        sys.exit(1)

    if args.list_files:
        for f in files:
            print(f)
        return

    # 3. Load Markers
    marker_path = Path(args.markers)
    if not marker_path.exists():
        logger.error(f"Marker file not found: {args.markers}")
        sys.exit(1)

    try:
        with open(marker_path, "r", encoding="utf-8") as f:
            markers = Marker.parse(f.read())
    except json.JSONDecodeError:
        logger.error(f"Malformed JSON in marker file: {args.markers}")
        sys.exit(1)
    except Exception as e:
        logger.error(f"Failed to parse markers: {e}")
        sys.exit(1)

    # 4. Parse Documentation
    docs_entries = []
    for i, file_path in enumerate(files, start=1):
        try:
            logger.info(f"[{i}/{len(files)}] Parsing {file_path}...")
            parser = Parser(Path(file_path), prefix="@", comment=args.comment_style)
            parsed_data = parser.parse(markers)
            
            for doc in parsed_data:
                docs_entries.append({
                    "file": str(file_path),
                    "docs": doc
                })
        except Exception as e:
            logger.error(f"Failed to parse {file_path}: {e}")

    # 5. Prepare Output
    output_payload = {
        "name": args.name or Path.cwd().name, 
        "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
        "docs": docs_entries
    }

    # 6. Write JSON Output
    out_dir = Path(args.output)
    try:
        out_dir.mkdir(parents=True, exist_ok=True)
        json_path = out_dir / "tiny.docs.json"
        
        with open(json_path, "w", encoding="utf-8") as f:
            json.dump(output_payload, f, indent=4, ensure_ascii=False)
        
        logger.info(f"Documentation data saved to {json_path}")
    except Exception as e:
        logger.error(f"Failed to write output JSON: {e}")
        sys.exit(1)

    # 7. Site Generation
    if args.generate:
        try:
            gen = SiteGenerator(json_path=str(json_path), output_dir=str(out_dir))
            gen.generate()
            logger.info(f"Static site generated in {out_dir}/")
        except Exception as e:
            logger.error(f"Site generation failed: {e}")
            sys.exit(1)


if __name__ == "__main__":
    main()
