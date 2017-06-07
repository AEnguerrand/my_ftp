/*
** send_response.c for PSU_2016_myftp in /home/enguerrand/delivery/
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Fri May 12 18:30:57 2017 Enguerrand Allamel
** Last update Sun May 21 17:21:31 2017 Allamel Enguerrand
*/

#include "../includes/my_ftp.h"

static t_my_ftp_command_func g_command[] =
{
	{"AUTH", &cmd_auth},
	{"USER", &cmd_login_user},
	{"PASS", &cmd_login_pass},
	{"PWD", &cmd_work_dir_pwd},
	{"CWD", &cmd_work_dir_cwd},
	{"CDUP", &cmd_work_dir_cdup},
	{"TYPE I", &cmd_type},
	{"PASV", &cmd_tranfer_type_pasv},
	{"PORT", &cmd_tranfer_type_port},
	{"LIST", &cmd_file_list},
	{"RETR", &cmd_file_retr},
	{"STOR", &cmd_file_stor},
	{"DELE", &cmd_file_dele},
	{"NOOP", &cmd_utils_noop},
	{"HELP", &cmd_utils_help},
	{"QUIT", &cmd_utils_quit},
	{NULL, NULL}
};

static int	compare_command(const char *cmd, const char *text)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  while (cmd && text && cmd[i] && text[j] && cmd[i] == text[j])
    {
      i += 1;
      j += 1;
    }
  if (cmd && cmd[i] == '\0')
    return (1);
  return (0);
}

static int	dispatch_command(t_ftp_client_info	*client_info,
				 const char		*cmd)
{
  int		i;

  i = 0;
  while (cmd && g_command[i].cmd &&
	 compare_command(g_command[i].cmd, cmd) == 0)
    i += 1;
  if (g_command[i].cmd)
    return (g_command[i].func_ptr(client_info, cmd));
  send_response(client_info, 500, "Command not implemented.");
  return (0);
}

int	send_response(t_ftp_client_info	*client_info,
		      int		type,
		      const char	*text)
{
  char	*cmd;

  if (!text || type > 999)
    return (1);
  else if ((!(cmd = malloc(3 + strlen(text) + strlen(END_OF_CMD) + 2))) ||
	   (!memset(cmd, 0, 3 + strlen(text) + strlen(END_OF_CMD) + 2)) ||
	   (sprintf(cmd, "%d %s%s", type, text, END_OF_CMD) <= 0) ||
	   (write(client_info->client.fd, cmd, strlen(cmd)) < 0))
    {
      fprintf(stderr, "FAIL Send command\n");
      if (cmd)
	fprintf(stderr, "CMD [%s]\n", cmd);
      return (1);
    }
  free(cmd);
  if (client_info->is_debug)
    console_log_server_to_client_cmd(client_info->id, type, text);
  return (0);
}

int	read_command(t_ftp_client_info *client_info)
{
  char	*line;
  int	ret;
  char	msg[4096 + 1];

  bzero(msg, 4096 + 1);
  if (read(client_info->client.fd, msg, 4089) <= 0)
    return (1);
  ret = 0;
  if (!(line = strtok(msg, "\r\n")))
    return (1);
  while (ret >= 0 && ret != 20 && line)
    {
      if (client_info->is_debug)
	console_log_client_to_server_cmd(client_info->id, line);
      ret = dispatch_command(client_info, line);
      line = strtok(NULL, "\r\n");
    }
  return (ret);
}

int	send_response_fd(int fd, int type, const char *text)
{
  char	*cmd;

  if (!text || type > 999)
    return (1);
  else if ((!(cmd = malloc(3 + strlen(text) + strlen(END_OF_CMD) + 2))) ||
	   (!memset(cmd, 0, 3 + strlen(text) + strlen(END_OF_CMD) + 2)) ||
	   (sprintf(cmd, "%d %s%s", type, text, END_OF_CMD) <= 0) ||
	   (write(fd, cmd, strlen(cmd)) < 0))
    return (1);
  free(cmd);
  return (0);
}
