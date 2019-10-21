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

The data sources (`JSON_TYPE`) are:

* `AQI_ECO` - reads the JSON from the  [aqi.eco](https://aqi.eco), eg. `https://smolna.aqi.eco/13b/data.json`,
* `LOCAL_DEVICE` - reads data from a local, Luftdaten sensor. The URL looks like this: `http://192.168.0.130/data.json`.

## Building

The project uses [platform.io](https://platform.io/). It can be build and uploaded with:

```
pio run -t upload
```

## Hardware

Hardware is available at the Nettigo's website: https://nettigo.pl/products/plytka-pcb-ekran-dotykowy-z-wifi-i-karta-sd-do-wemos-d1-mini