#!/bin/bash -e

pio run -e lcd -e led

cp .pio/build/lcd/firmware.bin bin/firmware-lcd.bin
cp .pio/build/led/firmware.bin bin/firmware-led.bin
