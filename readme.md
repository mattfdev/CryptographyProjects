CPS713 Lab 2 Template
===

## Building

## Linux

This template uses CMake. It can be loaded in IDEs such as CLion that support CMake.

To output a standard makefile, for building on the command line you can do something like this from your source folder:
```$bash
mkdir build
cd build
cmake ..
```

### OS X


On OS X it may be necessary to pass the following CMake option if using OpenSSL  from homebrew (which you should to get the latest OpenSSL):

`cmake -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl ..`

### Windows

Have you considered the [Windows Subsystem for Linux](https://msdn.microsoft.com/en-us/commandline/wsl/about)?