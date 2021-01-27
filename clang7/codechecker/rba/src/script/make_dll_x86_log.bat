@echo off
set ARCH=x86
set LOG=ON
set MODE=%1

if "%MODE%" == "" (
    set MODE=Release
)
if not "%MODE%" == "Debug" (
    if not "%MODE%" == "Release" (
        echo Usage: %0 Debug or Release
        goto end
    )
)
set LOGLABEL=
if "%LOG%" == "ON" (
    set LOGLABEL=_log
) else (
    set LOGLABEL=_nolog
)

set CMAKE_OPTION=
if "%ARCH%" == "x86" (
   set CMAKE_OPTION="Visual Studio 15 2017"
) else if "%ARCH%" == "x64" (
   set CMAKE_OPTION="Visual Studio 15 2017 Win64"
)

set DIRNAME=build_%ARCH%%LOGLABEL%
set OUTNAME=%MODE%_%ARCH%%LOGLABEL%

if exist "%DIRNAME%\" (
   goto exec_make
)

mkdir %DIRNAME%
cd %DIRNAME%

if "%LOG%" == "ON" (
    cmake -G %CMAKE_OPTION% ..
) else (
    cmake -G %CMAKE_OPTION%  -DNOLOG=1 ..
)
cd ..

:exec_make
cmake --build %DIRNAME% --config %MODE%

:end
echo done.
