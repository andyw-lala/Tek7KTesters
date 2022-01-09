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

The following image shows the same input pulse in blue, but the red trace reflects the time spent in the interrupt handler on the ARM CPU in the PSoC. The ISR is reading the timeslot value from the counter and then writing new values to the I/O expander via SPI. In practice, an additional lookup will be involved, but that will hardly impact the duration of the ISR.

![Input ISR Timing](/Images/TS_Pulse_Input_ISR_Timing.png)

This demonstrates that the solution will work, and as long as we do not make interrupts for extended periods we can use software to service the readout circuitry.

### Readout Row and Column Currents
Four current sinks (two channels, each with independent row & column currents)  encode the data for the currently indicated timeslot.  
Channel 1 data will appear at the top of the screen, Channel 2 data will appear at the bottom of the screen.

The circuit used is shown below:

![Readout Current Sink](/Images/TS_Current_Sink.png)

Inputs (Bit0-3) are 5V logic level inputs that select 0 - 1500 uA currents in 100 uA steps. The output is a current sink to the -15 V rail that reflects the selected value.

The theory of operation is as follows:

* T1 is configured as a common emitter stage which is reliably driven between cut-off and saturation by 5 V logic level inputs.
* Worst case logic 0 GPIO output from MCP23S17 I/O expander chip of 0.6 V only results in ~400 mV on the base, ensuring T1 remains firmly off.
* T1 is driven into saturation by a logic 1 input, resulting in the base of T2 being held at around 30 mV.
* T2 then functions as a 100 uA current source, with the current defined by R10 (since the emitter will be held at (Vbe + ~ 30 mV).
* Similarly for each of the other three bits. The values of R12, R14, and R16 result in binary weighted current sources.
* These are summed via 10K resistors and used to drive a Wilson current mirror that provides the signal required by the mainframe as a current sink to the -15 V rail.

This circuit is repeated four times (row and column for two channels.)

## PSoC Connectivity

### Inputs

The timeslot input circuitry uses two pins of analog I/O into the PSoC.
Internally these are conditioned via comparators (as described above) and used to maintain a counter of the most recent timeslot requested, and generate interrupts so that the firmware can determine the approriate row/column currents for each channel.

Combining the nine timeslot signals as show reduces the number of input pins required, at the cost of obscuring specific timeslot outputs from the mainframe that may be malfunctioning.

### Outputs

Output requires 16 pins of digital GPIO for all 4 current sinks, while this may be possible with specific members of the PSoC device family, it was highly desirable to be able to use the CY8CKIT-059, meaning that the GPIO pin count was constrained. Therefore an I/O expander chip was used. SPI interface was selected to facilitate high speed (low latency) communication between the PSoC and the expander. The MCP23S17 provides 16 pins of I/O, while only using 4 pins on the PSoC/CY8CKIT-059.
