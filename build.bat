@ECHO off

REM Build file for CPPX

SET PROJECTDIR=%cd%
SET OUTDIR=%PROJECTDIR%\out

IF NOT EXIST %OUTDIR% MKDIR %OUTDIR%

PUSHD %OUTDIR%

SET DEBUGOPTS=/std:c++17 /DEBUG /MT /EHsc

REM cl %DEBUGOPTS% %PROJECTDIR%\object-pointer-cmp.cpp
REM cl %DEBUGOPTS% %PROJECTDIR%\storage-duration.cpp
REM cl %DEBUGOPTS% %PROJECTDIR%\lambdas.cpp
cl %DEBUGOPTS% %PROJECTDIR%\functions-as-objects.cpp

REM cl %DEBUGOPTS% %PROJECTDIR%\explicit.cpp
REM cl %DEBUGOPTS% %PROJECTDIR%\rule-of-zero.cpp

REM cl %DEBUGOPTS% /d1reportSingleClassLayoutDerived %PROJECTDIR%\vtable.cpp
REM cl %DEBUGOPTS% %PROJECTDIR%\friend.cpp
REM cl %DEBUGOPTS% %PROJECTDIR%\typecasting.cpp

REM cl %DEBUGOPTS% %PROJECTDIR%\fake-cmdline.cpp

REM cl %DEBUGOPTS% %PROJECTDIR%\string_view.cpp

REM Return to original location in shell
POPD
