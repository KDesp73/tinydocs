from enum import Enum
from typing import Optional


class MarkerType(Enum):
    NAME = "name"
    DESCRIPTION = "description"
    AUTHOR = "author"
    EXAMPLE = "example"
    LICENSE = "license"


class Argument(Enum):
    REQUIRED = "required"
    OPTIONAL = "optional"
    NONE = "none"


class Marker:
    def __init__(
        self,
        prefix: str,
        name: str,
        type: MarkerType,
        arg: Optional[Argument] = Argument.NONE
    ):
        self.prefix = prefix.strip()
        self.name = name.strip()
        self.type = type
        self.arg = arg

    def template(self):
        template = f"{self.prefix}{self.name}"
        if self.arg != Argument.NONE:
            template = template + " {{arg}}"
        return template


if __name__ == "__main__":
    marker = Marker("@", "name", MarkerType.NAME, Argument.NONE)
    print(marker.template())
