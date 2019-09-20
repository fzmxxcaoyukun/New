# New
Code is not working right now.
The example is in Ti resource exploerer/software/simplelinkMsp432E4SDK/Examples/Development Tools/MSP432E401Y launchpad/Network Service/udpecho/TI-RTOS/CSS complier.
1)Download this example and import to the IDE.
2)Replace the code in "udpEcho.c" with the code in the attched file.
If the server is run on another computer, the  ip address in the board code need to be changed. gethostbyname() function didn't work on the board.
serv_addr.sin_addr.s_addr=inet_addr("143.167.229.255");//change the ip address to the server ip address used
