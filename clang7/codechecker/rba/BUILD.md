# Biuld of aribrator

## 1. Overview

This document describes build of Rule Based Arbitrator

## 2. Directory structure and library

|Path|Contents|
|:---|:---|
| rba/include/ | header files  |
| rba/src/ | source code files |
| rba/lib/ | libraries |
| rba/lib/librba.a | Arbitrator staticl lib<br>(on Linux) |
| rba/lib/librba.so | Arbitrator shared lib<br>(on Linux) |
| rba/lib/rba.dll | Arbitrator DLL<br>(on Windows) |
| rba/unittest/ | for unit test |
| rba/doc/ | Documents |
| rba/script/ | include script file |
| rba/script/make_dll_x64.bat | for creation of DLL |


## 3. Build step

### 3-1. Linux 

#### 3-1-1. Environment

* OS
  - Ubuntu 16.04
  - Ubuntu 18.04
  - Windows Subsystem for Linux (Ubuntu 16.04.5 LTS)
* Development env.
  - g++ 5.4.0
  - make 4.1
  - CMake 3.5.1

#### 3-1-2. Build

```
$ cd rba
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ls -F ../lib
librba.a    librba.so
```
If build will be succeed,you can get **librba.a** and **librba.so**.

### 3-2. Windows

#### 3-2-1. Environment

* OS
  - Microsoft Windows 7 Professional 64bit
  - Microsoft Windows 10 Pro 64bit
* Development Env
  - Visual Studio Professional 2017
    - Desktop for C++
      - include Visual C++ tool of CMake

#### 3-2-2. Build

Execute command prompt for VS 2017, then executer bat file like below.

```
> cd rba
> script¥make_dll_x64.bat
> dir lib /w
[.]       [..]      rba.dll   rba.exp   rba.lib
```

If build will be succeed,you can get ```rba.dll```.

