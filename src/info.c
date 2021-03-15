/*
** EPITECH PROJECT, 2020
** info
** File description:
** display info
*/

#include "my_ftp.h"

void display_pwd(client_t *client, int user)
{
    char gui = 34;

    if (client[user].loged == true) {
    write(client[user].fd, "257 ", 4);
    write(client[user].fd, &gui, 1);
    write(client[user].fd, client[user].pwd, strlen(client[user].pwd));
    write(client[user].fd, &gui, 1);
    write(client[user].fd, "\r\n", 2);
    } else {
        write(client[user].fd, "530 Need account for login.\r\n", 29);
    }
    return;
}

void display_info_next(client_t *client, int user, char *cmd)
{
    if (strcmp(cmd, "PASV\r\n") == 0)
        write(client[user].fd, "214 PASV Enable passive mode\r\n", 30);
    if (strcmp(cmd, "STOR\r\n") == 0)
        write(client[user].fd, "214 STOR Upload file from client\r\n", 34);
    if (strcmp(cmd, "RETR\r\n") == 0)
        write(client[user].fd, "214 RETR Download file\r\n", 24);
    if (strcmp(cmd, "LIST\r\n") == 0)
        write(client[user].fd, "214 LIST List files in the current\r\n", 36);
    if (strcmp(cmd, "DELE\r\n") == 0)
        write(client[user].fd, "214 DELE Delete file on the server\r\n", 36);
    if (strcmp(cmd, "PWD\r\n") == 0)
        write(client[user].fd, "214 PWD Print working directory\r\n", 33);
    if (strcmp(cmd, "QUIT\r\n") == 0)
        write(client[user].fd, "214 QUIT Disconnection\r\n", 24);
    if (strcmp(cmd, "NOOP\r\n") == 0)
        write(client[user].fd, "214 NOOP Do nothing\r\n", 21);
    return;
}

void display_info_cmd(client_t *client, int user, char *cmd)
{
    if (client[user].loged == false) {
        write(client[user].fd, "530 Need account for login.\r\n", 29);
        return;
    }
    if (strcmp(cmd, "USER\r\n") == 0)
        write(client[user].fd, "214 USER Specify authentication\r\n", 33);
    if (strcmp(cmd, "PASS\r\n") == 0)
        write(client[user].fd, "214 PASS password for authentication\r\n", 38);
    if (strcmp(cmd, "CWD\r\n") == 0)
        write(client[user].fd, "214 CWD Change working directory\r\n", 34);
    if (strcmp(cmd, "CDUP\r\n") == 0)
        write(client[user].fd, "214 CDUP Change to parent\r\n", 25);
    if (strcmp(cmd, "QUIT\r\n") == 0)
        write(client[user].fd, "214 QUIT Disconnection\r\n", 24);
    if (strcmp(cmd, "PORT\r\n") == 0)
        write(client[user].fd, "214 PORT Enable active mode\r\n", 29);
    display_info_next(client, user, cmd);
    return;
}

void display_cmd_help(client_t *client, int user)
{
    if (client[user].loged == false) {
        write(client[user].fd, "530 Need account for login.\r\n", 29);
        return;
    }
    write(client[user].fd, "214 Commands may be abbreviated:\r\n", 34);
    write(client[user].fd, "USER, PASS, CWD, CDUP, QUIT, PORT\n", 33);
    write(client[user].fd, "PASV, STOR, RETR, LIST, DELE, PWD\n", 33);
    write(client[user].fd, "HELP, NOOP\r\n", 12);
    write(client[user].fd, "214 Help message.\r\n", 19);
    return;
}
