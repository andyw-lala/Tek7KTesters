# Patttern Generator
Generate assorted patterns, either via 100mV/division single-ended outputs, or via the backplane connectors (50mV/division differential)
Purpose is to create test patterns that are used to ensure performance and geometry of the mainframe.

## Overview
Need to generate ramps (horiz and vertical sweeps), steps (resulting in lines when combined with a sweep.)
Tek fixtures 067-0587-* could generate either 11 or 110 lines, with sweeps from 10Hz to 1MHz.
Stretch goal of combining two step generators to produce a field of dots.
Produce appropriate Z-axis signals as required.

Design built around a PSOC5LP from Cypress, which has configurable mixed signal functionality on-chip, including multiple current DACs, combined with an ARM-based micro controller, with RAM & Flash.

[CY8CKIT-059](https://www.mouser.com/ProductDetail/Cypress-Semiconductor/CY8CKIT-059)
[PSoC Creator IDE](https://www.cypress.com/products/psoc-creator-integrated-design-environment-ide)

TODO:
* block diagram
* PSoC Creator files
