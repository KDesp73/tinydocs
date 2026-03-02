# @module ignore
import os
from pathlib import Path
from fnmatch import fnmatch
from typing import List, Optional


# @class IgnoreChecker
# @desc This class provides utility methods to check if files or directories 
# should be ignored based on glob patterns, similar to .gitignore.
class IgnoreChecker:
    # @constructor
    # @param patterns A list of initial glob patterns to use for ignoring.
    def __init__(self, patterns=None):
        self.patterns = []
        if patterns:
            for p in patterns:
                self.add_pattern(p)

    # @method add_pattern
    # @desc Parses and adds a single ignore pattern to the internal list, 
    # handling negations and directory-only constraints.
    # @param pattern The glob string to add.
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

    # @method load_ignore_files
    # @desc Reads ignore patterns from one or more physical files 
    # (e.g., '.gitignore' or '.eslintignore').
    # @param file_paths A list or comma-separated string of file paths to load.
    def load_ignore_files(self, file_paths):
        for file_path in file_paths:
            if os.path.exists(file_path):
                with open(file_path, 'r', encoding='utf-8') as f:
                    for line in f:
                        self.add_pattern(line)

    # @method is_ignored
    # @desc Evaluates if a given path matches any ignore rules, checking 
    # the full path, the basename, and all parent directories.
    # @param path The file or directory path to check.
    # @returns bool True if the path should be ignored.
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

    # @method filter
    # @desc Recursively scans directories and returns a list of files 
    # that are not excluded by the ignore patterns.
    # @param dirs A comma-separated string of directory paths to scan.
    # @returns List[str] A sorted list of non-ignored file paths.
    def filter(self, dirs: List[str]) -> List[str]:
        files = []
        
        dirs = [d.strip() for d in dirs]
        for d_path in dirs:
            path_obj = Path(d_path)
            if path_obj.is_dir():
                for item in path_obj.rglob("*"):
                    if item.is_file() and not self.is_ignored(item):
                        files.append(str(item))

        return sorted(set(files))
