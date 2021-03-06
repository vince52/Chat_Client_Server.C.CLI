/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** help_cmd
*/

#include "help_cmd.h"
#include "my_teams_srv.h"
#include "return_codes.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help_cmd(int fd, command_t *cmd)
{
    char *rsp = NULL;
    connex_t *user_connex = find_connex(fd);
    unsigned int rsp_len = 0;

    rsp_len = strlen("START_RSP\r\n000\r\n") + strlen(HELP_MSG) +
        strlen("END_RSP\r\n");
    rsp = calloc(rsp_len, sizeof(char));
    sprintf(rsp, "START_RSP\r\n%d\r\n%sEND_RSP\r\n",
        RSP_HELP, HELP_MSG);
    send_direct(user_connex->sock_fd, rsp);
    free(rsp);
}