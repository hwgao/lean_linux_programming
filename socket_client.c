#include<stdio.h>
#include<string.h>
#include<unistd.h> //write, read, close
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr

int main()
{
    int socket_desc;
    struct sockaddr_in server;
    char *message = NULL;
    char server_reply[2000];

    socket_desc = socket(AF_INET , SOCK_STREAM , 0);

    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }

    server.sin_addr.s_addr = inet_addr("74.125.68.101");
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
    if (connect(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }

    puts("connected");

    // Send some data
    message = "GET / HTTP/1.1\r\n\r\n";
    // if (send(socket_desc, message, strlen(message), 0) < 0)
    if (write(socket_desc, message, strlen(message)) < 0)
    {
        puts("Send failed");
        return 1;
    }
    puts("Data Send");

    //Receive a reply from the server
    // if (recv(socket_desc, server_reply, 2000, 0) < 0)
    if (read(socket_desc, server_reply, 2000) < 0)
    {
        puts("recv failed");
    }

    puts("Reply received");
    puts(server_reply);

    close(socket_desc);

    return 0;
}
