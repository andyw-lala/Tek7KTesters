# Readout-related circuits
The 7000-series readout circuitry is a clever, subtle, and novel solution, as you would expect once you learn that the designer was [Barrie Gilbert](https://w140.com/tekwiki/wiki/Barrie_Gilbert).
It is based on circuitry in the mainframe scanning the modules for characters to display in specific timeslots.
There are 10 possible timeslots (character positions) per screen location, and 2 screen locations per plug-in bay (e.g., 8 total screen locations in a 7904A, for a maximum total of 80 characters, though far fewer are displayed in normal operation.)
Display characters, or other metadata, are encoded in each timeslot by two currents (row and column) per location.
Currents are encoded in 100uA steps.
Modules need to always be prepared to sink either two or four currents to drive the display, but while the timeslot signals are simply bussed across all plug-in bays, the mainframe is paying attention to only one plug-in at a time (there is no indication to a plug-in that it is the active one.)
The system can be fully implemented by passive components and wiring and/or switches, including modifying scales/prefixes. Changes can be accomplished simply by summing currents, and common scope operations (e.g., input sensitivity modification by x10, x100, x1000 probes) are easily implemented by plug-ins.
## Interfaces
There are two interfaces needed to interact with the 7000-series readout system - one from the mainframe to the plug-ins and one from the plug-ins to the mainframe:

### Timeslot Signals

The ten timeslot scanning signals from the mainframe to the plug-in.
Each individual timeslot signal is activated in a repeating sequence.
Each pulse is ~130-250uS wide and drives from ground to -15V, but is carefully slew-rate controlled, in order to avoid generating noise in sensitive plug-ins.
The timing is not explicitly specified in the documentation (that I can find), specifically when the current sinks are sampled, or setup/hold times.

![TS0 Pulse](/Images/Tek7K-TS0-202107301946.png)

The above image clearly shows a timeslot pulse that is around 130us wide, with a plateau at -15V between approximately 45us and 65us, which is where the sampling must occur for the specified resistor values to generate the appropriate currents.

# Interfacing to PSoC

Working from a circuit from [Ed Breya on the TekScopes mailing list](https://groups.io/g/TekScopes/photo/266548/3273411), I adapted it to feed two on-chip comparators, both of which use the on-chip 1.024 V reference.

![Input Conditioning](/Images/TS_Pulse_Inputs.png)

The outputs from the comparators feed an on-chip counter (not shown.) TS_0 resets it, TS_n increments it, either signal will generate an interrupt.

This circuit offers approximately 35 uS lead-time from the input signal crossing the 1.024 V threshold to the bottom of the input pulse when the current sinks need to be set-up.

![Input Timing](/Images/TS_Pulse_Input_Timing.png)

The blue trace (LH axis) is the input pulse from the mainframe, red trace (RH axis) is the signal as seen by the PSoC.

### Readout Row and Column Currents
The two or four current sinks (one or two channels respectively, each with independent row & column currents) that encode the data for the currently indicated timeslot.  
Channel 1 data will appear at the top of the screen, Channel 2 data will appear at the bottom of the screen.

![Readout Current Sink](/Images/readout_current_sink_v1.png)

Again, resistor values shown are valid for 5V logic, they will need to be modified as required for 3.3V operation.

TODO: Document DAC-based current sink alternative.

## Microcontroller Connectivity
Given enough I/O pins on whatever is determining what to display (10 for timeslot reporting, 16 for current selection), you can interface directly with a microcontroller. However, an SPI interface is also defined which reduces the I/O requirement to six pins (SCLK, MOSI, MISO, CS0, CS1, INT.)  
There is a possible optimization that reduces the I/O pin count used by both the 7M13 and Ed Breya's design: timeslots 2 - 10 are or'ed together and simply advance a counter. Timeslot 1 is handled specially and resets the counter.

