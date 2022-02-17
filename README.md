# Lab 3
#### Name: Matthew Teets
#### Date: 2/16/22
#### Class: CSCI 3800

#

### **Description:**
This project use a server-client datagram and allows communinication between one client and multiple servers.
For this program to work with multiple servers, the user must have 5 terminal windows open and connected to the csegrid (1 client and 4 servers).
The client program can run on any gnode and work fine. However, the server programs must be ran on gnodes 1-4. 
The config.txt contains the IP addresses of the 4 gnode servers and 4 port numbers. The port numbers are command line arguments that must be      
entered when running the server programs (example below).

#

### **The 2 programs:**
- server3.c
  - Creates and binds a DGRAM socket to the server address
  - Server remains open, listening for datagram packets from the client program
  - Messages from the client is processed and printed to the terminal
  - These steps are looped until the program is manually terminated using Control + C
- client3.c
  - Reads the config file into a struct
  - Creates the socket/address info using the struct
  - Promts the user for a message to send to the server
  - If successfully sent, the message will send to all 4 servers
  - These steps loop until the user sends the message 'STOP' to the servers
    - This will terminate the client’s connection to the servers
    
#

### **How to run:**
- Connect to CSE-grid
  - Example: ssh username@csegrid.ucdenver.pvt
  - Connect 5 terminal windows to this Linux server
- cd to the file containing the c programs, makefile, and config.txt

**Terminal window used to run server3.c**
```
  $ ssh csci-gnode-NUM   //Use this command to get each terminal to the correct gnode number (i.e., csci-gnode-01)
  $ make -f Makefile     // Compiles the c programs
  $ ./server3 [SERVER-PORT-NUMBER]    // Command to run the executable
```
Example: $ ./server3 1101

**Terminal window used to run client3.c**
```
  $ make -f Makefile
  $ ./client3
```
  
  
  
  
