/*
** EPITECH PROJECT, 2020
** Initialisation
** File description:
** init of core
*/

#include "my_ftp.h"

int init_bind(char **av, server_t *server)
{
    if (bind(server->server_fd, (struct sockaddr *)&server->address,
    sizeof(server->address)) < 0) {
        perror("bind failed");
        return 84;
    }
    if (listen(server->server_fd, 3) < 0) {
        perror("listen");
        return 84;
    }
    server->addrlen = sizeof(server->address);
    server->home_directory = av[2];
    return 0;
}

int init_serveur(char **av, server_t *server)
{
    int opt = 1;

    server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->server_fd == 0) {
        perror("socket failed");
        return 84;
    }
    if (setsockopt(server->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
    &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = htonl(INADDR_ANY);
    server->address.sin_port = htons(atoi(av[1]));
    if (init_bind(av, server) == 84)
        return 84;
    return 0;
}

void init_client(client_t *client, char **av)
{
    for (int i = 0; i < 10; i++) {
        client[i].fd = 0;
        client[i].loged = false;
        client[i].pwd = av[2];
        client[i].active = false;
        client[i].name = "undefind";
    }
    return;
}
