# Linux AOSP RIL
Linux AOSP RIL implementation

For the original parts in this project Copyright (c) 2019 Daniele Palmas <dnlplm@gmail.com>

The project allows building and using AOSP RIL in a standard Linux environment.

## Directories
- Include: include files from AOSP needed to build the library
- reference-ril: AOSP reference-ril source code, customized for building in a standard Linux environment
- tests: simple test applications

## Usage
- To build type make in project root: the output is a shared library inside directory reference-ril and sample application inside directory tests

## Dependencies
libbsd-dev

## Contributors

Daniele Palmas <dnlplm@gmail.com>

## License

For the original parts in this project GPL V3
