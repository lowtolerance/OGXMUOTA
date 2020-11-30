## ESP32-S2 OG Xbox memory unit emulation

This project attempts to port ryzee119's ogx360_t4 XMU emulation to the ESP32-S2 family of microcontrollers.

The ESP32-S2 has some significant differences from the "regular" ESP32 chips, but perhaps the most interesting difference for the purposes of modding the OG Xbox is the inclusion of a USB OTG controller with backward compatability for USB 1.1 devices. Helping matters more is the fact that Ryzee's OGX360_T4  code is built on a new stack that happens to have an esp32-s2 port.

The ESP32-S2's USB OTG capabilities not only mean that one can hopefully use it to emulate an XMU(and most  controllers, probably), but they can also be utilized to flash new firmware and easily access a console for debugging.

This code is meant to compliment a small, open-source PCB I've designed to plug directly into a controller port slot (a big thanks to James Boulding for the contact pad footprint!).

Hardware
--------

The hardware is untested as of yet, even by myself, as the modules they are built around are not yet widely available for public consumption. I managed to get my hands on some engineering samples, however, and I'm just waiting on the prototype pcbs to be delivered.

Schematic
---------

I will post the schematic once I've verified that it actually  works. As is, it's stupidly simple and many of you could probably work it out for yourselves. But in essence, all my circuit is really doing smoothing voltage spikes is dropping 5v to 3.3v to drive the module and routing some traces.

The ESP modules aren't too picky about voltage, but 5v is way too much. Anything between 3.0 and 3.6 should be sufficient. These are very low power devices, so I'm gamling on a simple voltage divider doing the job.



The BOM
-------

* ESP32-S2-MINI-1 module^1
* 2 0603 0.1uF capacitors (>5V)
* 1 0603 22uF capacitor (>5V)
* 2 0603 0 ohm resistors^2
* 1 0603 1k resistor
* 1 0603 2k resistor
* 1 0603 10k resistor

1: These actually aren't  available for public consumption just yet. I managed to snag a handful of engineering samples, but I have not put my hands on one yet.
2: This is a placeholder value for now, I might need to apply some resistance in the end. But don't just jump the pads, there are traces running between them.

That's it. If you're in the US and ordering PCBs from OSHPark and parts from DigiKey, your total cost to build three boards should be well under $20 -- **with shipping**. 

And I do recommend ordering these from OSHPark -- the ENIG finish should be better than HASL for soldering the QFN56 package as well as for making good contact with the controller port pins. 

**Whereever you choose to have them made, be sure to specify a thickness of between 0.8mm and 1.0mm; anything thinner might not make secure contact with the pins in the controller port, and anything thicker may not fit without excess force**.  

I highly recommend assembling these with a reflow oven or hot plate setup. If you lack access to the equipment but still want to experiment with assembling a prototype yourself, then you might look into the process of reflowing with hot sand as an affordable alternative. 

**I don't know that it would even be possible to solder these modules with an iron or hot air, but if you're attempting it, *don't* attempt to solder the 9 nine "e-Pads" at the center of the module footprint**. It's better to leave those pads unsoldered than to solder them poorly.

Hooking up to PC
----------------

The most economical way of doing this would probably be just repurposing a controller port. Wire the controller wires from the port to a male USB plug, leaving the yellow composite video sync wire accessible, because here it's going to be used to enter DFU mode by grounding it while plugging it in and then ungrounding it. 

At some point I can throw together another PCB design with a female connector end and male USB plug, as well as a button to make the whole setup a little easier to work with.

If you've managed to properly assemble the PCB, adapt it to USB, and enter DFU mode (again, by pulling down the signal for the yellow wire at boot), the esp32 should be recognized as a new device and you will be able to flash it using ESP-IDF's `dfu-util` for the esp32-s2.