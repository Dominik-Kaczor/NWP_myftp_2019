/*
** EPITECH PROJECT, 2020
** main
** File description:
** main
*/

#include "my_ftp.h"

int main(int ac, char **av)
{
    if (check_len(ac, av) == 84)
        return 84;
    if (check_folder(av[2]) == 84)
        return 84;
    if (check_port(av[1]) == 84)
        return 84;
    return (myftp(av));
}
