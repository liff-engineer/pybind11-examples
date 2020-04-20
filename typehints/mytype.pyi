import enum


class Kind(enum.Enum):
    Dog = 0
    Cat = 1


class Pet:
    name: str
    type: Kind

    def __init__(self, name: str, type: Kind):
        self.name = name
        self.type = type
