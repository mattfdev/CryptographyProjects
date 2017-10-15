CPS713 Lab 2
===

## Building


This project should build correctly on OSX, and Linux, being tested on OSX, a local Linux machine, and the Ryerson Moons.
Run the following to compile the entire project, assuming you are in the root directory of the project.
```
cmake .
make
```
Code was written to be compatible with default g++ settings as to ensure wide compatibility. It is therfore C++ 11 compliant.
## Running Executables
### Task 3
Specify a filename as an argument for the task3 executable. Because readme.md is already part of the project, it is used here as a simple example.
```
./task3 readme.md
```
### Task 4
Please supply a 6 letter hex string to the program. Any letter > F will result in the hex being rejected (invalid hex). Likewise the hex must be 6 digits long as specified by the lab, and must only be letters, also required by the lab. So valid input must consist of 6 letters of the range (a,b,c,d,e,f).
```
./task4 baddeb
```
### Task 5
For this lab please ensure crypt is avaialble on your system (Not avaialble on OSX preinstalled).
Please supply a number representing the number of bad password attempts allowed. This number must be greater than 0.
UserId and password requirements are exactly as specified in the lab, refer to lab or source code for details.
```
./task5 5
```

