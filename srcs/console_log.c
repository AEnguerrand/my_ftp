/*
** console_log.c for PSU_2016_myftp in /home/enguerrand/delivery/
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Sat May 13 14:43:56 2017 Enguerrand Allamel
** Last update Sun May 21 17:54:12 2017 Allamel Enguerrand
*/

#include "../includes/my_ftp.h"

void	console_log_server_to_client_cmd(size_t		id,
					 int		type,
					 const char	*text)
{
  printf("[FTP Server][Client %ld] %s[Response] %d %s%s\n",
	 id,
	 ANSI_COLOR_GREEN,
	 type,
	 text,
	 ANSI_COLOR_RESET);
}

void	console_log_client_to_server_cmd(size_t id, const char *text)
{
  printf("[FTP Server][Client %ld] %s[Command] %s%s\n",
	 id,
	 ANSI_COLOR_CYAN,
	 text,
	 ANSI_COLOR_RESET);
}
