# AQI LCD

This is an app for the Wemos-based TFT display, presenting the pollution level:

![](docs/photo.jpg)
(photo: [nettigo.pl](https://nettigo.pl/products/plytka-pcb-ekran-dotykowy-z-wifi-i-karta-sd-do-wemos-d1-mini))

## Configuration

When the device starts, it creates a wifi network, called `AQI LCD`. Please connect to it, to configure the wifi network and the sensor URL. For now, two sensor types are supported:

* `AQI_ECO` - reads the JSON from the  [aqi.eco](https://aqi.eco), eg. `https://smolna.aqi.eco/13b/data.json`,
* `LOCAL_DEVICE` - reads data from a local, Luftdaten sensor. The URL looks like this: `http://192.168.0.130/data.json`.

After saving the configuration, the device will be connected to the configured network.

### Resetting configuration

Hitting the "Reset" button twice will reset the device in AP mode, creating the `AQI LCD` network again.

## Building

The project uses [platform.io](https://platform.io/). It can be build and uploaded with:

```
pio run -t upload -e lcd
```

## Hardware

Hardware is available at the Nettigo's website: https://nettigo.pl/products/plytka-pcb-ekran-dotykowy-z-wifi-i-karta-sd-do-wemos-d1-mini

## Neopixel LED frontend

AQI-LCD can be build in an alternative mode, in which the WS2812-based LED driver is used to display the pollution level:

```
pio run -t upload -e led
```

By default it assumes that a 60-LED strip is connected to the `D4` pin on Wemos. It can be configured with the build flags set in the [platformio.ini](platformio.ini):

```
  -DLED_COUNT=60  # how many LEDs (ring=16, stripe=60)
  -DLED_PIN=2     # D4 on wemost
  -DBRIGHTNESS=25 # max: 255
```