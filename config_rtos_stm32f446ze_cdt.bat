@if exist ..\build rmdir /S /Q ..\build
@mkdir ..\build
@cd ..\build
@echo --- Executing cmake to create makefiles based project
@cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=..\eel\cmake\Toolchain.cmake ^
  -DCMAKE_MAKE_PROGRAM=%EEL_MAKE_PROGRAM% -DCMAKE_BUILD_TYPE=Debug ^
  -DEelMcu=stm32f446ze -DEnableRtos=On -DEnableSamples=On ..\eel
@cd ..\eel
@exit /b 0

