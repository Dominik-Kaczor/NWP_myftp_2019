/*
** EPITECH PROJECT, 2020
** transfer_params
** File description:
** transfer
*/

#include "my_ftp.h"

void cmd_port(client_t *client, int user)
{
    client[user].active = true;
    write(client[user].fd, "200 Command okay.\r\n", 19);
    return;
}

void cmd_pasv(client_t *client, int user)
{
    int port = rand() % (65000 - 1024) + 1024;

    client[user].active = true;
    dprintf(client[user].fd,
    "227 Entering Passive Mode (127,0,0,1,%d,%d)\r\n",
    port / 256, port % 256);
    return;
}
