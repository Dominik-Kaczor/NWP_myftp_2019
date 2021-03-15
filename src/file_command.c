/*
** EPITECH PROJECT, 2020
** file_commande
** File description:
** File action commands
*/

#include "my_ftp.h"

void dele_file(client_t *client, int user, char *arg)
{
    int returnCode = -1;

    if (client[user].loged == true) {
        returnCode = remove(strcat(client[user].pwd, arg));
        if (returnCode != 0 )
            write(client[user].fd, "550 cannot remove the file.\r\n", 38);
        else
            write(client[user].fd,
            "250 Requested file action completed.\r\n", 38);
    } else
        write(client[user].fd, "530 Need account for login.\r\n", 29);
    return;
}

void display_ls(client_t *client, int user, FILE *fp)
{
    char path[1024];
    int first = 0;

    dprintf(client[user].fd, "150 File status okay; about\r\n");
    while (fgets(path, 1024, fp) != NULL) {
        if (first != 0)
            dprintf(client[user].fd, "%s", path);
        else
            first = 1;
    }
    if (pclose(fp) == 0)
        dprintf(client[user].fd, "226 Closing data connection.\r\n");
    else
        dprintf(client[user].fd, "500 Bas closing data transfer\r\n");
    return;
}

void display_file(client_t *client, int user, char *arg)
{
    FILE *fp;
    char *ls = my_strcat("ls -l ", client[user].pwd);

    ls = my_strcat(ls, arg);
    if (client[user].loged == false) {
        write(client[user].fd, "530 Need account for login.\r\n", 29);
        return;
    } else if (client[user].active == false) {
        write(client[user].fd, "425 Use PORT or PASV first.\r\n", 29);
        return;
    }
    fp = popen(ls, "r");
    if (fp == NULL) {
        dprintf(client[user].fd, "500 Bas closing data transfer\r\n");
        return;
    }
    display_ls(client, user, fp);
    return;
}
