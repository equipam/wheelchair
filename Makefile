# --- Development Setup
sym-links:
ifeq ($(OS),Windows_NT)
	cmd /c "for /f %F in ('dir arduino\main /b /a-d ^| findstr ".cpp .h"') do del arduino\tests\%F"
	cmd /c "for /f %F in ('dir arduino\main /b /a-d ^| findstr ".cpp .h"') do mklink /h arduino\tests\%F arduino\main\%F"
	ECHO "Finished creating Symbolic links"
else
	mkdir -p arduino/tests/temp
	mv arduino/tests/Arduino.h arduino/tests/mockVitro.cpp arduino/tests/test-vitro arduino/tests/compile-vitro arduino/tests/au2ju arduino/tests/tests.ino arduino/tests/.gitignore arduino/tests/temp
	rm -f ./arduino/tests/*.cpp
	rm -f ./arduino/tests/*.h
	mv arduino/tests/temp/* arduino/tests/temp/.gitignore arduino/tests/
	cp --symbolic-link $(PWD)/arduino/main/*.h $(PWD)/arduino/tests/
	cp --symbolic-link $(PWD)/arduino/main/*.cpp $(PWD)/arduino/tests/
endif

dev-setup: deps sym-links

deps:
	sudo apt-get install -y libserial-dev

# ---

# --- Jetson Nano

JETSON_USER := iw20
ARDUINO_PORT := /dev/ttyUSB0

jetson-setup: deps

jetson-build:
	cd jetson/lib && make

jetson-service:
	sudo cp -f ./jetson/wheelchair.service /lib/systemd/system/
	sudo systemctl daemon-reload

jetson-service-activation:
	sudo systemctl start wheelchair.service
	sudo systemctl enable wheelchair.service

jetson-install: jetson-build jetson-service

# --- Arduino setup for Jetson Nano
arduino-setup:
# sudo usermod -a -G dialout $(JETSON_USER)
	sudo apt-get install wget
	sudo apt-get install screen
	rm -rf output
	mkdir output
ifeq ($(uname -m),aarch64)
	wget https://downloads.arduino.cc/arduino-1.8.19-linuxaarch64.tar.xz
	tar -xf arduino-1.8.19-linuxaarch64.tar.xz
	rm arduino-1.8.19-linuxaarch64.tar.xz
else
	wget https://downloads.arduino.cc/arduino-1.8.19-linux64.tar.xz
	tar -xf arduino-1.8.19-linux64.tar.xz
	rm arduino-1.8.19-linux64.tar.xz
endif
#./arduino-1.8.19/arduino --install-boards "arduino:avr:nano:cpu=atmega328p"
	./arduino-1.8.19/arduino --install-library "ArduinoUnit:3.0.4"
	./arduino-1.8.19/arduino --pref build.path=output --save-prefs

arduino-upload:
	./arduino-1.8.19/arduino --upload ./arduino/main/main.ino --port $(ARDUINO_PORT)

# Setup and deploy
setup: jetson-setup arduino-setup

deploy: jetson-install jetson-service jetson-service-activation arduino-upload

# ---

# --- TESTS
jetson-test:
	cd jetson/tests && \
	make build && \
	make run

arduino-test: sym-links
	./arduino-1.8.19/arduino --upload ./arduino/tests/tests.ino --port $(ARDUINO_PORT)
	timeout 10s screen $(ARDUINO_PORT) 9600

arduino-invitro-test:
	cd arduino/tests && ./compile-vitro && ./test-vitro

test-local: jetson-test arduino-invitro-test

test: jetson-test arduino-test
