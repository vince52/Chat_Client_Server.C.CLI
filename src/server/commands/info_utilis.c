/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** info_utilis
*/

#include "my_teams_srv.h"
#include <stddef.h>

char *get_user_str(user_t *user)
{
    char buff[128] = {0};
    char *user_str = NULL;
    int length = 0;
    int status = is_connected(user);

    sprintf(buff, "username: \"%s\" useruuid: \"%s\" status: \"%d\"\r\n",
        user->user_name, user->user_uuid, status);
    length = strlen(buff);
    user_str = realloc(user_str, (length + 1) * sizeof(char));
    memset(user_str, 0, (length + 1) * sizeof(char));
    strcat(user_str, buff);
    return (user_str);
}

char *get_team_str(team_t *team)
{
    char buff[128] = {0};
    char *team_str = NULL;
    int length = 0;

    sprintf(buff, "teamname: \"%s\" teamuuid: \"%s\" teamdesc: \"%s\"\r\n",
        team->team_name, team->team_uuid, team->team_desc);
    length = strlen(buff);
    team_str = realloc(team_str, (length + 1) * sizeof(char));
    memset(team_str, 0, (length + 1) * sizeof(char));
    strcat(team_str, buff);
    return (team_str);
}

char *get_channel_str(channel_t *channel)
{
    char buff[128] = {0};
    char *channel_str = NULL;
    int length = 0;

    sprintf(buff, "channelname: \"%s\" channeluuid: \"%s\" channeldesc: \"%s\""
        "\r\n", channel->channel_name, channel->channel_uuid,
        channel->channel_desc);
    length = strlen(buff);
    channel_str = realloc(channel_str, (length + 1) * sizeof(char));
    memset(channel_str, 0, (length + 1) * sizeof(char));
    strcat(channel_str, buff);
    return (channel_str);
}




char *get_threads_str(connex_t *user_connex)
{
    char *buff = NULL;
    char *threads_str = NULL;
    char *thread_body = NULL;
    const thread_t *threads = ((channel_t *)(user_connex->context))->threads;
    unsigned int length = 0;

    for (int i = 0; threads != NULL; i++) {
        thread_body = get_thread_body(threads);
        buff = malloc((strlen(thread_body) + 256) * sizeof(char));
        sprintf(buff, "threaduuid: \"%s\" useruuid: \"%s\" time: \"%s\" "
            "threadtitle: \"%s\" body: %s\r\n", threads->thread_uuid,
            threads->user_uuid, threads->timestamp, threads->thread_title,
            thread_body);
        length += strlen(buff);
        threads_str = realloc(threads_str, (length + 1) * sizeof(char));
        if (i == 0) memset(threads_str, 0, (length + 1) * sizeof(char));
        strcat(threads_str, buff);
        get_threads_str_helper(buff, thread_body);
        threads = threads->next;
    }
    return (threads_str);
}

//! Handler called when the user ask for a thread in particular (/info CLI command)
/*!
	\param thread_id a character pointer corresponding to the universally unique id assigned to the thread.
	\param user_id a character pointer corresponding to the universally unique id assigned to the user who created the thread.
	\param thread_timestamp an unsigned integer corresponding to the timestamp of the thread's creation.
	\param thread_title a character pointer corresponding to the thread title.
	\param thread_body a character pointer corresponding to the thread body.
	\return On success, 1 is returned. On error, -1 is returned and errno is set appropriately
*/

char *get_thread_str(thread_t *thread)
{
    char *buff = NULL;
    char *channel_str = NULL;
    int length = 0;
    char *thread_body = get_thread_body(thread);

    buff = malloc((strlen(thread_body) + 256) * sizeof(char));
    sprintf(buff, "threaduuid: \"%s\" useruuid: \"%s\" time: \"%s\""
        " threadtitle: \"%s\" body: %s\r\n", thread->thread_uuid,
        thread->user_uuid, thread->timestamp, thread->thread_title,
        thread_body);
    length = strlen(buff);
    channel_str = realloc(channel_str, (length + 1) * sizeof(char));
    memset(channel_str, 0, (length + 1) * sizeof(char));
    strcat(channel_str, buff);
    return (channel_str);
    return (threads_str);
}