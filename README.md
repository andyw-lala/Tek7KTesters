# Tek7KTesters

Project to create modern test fixtures/plug-ins for the Tektronix 7000-series scope mainframes.
For more info on the 7000 series, see the excellent [Tekwiki](https://w140.com/tekwiki/wiki/Introduction_to_the_7000-Series).

7000-series calibration plug-ins are a rare beast, and usually expensive when they can be found.

This project hopes to create some new calibration & test solutions, with circuit ideas and software that can be reused, mixed-and-matched, extended, and improved. Where appropriate, modern chip-level solutions are encouraged to be used, examples include: differential drivers (both analog and LVDS), and microcontrollers.

Some of this work may be applicable or portable to other Tek plug-in based scopes, such as the 5000 series, but I don't own any of those (yet.)

## Contents:

### [Tek 7K Breakout Board](/Breakout)
This is a simple breakout board to facilitate experimentation and development using the Tek 7000 backplane connections.

### [Pattern Generator](/Pattern)
Circuit to generate test patterns, consisting of vertical lines, horizontal lines, vertical and horizontal lines, and dots.
Based on the Infineon (nee Cypress) PSOC5LP, plus required external circuitry.

### [Readout Interface](/Readout)
Circuit to interface the mainframe's readout subsystem to the PSoC, to permit displaying of arbitrary information, and/or testing of the mainframe readout system.

## Licence
All work here is covered by the MIT Licence, which is simple and permissive.

## Background
There is information to be found in many places, but a great starting point is [Tektronix 7000-Series Plug-in to Mainframe Interface Manual](https://w140.com/tekwiki/images/7/7c/Tek_7000-series_plug-in_mainframe_interface_manual_ocr.pdf). Originally a Tek-internal engineering document, now freely available.

Manuals for original calibration/test fixtures:
* [067-0587-01](http://w140.com/tek_067_0587_01.pdf)
* [067-0587-02](http://w140.com/tek-067-0587-02.pdf)
* [067-0587-10](http://w140.com/tek_067-0587-10_service.pdf)
* [067-0711-99](https://w140.com/tekwiki/images/8/87/Tek_067-0711-99.pdf)
* [7M13](https://w140.com/tekwiki/images/3/33/070-1577-00.pdf)

The [TekScopes mailing list](https://groups.io/g/TekScopes) is an invaluable source of knowledge, experience, and expertize on all Tek oscilliscopes, not just the 7000-series.

## TODO
* Fast edge driver, ideas include LVDS drivers, or MAX3949 (like the Leo Bodnar pulser I have that happily does <40pS edges, I like this because it is configurable to some extent)
* Levelling amp, will likely think about this last, as I believe it will be the most difficult subsystem to get right, and make repeatable, especially up to 7104 bandwidths..

## Disclaimer
This project is presented as-is, all work and consequences are your sole responsibility. Do not work on Tek 7000 scopes unless you have the skills and knowledge to work safely, they contain **lethal** voltages. You perform all work at your own risk, and I have no responsibility for any damage or injury whatsoever.
