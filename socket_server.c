#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdint.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h> // for threading, link with lpthread

void *connection_handler(void *socket_desc)
{
    int socket = (intptr_t)socket_desc;
    char *msg = "message from thread\n";
    write(socket, msg, strlen(msg));

    close(socket);

    return NULL;
}

int main()
{
    intptr_t socket_desc;

    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        puts("Could not create socket");
    }

    //Prepare the sockaddr_in sturcture
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    //Bind
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("bind failed");
    }

    puts("bind done");

    //Listen
    listen(socket_desc, 3);

    puts("Waiting for incoming connections ...");

    int c = sizeof(struct sockaddr_in);
    struct sockaddr_in client;
    int new_socket;

    while (1)
    {
        new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
        if (new_socket < 0)
        {
            puts("accept failed");
            return 1;
        }

        puts("Connection accepted");
        printf("Client ip is %s, and port is %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        char *message = "Hello Client A\n";
        write(new_socket, message, strlen(message));

        pthread_t sniffer_thread;

        if (pthread_create(&sniffer_thread, NULL, connection_handler, (void*)(intptr_t)new_socket) < 0)
        {
            perror("could not create thread");
            return 1;
        }

        pthread_join(sniffer_thread, NULL);
    }

    return 0;
}
