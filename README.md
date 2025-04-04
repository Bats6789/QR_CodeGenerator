# QR_CodeGenerator
A simple QR code generator written in C.

## Dependencies

This project depends on the following dependencies:

* libpng

## Generate

### Using vcpkg

Assuming you set up your **CMakeUserPresets.json** with the profile `default`,
the following command can be used to generate the build files:

`cmake -B build --preset=default`

For more information on setting up **CMakeUserPresets.json** for vcpkg,
see this [tutorial](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-powershell#4---build-and-run-the-project).

### Without vcpkg

Assuming you have the dependencies installed, build files can be generated using:

`cmake -B build`

## Build

After you generate your build files, the project can be built with:

`cmake --build build`

This should generate all the libraries, tests, and binaries.

The binary `QRCode` will be placed in the **bin** folder.

## Testing

Some basic tests are included and compatible with CTest. In order to run the test,
first build the project and then run the following command:

`ctest --test-dir build`

## Example

This is an example of a QR code generated with the command `bin\QRCode DEMO12345`

![example1.png](sample/example1.png) 
