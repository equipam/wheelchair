# --- Development Setup
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

#deps:
#ifeq ($(OS),Windows_NT)
#	choco install 
#else
#	sudo apt-get install 
#endif

dev-setup: deps sym-links

# ---

# --- Jetson Nano

JETSON_USER := iw20

jetson-setup:
	git clone https://github.com/pjueon/JetsonGPIO
	cd JetsonGPIO && \
	mkdir build && cd build && \
	cmake .. -DBUILD_EXAMPLES=OFF && \
	sudo make install
	rm -rf JetsonGPIO

jetson-build:
	cd jetson/lib && make

jetson-service:
	sudo mv -f ./jetson/wheelchair.service /etc/systemd/system/
	sudo systemctl daemon-reload

jetson-service-activation:
	sudo systemctl start wheelchair.service
	sudo systemctl enable wheelchair.service

jetson-install: jetson-build jetson-service

# --- Arduino setup for Jetson Nano
arduino-setup:
	sudo apt-get install wget
	sudo apt-get install screen
	mkdir output
	wget https://downloads.arduino.cc/arduino-1.8.19-linuxaarch64.tar.xz
	tar -xf arduino-1.8.19-linuxaarch64.tar.xz
	rm arduino-1.8.19-linuxaarch64.tar.xz
	./arduino-1.8.19/arduino --install-boards arduino:avr:nano:cpu=atmega168
	./arduino-1.8.19/arduino --install-library "ArduinoUnit:3.0.4"
	./arduino-1.8.19/arduino --pref build.path=$(pwd)/output --board arduino:avr:nano:cpu=atmega168 --save-prefs

arduino-upload:
	./arduino-1.8.19/arduino --upload ./arduino/main/main.ino

# Setup and deploy
setup: jetson-setup arduino-setup

deploy: jetson-install jetson-service jetson-service-activation arduino-upload

# ---

# --- TESTS
jetson-test:
	echo "no tests to run for jetson"

arduino-test: sym-links
	./arduino-1.8.19/arduino --upload ./arduino/tests/tests.ino
	screen /dev/ttyACM0 9600

test: jetson-test arduino-test
