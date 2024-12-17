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

Adapting the timeslot input circuitry used on the 7D11, the timeslot pulses from the mainframe are fed to a JFET, which is normally conducting, with its drain at 0V. When the TS pulse starts to go negative, the JFET will turn off, allowing the voltage at the drain to rise. Since the PSOC lacks schmitt trigger inputs, we use on-chip comparators with hysterisis enabled to condition the input signal. This circuit is implemented twice, once for TS1 and once for all the other TS signals, diode or-ed together. A 100K pull-down resistor on the JFET gate ensures a timely turn on of the fet as the diodes would otherwise isolate the gate. Although the TS1 signal strictly speaking does not require the diode, it is implemented so that the circuitry and timing seen by each timeslot is identical.

![Input Conditioning](/Images/TS_Pulse_Input_Detail_20230703.png)

This circuit offers approximately 57 uS lead-time from the input signal crossing the 1.024 V threshold to the bottom of the input pulse when the current sinks need to be set-up.

![Input Timing](/Images/TS_Pulse_Inputs_20230703.png)

The blue trace (LH axis) is the input pulse from the mainframe, red trace (RH axis) is the signal as seen by the PSoC.

The following image shows the same input pulse in blue, but the red trace reflects the time spent in the interrupt handler on the ARM CPU in the PSoC (note the timebase change from 20us to 10us per division.) The ISR is reading the timeslot value from the counter and then writing new values to the readout current circuitry via the shift registers described below. In practice, additional lookups will be involved, but that will hardly impact the duration of the ISR.

![Input ISR Timing](/Images/TS_Pulse_Input_ISR_Timing_20230703.png)

This demonstrates that the solution will work, and as long as we do not mask interrupts for extended periods we can use software to service the readout circuitry.

## PSoC Connectivity

### Inputs

The timeslot input circuitry uses two pins of analog I/O into the PSoC.
Internally these are conditioned via comparators (as described above) and used to maintain a counter of the most recent timeslot requested, and generate interrupts so that the firmware can determine the approriate row/column currents for each channel.

Combining the nine timeslot signals as shown reduces the number of input pins required, at the cost of obscuring specific timeslot outputs from the mainframe that may be malfunctioning.

![TS Input](/Images/Readout_input_20230703.png)

### Outputs

Output requires 16 pins of digital GPIO for all 4 current sinks, while this may be possible with specific members of the PSoC device family, it was highly desirable to be able to use the CY8CKIT-059, meaning that the GPIO pin count was constrained. Initially a Microchip MCP23S17 I/O expander using SPI was prototyped, but the final design was uses 74HC595 shift registers coupled with a simple driver circuit implemented in the PSOC as a write-only port expander. Two 595 shift registers are used, each implemeting the 8 bits (4 row + 4 column) required for one channel. These are daisy-chained, so that the PSOC clocks 16 bits out in one operation and then strobes the register clock line to simultaneously present all 16 bits to the current generation circuit.

![TS Output Logic](/Images/Readout_output_20230703.png)

### Readout Row and Column Currents
Four current sinks (two channels, each with independent row & column currents)  encode the data for the currently indicated timeslot.  
Channel 1 data will appear at the top of the screen, Channel 2 data will appear at the bottom of the screen.

The circuit used is shown below:

![Readout Current Sink](/Images/Readout_V4_Extract.png)

The parallel outputs of the shift registers drive four 4-bit [R-2R voltage DACs](https://en.wikipedia.org/wiki/Resistor_ladder#R%E2%80%932R_resistor_ladder_network_(digital_to_analog_conversion)). These output 0 - 4.6875V in 312.5mV steps, for values between 0 and 15 respectively. Note that R-2R ladders maintain a fixed impedance, equal to R regardless of input value.
As noted above, the mainframe measures the current flowing out of the mainframe row and current connections in 100uA steps when the timeslot signal is stable at -15V (the middle of the pulse.)
The mainframe row and current sense pins are nominally at ground.
This current is developed by applying a negative voltage across a fixed resistor which connects to the mainframe row and column pins. Since 5K precision (1%) resistors are aleady used elsewhere in the design, this value was selected.
100uA corresponds to 500mV across a 5K resistor, therefor a simple inverting amplifier with a gain of -1.6 can be used to convert the DAC output into a suitable negative voltage to convert each 312.5mV step from the DAC into a 100uA current flowing out of the mainframe sense pins.
Thus we can generate four independant 0 - 1500uA current sinks each with 100uA resolution, using only 3 pins on the PSoC, and 3 low-cost ICs.

## Demonstration of circuit in action
![Image of readout display](/Images/Readout_Example_20230703.jpg)

This is generated by the following crude code with magic numbers:

```
void
Readout_Write(uint8 ch1, uint8 ch2)
{
    uint16 readout = ch1 | (ch2 << 8);
    /*
     * Row is lower nibble of each byte, column is the upper nibble.
     */
    Readout_SR_WriteRegValue(readout);
    Readout_Control_Write(0x01);
}
static char top[10] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xa0};
static char bottom[10] = {0x34, 0x74, 0x81, 0xa5, 0xa4, 0x75, 0x83, 0x54, 0x31, 0x85};

CY_ISR (TS_ISR)
{
    uint8 ts;
    
    ts = Timeslot_Read();
    
    if (ts >= 10) {
        Readout_Write(0x53, 0x53);
    } else {
        Readout_Write(top[ts], bottom[ts]);
    }
}
```
