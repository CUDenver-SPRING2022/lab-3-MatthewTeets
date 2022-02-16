// Student: Matthew Teets
// Date:
// Class: CSCI 3800
// Description:

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

// Structure that holds info of config.txt file
struct _configure {
    char port_num[4];
    char ip[14];
};

// This function allows the client to send data to the server
int sendData(char *buffer, int sd, struct sockaddr_in server_address);

int main(int argc, char * argv[]) {
    
    // Struct info for servers 1 - 4
    struct _configure s1 [100];
    struct _configure s2 [100];
    struct _configure s3 [100];
    struct _configure s4 [100];
    
    // Opens config file
    FILE *f = fopen("config.txt", "r");
    char line[250];
    
    // Error checking if file exists
    if (f == NULL)
    {
        printf("Error: No file \n");
    }
    
    // Reads config file into struct members for each server
    fgets(line, sizeof(line), f);
    sscanf(line, "%s\n%s\n", s1[14].ip, s1[4].port_num);
    
    fgets(line, sizeof(line), f);
    sscanf(line, "%s\n%s\n", s2[14].ip, s2[4].port_num);
    
    fgets(line, sizeof(line), f);
    sscanf(line, "%s\n%s\n", s3[14].ip, s3[4].port_num);
    
    fgets(line, sizeof(line), f);
    sscanf(line, "%s\n%s\n", s4[14].ip, s4[4].port_num);
    
    fclose(f); // Closes file when we have what we need
    
    // All socket descriptors
    int sd;
    int sd_2;
    int sd_3;
    int sd_4;
    
    struct sockaddr_in server_address; // Provides address info for datagram server 1
    struct sockaddr_in server_address_2; // Provides address info for datagram server 2
    struct sockaddr_in server_address_3; // Provides address info for datagram server 3
    struct sockaddr_in server_address_4; // Provides address info for datagram server 4
    
    // Variables to hold port numbers and IP addresses read in from the config file
    // Server 1
    int portNumber_1;
    char serverIP_1[29];
    
    // Server 2
    int portNumber_2;
    char serverIP_2[29];
    
    // Server 3
    int portNumber_3;
    char serverIP_3[29];
    
    // Server 4
    int portNumber_4;
    char serverIP_4[29];
    
    // All socket descriptors
    sd = socket(AF_INET, SOCK_DGRAM, 0); // Creates the socket 1
    sd_2 = socket(AF_INET, SOCK_DGRAM, 0); // Creates the socket 2
    sd_3 = socket(AF_INET, SOCK_DGRAM, 0); // Creates the socket 3
    sd_4 = socket(AF_INET, SOCK_DGRAM, 0); // Creates the socket 4
    
    // Gets the IP address and port number from the command line
    // portNumber = strtol(argv[2], NULL, 10); // Converts the string inside argv[2] to a long int
    portNumber_1 = strtol(s1[4].port_num, NULL, 10);
    strcpy(serverIP_1, s1[14].ip);
    
    portNumber_2 = strtol(s2[4].port_num, NULL, 10);
    strcpy(serverIP_2, s2[14].ip);
    
    portNumber_3 = strtol(s3[4].port_num, NULL, 10);
    strcpy(serverIP_3, s3[14].ip);
    
    portNumber_4 = strtol(s4[4].port_num, NULL, 10);
    strcpy(serverIP_4, s4[14].ip);
    
    // Structure containing the address of servers 1-4
    server_address.sin_family = AF_INET; // Sets the address family for the transport address
    server_address.sin_port = htons(portNumber_1); // Changes the portNumber to a network order byte and binds it
    server_address.sin_addr.s_addr = inet_addr(serverIP_1); // Makes the serverIP variable a usable internet address
    
    server_address_2.sin_family = AF_INET;
    server_address_2.sin_port = htons(portNumber_2);
    server_address_2.sin_addr.s_addr = inet_addr(serverIP_2);
    
    server_address_3.sin_family = AF_INET;
    server_address_3.sin_port = htons(portNumber_3);
    server_address_3.sin_addr.s_addr = inet_addr(serverIP_3);
    
    server_address_4.sin_family = AF_INET;
    server_address_4.sin_port = htons(portNumber_4);
    server_address_4.sin_addr.s_addr = inet_addr(serverIP_4);
    
    char buffer[100]; // Stores the message being sent to the servers
    
    for(;;)
    {
        char stop[] = "STOP"; // Used to compare against the user's message
        memset (buffer, '\0', 100); // Sets all characters to '\0'
        printf("\nEnter message: \n"); // Prompts user to enter message
        fgets(buffer, sizeof(buffer), stdin); // Reads entire message user inputs
        buffer[strlen(buffer) - 1] = '\0'; // Gets the message and excludes the null terminator
        printf ("Sending: '%s'\n", buffer); // Displays to the client what is being sent
        
        // If/else statement that determines whether the user wants to close connection to the server.
        if (strcmp(buffer, stop) == 0) // If the user-input is equal to 'STOP' close program
        {
            printf("\nClient program has ended. \n"); // Client ending message
            break; // Breaks out of the for loop and exits the program
            
        } else { // Else continue and send message to server
            printf("The length of the string is %lu bytes. \n\n", strlen(buffer)); // Prints to the console the usigned int length of the string
            
            // Calls 'sendData' function to send message to each server
            sendData(buffer, sd, server_address);
            sendData(buffer, sd_2, server_address_2);
            sendData(buffer, sd_3, server_address_3);
            sendData(buffer, sd_4, server_address_4);
            
        }
    }
    
    close(sd); // Closes the client socket
    return 0;
    
}

int sendData(char *buffer, int sd, struct sockaddr_in server_address){
    int rc = 0;
    
    /*
       All information being sent out to the server :
            sd                                   ->  socket descriptor
            buffer                               ->  data being sent
            strlen(buffer)                       ->  how many bytes of data being sent
            0                                    ->  flags
            (struct sockaddr *) &server_address  ->  TO: address of the server
            sizeof(server_address)               ->  size of the data structure being sent
     */
    
    rc = sendto(sd, buffer, strlen(buffer), 0, (struct sockaddr *) &server_address, sizeof(server_address));
    
    if(rc <= 0)
    {
        printf("ERROR: No bytes were sent to server... \n");
        exit(1);
    }
    
    return(0);
}
