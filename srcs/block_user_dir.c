/*
** block_user_dir.c for PSU_2016_myftp in /home/enguerrand/delivery/
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Fri May 19 18:55:34 2017 Enguerrand Allamel
** Last update Sun May 21 17:02:39 2017 Allamel Enguerrand
*/

#include "../includes/my_ftp.h"

char	*get_path_user(t_ftp_client_info *client_info)
{
  (void)client_info;
  return (getcwd(NULL, 0));
}

char	*get_path_real(t_ftp_client_info *client_info, const char *path)
{
  (void)client_info;
  return (realpath(path, NULL));
}
