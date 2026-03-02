import os
from pathlib import Path
from fnmatch import fnmatch
from typing import List


class IgnoreChecker:
    def __init__(self, patterns=None):
        self.patterns = []
        if patterns:
            for p in patterns:
                self.add_pattern(p)

    def add_pattern(self, pattern):
        pattern = pattern.strip()
        if not pattern or pattern.startswith('#'):
            return
        
        negate = pattern.startswith('!')
        if negate:
            pattern = pattern[1:]
        
        is_dir_only = pattern.endswith('/')
        if is_dir_only:
            pattern = pattern[:-1]

        self.patterns.append({
            'pattern': pattern,
            'negate': negate,
            'is_dir_only': is_dir_only
        })

    def load_ignore_files(self, file_paths):
        if isinstance(file_paths, str):
            file_paths = [f.strip() for f in file_paths.split(",") if f.strip()]

        for file_path in file_paths:
            if os.path.exists(file_path):
                print(f"Loading ignore rules from {file_path}...")
                with open(file_path, 'r', encoding='utf-8') as f:
                    for line in f:
                        self.add_pattern(line)

    def is_ignored(self, path):
        """Returns True if the path or any of its parent directories match the patterns."""
        ignored = False
        path_obj = Path(path)
        # Normalize to forward slashes for cross-platform pattern matching
        path_str = str(path_obj).replace(os.sep, '/')
        
        # Breakdown the path into components (e.g., '.venv/bin/python' -> ('.venv', 'bin', 'python'))
        parts = path_obj.parts

        for rule in self.patterns:
            pattern = rule['pattern']
            match = False

            # 1. Check if the full path matches
            if fnmatch(path_str, pattern):
                match = True
            
            # 2. Check if the basename matches (e.g., '*.py')
            elif fnmatch(os.path.basename(path_str), pattern):
                match = True
            
            # 3. Check if any parent directory matches the pattern
            # This handles ignoring the entire content of .git or .venv
            else:
                current_parent = ""
                for part in parts:
                    current_parent = f"{current_parent}/{part}" if current_parent else part
                    if fnmatch(current_parent, pattern):
                        match = True
                        break

            if match:
                ignored = not rule['negate']
        
        return ignored

    def filter(files: List[str])
