# AQI LCD

This is a simple app for the Wemos-based TFT display, presenting the pollution level:

![](docs/photo.jpg)

## Configuration

There's no configuration dashboard yet. The configuration has to be made inside the [config.h](include/config.h) file before building the project. For instance:

```
#define JSON_URL "https://smolna.aqi.eco/13b/data.json"
#define JSON_TYPE AQI_ECO

#define WIFI_SSD "my-home-network"
#define WIFI_PASSWORD "wifi password 123"
```

For now, only the [aqi.eco](https://aqi.eco) is supported as a data source. In the future, the app will be able to gather stats from the local [Luftdaten](https://luftdaten.info/)-compatible device.

## Building

The project uses [platform.io](https://platform.io/). It can be build and uploaded with:

```
pio run -t upload
```

## Hardware

Hardware is available at the Nettigo's website: https://nettigo.pl/products/plytka-pcb-ekran-dotykowy-z-wifi-i-karta-sd-do-wemos-d1-mini