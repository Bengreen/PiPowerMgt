# Introduction


Requirements:
1. Fan on/off
2. Power on/off
3. Watchdog on/off



## Pin Configurations
1. Serial interface
2. i2c (slave) to receive inputs from masters
3. Control for power
4. Control for fan

## Addresses
Each PI is assigned an address. It is then required to use that address when updating commands to the Arduino.

## Communication
Establish a standard packet structure to make comms simple .. (ie send data structures)
<ADDRESS><COMMAND><PAYLOAD>

### Commands
Fan on - NONE
Fan off - NONE
Power on - NONE
Power off - NONE
Power off after delay - Delay
Power off after delay and restart after time - delay, restart wait
Watchdog ON - NONE
Watchdog OFF - NONE
Watchdog Update - Timestamp

# Considersations
Can or should we use an event system or a structured set of scans.
BUT if we go with event system we need an event Q which may not be ideal for an embedded environment.
BUT on other hand it coudl be efficient and neat to implement with good service times and no wasted time scanning tables.

So consider to create two task lists. One is the list of future tasks and the other is the list of immediate tasks to do.

# Help
How to exit `monitor` CTRL-a k followed by y