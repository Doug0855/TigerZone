# TigerZone™ :tiger:

## TEAM J MEMBERS
- Austin Lindenberg @alindenberg
- Colton Moler @cmoler
- Jose Bohorques @jmbo
- Doug Hewitt @Doug0855
- Jordan Young @jordan-a-young
- James Ziegenfelder @Jziggy

## TigerZone™ Design Documents
- [TigerZone™ Classes] (https://github.com/Doug0855/TigerZone/blob/master/HOMEPAGE-Team_J/TigerZoneClasses.pdf)
- [TigerZone™ Communication] (https://github.com/Doug0855/TigerZone/blob/master/HOMEPAGE-Team_J/TigerZoneCommunication.pdf)
- [TigerZone™ FlowChart] (https://github.com/Doug0855/TigerZone/blob/master/HOMEPAGE-Team_J/TigerZoneFlowChart.pdf)

## Compiling our TigerZone™ implementation
1. Clone our TigerZone™ repository into your local computer
2. Run the ```make``` command in the terminal and a tiger.out executable compiled with g++ should be created

## Compiling our Mock server implementation
1. Clone our TigerZone™ repository into your local computer
2. Run ```g++ server.cpp -o server.out``` to compile our mock server implementation

## Running our TigerZone™ implementation
Usage: ```tiger.out <IP_ADDRESS> <PORT_NUMBER> <CHALLENGE_PASS> <TEAM_NAME> <TEAM_PASSWORD>```

## Running our Mock Server implementation
Usage: ```server.out <PORT_NUMBER> < <SERVER_COMMANDS>```

## Testing our Server-Client model implementation
1. Run the server locally by entering ```./server.out 3333 < TigerZone_ServerCommands2``` into the terminal
   [TigerZone_ServerCommands] (https://github.com/Doug0855/TigerZone/blob/master/TigerZone_ServerCommands) can be found in our repo along with other mock server commands
2. On another terminal run the the TigerZone™ implementation by entering     
    ```./tiger.out localhost 3333 TIGERZONE TEAMJ IAMJ ```

Note: The Challenge will end very quickly as only a few moves are executed. The mock server tests the client server communication flow logic by sending mock commands. Some of the commands are erronous and this test does not check for syntactically correct commands from either the server or client. This test will test that the Network Protocol is followed correctly. 
