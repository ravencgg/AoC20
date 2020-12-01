@echo off

REM blank lines:
echo.
echo    Building AoC 2020!
echo.

SET batch_loc=%~dp0

if "%SHELLSETUP%"=="" (
    set SHELLSETUP=""
    REM echo Running shell.bat
    REM call %batch_loc%shell.bat
	REM "%VS140COMNTOOLS%"vsvars32.bat x86_amd64

    IF EXIST "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" (
        REM VS 2019 already reports this info in vcvarsall.bat, no need to output this
        REM echo Setting up shell for x86_64 compiling with VS 2019
        call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\"vcvarsall.bat x86_amd64
    ) ELSE IF EXIST "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\"vcvarsall.bat (
        echo Setting up shell for x86_64 compiling with VS 2015
        call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\"vcvarsall.bat x86_amd64
    )
) ELSE (
    REM echo Skipping setup
)

set CommonCompilerFlags=-Od

set CommonCompilerFlags=-WL /std:c++17 -nologo -fp:fast -fp:except- /EHsc -Gm- -GR- -EHa- -Zo -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4505 -wd4127 -FC -Z7 -GS- -Gs9999999 %CommonCompilerFlags%
set CommonLinkerFlags= -incremental:no -opt:ref user32.lib
REM gdi32.lib winmm.lib kernel32.lib shlwapi.lib Shell32.lib

IF NOT EXIST %batch_loc%\bin mkdir %batch_loc%\bin
pushd %batch_loc%\bin

del *.pdb > NUL 2> NUL

REM 64-bit build
REM Optimization switches /wO2
cl %CommonCompilerFlags% ../main.cpp -Feaoc.exe -MTd /link %CommonLinkerFlags%
set LastError=%ERRORLEVEL%
popd

SET batch_loc=

echo.

