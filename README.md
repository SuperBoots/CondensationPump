# CondensationPump
This code is written for an Adafruit ItsyBitsy 32u4 - 5V 16MHz microcontroller.

I have a problem, I need to remove water that is accumulating below my HVAC system. Water accumulates in the reservoir below the heat pump coil when the AC is on because the condensation does not drip into the drain tray like it's supposed to. It eventually overflows and we get water accumulating on the garage floor.

Solution: Instead of paying for an entirely new HVAC system like the HVAC company suggested, set up a small submersible pump to pump the water from the overflow basin into the drain pipe when the level is high enough for the submersible pump to operate.

Two float sensors, one to detect when the water level is too low to pump, and the other to sit at a higher point which will trigger a pump cycle when the water gets that high. Both the float sensors will connect to the Adafruit ItsyBitsy and it will use computer magic to determine when to run the pump. The 120v side of the relay will connect to an aquarium pump. I was going to put it all in a plastic project box so that I can just have a 120v outlet on the box that I can plug the pump into that's switched by the water level.

Parts list (prices are whatever they were when I purchased in July 2022):
* $10 Amazon Basics Power Cord - 12-Foot, Black get power to project box
* $8 10A Fuse Switch Male Power Socket input power plug and switch for project box (3 pack)
* $9 Otdorpatio Project Box DIY Electronic Power Enclosure 7.87 x4.72 x2.95
* $15 Anndason 6 Pieces Black Water Level Sensor connected to 5v microcontroller
* $7 HiLetgo 2pcs 5V One Channel Relay Module Relay Switch with OPTO Isolation High Low Level Trigger (2 pack) 5v side connected to microcontroller, 120v side connects to 120v input for project box and 125v panel mount outlet that pump will plug into
* $9 AC 125V US Outlet Panel Mount Power Rewiring (3 pack) Socket to plug pump into
* $60 Superior Pump 91025 1/5 HP Thermoplastic Submersible Utility Pump (already have hot tub pump, try that first) 
* $27 Marketing Holders 15" Square Clear Acrylic Tile for window into mess
* $24 Nashua Tape 2.5 in. x 60 yd. 324A Premium Foil HVAC UL Listed Duct Tape
* $10 Adafruit ItsyBitsy 32u4 - 5V 16MHz
* $6 5V 1A (1000mA) USB port power supply
* $3 USB cable - 6" A/MicroB
* $5 Adafruit Perma-Proto Half-sized Breadboard PCB, not sure which one I'll use
* $3 Adafruit Perma-Proto Quarter-sized Breadboard PCB, not sure which one I'll use
* $1 Short Male Header Kit for ItsyBitsy (turns out the ItsyBitsy comes with headers)
* $5 Rugged Metal Pushbutton with Red LED Ring - 16mm Red Momentary press to disable automatic pumping. Red light on indicates auto pumping disabled.
* $5 Rugged Metal Pushbutton with Green LED Ring - 16mm Green Momentary hold to manually activate pump. Green light indicates pump is active.

https://learn.adafruit.com/introducting-itsy-bitsy-32u4/pinouts
