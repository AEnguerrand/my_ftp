/*
** utils.c for PSU_2016_myftp in /home/enguerrand/delivery/PSU_2016_myftp/
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Sat May 13 18:03:16 2017 Enguerrand Allamel
** Last update Sun May 21 17:37:17 2017 Allamel Enguerrand
*/

#include "../includes/my_ftp.h"

char	*replace_char(const char *str, char c, char a)
{
  int	i;
  char	*res;

  i = 0;
  if (!str)
    return (NULL);
  else if (!(res = strdup(str)))
    return (NULL);
  while (res && res[i])
    {
      if (res[i] == c)
	res[i] = a;
      i += 1;
    }
  return (res);
}

const char	*get_pos_args(const char *cmd)
{
  const char	*pos;

  if (!cmd)
    return (NULL);
  else if (!(pos = strstr(cmd, " ")))
    return (NULL);
  else if (pos && (*pos != '\0')  && (*(pos + 1) != '\0'))
    return (pos + 1);
  return (NULL);
}

uint32_t	get_addr_ip(int fd, struct sockaddr_in *addr)
{
  socklen_t	socklen;

  socklen = sizeof(*addr);
  if (getsockname(fd, (struct sockaddr *)addr, &socklen) == 1)
    return (-1);
  return (addr->sin_addr.s_addr);
}

void	init_client_data_port(t_ftp_client_data	*client_data,
			      const char	*cmd)
{
  char	*str[7];
  char	buff[1024];

  if (!(cmd = get_pos_args(cmd)) ||
      !(str[0] = strdup(cmd)) ||
      !(str[1] = strtok(str[0], ",")) ||
      !(str[2] = strtok(NULL, ",")) ||
      !(str[3] = strtok(NULL, ",")) ||
      !(str[4] = strtok(NULL, ",")) ||
      !(str[5] = strtok(NULL, ",")) ||
      !(str[6] = strtok(NULL, ",")) ||
      !memset(buff, 0, 1024) ||
      sprintf(buff, "%s.%s.%s.%s", str[1], str[2], str[3], str[4]) <= 0)
    return ;
  client_data->server.addr.sin_addr.s_addr = inet_addr(buff);
  client_data->server.addr.sin_port = htons((atoi(str[5]) * 256) +
					    atoi(str[6]));
}
