# Readout-related circuits
The 7000-series readout circuitry is a clever, subtle, and novel solution.
It is based on circuitry in the mainframe scanning the modules for characters to display in specific timeslots.
There are 10 possible timeslots (character positions) per screen location, and 2 screen locations per plug-in bay (e.g., 8 total screen locations in a 7904A, for a maximum total of 80 characters, though usually far fewer are displayed in normal operation.)
Display characters, or other metadata, are encoded in each timeslot by two currents (row and column) per location.
Currents are encoded in 100uA steps.
Modules need to always be prepared to sink either two or four currents to drive the display, but while the timeslot signals are simply bussed across all plug-in bays, the mainframe is paying attention to only one plug-in at a time (there is no indication to a plug-in that it is the active one.)
The system can be fully implemented by passive components and wiring and/or switches, including modifying scales/prefixes. Changes can be accomplished simply by summing currents.
## Interfaces
There are two interfaces needed to interact with the 7000-series readout system - one from the mainframe to the plug-ins and one from the plug-ins to the mainframe:
* The ten timeslot scanning signals from the mainfram to the plug-in.
  Each is a ~130-250uS wide pulse that drives to -15V, but is slew-rate controlled, in order to avoid generating noise in sensitive plug-ins.
  The timing is not explicitly specified in the documentation (that I can find), specifically when the current sinks are sampled, or setup/hold times.

  ![TS0 Pulse](/Images/Tek7K-TS0-202107301946.png)

  The above image clearly shows a timeslot pulse that is around 130us wide, with a plateau at -15V between approximately 45us and 65us, which is where the sampling must occur for the resistor values to generate the appropriate currents.

  TODO: Document possible interface circuits (1 discrete, 1 based on 74AC14) - including timing diagrams.

* The four current sinks (row & column, channels 1 and 2) that encode the data for the indicated timeslot.

  TODO: Document useful current sink circuits, including current DACs and discrete solutions.

Given enough I/O pins on whatever is determining what to display (10 for timeslot reporting, 16 for current selection), you can interface directly with a microcontroller. However, an SPI interface is also defined which reduces the I/O requirement to six pins (SCLK, MOSI, MISO, CS0, CS1, INT.)

