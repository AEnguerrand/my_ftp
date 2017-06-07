/*
** my_ftp.h for PSU_2016_myftp in /home/enguerrand/delivery/PSU_2016_myftp/
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Fri May 12 15:49:43 2017 Enguerrand Allamel
** Last update Sun May 21 17:50:54 2017 Allamel Enguerrand
*/

#ifndef PSU_2016_MYFTP_MY_FTP_H
# define PSU_2016_MYFTP_MY_FTP_H

# include <arpa/inet.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>

# define END_OF_CMD "\r\n"

# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"

typedef	struct		s_tcp_tunnel
{
  struct sockaddr_in	addr;
  int			fd;
}			t_tcp_tunnel;

typedef struct	s_ftp_server_info
{
  size_t	port;
  char		path[PATH_MAX + 1];
  t_tcp_tunnel	server;
  size_t	nb_accept;
}		t_ftp_server_info;

typedef enum	e_ftp_mode
{
  FTP_MODE_NOT_SET = 0,
  FTP_MODE_PASV = 1,
  FTP_MODE_ACTIVE = 2
}		t_ftp_mode;

typedef enum	e_ftp_data_cmd
{
  FTP_DATA_CMD_NOT_SET = 0,
  FTP_DATA_CMD_LIST = 1,
  FTP_DATA_CMD_RETR = 2,
  FTP_DATA_CMD_STOR = 3
}		t_ftp_data_cmd;

typedef struct		s_ftp_client_data
{
  t_ftp_mode		mode;
  t_tcp_tunnel		client_control;
  t_tcp_tunnel		client;
  t_tcp_tunnel		server;
  t_ftp_data_cmd	cmd;
  const char		*arg;
}			t_ftp_client_data;

typedef struct		s_ftp_client_info
{
  size_t		id;
  t_tcp_tunnel		client;
  t_ftp_server_info	server_info;
  int			is_debug;
  char			*username;
  int			is_log;
  char			*path_default;
  t_ftp_client_data	client_data_last;
  uint32_t		ip_addr_public;
}			t_ftp_client_info;

typedef struct	s_my_ftp_command_func
{
  const char	*cmd;
  int		(*func_ptr)(t_ftp_client_info	*client_info,
			    const char		*cmd);
}	t_my_ftp_command_func;

typedef struct		s_my_ftp_op_data_func
{
  t_ftp_data_cmd	cmd;
  int			(*func_ptr)(t_ftp_client_data	*client_data_info,
				    const char		*arg);
}			t_my_ftp_op_data_func;

uint32_t	get_addr_ip(int fd, struct sockaddr_in *addr);

int	accept_client(t_ftp_server_info *server_info);

void	error_server_init(char *func, int server_fd);

void	one_client(t_ftp_client_info client_info);

int	send_response(t_ftp_client_info	*client_info,
		      int		type,
		      const char	*text);

int	send_response_fd(int fd, int type, const char *text);

int	read_command(t_ftp_client_info *client_info);

void	console_log_server_to_client_cmd(size_t		id,
					 int		type,
					 const char	*text);

void	console_log_client_to_server_cmd(size_t id, const char *text);

int	check_is_log(t_ftp_client_info *client_info);

int	run_one_client_data(t_ftp_client_info	*client_info,
			    t_ftp_data_cmd	data_cmd,
			    const char		*arg);

t_ftp_client_data	init_client_data_info(t_ftp_client_info	*client_info,
					      size_t		*port,
					      t_ftp_mode	mode,
					      const char	*cmd);

char	*read_check_end(int fd);

char	*get_path_user(t_ftp_client_info *client_info);

char	*get_path_real(t_ftp_client_info *client_info, const char *path);

/*
 * Utils
 */
char		*replace_char(const char *str, char c, char a);
const char	*get_pos_args(const char *cmd);
void		init_client_data_port(t_ftp_client_data	*client_data,
				      const char	*cmd);

/*
 * Command Func
 */
int	cmd_auth(t_ftp_client_info *client_info, const char *cmd);

int	cmd_login_user(t_ftp_client_info	*client_info,
		       const char		*cmd);
int 	cmd_login_pass(t_ftp_client_info	*client_info,
		       const char		*cmd);

int	cmd_work_dir_pwd(t_ftp_client_info *client_info, const char *cmd);
int	cmd_work_dir_cwd(t_ftp_client_info *client_info, const char *cmd);
int	cmd_work_dir_cdup(t_ftp_client_info *client_info, const char *cmd);

int	cmd_type(t_ftp_client_info *client_info, const char *cmd);

int	cmd_tranfer_type_pasv(t_ftp_client_info	*client_info,
			      const char	*cmd);
int 	cmd_tranfer_type_port(t_ftp_client_info	*client_info,
			      const char	*cmd);

int	cmd_utils_noop(t_ftp_client_info *client_info, const char *cmd);
int	cmd_utils_quit(t_ftp_client_info *client_info, const char *cmd);
int	cmd_utils_help(t_ftp_client_info *client_info, const char *cmd);

int	cmd_file_list(t_ftp_client_info *client_info, const char *cmd);
int	cmd_file_retr(t_ftp_client_info *client_info, const char *cmd);
int	cmd_file_stor(t_ftp_client_info *client_info, const char *cmd);
int 	cmd_file_dele(t_ftp_client_info *client_info, const char *cmd);

/*
 * Op Data Func
 */
int	op_data_file(t_ftp_client_data	*client_data_info, const char *arg);
int	op_data_retr(t_ftp_client_data	*client_data_info, const char *arg);
int	op_data_stor(t_ftp_client_data	*client_data_info, const char *arg);

#endif //PSU_2016_MYFTP_MY_FTP_H
