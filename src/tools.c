/*
** EPITECH PROJECT, 2020
** tools
** File description:
** tools of the my_ftp
*/

#include "my_ftp.h"

void close_client(client_t *client, reading_t *reading, int user)
{
    client[user].active = false;
    client[user].loged = false;
    client[user].name = strdup("undefind");
    client[user].pwd = strdup(reading->defaut_direct);
    write(client[user].fd, "221 Service closing.\r\n", 22);
    close(reading->sd);
    client[user].fd = 0;
    return;
}

void display_help(void)
{
    printf("USAGE: ./myftp port path\n\tport is the port number on which");
    printf(" the server socket listens\n\tpath is the path to the home ");
    printf("directory for the Anonymous user\n");
    return;
}

void read_serveur(client_t *client, reading_t *reading)
{
    char buffer[1025];

    for (int i = 0; i < 10; i++) {
        reading->sd = client[i].fd;
        if (FD_ISSET(reading->sd, &reading->readfds)) {
            reading->valread = read(reading->sd, buffer, 1024);
            if (reading->valread == 0) {
                close(reading->sd);
                client[i].fd = 0;
            } else {
                buffer[reading->valread] = '\0';
                printf("Client %d : %s", i, buffer);
                protocol(buffer, reading, i);
            }
        }
    }
}

int connection(server_t *server, client_t *client, reading_t *reading)
{
    int new_socket;

    reading->defaut_direct = server->home_directory;
    if (FD_ISSET(server->server_fd, &reading->readfds)) {
        if ((new_socket = accept(server->server_fd,
        (struct sockaddr *)&server->address,
        (socklen_t *)&server->addrlen)) < 0) {
            perror("accept");
            return 84;
        }
        write(new_socket, "220 \r\n", 6);
        for (int i = 0; i < 10; i++) {
            if (client[i].fd == 0) {
                client[i].fd = new_socket;
                break;
            }
        }
    }
    return 0;
}

int decoding(char *message)
{
    int size = (sizeof(list_cmd)/sizeof(cmd_struct_t));

    for (int i = 0; i < size; i++) {
        if (strcmp(list_cmd[i].cmd, message) == 0)
            return list_cmd[i].val;
    }
    return -1;
}
