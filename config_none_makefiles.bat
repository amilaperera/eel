@if exist build rmdir /S /Q build
@mkdir build
@cd build
@echo --- Executing cmake to create makefiles based project
@cmake -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=cmake\Toolchain.cmake ^
  -DCMAKE_MAKE_PROGRAM=%EEL_MAKE_PROGRAM% -DCMAKE_BUILD_TYPE=Debug ^
  -DEEL_MCU=stm32f446ze -DEEL_F4_SAMPLES=On -DEnableSamples=On ..
@cd ..
@exit /b 0

