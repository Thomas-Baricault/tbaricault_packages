# tbaricault/packages

[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
![C++23](https://img.shields.io/badge/C%2B%2B-23-blue)
![CMake](https://img.shields.io/badge/CMake-3.20%2B-blue)

## Description

This is a C++23 library providing classes for packages managment tools.

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Requirements](#requirements)
- [Usage](#usage)
    - [Download and install](#download-and-install)
    - [Uninstall](#uninstall)
    - [CMake](#cmake)
    - [Include](#include)
    - [Environment](#environment)
- [Documentation](#documentation)
- [Examples](#examples)
    - [Version demonstration](#version-demonstration)
- [License](#license)

## Features

- Version class

## Requirements

- C++23 or later
- CMake 3.20 or later
- [tbaricault/str](https://github.com/Thomas-Baricault/tbaricault_str)
- [tbaricault/uniconvert](https://github.com/Thomas-Baricault/tbaricault_uniconvert)

## Usage

### Download and install

```bash
git clone https://github.com/Thomas-Baricault/tbaricault_packages_.git
cd tbaricault_packages
make install
```

### Uninstall

```bash
make uninstall
```

### CMake

Add the library to your project:

```cmake
find_package(tbaricault_packages REQUIRED)

target_link_libraries(
    my_target
    PRIVATE
        tbaricault::packages
)
```

### Include

```cpp
#include <tbaricault/packages.hpp>
```

### Environment

If you have a custom C++ installation, you can edit the `ENV` variable in the `Makefile` to specify your environment path.

Example on Windows with MSYS2/MinGW64:

```makefile
ENV = C:/msys64/mingw64
```

## Documentation

Read the complete documentation at [https://docs.thomas-baricault.fr/packages](https://docs.thomas-baricault.fr/packages).

## Examples

### Version demonstration

```cpp
#include <iostream>
#include <tbaricault/packages.hpp>


int main()
{
    tbaricault::packages::Version a(1, 73);
    tbaricault::packages::Version b(1, 42);

    std::cout << (a < b) << std::endl;
    std::cout << (a > b) << std::endl;

    return (0);
}
```

Output:

```text
0
1
```

## Roadmap

- Package class
- Topological sort for packages

## License

This project is licensed under the MIT License.

See [LICENSE](LICENSE) for details.
