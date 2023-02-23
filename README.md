# Tigraf-Core
Tigraf-Core is a lightweight and cross-platform library that provides a simple and intuitive interface for handling windows, events, input, graphics API, and more. It is designed to be easily expandable and customizable, allowing developers to quickly build applications with minimal effort.

**Note**: Tigraf-Core has only been tested on Windows using CMake, and it may not work properly on other platforms or with other IDEs.

## License
Tigraf-Core is released under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International Public License. This means that you are free to use, copy, distribute, and transmit the software for non-commercial purposes only, and you must give appropriate credit to the author(s).

## Dependencies
Tigraf-Core relies on the following third-party libraries:

- **GLM**: A header-only C++ mathematics library for graphics software. It provides classes and functions designed and implemented with the same naming conventions and functionalities than OpenGL/GLSL.
- **STB**: A collection of single-file libraries for C/C++ that provide various useful utilities, including image loading and writing.
- **SDL**: A cross-platform development library designed to provide low-level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D.
- **GLFW**: A lightweight and cross-platform library for creating windows and handling input and events.
- **spdlog**: A fast C++ logging library with a simple interface and performance-oriented design.
- **Glad**: A multi-language GL/GLES/EGL/GLX/WGL loader-generator based on the official specs.

## Building Tigraf-Core
To build Tigraf-Core, follow these steps:

1. Install CMake on your system.
2. Clone the repository recursively by running the following command: git clone --recursive https://github.com/P3RK4N/Tigraf-Core.git
3. In project folder, navigate to scripts and run project generation command. Alternatively, you can run with your own command for specific tool

## Features
Tigraf-Core provides the following features:

- Window creation and management
- Event handling
- Input handling (keyboard and mouse)
- Cross-platform support (Windows, macOS, Linux)
- Support for multiple graphics APIs (OpenGL, DirectX, Vulkan, Metal)

## Contributing
Contributions are always welcome! If you would like to contribute to Tigraf-Core, please follow these guidelines:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Write your code and tests.
4. Submit a pull request.
