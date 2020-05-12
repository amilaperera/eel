@if exist build rmdir /S /Q build
@mkdir build
@cd build
@echo --- Executing cmake to create vs based project
@cmake -G "Visual Studio 16 2019" -DEnableRtos=On -DEnableSamples=On ..
@cd ..
@exit /b 0

