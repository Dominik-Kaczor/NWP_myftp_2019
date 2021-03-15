/*
** EPITECH PROJECT, 2020
** mystrcut
** File description:
** include
*/

#ifndef MY_STRUCT
#define MY_STRUCT

typedef struct {
    char *cmd;
    int val;
} cmd_struct_t;

static const cmd_struct_t list_cmd[] = {
    { "USER", 1 },
    { "PASS", 2 },
    { "CWD", 3 },
    { "CDUP\r\n", 4 },
    { "QUIT\r\n", 5 },
    { "PORT", 6 },
    { "PASV\r\n", 7 },
    { "STOR", 8 },
    { "RETR", 9 },
    { "LIST", 10 },
    { "DELE", 11 },
    { "PWD\r\n", 12 },
    { "HELP", 13 },
    { "NOOP\r\n", 14 },
    { "HELP\r\n", 15 },
    { "LIST\r\n", 16 },
    { "PASS\r\n", 17 }
};

typedef struct client_s {
    int fd;
    char *pwd;
    char *name;
    bool loged;
    bool active;
} client_t;

typedef struct server_s {
    int server_fd;
    struct sockaddr_in address;
    int addrlen;
    char *home_directory;
} server_t;

typedef struct reading_s {
    int valread;
    fd_set readfds;
    char *defaut_direct;
    int activity;
    int sd;
    client_t client[10];
} reading_t;

#endif /* !MY_STRUCT */
