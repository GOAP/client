GOAP Client
===========

Hi.

## Compile under Linux

* Make sure you have downloaded all the dependencies. Download something like `libsfml-dev` from your package manager of choice. On Arch Linux, `pacman -S sfml`.

* Create a directory for the build files: `mkdir build && cd build`

* Create the Makefile: `cmake ..`

* Compile: `make`


## Compile under Windows

(NOTE: Untested. Someone please try this.)

* Download SFML from http://sfml-dev.org/download/sfml/2.1/

* Create a new folder for the build files: `mkdir build` 

* Create the Visual Studio solution: `cmake .. -G "Visual Studio 10 Win64"` (or your Visual Studio of choice)

* Open Visual Studio and click things until it eventually compiles.
