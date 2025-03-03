REM Build script for engine
@ECHO OFF
SetLocal EnableDelayedExpansion

REM Get a list of all the .c files.
SET files=
FOR /R %%f in (*.c) do (
    SET files=!files! %%f
)

REM echo "Files:" %files%

SET assembly=engine
SET compilerFlags=-g -shared -Wvarargs -Wall -Werror
REM -Wall -Werror
SET includeFlags=-Isrc -I%VULKAN_SDK%/Include
SET linkerFlags=-luser32 -lvulkan-1 -L%VULKAN_SDK%/Lib
SET defines=-D_DEBUG -DMEXPORT -D_CRT_SECURE_NO_WARNINGS
DEL ..\bin\%assembly%.*

ECHO "Building %assembly%%..."
clang %files% %compilerFlags% -o ../bin/%assembly%.dll %defines% %includeFlags% %linkerFlags%
