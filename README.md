# AQI LCD

This is a simple app for the Wemos-based TFT display, presenting the pollution level:

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
