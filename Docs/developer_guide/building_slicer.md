# Building Slicer

Building Slicer is the process of obtaining a copy of the source code of the
project and use tools, such as compilers, project generators and build systems,
to create binary libraries and executables&mdash;Slicer documentation can be
also generated in this process. Users interested on using the Slicer application
and its ecosystem of extensions will not typically be interested on building 3D
Slicer. On the other hand, users interested on developing Slicer
[modules](../user_guide/modules/index.html) or contributing to the development of
Slicer, need to have the source code of Slicer and the corresponding generated
binaries.

Slicer is based on a *superbuild* architecture. This means that the in the
building process, some of the dependencies of Slicer will be downloaded in local
directories (within the Slicer build directory) and will be configured, built
and installed locally, before Slicer itself is built. This helps reducing the
complexity for developers while keeping 

The instructions provided in this document have been tested for Slicer in its
**latest version** and generally will work on versions that are not too far from it
in the development process.

## GNU/Linux systems

The instructions to build Slicer for GNU/Linux systems are slightly different
depending on the linux distribution and the specific configuration of the
system. In the following sections you can find instructions that will work for
some of the most common linux distributions in their standard configuration. If
you are using a different distribution you can use these instructions as
guidelines to adapt the process to your system. You can also ask questions
related to the building process in the [Slicer forum](https://discourse.slicer.org).

### Pre-requisites

First, you need to install the tools that will be used for fetching the source
code of slicer, generating the project files and build the project.

- Git and Subversion for fetching the code and version control.
- GNU Compiler Collection (GCC) for code compilation.
- CMake for configuration/generation of the project.
  - (Optional) CMake curses gui to configure the project from the command line.
  - (Optional) CMake Qt gui to configure the project through a GUI.
- GNU Make
- GNU Patch
  
In addition, Slicer requires a set of support libraries that are not includes as
part of the *superbuild*:

- Qt5 with the following components:
  - Multimedia
  - UiTools
  - XMLPatterns
  - SVG
  - WebEngine
  - Script
  - X11Extras
  - Private
- libXt
  
#### Debian Stable (Buster)

Install the development tools and the support libraries:
```
sudo apt install git subversion build-essential cmake cmake-curses-gui cmake-qt-gui qt5-default qt5multimedia-dev qttools5-dev libqt5xmlpatterns5-dev libqt5svg5-dev qtwebengine5-dev qtscript5-dev  lqtbase5-private-dev libqt5x11extras5-dev libxt-dev 
```

#### Debian Testing (Bullseye)

Install the development tools and the support libraries:
```
sudo apt install git subversion build-essential cmake cmake-curses-gui cmake-qt-gui qt5-default qtmultimedia5-dev qttools5-dev libqt5xmlpatterns5-dev libqt5svg5-dev qtwebengine5-dev qtscript5-dev qtbase5-private-dev libqt5x11extras5-dev libxt-dev 
```
#### Ubuntu 20.04 (Focal Fossa)

Install the development tools and the support libraries:
```
sudo apt install git subversion build-essential cmake cmake-curses-gui cmake-qt-gui qt5-default qtmultimedia5-dev qttools5-dev libqt5xmlpatterns5-dev libqt5svg5-dev qtwebengine5-dev qtscript5-dev qtbase5-private-dev libqt5x11extras5-dev libxt-dev 
```
#### ArchLinux
#### Gentoo


