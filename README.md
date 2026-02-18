## Animus Jammer V1.0

### Overview

After buying an esp32 I decided to try navigate into wireless security after playing around with it for a while. I decided to make a 2.4GHz jammer, it wasnt as hard as I expected but it had it's challenges.
I decided to make it open source as I believe information should be free, even if the law disagrees. I added in the bare minimum needed to begin jamming, feel free to study the code and take it from there in your own projects. Happy hacking!


### Features
-- **Bluetooth Jamming**: Bluetooth and BLE operate on channels 1 - 80 and 1 - 40 respectively, which this device jams by default.
--**2.4GHz WiFi Jamming**: Most wifi networks use a frequency of 2.4GHz which can be disrupted using this jammer, with enough modification.

### How to operate

Change the SPI code for yourself as the SPI.begin function matches the requirements as I am using an esp32 arduino nano, on other microcontrollers it will be different. Once you have the wiring complete, wait for the radio
check to finish and hit enter and the jamming should commence.

### Future

At the time of writing, I have a few more components on the way and from there I plan to make this a fully fledged jammer with a menu, OLED, blah blah blah and I plan to make a full schematic using KiCad and upload it also!
So it's just a waiting game for now.
