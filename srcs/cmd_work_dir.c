/*
** cmd_work_dir.c for PSU_2016_myftp in /home/enguerrand/delivery/
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Sat May 13 15:54:40 2017 Enguerrand Allamel
** Last update Sun May 21 17:17:19 2017 Allamel Enguerrand
*/

#include "../includes/my_ftp.h"

int	cmd_work_dir_pwd(t_ftp_client_info *client_info, const char *cmd)
{
  char	*res;
  char	*path;

  (void)cmd;
  if (!check_is_log(client_info))
    return (1);
  else if (!(path = get_path_user(client_info)) ||
	  (!(res = malloc(sizeof(path) + 1024))) ||
	  (!memset(res, 0, sizeof(path) + 1024)) ||
	  (sprintf(res, "\"%s\" is the current directory", path) <= 0))
    return (-1);
  send_response(client_info, 257, res);
  free(res);
  free(path);
  return (0);
}

int		cmd_work_dir_cwd(t_ftp_client_info	*client_info,
				 const char		*cmd)
{
  char		*path;
  const char	*ph;

  if (!check_is_log(client_info))
    return (1);
  else if (!get_pos_args(cmd))
    {
      send_response(client_info, 550,
		    "Need arguments for CWD.");
      return (1);
    }
  if (!(ph = get_pos_args(cmd)) ||
      !(path = get_path_real(client_info, ph)) ||
      (chdir(path) != 0))
    {
      send_response(client_info, 550,
		   "Requested action not taken. CPWD not good.");
      return (1);
    }
  send_response(client_info, 250, "Directory successfully changed.");
  free(path);
  return (0);
}

int	cmd_work_dir_cdup(t_ftp_client_info 	*client_info,
			  const char		*cmd)
{
  char	*path;

  (void)cmd;
  if (!check_is_log(client_info))
    return (1);
  if (!(path = realpath(get_path_real(client_info, ".."), NULL)) ||
      (chdir(path) != 0))
    {
      send_response(client_info, 550,
		    "Requested action not taken. CDUP not good.");
      return (1);
    }
  send_response(client_info, 250, "Directory successfully changed.");
  free(path);
  return (0);
}
