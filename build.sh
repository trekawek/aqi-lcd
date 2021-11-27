#!/bin/bash -e

pio run -e lcd -e led -e led-matrix

cp .pio/build/lcd/firmware.bin bin/firmware-lcd.bin
cp .pio/build/led/firmware.bin bin/firmware-led.bin
cp .pio/build/led-matrix/firmware.bin bin/firmware-led-matrix.bin
