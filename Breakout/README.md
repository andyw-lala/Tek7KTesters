# 7000-series Backplane Breakout Board
## Version 1
This board brings out the most commonly used high speed signals out to BNC connectors, and low-speed or power signals to screw connectors.
The intent is to allow cables to be routed out the front of the scope for connection to external circuits or test equipment.

### Board Outline
This is a crude dimensioned drawing of the basic board outline for the V1 breakout board.
I make no apologies for the mixed units, the edge connector width is tied tightly to the 38-way 0.1" edge connector and the board width of 4.5".
All other dimensions were directly measured with a caliper from multiple 7000 plug-in modules.
Form, fit, and function have been validated with plug-in frames, including the rear plastic housing (e.g., Tek part number 386-1402-00.)

### Eagle Files
Schematic and board files for a 4-layer implementation.
Note that this does not include any indication for hard gold plating on the edge connector, or chamfering of the board edge.

### OSHpark Project
The V1 board is available as a shared project from [OSHpark](https://oshpark.com/shared_projects/c7Hx5qZ4)

### Important Note
It is recommended by several members of the TekScopes mailing list to manually chamfer the edge connector and clean to remove dust before inserting into a scope mainframe, in order to avoid possible damage to the backplane connectors. As mentioedn above, the eagle files to not include this, and OSHpark does not offer chamfering on their boards, so you need to do this manually for OSHpark boards.
