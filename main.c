//
//  main.c
//  VSCP-UDP-CLIENT
//
//  Created by Gerhard Sabeditsch on 07.05.17.
//  Copyright © 2017 Gerhard. All rights reserved.
//

/************* UDP CLIENT CODE *******************/

/* INFORMATION OF THE STRUCTS */

/*
 #include <netinet/in.h>
 
 struct sockaddr_in {
 short            sin_family;   // e.g. AF_INET
 unsigned short   sin_port;     // e.g. htons(3490)
 struct in_addr   sin_addr;     // see struct in_addr, below
 char             sin_zero[8];  // zero this if you want to
 };
 
 struct in_addr {
 unsigned long s_addr;  // load with inet_aton()
 };
*/


#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

/*VSCP UDP OFFSET DEFINES*/
#define VSCP_UDP_POS_HEAD    0
#define VSCP_UDP_POS_CLASS   1
#define VSCP_UDP_POS_TYPE    3
#define VSCP_UDP_POS_GUID    5
#define VSCP_UDP_POS_SIZE    21
#define VSCP_UDP_POS_DATA    23
#define VSCP_UDP_POS_CRC     len - 2


/*
 IANA Ports for VSCP
 UDP    9598
 TCP    9598
 */

int main(){
    int clientSocket, portNum, nBytes;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    
    portNum = 9598;
    
    
    /*Create UDP socket*/
    clientSocket = socket(PF_INET, SOCK_DGRAM, 0);
    
    /*Configure settings in address struct*/
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(portNum);
    
    
//    inet_aton("127.0.0.1", &serverAddr.sin_addr);  //stores the IP-Address in "serverAddr.sin_addr.s_addr"
    
//    inet_aton("192.168.17.1", &serverAddr.sin_addr);  //stores the IP-Address in "serverAddr.sin_addr.s_addr"
    inet_aton("172.16.151.1", &serverAddr.sin_addr);  //stores the IP-Address in "serverAddr.sin_addr.s_addr"
//    inet_aton("127.0.0.1", &serverAddr.sin_addr);  //stores the IP-Address in "serverAddr.sin_addr.s_addr"

    
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    
    /*Initialize size variable to be used later on*/
    addr_size = sizeof serverAddr;
    
    while(1){
        
        
        //printf("Type a sentence to send to server:\n");
        //fgets(buffer,1024,stdin);
        //printf("You typed: %s",buffer);

        
        strncpy(buffer, "VSCP Daemon @ FF:FF:FF:FF:FF:FF:FF:EE:00:0C:29:4E:9A:9C:00:00", sizeof(buffer));
        
        printf("You typed: %s \n",buffer);
        
        nBytes = (int) strlen(buffer) + 1;
        
        /*Send message to server*/
        sendto(clientSocket,buffer,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);
        
        //Delete the buffer
        memset(buffer, 0, sizeof buffer);
        
        int i,ii;

        
        for(i=0; i<1000000; i++) {
            for(ii=0; ii<1000; ii++) {
                
            }
            
        }
        
        printf("----loop---- \n");
        
        
        /*Receive message from server*/
        //nBytes = (int) recvfrom(clientSocket,buffer,1024,0,NULL, NULL);
        
        //printf("Received from server: %s\n",buffer);
        
    }
    
    return 0;
}
