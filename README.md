<a name="readme-top"></a>
<!--
*** Readme based upon Best-README-Template.
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



### Built With

* [![ESPHome][esphome.io]][esphome-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## Developing, Testing & Debugging
Create/activate environment by running from project root:
```bash
source scripts/setup_build_env.sh
```

Build firmware on your local machine:
```bash
esphome compile config/DisplayTest.yaml
```

Upload firmware to your Board:
```bash
esphome upload config/DisplayTest.yaml
```

Connect the device to your wifi network:
1. Go to: [web.esphome.io](https://web.esphome.io)
2. Click on "Connect" and select the correct JTAG/serial debug unit
3. Click on the three dots and select 'Configure WiFi'

Tail the Board's Logs:
1. Go to: [web.esphome.io](https://web.esphome.io) and connect then click logs... or
2. Tail the ESPHome logs of the Board's running firmware from the command line:
```bash
esphome logs config/DisplayTest.yaml
```