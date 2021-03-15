/*
** EPITECH PROJECT, 2020
** loging
** File description:
** cmd of loging
*/

#include "my_ftp.h"

char *my_strcat(char *one, char *two)
{
    char *final = malloc(sizeof(char) * (strlen(one) + strlen(two) + 1));
    int i = 0;
    int k = 0;

    for (; one[i]; i++)
        final[i] = one[i];
    for (; two[k]; i++, k++)
        final[i] = two[k];
    final[i] = '\0';
    return (final);
}

char *re_write(char *str)
{
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        if (str[i] == '\r') {
            str[i] = '\0';
            return str;
        }
    }
    return str;
}

void cmd_user(client_t *client, int user, char *arg)
{
    client[user].name = strdup(arg);
    write(client[user].fd, "331 User name okay, need password.\r\n", 36);
    return;
}

void pass_user(client_t *client, int user, char *arg)
{
    if (strcmp(arg, "undefind") == 0) {
        write(client[user].fd, "332 Need account for login.\r\n", 29);
        return;
    }
    if (strcmp(arg, "\r\n") == 0
    && strcmp(client[user].name, "Anonymous\r\n") == 0) {
        write(client[user].fd, "230 User logged in, proceed.\r\n", 30);
        client[user].loged = true;
    } else if (strcmp(client[user].name, "Anonymous\r\n") == 0)
        write(client[user].fd, "530 Bad Password\r\n", 18);
    else
        write(client[user].fd, "530 Need account for login.\r\n", 29);
    return;
}

void move_directory(client_t *client, int user, char *arg)
{
    char *path = my_strcat(client[user].pwd, arg);

    if (client[user].loged == false) {
        write(client[user].fd, "530 Need account for login.\r\n", 29);
        return;
    }
    if (path[strlen(path) - 1] != '/')
        path = my_strcat(path, "/");
    if (check_folder(path) == 0) {
        client[user].pwd = strdup(path);
        dprintf(client[user].fd, "250 Requested file.\r\n");
    } else
        dprintf(client[user].fd, "550 Bad moving in the directory.\r\n");
    return;
}
