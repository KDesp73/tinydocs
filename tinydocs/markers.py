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
        prefix: str,
        name: str,
        type: MarkerType,
        arg: Optional[Argument] = Argument.REQUIRED,
        argc: Optional[int] = 1
    ):
        self.prefix = prefix.strip()
        self.name = name.strip()
        self.type = type
        self.arg = arg
        self.argc = argc

    def pattern(self):
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
