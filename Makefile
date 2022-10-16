# --- DEVELOPMENT SETUP
sym-links:
ifeq ($(OS),Windows_NT)
	cmd /c "for /f %F in ('dir arduino\main /b /a-d ^| findstr ".cpp .h"') do del arduino\tests\%F"
	cmd /c "for /f %F in ('dir arduino\main /b /a-d ^| findstr ".cpp .h"') do mklink /h arduino\tests\%F arduino\main\%F"
	ECHO "Finished creating Symbolic links"
else
	rm -f ./arduino/tests/*.cpp
	rm -f ./arduino/tests/*.h
	cp --symbolic-link $(PWD)/arduino/main/*.h $(PWD)/arduino/tests/
	cp --symbolic-link $(PWD)/arduino/main/*.cpp $(PWD)/arduino/tests/
endif

deps:
	cd jetson && python -m pip install -r dev_requirements.txt

dev-setup: deps sym-links

# ---

# --- Jetson Nano Setup

JETSON_USER := iw20

jetson-deps:
	git clone https://github.com/pjueon/JetsonGPIO
	cd JetsonGPIO && \
	mkdir build && cd build && \
	cmake .. -DBUILD_EXAMPLES=OFF && \
	sudo make install
	rm -rf JetsonGPIO/*

jetson-build:
	cd jetson/lib && make

jetson-setup: jetson-deps jetson-gpio
	
# ---

# --- TESTS
unit-tests:
	cd jetson && python -m pytest src
acceptance-tests:
	cd jetson && python -m pytest tests

test: unit-tests acceptance-tests
