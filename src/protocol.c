/*
** EPITECH PROJECT, 2020
** protocole
** File description:
** all protocole of my_ftp
*/

#include "my_ftp.h"

int logout_info(char *fa, reading_t *reading, int user, char *sa)
{
    switch(decoding(fa)) {
    case 5 :
        close_client(reading->client, reading, user);
        return 0;
    case 14:
        write(reading->client[user].fd, "200 Command okay.\r\n", 19);
        return 0;
    case 13:
        display_info_cmd(reading->client, user, sa);
        return 0;
    case 12:
        display_pwd(reading->client, user);
        return 0;
    case 15:
        display_cmd_help(reading->client, user);
        return 0;
    }
    return 84;
}

int loging(char *fa, reading_t *reading, int user, char *sa)
{
    switch(decoding(fa)) {
    case 1:
        cmd_user(reading->client, user, sa);
        return 0;
    case 2:
        pass_user(reading->client, user, sa);
        return 0;
    case 3:
        move_directory(reading->client, user, re_write(sa));
        return 0;
    case 4: {
        write(reading->client[user].fd, "200 Dump working.\r\n", 19);
        reading->client[user].pwd = reading->defaut_direct;
        return 0;
    } case 17:
        pass_user(reading->client, user, "\r\n");
        return 0;
    }
    return 84;
}

int file_action(char *fa, reading_t *reading, int user, char *sa)
{
    switch(decoding(fa)) {
    case 8:
        return 0;
    case 9:
        return 0;
    case 10:
        display_file(reading->client, user, re_write(sa));
        return 0;
    case 11:
        dele_file(reading->client, user, re_write(sa));
        return 0;
    case 16:
        display_file(reading->client, user, "");
        return 0;
    }
    return 84;
}

int transfer_parameteres(char *fa, reading_t *reading, int user)
{
    switch(decoding(fa)) {
    case 6:
        cmd_port(reading->client, user);
        return 0;
    case 7:
        cmd_pasv(reading->client, user);
        return 0;
    }
    return 84;
}

void protocol(char *str, reading_t *reading, int user)
{
    char *first_arg = strtok(str, " ");
    char *seconde_arg = strtok(NULL, " ");

    if (loging(first_arg, reading, user, seconde_arg) != 84
    || logout_info(first_arg, reading, user, seconde_arg) != 84) {
    } else if (file_action(first_arg, reading, user, seconde_arg) != 84
    || transfer_parameteres(first_arg, reading, user) != 84) {
    } else
        write (reading->client[user].fd, "500 Invalid command\r\n", 21);
    return;
}
