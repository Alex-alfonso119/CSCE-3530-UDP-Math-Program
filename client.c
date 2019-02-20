/*
    Alexander Alfonso (aja0167) - CSCE 3530 PROGRAM 3 client
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
 
#define SERVER "129.120.151.94"
#define MAXSIZE 1024
 
void die(char *s)
{
    perror(s);
    exit(1);
}
 
int main(int argc, char *argv[])
{
    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);
    char buf[MAXSIZE];

    if(argc != 2)
    {
        printf("usage: ./executable port\n");
        exit(0);
    }
    int portno = atoi(argv[1]);
 
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
 
    memset((char *) &si_other, 0, sizeof(si_other));

    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(portno);
     
    if (inet_aton(SERVER , &si_other.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
 
    printf("client %d\n", portno);
    while(1)
    {
        memset(buf,'\0', MAXSIZE);

        printf("exprsn: ");
        gets(buf);
         
        //send the message
        if (sendto(s, buf, MAXSIZE, 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }

        if(strncmp(buf, "quit\n", strlen(buf)) == 0)
        {
            printf("terminating program...\n");
            close(s);
            exit(0);
        }
         
        //receive a reply and print it
        //clear the buffer by filling null, it might have previously received data
        memset(buf,'\0', MAXSIZE);

        //try to receive some data, this is a blocking call
        if (recvfrom(s, buf, MAXSIZE, 0, (struct sockaddr *) &si_other, &slen) == -1)
        {
            die("recvfrom()");
        }

        puts(buf);
    }
 
    close(s);
    return 0;
}