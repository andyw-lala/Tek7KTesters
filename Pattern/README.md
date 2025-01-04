# Pattern Generator
Generate various test patterns, including:
* Horizontal lines
* Vertical lines
* Cross-hatch (combination of horizontal and vertical lines)
* Field of dots
The lines can either be coarse and match only the major graticule markings (11 horizontal, 9 vertical), or fine and align with both major and minor graticule markings (51 total horizontal, 41 total vertical.)
The field of dots is designed to produce a dot at every intersection of the major graticule markings only.
Optionally produce Z axis signal(s) to highlight the central graticule lines (and also all major graticule markings when producing the fine liones or crosshatch.

All signals are brought out to front panel connectors (100mV per division, single-ended), and driven to the approriate backplane connections (50mV per division differential.)

## Overview
There are 4 signal sources used in various combinations to support each mode:
1. Ramp Generator

   This uses a current DAC in the PSoC to charge a capacitor, generating a linear ramp. This signal is then conditioned to be symmetrical around ground, and have the approriate amplitude.
2. X & Y Step Generators

   These are identical, and each also use a current DAC in the PSoC to develop a voltage across a precision resistor. These signals are then also conditioned like the ramp signal.
3. Z Axis driver

   This uses a voltage DAC in the PSoC, to source a voltage that is converted into a control current in the range -4 to +4 mA which can modulate the trace intensity (max intensity to full blanking, respectively.)

The ramp and step signals are highly configurable, and also switched/routed according to the desired pattern and the location of the test plug-in in the mainframe (more on this later.)
In addition to directly driving the approriate backplane signals, these are also brought out to front panel BNC connectors. Usually one of these is used to connect to a suitable plug-in to provide the "other" signal (e.g., in a vertical slot, if the tester is using a horizontal slot.)

The Tek 067-0587-* fixtures could generate either 11 or 110 lines, with sweeps from 10Hz to 1MHz.
The new fixture can generate 11 or 51 vertical lines, and 9 or 41 horizontal lines, with sweeps from approximately 50Hz to 450KHz, and independently control the ramp repetition frequency in 500nS steps. At the very slow speeds, the signals are so sparse that it can be difficult to visually align with the graticule markings, and at the very fastest speeds, the software can begin to have trouble setting up additional signals such as the Z Axis output, resulting in inconsistent trace intensity.
The independent and highly configurable ramp time and ramp repetition frequency , combined with flexible signal routing allows for a great range of possible test patterns and speeds, allowing for adjustment of mainframe horizontal and vertical amplifiers.

[CY8CKIT-059](https://www.mouser.com/ProductDetail/Cypress-Semiconductor/CY8CKIT-059)

[PSoC Creator IDE](https://www.cypress.com/products/psoc-creator-integrated-design-environment-ide)

TODO:
* block diagram
* PSoC Creator files
