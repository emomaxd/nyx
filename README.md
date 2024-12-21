# Nyx [![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://github.com/emomaxd/nyx/blob/master/LICENSE)

![Nyx](external/nyx-logo.png?raw=true "nyx")

## Overview

This repository includes various 3D physics simulations both using CPU and GPU with CUDA.

Since this repo has some tester visualizations with raylib, to see the result visually check [Physim](https://github.com/emomaxd/Physim).

## Simulations

- **Rope**: Simulates rope using verlet integration on the CPU.
- **Cloth**: Models cloth behavior on the GPU.
- **Double Pendulum**: Simulates two swinging pendulums on the CPU.
- **N-body**: Computes interactions in a system of particles on the GPU.
- **Fluid**: Simulates fluid dynamics on the GPU.

These simulations bundled into one program to easily jump from one to another.

## Dependencies

- [raylib](https://github.com/raysan5/raylib): you need to install raylib from source.
- [glm](https://github.com/g-truc/glm): The repo contains glm as submodule.

## Cloning & Building

```bash
git clone --recursive https://github.com/emomaxd/Nyx.git
```

```bash
mkdir build && cd build
cmake ..
make
./demo/demo
```