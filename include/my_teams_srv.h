/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** my_teams_srv
*/

#ifndef MY_TEAMS_SRV_H_
#define MY_TEAMS_SRV_H_

#include <stddef.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <uuid/uuid.h>


#define MAX_COMMAND_LENGTH 12
#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
#define MAX_PENDING 10

typedef struct {
    char cmd[MAX_COMMAND_LENGTH + 1];
    char **args;
    unsigned int num_args;
} command;

typedef struct thread {
    char thread_title[MAX_NAME_LENGTH + 1];
    uuid_t thread_uuid;
    char thread_init[MAX_BODY_LENGTH + 1];
    struct thread *next;
} thread_t;

typedef struct channel {
    char channel_name[MAX_NAME_LENGTH + 1];
    uuid_t channel_uuid;
    char channel_desc[MAX_DESCRIPTION_LENGTH + 1];
    struct thread *threads;
    struct channel *next;
} channel_t;

typedef struct team {
    char team_name[MAX_NAME_LENGTH + 1];
    char *team_uuid;
    char team_desc[MAX_DESCRIPTION_LENGTH + 1];
    struct channel *channels;
    struct team *next;
} team_t;

typedef struct chat {
    char chat_ref[42];
    struct chat *next;
} chat_t;

typedef struct user {
    char user_name[MAX_NAME_LENGTH + 1];
    uuid_t user_uuid;
    struct chat *chats;
    struct user *next;
} user_t;

typedef struct connex {
    int sock_fd;
    int logged_in;
    char context[4096];
    struct user *user;
    unsigned int team_cxt;
    unsigned int channel_cxt;
    unsigned int thread_cxt;
    struct connex *next;
} connex_t;

static const char *CMDS_STR[] = {"/help", "/login", "/logout", "/users",
    "/user", "/send", "/messages", "/subscribe", "/subscribed", "/unsubscribe",
    "/use", "/create", "/list", "/info"};

static connex_t *connect_list = NULL;

static const char *HELP_MSGS[] = {
    "/help : show help\n",
    "/login [“username”] : set the username used by client\n",
    "/logout : disconnect the client from the server\n",
    "/users : get the list of all users that exist on the domain\n",
    "/user [“user_uuid”] : get information about a user\n",
    "/send [“user_uuid”] [“message_body”] : send a message to a user\n",
    "/messages [“user_uuid”] : list all messages exchange with an user\n",
    "/subscribe [“team_uuid”] : subscribe to the event of a team and its sub"
        " directories (enable reception of all events from a team)\n",
    "/subscribed ?[“team_uuid”] : list all subscribed teams or list all users"
        " subscribed to a teamr\n",
    "/unsubscribe [“team_uuid”] : unsubscribe from a team\n",
    "/use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”] : use specify a"
        " context team/channel/thread\n",
    "/create : based on what is being used create the sub resource\n",
    "/list : based on what is being used list all the sub resources\n",
    "/info : based on what is being used list the current (see below)\n"
};

static const int NUM_CMDS = 14;

static const int MAX_CMD_LENGTH = 4096;

static const int MAX_CMD_NAME_LENGTH = 12;

static user_t *user_list = NULL;

int accept_conn(int server_fd, struct sockaddr_storage *client_addr);

void add_connex(int fd);

void add_user(const char *u_name, const char *u_uuid);

void delete_conn(int fd);

connex_t *find_connex(int fd);

user_t *find_user(const char *user_name, const char *user_uuid);

int get_sock(char *port);

const user_t *get_users();

void help_cmd(int fd, command *cmd);

void launch_server(char *port);

void listen_for_conn(int listen_fd);

void load_users();

void login_cmd(int fd, command *cmd);

void logout_cmd(int fd, command *cmd);

void monitor_fds(int *fd_max, fd_set *read_fds, fd_set *master);

void new_recv(int client_fd, command *cmd);

void respond(int fd, command *cmd);

void send_all(int client_fd, const char *buffer, int len);

void send_error(int error_num, const char *msg, int client_fd);

void user_cmd(int fd, command *cmd);

void users_cmd(int fd, command *cmd);

static void (* const CMD_FUNCS[14])(int fd, command *cmd) = {
    &help_cmd,
    &login_cmd,
    &logout_cmd,
    &users_cmd,
    &user_cmd,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

#endif /* !MY_TEAMS_SRV_H_ */
