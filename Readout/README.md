# Readout-related circuits
The 7000-series readout circuitry is a clever, subtle, and novel solution, as you would expect once you learn that the designer was [Barrie Gilbert](https://w140.com/tekwiki/wiki/Barrie_Gilbert).
It is based on circuitry in the mainframe scanning the modules for characters to display in specific timeslots.
There are 10 possible timeslots (character positions) per screen location, and 2 screen locations per plug-in bay (e.g., 8 total screen locations in a 7904A, for a maximum total of 80 characters, though usually far fewer are displayed in normal operation.)
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

The above image clearly shows a timeslot pulse that is around 130us wide, with a plateau at -15V between approximately 45us and 65us, which is where the sampling must occur for the resistor values to generate the appropriate currents.

Two circuits were investigated to map the 0 -> -15V pulse from the mainframe onto a logic-level signal:

  1. Discrete Timeslot Input Interface Circuit

     Based on the circuit used in the 7M13, using a single NPN transistor.

     ![Discrete Circuit](/Images/Discrete_timeslot_interface_snippet.png)

     The resistor values have been tweaked from the 7M13 design, to reduce quiescent current consumption.

     Channel 2 (blue) in the following scope capture shows the output of the circuit:

     ![Discrete Trace](/Images/Tek7K-TS0-202107271813.png)

  2. Schmitt Trigger Timeslot Input Interface Circuit

     Based on a circuit from [Ed Breya on the TekScopes mailing list](https://groups.io/g/TekScopes/photo/266548/3273411) which uses logic, clamping diodes, and current limiting resistors.

     ![Schmitt Trigger Circuit](/Images/Schmitt_trigger_timeslot_interface_snippet.png)

     Again, channel 2 (blue) is the resulting output:

     ![Schmitt Trigger Trace](/Images/Tek7K-TS0-202107281441.png)

Comparing the two circuits, the discrete design responds approximately 10us faster to the falling edge of the timeslot pulse, resulting in maximum setup time for the output currents.
However, I believe the schmitt trigger-based design offers improved noise margin and less opportunity for false edges.  
Measurements suggest the schmitt trigger circuit still offers adequate time (~30us) for firmware to react and set up the current sinks before the pulse bottoms out and the currents are sampled by the mainframe.  
Therefore the schmitt trigger based solution is preferred.

### Readout Row and Column Currents
The two or four current sinks (one or two channels respectively, each with independent row & column currents) that encode the data for the currently indicated timeslot.  
Channel 1 data will appear at the top of the screen, Channel 2 data will appear at the bottom of the screen.

TODO: Document useful current sink circuits, including current DACs and discrete solutions.

## Microcontroller Connectivity
Given enough I/O pins on whatever is determining what to display (10 for timeslot reporting, 16 for current selection), you can interface directly with a microcontroller. However, an SPI interface is also defined which reduces the I/O requirement to six pins (SCLK, MOSI, MISO, CS0, CS1, INT.)  
There is a possible optimization that reduces the I/O pin count used by both the 7M13 and Ed Breya's design: timeslots 2 - 10 are or'ed together and simply advance a counter. Timeslot 1 is handled specially and resets the counter.

