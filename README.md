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

OUX/C+ 2 for Windows. Detailed version in git log.

## 4. Purpose

The product is intended for software development in Windows operating system.

## 5. Risk

Developing software using this product requires developer experience. Good programming practices in C+ should be used.

## 6. Component materials

Compiled by:

Orwell Dev-C++ with 32‐bit “clang” (for Windows XP)

This product uses external libraries:

* “libc” and related libraries
* [PCRE2](https://github.com/PCRE2Project/pcre2) (used by “make-oux”)
* “kernel32”, “user32”, “gdi32”

## 7. EU declaration

No the EU declaration of conformity.

## 8. Support

Technical security support at: https://overcq.ct8.pl/oux-c-plus.html and via e‐mail: overcq@int.pl

Issues at: https://github.com/overcq/oux-windows/issues

Product support continues for the latest git release.

## 9. Installation and update

### Installing

The installation must be performed in a Linux environment and then transfer the files to Windows.

Fetching for first use can be done with a command, for example `git clone git@github.com:overcq/oux-windows.git`.

#### On Linux: preparing ‟PCRE2” source files for “make-oux”

Then download ‟PCRE2” to a separate directory, execute “./autogen.sh” in it and copy the “*.h” and “*.c” files from the “src” directory to the “pcre2” directory. In the "config.h" file, add the line:
```
#define PCRE2_CODE_UNIT_WIDTH 8
```
Then compile the "pcre2_dftables.c" file into the program and create the source file "pcre2_default_tables.c" with the command:
```
clang -DHAVE_CONFIG_H pcre2_dftables.c && ./a.out pcre2_default_tables.c && rm a.out
```

You must share the directory of the projectʼs source files to Windows (e.g. as a network resource and copy, or upload).

#### On Windows: creation of the “make-oux” program

You need to create a new project of the ‛static library’ type (named “pcre2”) in the “pcre2” directory and add the “*.c” files. In the project options, add `-D HAVE_CONFIG_H` in the C compiler parameters. And build the project.

You need to create a new ‛console’ project (named “make-oux”) in the “make-oux” directory and add the “main.c” file. In the project options, add `-fwrapv` in the C compiler parameters and “../pcre2/pcre2.a” in the linker parameters.

#### Creation of “*.c” files from “*.cx” in OUX/C+ project modules and programs

Open a Command Prompt window and go to the "make-oux" directory and run "make-oux.exe" there.

#### Creation of modules and available programs

You should create new ‛DLL’ projects (named “oux-base” and “oux-window”) in the subdirectories of the “module” directory, respectively, and add `-include E_cplus_S_to_libs.h -fwrapv` in the project options to the C compiler parameters, and for the “oux-window” project, add `-loux-base -lgdi32` in the linker parameters. And build these projects one by one.

You should create new ‛console’ projects in the subdirectories of the “program” directory and add `-include E_cplus_S_to_libs.h -fwrapv` in the C compiler parameters and in the linker parameters add the module libraries used by the program, e.g. `-loux-base -loux-window`. And build these projects one by one.

#### Launch one of the available programs

In the Command Prompt window, enter the relative path to the program (e.g. “..\program\gui\gui.exe”) and run it.

### Updating and deleting

The user should make regular updates, e.g. with a command `git pull`.

The product does not install files on the system. To completely remove the product, you must delete the source file directories on Windows and Linux respectively.
