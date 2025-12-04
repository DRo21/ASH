# ASH — just Another SHel

ASH is a modular, lightweight shell for Linux, built in C.  
It is designed for learning and experimentation, with a clean, modular structure that makes it easy to extend with new commands, builtins, and features.

---

## Features

- Modular architecture with separate libraries for core, input, execution, environment, extensions, and utilities.
- Easily extendable with new commands or plugins.
- Designed for clean and maintainable code using C and CMake.

---

## Quickstart

### Clone

```bash
git clone https://github.com/DRo21/ASH.git
cd ASH
mkdir build
cd build
cmake ..
make -j$(nproc)
./ash