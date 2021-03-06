# 7000-series Backplane Breakout Board
![Side A](/Images/Side+A.jpeg)
## Version 1
This board brings out the most commonly used high speed signals out to BNC connectors, and low-speed or power signals to screw connectors.  
The design intent is to allow cables to be routed via the front or sides of the scope for connection to external circuits or test equipment.

### [Board Outline](/Breakout/Tek7000_Breakout_v1_Outline.pdf)
A crude dimensioned drawing of the basic board outline for the V1 breakout board.  
I make no apologies for the mixed units - the edge connector width is tied directly to the 38-way 0.1" edge connector, and the board width was clearly intended to be 4.5".
All other dimensions were directly measured with a caliper from multiple 7000 plug-in modules.  
Form, fit, and function have been validated with plug-in frames, including the rear plastic housing (e.g., Tek part number 386-1402-00.)

### Eagle Files
[Schematic](/Breakout/V1.sch) and [board](/Breakout/V1.brd) files for a 4-layer implementation.  
High speed signals are designed to be *approximately* 50Ohm traces, but no attention has been paid to matching the signal path length for the differential signal pairs.  
Note also that the board file does not include any indication for hard gold plating on the edge connector, or chamfering of the board edge.

### BOM
The V1 board is designed for the following connectors:
* BNC (Qty 6)  
  Molex part number: 73171-3150  
  Mouser part number: 538-73171-3150
* Low Speed/Power  
  Pheonix Combicon MPT 0.1" pitch side entry screw connectors  
  Terminal count as required, TODO: list here

It is also possible to omit any or all of the connectors altogether and solder wires directly to the board, if desired.

### OSHpark Project
The V1 board is available as a shared project from [OSHpark](https://oshpark.com/shared_projects/c7Hx5qZ4).  
**Note:** These boards only have ENIG finish on the edge connector fingers, as mentioned above; and do not have chamfered edges (see below.)

### Important Note
It is recommended by several members of the TekScopes mailing list to manually chamfer the edge connector with a file and clean to remove dust before inserting into a scope mainframe, in order to avoid possible damage to the backplane connectors. As mentioned above, the eagle files to not include this and OSHpark does not offer chamfering, so you need to do this manually for OSHpark boards.
