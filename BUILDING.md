# Building Nyx

## Instructions

Steps to build Qbit from scratch for each operating system.

- [on Windows](#building-nyx-on-windows)
- [on Linux](#building-nyx-on-linux)
- [on macOS](#building-nyx-on-macos)


## Build System

Nyx uses the CMake build system.

Following build instructions use relative paths and assume you to you are in the correct directory in the **cmd.exe**, otherwise you may download the sources to another directory that you may not want to.

Qbit doesn't allow in-source builds, so it is recommended to create a folder - usually build\ - and follow the instructions.

## Building Nyx on Windows

### Prerequisites

- CMake
- Git
- Visual Studio (Tested on VS2022)

It is important to use **cmd.exe** and not powershell or any other shell, the instructions may not work otherwise.

### Download Sources

Clone the repository.
```shell
git clone https://github.com/emomaxd/nyx.git
```

### Compile Nyx

Create build directory
```shell
mkdir build && cd build
```

Configure with CMake
```shell
cmake ..
```

Compile using CMake, Then in the following command just substitute [CONFIG] with one of the following options: Release, Debug, RelWithDebInfo
```shell
cmake --build . --target INSTALL --config [CONFIG]
```

## Building Nyx on Linux

### Prerequisites

- CMake
- Git
- CXX compiler

It is important to use **cmd.exe** and not powershell or any other shell, the instructions may not work otherwise.

### Download Sources

Clone the repository.
```shell
git clone https://github.com/emomaxd/nyx.git
```

### Compile Nyx

Create build directory
```shell
mkdir build && cd build
```

Configure with CMake
```shell
cmake ..
```

Compile using CMake, Then in the following command just substitute [CONFIG] with one of the following options: Release, Debug.
```shell
cmake --build . --target INSTALL --config [CONFIG]
```

---

## Building Nyx on macOS

**macOS is not supported yet.**  
Support for macOS is planned for future releases. If you're interested in helping out or testing, feel free to contribute to the development or check back later for updates.

Alternatively, you may follow the instructions for Linux as a workaround if you want to try building on macOS with some adjustments.

NOTE: macOS support would really take **some** time.
