# OUX/C+ programming language: modules and build environment for Windows

The project is developed in parallel to the original project: [OUX/C+](https://github.com/overcq/oux).

# Information and instructions to the user

## 1. Contact

Manufacturer: overcq

Contact the manufacturer: overcq@int.pl

Source code: https://github.com/overcq/oux-windows

## 2. Vulnerabilities

Report vulnerabilities: https://github.com/overcq/oux-windows/security/advisories or via e‐mail: overcq@int.pl

## 3. Version

OUX/C+ 3 for Windows. Detailed version in git log.

## 4. Purpose

The product is intended for software development in Windows operating system.

## 5. Risk

Developing software using this product requires developer experience. Good programming practices in C+ should be used.

## 6. Component materials

This product requires to be installed:

* “llvm” + “mingw” dla Windows “x86_64” z “msvcrt”, dostępne ze strony https://www.mingw-w64.org/downloads/ (np. https://github.com/mstorsjo/llvm-mingw/releases)
* “cmake” (do zbudowania PCRE2)

This product uses external libraries:

* “libc” and related libraries
* [PCRE2](https://github.com/PCRE2Project/pcre2) (used by “make-oux”)
* “kernel32”, “user32”, “gdi32” and others

## 7. Support

Technical security support at: https://overcq.ct8.pl/oux-c-plus.html and via e‐mail: overcq@int.pl

Issues at: https://github.com/overcq/oux-windows/issues

Product support continues for the latest git release.

## 8. Installation and update

### Installing

Fetching for first use can be done with a command, for example `git clone https://github.com/overcq/oux-windows.git`.

Then download ‟PCRE2” to a separate directory and build with commands:

```shell
cmake -G 'MinGW Makefiles' -B build .
cmake --build build
```

#### Creation of the “make-oux” program

```shell
cd oux-windows\make-oux
mingw32-make
```

#### Creation of “*.c” files from “*.cx” in OUX/C+ project modules and programs

```shell
make-oux
```

#### Creation of modules and available programs

Run “make” in every module directory, for example for module “base”:

```shell
cd module\base
mingw32-make
```

Run “make” in target program directory, for example:

```shell
cd program\ui
mingw32-make
```

#### Launch one of the available programs

In the Command Prompt window, enter the relative path to the program (e.g. “program\ui\ui.exe”) and run it.

### Updating and deleting

The user should make regular updates, e.g. with a command `git pull`.

The product does not install files on the system. To completely remove the product, you must delete the source file directories.
