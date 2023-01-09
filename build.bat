@ECHO off

REM Build file for CPPX

SET PROJECTDIR=%cd%
SET OUTDIR=%PROJECTDIR%\out

IF NOT EXIST %OUTDIR% MKDIR %OUTDIR%

PUSHD %OUTDIR%

SET DEBUGOPTS=/DEBUG /MT /EHsc

REM %DEBUGOPTS% %PROJECTDIR%\rule-of-zero.cpp
REM cl %DEBUGOPTS% %PROJECTDIR%\friend.cpp
REM cl %DEBUGOPTS% /d1reportSingleClassLayoutDerived %PROJECTDIR%\vtable.cpp
REM cl %DEBUGOPTS% %PROJECTDIR%\class-variables.cpp
REM cl %DEBUGOPTS% %PROJECTDIR%\typecasting.cpp
REM cl %DEBUGOPTS% %PROJECTDIR%\explicit.cpp

cl %DEBUGOPTS% %PROJECTDIR%\fake-cmdline.cpp

REM Return to original location in shell
POPD
