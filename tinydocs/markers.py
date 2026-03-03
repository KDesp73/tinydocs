# @module markers
import json
import re
from enum import Enum
from typing import Dict, List, Optional, Any


# @enum Argument
# @desc Defines the argument necessity states
class Argument(Enum):
    REQUIRED = "required"
    NONE = "none"


# @enum MarkerType
# @desc Defines the various types of markers
class MarkerType(Enum):
    MODULE = "module"
    FUNCTION = "function"
    CLASS = "class"
    TYPE = "type"
    DESCRIPTION = "description"
    PARAMETER = "parameter"
    RETURN = "return"
    AUTHOR = "author"
    EXAMPLE = "example"
    LICENSE = "license"
    ANY = "any"


# @class Marker
# @desc Represents a documentation tag configuration, defining how 
# to identify and split arguments for specific markers.
class Marker:
    # @constructor
    # @param name The name of the marker (e.g., 'param', 'method')
    # @param arg Whether the marker requires an argument
    # @param argc The number of expected arguments for splitting
    # @param prefix The symbol prefix, usually '@'
    def __init__(
        self,
        name: str,
        type: Optional[MarkerType] = MarkerType.ANY,
        arg: Optional[Argument] = Argument.REQUIRED,
        argc: Optional[int] = 1,
        prefix: Optional[str] = None,
    ):
        self.prefix = prefix.strip() if prefix else None
        self.name = name.strip()
        self.type = type
        self.arg = arg
        self.argc = argc

    # @method pattern
    # @desc Generates a regex pattern to match the marker in a string
    # @returns str The compiled regex pattern
    def pattern(self):
        if not self.prefix:
            raise ValueError("Prefix not specified")

        pfx = re.escape(self.prefix)
        nm = re.escape(self.name)
        base = f"{pfx}{nm}"
        if self.arg == Argument.NONE:
            return rf"{base}(?=\s|$)"
        return rf"{base}\s+(?P<arg>.+)"

    # @method to_dict
    # @desc Serializes the marker instance into a dictionary
    # @returns Dict[str, Any]
    def to_dict(self):
        return {
            "prefix": self.prefix,
            "name": self.name,
            "type": self.type.value,
            "arg": self.arg.value if self.arg else Argument.NONE.value,
            "argc": self.argc
        }

    # @method from_dict
    # @param d The dictionary containing marker data
    # @returns Marker A new instance of Marker
    @staticmethod
    def from_dict(d: Dict[str, Any]) -> "Marker":
        type_name = next((t for t in MarkerType if t.value == d.get("type")), MarkerType.ANY)
        arg_name = next((a for a in Argument if a.value == d.get("arg")), Argument.REQUIRED)

        return Marker(
            name=d.get("name", ""),
            arg=arg_name,
            type=type_name,
            argc=d.get("argc", 1),
            prefix=d.get("prefix")
        )

    # @method parse
    # @param json_str A JSON string representing a list of markers
    # @returns List[Marker] A list of parsed Marker instances
    @staticmethod
    def parse(json_str: str) -> List["Marker"]:
        try:
            data = json.loads(json_str)
            if not isinstance(data, list):
                raise ValueError("JSON must be a list of marker objects")
            return [Marker.from_dict(item) for item in data]
        except json.JSONDecodeError as e:
            raise ValueError(f"Invalid JSON provided: {e}")
