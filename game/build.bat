REM Build script for game
@ECHO OFF
SetLocal EnableDelayedExpansion

REM Get a list of all the .c files.
SET files=
FOR /R %%f in (*.c) do (
    SET files=!files! %%f
)

REM echo "Files:" %files%

SET assembly=game
SET compilerFlags=-g 
REM -Wall -Werror
SET includeFlags=-Isrc -I../engine/src/
SET linkerFlags=-L../bin/ -lengine.lib
SET defines=-D_DEBUG -DMIMPORT

ECHO "Building %assembly%%..."
clang %files% %compilerFlags% -o ../bin/%assembly%.exe %defines% %includeFlags% %linkerFlags%
