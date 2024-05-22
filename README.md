# F-IKOS

F-IKOS is a runtime error analyzer for Fortran programs based on abstract interpretation. Its frontend parser is sourced from [Flang](https://github.com/flang-compiler/flang). Flang is a compiler for Fortran programs that can convert `.f`, `.f90`, `.f95`, and `.f03` files into `.bc` or `.ll` files. The backend analyzer is based on [IKOS](https://github.com/NASA-SW-VnV/ikos), which can analyze `.c`, `.cpp`, or `.bc` files to check for runtime errors. However, [IKOS cannot check numerical properties for floating-point programs](https://github.com/NASA-SW-VnV/ikos/issues/210), and since floating-point types are very common in Fortran programs, we extended IKOS. The extended IKOS supports runtime error checking for programs containing both integer and floating-point types. Notably, the extended IKOS supports sound analysis of floating points, considering rounding errors in the program, ensuring that the analysis results are sound. This repository contains the extended IKOS, and to analyze Fortran programs, we also need its frontend, Flang. The installation and usage instructions are provided below.

## Install Flang

We use the legacy branch from [flang-compiler/flang](https://github.com/flang-compiler/flang) because it and IKOS both support the LLVM-14 environment. Detailed installation instructions for Flang can be found here: [How to build Flang](https://github.com/zoush99/f-ikos/wiki/How-to-build-Flang).

If you only need to use the extended IKOS to analyze programs, you do not need to install the Fortran frontend, so you can skip this step.

## Install Extended IKOS

### Dependencies

To build and run the analyzer, you will need the following dependencies:

* A C++ compiler that supports C++14 (gcc >= 4.9.2 or clang >= 3.4)
* CMake >= 3.4.3
* GMP >= 4.3.1
* Boost >= 1.55
* Python >= 3.3
* SQLite >= 3.6.20
* TBB >= 2
* LLVM and Clang 14.0.x
* APRON >= 0.9.10

Most of them can be installed using your package manager.

Note: If you build LLVM from source, you need to enable run-time type information (RTTI).

## Build and Install

Now that you have all the dependencies on your system, you can build and install IKOS.

As you open the IKOS distribution, you shall see the following directory structure:

```
.
├── CMakeLists.txt
├── LICENSE.pdf
├── README.md
├── RELEASE_NOTES.md
├── TROUBLESHOOTING.md
├── analyzer
├── ar
├── cmake
├── core
├── doc
├── frontend
├── script
└── test
```

IKOS uses the CMake build system. You will need to specify an installation directory that will contain all the binaries, libraries, and headers after installation. If you do not specify this directory, CMake will install everything under `install` in the root directory of the distribution. In the following steps, we will install IKOS under `/path/to/ikos-install-directory`.

Here are the steps to build and install IKOS:

```
$ mkdir build
$ cd build
$ cmake -DCMAKE_INSTALL_PREFIX=/path/to/ikos-install-directory ..
$ make
$ make install
```

Then, add IKOS to your PATH (consider adding this to your .bashrc):

```
$ PATH="/path/to/ikos-install-directory/bin:$PATH"
```

### Tests

To build and run the tests, simply type:

```
$ make check
```

## Examples

Suppose we want to analyze the following Fortran program in a file called *cap.f90*:

```fortran
real function cap(x)
implicit none
real, intent(in) :: x
real :: y
y = x
! Cap the value of y based on certain conditions
if (10.0 > y) then
  y = 10.0
else if (15.0 < y) then
  y = 20.0
else
  y = y / (y - x)
end if
cap = y
end function cap

program main
implicit none
real,external :: cap
real :: x
x = 13.3
! Cap the value of x by calling the cap function
a = cap(x)
end program main
```

To analyze this program with F-IKOS, simply run:

```sh
flang -emit-llvm -S -c cap.f90 -o cap.ll
ikos cap.ll --entry-point=MAIN_ -a='*,-sound,-upa' -d=apron-polka-polyhedra
```

You shall see the following output. F-IKOS reports an occurrence of divide-by-zero at line 12.

```
$ flang -emit-llvm -S -c cap.f90 -o cap.ll
$ ikos cap.ll --entry-point=MAIN_ -a='*,-sound,-upa' -d=apron-polka-polyhedra
[*] Running ikos preprocessor
[*] Running ikos analyzer
[*] Translating LLVM bitcode to AR
[*] Running liveness analysis
[*] Running widening hint analysis
[*] Running interprocedural value analysis
[*] Analyzing entry point 'MAIN_'
[*] Checking properties for entry point 'MAIN_'

# Time stats:
ikos-analyzer: 0.013 sec
ikos-pp      : 0.011 sec

# Summary:
Total number of checks                : 18
Total number of unreachable checks    : 0
Total number of safe checks           : 17
Total number of definite unsafe checks: 1
Total number of warnings              : 0

The program is definitely UNSAFE

# Results
cap.f90: In function 'cap_':
cap.f90:12:1: error: division by zero
  y = y / (y - x)
^
```

## Others

For more details on the use of IKOS, please refer to [IKOS GitHub Repository](https://github.com/NASA-SW-VnV/ikos).