/*
** EPITECH PROJECT, 2020
** error_handling
** File description:
** all error gestion
*/

#include "my_ftp.h"

int check_int(char *nb)
{
    for (int i = 0; nb[i]; i++) {
        if (nb[i] < '0' || nb[i] > '9')
            return 84;
    }
    return 0;
}

int check_folder(char *dir)
{
    struct stat s_stat;
    int nb_error = stat(dir, &s_stat);

    if (nb_error == -1) {
        if (ENOENT == errno) {
            printf("Invalide Stat\n");
            return  84;
        } else {
            perror("stat");
            return 84;
        }
    } else {
        if (S_ISDIR(s_stat.st_mode)) {
            return 0;
        } else {
            printf("The path is not a directory\n");
            return 84;
        }
    }
    return 0;
}

int check_len(int ac, char **av)
{
    if (ac == 3)
        return 0;
    else if (ac == 2 && strcmp(av[1], "-help") == 0) {
        display_help();
        return 84;
    } else {
        printf("Bad number of the arguments\n");
        return 84;
    }
}

int check_port(char *port_s)
{
    int port_i;

    if (check_int(port_s) == 84) {
        printf("The port is not number\n");
        return 84;
    }
    port_i = atoi(port_s);
    if (port_i < 1 || port_i > 65535) {
        printf("Port is invalide\n");
        return 84;
    }
    return 0;
}