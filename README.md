# Tigraf-Core 0.1.0 ![Drawgon-logo](https://user-images.githubusercontent.com/87949029/220889714-97fc5c4b-8abe-46ae-8daa-07499247a352.png)

Tigraf-Core is a lightweight and cross-platform library that provides a simple and intuitive interface for handling windows, events, input, graphics API, and more. It is designed to be easily expandable and customizable, allowing developers to quickly build applications with minimal effort.

**Note**: For now, Tigraf-Core has only been tested on Windows using CMake and Visual Studio 2022, and it may not work properly on other platforms or with other IDEs.

## License
Tigraf-Core is released under the MIT License. This means that you are free to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the software for both commercial and non-commercial purposes. However, any distribution of the software must include a copy of the MIT License, and any modifications made to the software must also be released under the same MIT License terms.

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
2. Clone the repository recursively by running the following command: "git clone --recursive https://github.com/P3RK4N/Tigraf-Core"
3. In project folder, navigate to scripts and run project generation command. Alternatively, you can run with your own command for specific tool

**NOTE**: It's preferred that you have latest vulkan installed or DirectX if you are on windows

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
