/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:25:30 by staverni          #+#    #+#             */
/*   Updated: 2025/05/18 10:59:59 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/******************************* INSTRUCTIONS *********************************/

/*	AUTHORISED FUNCTIONS
- dirent.h
	opendir, readdir, closedir
- readline.h
	readline, rl_clear_history, rl_on_new_line,
	rl_replace_line, rl_redisplay, add_history
- stdlib.h
	free, malloc, exit, getenv
- signal.h
	signal, sigaction, sigemptyset, sigaddset, kill
- stdio.h
	printf, perror
- string.h
	strerror
- sys/ioctl.h
	ioctl
- sys/stat.h
	stat, lstat, fstat
- sys/wait.h
	waitpid, wait, wait3, wait4
- termios.h
	tcgetattr, tcsetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
- unistd.h
	write, access, open, read, close
	fork, getcwd, chdir, unlink, execve, dup, dup2, pipe
	isatty, ttyname, ttyslot,
*/

/********************************* INCLUDES ***********************************/

// System includes
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

//libft include
# include "libft.h"

// Local includes
# include "buffer.h"
# include "colors.h"
# include "exec.h"
# include "parsing.h"

/********************************** GLOBALS ***********************************/

extern int	g_exit_status;
extern char	**environ;

/********************************** STRUCTS ***********************************/

typedef struct s_shell
{
	char	*input;
	t_token	*tokens;
	t_list	*env;
	t_cmd	*tree;
}			t_shell;

/********************************** MAIN **************************************/

void		set_signals(void);
void		reset_signals(void);
int			get_input(t_shell *sh);
int			lex_input(t_shell *sh);
int			parse_input(t_shell *sh);
int			exec_input(t_shell *sh);
void		clean_shell(t_shell *sh);
void		exit_shell(t_shell *sh, int status);

/********************************* ENVIRON ************************************/

int			compare_env_name(const void *content, const void *name_ref);
int			is_valid_char(char c);
char		*ft_getenv(char *var, t_list *env);
char		*get_env_var(char *var_start, t_list *env);
char		*env_value(const char *env_string);
char		*env_name(const char *env_string);
char		*resolve_cmd_path(char *cmd_name, t_list *env);
char		*build_env_string(const char *name, const char *value);
t_list		*environ_to_list(void);
char		**list_to_envp(t_list *env);

/********************************* ERRORS *************************************/

void		*token_syntax_error(char *token, size_t len);
void		*print_error_null(char *message);
void		*exec_error(char *exec);
int			access_error(char *file, int mode);

#endif
