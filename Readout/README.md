# Readout-related circuits
The 7000-series readout circuitry is a clever, subtle, and novel solution, as you would expect once you learn that the designer was [Barrie Gilbert](https://w140.com/tekwiki/wiki/Barrie_Gilbert).
It is based on circuitry in the mainframe scanning the modules for characters to display in specific timeslots.
There are 10 possible timeslots (character positions) per screen location, and 2 screen locations per plug-in bay (e.g., 8 total screen locations in a 7904A, for a maximum total of 80 characters, though far fewer are displayed in normal operation.)
Display characters, or other metadata, are encoded in each timeslot by two currents (row and column) per location.
Currents are encoded in 100uA steps.
Modules need to always be prepared to sink either two or four currents to drive the display, but while the timeslot signals are simply bussed across all plug-in bays, the mainframe is paying attention to only one plug-in at a time (there is no indication to a plug-in that it is the active one.)
The system can be fully implemented by passive components and wiring and/or switches, including modifying scales/prefixes. Changes can be accomplished simply by summing currents, and common scope operations (e.g., input sensitivity modification by x10, x100, x1000 probes) are easily implemented by plug-ins using simple, but sometimes subtle, solutions.

## Interfaces
There are two interfaces needed to interact with the 7000-series readout system - one from the mainframe to the plug-ins and one from the plug-ins to the mainframe:

### Timeslot Signals

There are ten timeslot scanning signals from the mainframe to the plug-in.
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

The following image shows the same input pulse in blue, but the red trace reflects the time spent in the interrupt handler on the ARM CPU in the PSoC. The ISR is reading the timeslot value from the counter and then writing new values to the readout current circuitry via the shift registers described below. In practice, additional lookups will be involved, but that will hardly impact the duration of the ISR.

![Input ISR Timing](/Images/TS_Pulse_Input_ISR_Timing.png)

This demonstrates that the solution will work, and as long as we do not mask interrupts for extended periods we can use software to service the readout circuitry.

## PSoC Connectivity

### Inputs

The timeslot input circuitry uses two pins of analog I/O into the PSoC.
Internally these are conditioned via comparators (as described above) and used to maintain a counter of the most recent timeslot requested, and generate interrupts so that the firmware can determine the approriate row/column currents for each channel.

Combining the nine timeslot signals as show reduces the number of input pins required, at the cost of obscuring specific timeslot outputs from the mainframe that may be malfunctioning.

![TS Input](/Images/TS_Input.png)

### Outputs

Output requires 16 pins of digital GPIO for all 4 current sinks, while this may be possible with specific members of the PSoC device family, it was highly desirable to be able to use the CY8CKIT-059, meaning that the GPIO pin count was constrained. Initially a Microchip MCP23S17 I/O expander using SPI was prototyped, but the design was quickly refined to use 74HC596 open-drain shift registers instead, with a simple driver circuit implemented in the PSOC. Two 596 shift registers are used, each implemeting the 8 bits (4 row + 4 column) required for one channel. These are daisy-chained, so that the PSOC clocks 16 bits out in one operation and then strobes the register clock line to simultaneously present all 16 bits to the current generation circuit.

![TS Output Logic](/Images/TS_Output_Logic.png)

The function to invert and write a 16-bit value to the outboard shift registers takes under 1 uS.

### Readout Row and Column Currents
Four current sinks (two channels, each with independent row & column currents)  encode the data for the currently indicated timeslot.  
Channel 1 data will appear at the top of the screen, Channel 2 data will appear at the bottom of the screen.

The circuit used is shown below:

![Readout Current Sink](/Images/TS_Current_Sink_2.png)

Inputs (4 bits per current sink) are open-drain inputs that select 0 - 1500 uA currents in 100 uA steps. The output is a current sink to the -15 V rail that reflects the selected binary value.

The theory of operation is as follows:

* Each bit consists of a single PNP transistor whose base is pulled up by a 4k7 resistor. When the open-drain driver is active, the base is pulled to within a few mV of ground, turning the transistor on.
* Each transistor has an emitter resistor that is chosen to deliver a specific current based on the 4.3V drop between the 5V rail and Vbe (approx 0.7V).
* 43K => 100uA, 21K5 => 200uA, 10K7 => 400uA, 5K36 => 400uA
* These currents are summed via individual 1K resistors, and mirrored against the -15V rail by a current mirror using a THAT 300S (4 matched NPN transistors.)
* Because the weighted output current is selected when the open drain output is low, the value written needs to be the bitwise inverse of the desired current.

This circuit is repeated four times (row and column for each of two channels.)

## Prototype Test PCB
![Q2 2022 Prototype and eval board](/Images/Proto-board-Q2-22.png)

# TODO:
* Add example code.
