# Interface Definition and Language Mapping

# Introduction
A part of the IDL (Interface Definition Language) standard specification is implemented in Morse, enabling the description of interfaces between various software components.

Morse supports certain elements of the IDL 4.2 standard, available at https://www.omg.org/spec/IDL/4.2. The aim of this article is to clarify the various sections supported by Morse. Whatever is not listed below is probably not supported at the moment.

## Exemple
```
#include "GeoData/Position.idl"

module Simulation {
  module World {
    enum WeatherState
    {
        RAIN, 
        SNOW,
        SUN
    };
    struct Terrain {
      string Name;
      GeoData::Position Center; 
      sequence<uint8> HeightData;
    };
  };
};
```


# Lexical Convention
## Identifier
An identifier must start with an is an ASCII alphabetic characteran followed by any number of ASCII alphabetic, digit and underscore (_) characters.

## Comments
Line comments (//) are supported.
```
// Cool another tool
```

## Literals
All of the following literals are supported:
    Integer
    Character
    String
    Floating-point
    Fixed-point


# Building Blocks

## Import 
Imports must be used to reference other .idl file which declare data types used in this .idl file.

```
#include "Module1/ModuleN/HumanData.idl"
```

## Modules
Each module must contain at least one definition and they can be nested.
```
module Module1 {
  module ModuleN {

  };
};
```

## Structures
A structure must contain at least one member.
```
struct HumanData {
    string Name;
    bool IsHappy;
    double Age;
};
```

## Enumeration
An enumeration contains an ordered list of enumerators.
```
enum HumanState
{
    WORKING,
    SINGING,
    RUNNING
};
```

# Types
## Basic
| Type         | Definition                                             |
|--------------|--------------------------------------------------------|
| `float`      | A single-precision floating-point format.              |
| `double`     | A double-precision floating-point format.              |
| `char`       | A character type that typically represents ASCII characters. |
| `wchar_t`    | A wide character type for representing Unicode characters. |
| `bool`       | A boolean type representing true or false.             |
| `octet`      | An 8-bit unsigned integer.                             |
| `int8_t`     | A signed 8-bit integer.                                |
| `uint8_t`    | An unsigned 8-bit integer.                             |
| `int16_t`    | A signed 16-bit integer.                               |
| `uint16_t`   | An unsigned 16-bit integer.                            |
| `int32_t`    | A signed 32-bit integer.                               |
| `uint32_t`   | An unsigned 32-bit integer.                            |
| `int64_t`    | A signed 64-bit integer.                               |
| `uint64_t`   | An unsigned 64-bit integer.                            |

## String
| Type   | Description                           |
|--------|---------------------------------------|
| string | Sequence of characters except null    |

## Lists
| Type   | Description                           |
|--------|---------------------------------------|
| sequence<struct>| Sequence of struct (the sequence is unbounded and no maximum size is specified)|
| sequence<basic_type>| Sequence of basic type (the sequence is unbounded and no maximum size is specified)|


## Constructed Types
| Type               | Description                                       |
|--------------------|---------------------------------------------------|
| struct_identifier  | Structure defined in the same file or in another file (with the right include)|


# Annotations

The syntax for arbitrary annotations is not supported yet. 