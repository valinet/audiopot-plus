# AudioPot+
AudioPot+ is the second attempt at producing a volume knob for a computer using an Arduino. It is an evolution of the original [AudioPot](https://github.com/valinet/AudioPot) project.

This time, a KY-040 rotary encoder is connected to the microcontroller, which has the advantage that it provides unlimited turns, allowing for smoother operation and easier interaction with the host (only volume increase/decrease messages have to be communicated, not the absolute value). Furthermore, instead of communicating over serial with the host, which had to run a custom service that interpreted the messages, this solution is entirely microcontroller-driven - the Arduino emulates a USB keyboard and emits corresponding keycodes when the encoder is rotated or pressed; this has the huge advantage that no code has to run on the host, and that the current solution is also portable (it works on any OS).

Taking into consideration the above mentioned stuff, I consider this to be the optimal implementation and I will probably archive the original project (I do not have the original hardware as well, I repurposed it for this).

<img src="res\cover.jpg" alt="cover" style="zoom:50%;" />

## Why not a Leonardo/(Pro) Micro?

For those who are not familiar, Arduino Leonardo or Arduino (Pro) Micro have built-in USB host support (due to using a different microcontroller, the ATmega32u4 as opposed to the ATmega328 in Uno/Nano etc).

* I couldn't find one in the short/medium term.
* More expensive.
* I have tons of Arduino Nano boards and availability is pretty good.
* I wanted the thing NOW.

## Schematic

<img src="res\schematic.png" alt="schematic" style="zoom:50%;" />

* Original V-USB schematic is available [here](https://petrockblog.files.wordpress.com/2012/05/wpid-photo-19-05-2012-22201.jpg).
* I have used 100 Ohm resistors instead of 68 because that is what I had available. It seems to work just fine.
* I have omitted the Zener diodes because I understand they do not play a crucial role, I did not have any available and it just works without them, as explained [here](https://www.element14.com/community/thread/28401/l/can-someone-explain-how-this-v-usb-circuit-works).
* Green wire is USB Data+, white wire is USB Data-. The 2.2kOhm resistor signals a low speed USB device. It is connected to pin 5 of Arduino so that we can disconnect/reconnect the USB device from code.
* SW has a pullup connected internally on the Arduino.
* The capacitors may be optional, it depends on how noisy your KY-040 encoder is.

## How to build?

Physically building this device can be challenging. Of course, folks with 3D printers will have to spend like 10 minutes to create something rather nice, but since I do not have a 3D printer, I had to come up with something that looks nice and works okay.

To build the physical housing, I recommend using 2 Pringles cans (any flavor works). But hurry up, I heard a redesign of the package is on the way to become more eco-friendly. From those, you'll need the metal base. Use a large knife to cut the base from one of the cans. You'll seat all the components on this. For the other can, leave a few inches of material from the tube (do not cut exactly near the base), as that will come on top and will rotate (be the actual knob, so it needs a margin and some height in order to hide the internals). Cover the messages on the packaging using black electrical tape.

Place the components on the base, in any layout you want. For them to stick, I recommend double sided tape. Pay extra attention to place the encoder exactly in the center of the base, as otherwise, the rotation of the knob won't perfectly overlap the base. Use a file and cut the lip of the base in some place to make way for the USB cable.

For attaching the knob, the way I do it is: take the cap for the shaft of the encoder and hot glue it vertically on some spare metal sheet (you can use another spare Pringles metal base). You have to do this on some material that the glue won't enter into a reaction with. The reason is simple: when the glue dries, I take slice the contraption off the metal shield and attach it on top of the encoder. Then, to finish everything off, and make sure the knob is perfectly centered, put double sided tape on its inner side and slowly place it above the hot-glued cap, adjusting its position slightly before pressing it hard so that the tape sticks to the hot glue contraption.

A slight annoyance is that the expiration date is stamped on the metal bases, but maybe some type of alcohol can take it off without ruining the appearance. For now, it works fine for me the way it is.

A few photos so that it is easier to understand what I tried to explain:

> <img src="res\opened.jpg" alt="opened" />
>
> The internals

> <img src="res\knob.jpg" alt="knob" />
>
> A closer view of the insides of the knob.

> <img src="res\base.jpg" alt="base" />
>
> A closer view of the base board.

> <img src="res\device.jpg" alt="device" />
>
> The device in its operational state and appearance.

If you do not have a KY-040, you can instead use a USB mouse wheel instead (you have to get creative mounting it). Just pick the cheapest USB mouse you can find and extract the encoder from in there.

## Libraries

This project uses the following libraries:

* [Encoder](https://github.com/PaulStoffregen/Encoder) - reliably decode rotary encoder turns
* [USBKeyboard](https://github.com/valinet/USBKeyboard) - a slightly tweaked version of the library which allows for virtual USB communication (it adds a `SendMultimediaKey` method and changes the capabilities the virtual USB reports so that media control works properly)

## Compiling

This repository contains all the necessary info to clone and correctly compile this, by including specific versions of the libraries used in the project. To correctly clone this repository, do:

```bash
git clone --recursive https://github.com/valinet/audiopot-plus
```

This project compiles successfully using Arduino IDE 1.8.3. Future versions may work as well; to compile successfully, make sure you do not already have copies of the libraries used in this project already in your Documents/libraries folder (this is because of a quirk of the Arduino build system; otherwise, you will get linker errors because some translation units will be compiled twice). Please temporarily remove the libraries from your libraries folder when attempting to compile this from the Arduino IDE.

I recommend flashing your Arduino with the [MiniCore](https://github.com/MCUdude/MiniCore) bootloader, as that is what I use for all my latest Arduino projects, but the default bootloaders should work as well.

## License

Licensed under [GPLv3](https://github.com/valinet/audiopot-plus).