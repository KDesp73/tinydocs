import json
import re
from enum import Enum
from typing import Optional


class MarkerType(Enum):
    MODULE = "module"
    FUNCTION = "function"
    CLASS = "class"
    TYPE = "type"
    DESCRIPTION = "description"
    PARAMETER = "parameter"
    AUTHOR = "author"
    EXAMPLE = "example"
    LICENSE = "license"
    ANY = "any"


class Argument(Enum):
    REQUIRED = "required"
    NONE = "none"


class Marker:
    def __init__(
        self,
        name: str,
        type: MarkerType,
        arg: Optional[Argument] = Argument.REQUIRED,
        argc: Optional[int] = 1,
        prefix: Optional[str] = None,
    ):
        self.prefix = prefix.strip() if prefix else None
        self.name = name.strip()
        self.type = type
        self.arg = arg
        self.argc = argc

    def pattern(self):
        if not self.prefix:
            raise ValueError("Prefix not specified")

        pfx = re.escape(self.prefix)
        nm = re.escape(self.name)
        base = f"{pfx}{nm}"
        if self.arg == Argument.NONE:
            return rf"{base}(?=\s|$)"
        return rf"{base}\s+(?P<arg>.+)"

    def to_dict(self):
        return {
            "prefix": self.prefix,
            "name": self.name,
            "type": self.type.value,
            "arg": self.arg.value if self.arg else Argument.NONE.value,
            "argc": self.argc
        }
