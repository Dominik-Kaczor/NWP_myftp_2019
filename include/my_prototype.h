/*
** EPITECH PROJECT, 2020
** myprototype
** File description:
** include
*/

#ifndef MY_PROTO
#define MY_PROTO

#include "my_struct.h"

int check_folder(char *);
int check_len(int, char **);
int check_port(char *);
void display_help(void);
int myftp(char **);
int connection(server_t *, client_t *, reading_t *);
void read_serveur(client_t *, reading_t *);
void protocol(char *, reading_t *, int);
int decoding(char *);
void pass_user(client_t *, int, char *);
void cmd_user(client_t *, int, char *);
void move_directory(client_t *, int, char *);
void display_pwd(client_t *, int);
void display_info_cmd(client_t *, int, char *);
void display_cmd_help(client_t *, int);
void close_client(client_t *, reading_t *, int);
void init_client(client_t *, char **);
int init_serveur(char **, server_t *);
int init_bind(char **, server_t *);
void display_file(client_t *, int, char *);
void dele_file(client_t *, int, char *);
char *re_write(char *);
void cmd_port(client_t *client, int user);
void cmd_pasv(client_t *client, int user);
char *my_strcat(char *, char *);

#endif /* !MY_PROTO */
