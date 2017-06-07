/*
** main.c for PSU_2016_myftp in /home/enguerrand/delivery/
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Fri May 12 15:48:14 2017 Enguerrand Allamel
** Last update Sun May 21 18:15:08 2017 Allamel Enguerrand
*/

#include "../includes/my_ftp.h"

static int	put_args_in_server_info(t_ftp_server_info	*server_info,
					char			*av1,
				  	char			*av2)
{
  int		port;

  if ((port = atoi(av1)) <= 0)
    {
      printf("Usage: port only > 0\n");
      return (0);
    }
  server_info->port = (size_t)port;
  if (!(realpath(av2, server_info->path)))
    return (-1);
  return (1);
}

int			main(int ac, char **av)
{
  t_ftp_server_info	server_info;

  if (ac != 3 || !av[1] || !av[2])
    {
      printf("Usage: %s port path\n", av[0]);
      return (EXIT_FAILURE);
    }
  else if (put_args_in_server_info(&server_info, av[1], av[2]) != 1)
    return (EXIT_FAILURE);
  return (accept_client(&server_info));
}
