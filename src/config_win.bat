@if exist ..\build rmdir /S /Q ..\build
@mkdir ..\build
@cd ..\build
@echo --- Executing cmake to create vs based project
@cmake -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Debug -DEEL_WIN_SAMPLES=On ..\src\
@cd ..\src
@exit /b 0

