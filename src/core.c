/*
** EPITECH PROJECT, 2020
** core
** File description:
** my_ftp core
*/

#include "my_ftp.h"

int init_mutli(server_t *server, client_t *client, reading_t *reading)
{
    int max_sd = 0;

    FD_ZERO(&reading->readfds);
    FD_SET(server->server_fd, &reading->readfds);
    max_sd = server->server_fd;
    for (int i = 0; i < 10; i++) {
        reading->sd = client[i].fd;
        if (reading->sd > 0)
            FD_SET(reading->sd, &reading->readfds);
        if (reading->sd > max_sd)
            max_sd = reading->sd;
    }
    return max_sd;
}

void multi_threading(server_t *server, client_t *client, reading_t *reading)
{
    int max = init_mutli(server, client, reading);

    reading->activity = select(max + 1, &reading->readfds, NULL, NULL, NULL);
    if (reading->activity < 0 && errno != EINTR)
            printf("select error\n");
    return;
}

int myftp(char **av)
{
    server_t *server = malloc(sizeof(server_t));
    reading_t *reading = malloc(sizeof(reading_t));

    init_client(reading->client, av);
    if (init_serveur(av, server) == 84)
        return 84;
    while (true) {
        multi_threading(server, reading->client, reading);
        if (connection(server, reading->client, reading) == 84)
            return 84;
        read_serveur(reading->client, reading);
    }
    return 0;
}