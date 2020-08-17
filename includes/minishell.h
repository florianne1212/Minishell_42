/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/08/17 14:20:14 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <dirent.h>
# include <sys/errno.h>
# include <string.h>
# include <fcntl.h>
# include "libft.h"

typedef enum
{
	TT_STRING		= 0b0000001,
	TT_PIPE			= 0b0000010,
	TT_APPEND		= 0b0000100,
	TT_OUT			= 0b0001000,
	TT_IN			= 0b0010000,
	TT_SEMICOLOM	= 0b0100000,
	TT_END			= 0b1000000
} t_token_type;

typedef struct
{
	t_token_type type;
	size_t start;
	size_t end;
	char *str;
} t_token;

typedef struct	s_list_env
{
	char		*name;
	char		*value;
	struct s_list_env	*next;
}				t_list_env;

typedef struct s_lex
{
	int			nb_words;
	int			count;
	int			e;
	int			j;
	t_token		**tokens;
}				t_lex;

/*
**typedef struct	s_simple_command
**{
**	int			command; //nom commande argument 0
**	int			num_arg;
**	char 		**arguments;
**	char		*outfile;
**	char		*infile;
**}				t_simple_command;
*/

typedef enum
{
	FALSE, TRUE
} t_bool;

typedef struct
{
	char *path;
	int fd;
	int error;
} t_file;

typedef struct	s_command
{
	char	*exec;
	char	**argv;
	char	**cmd_arg;
	pid_t	pid;
	t_bool	pipe;
	t_file  in;
	t_file  out;
	t_bool  append;
}				t_command;

typedef struct	s_shell
{
	//changements pour tester
	int tmpin; //a mettre dans global
	int tmpout; //a mettre dans global
	int fdin; //a mettre dans global
	int fdout; //a mettre dans global
	int infile; //le dernier infile du pipe
	int outfile; //le dernier outfile du pipe
	int cmd_index;
	int piping_index;
	int running;
	//fin changement pour tester

	char		**envirron; //tableau similaire a "environ", a mettre a null++
	//en fin de programme , appeler env_destroy_array, sinon leaks
	int			retour; //echo $?
	char		**line;
	int			error;
	t_lex		*lex;
	t_list_env	*list_env;
	t_command	*cmd;
	int			fd;//probablement a enlever mais utile actuellemet
}				t_shell;

int		global_retour;

/*
** cotrol.c
*/
void			manage_control();
void			control_c(int i);
void			control_back(int i);

//fonction que tu as peut etre deja :
t_list_env		*add_link(t_list_env *list, char *str);
void			print_list(t_list_env *list);

char 	*ft_getenv(t_list_env *env, const char *name);
int		ft_putenv(t_list_env **env, char *string);
int		ft_unsetenv(t_list_env **env, const char *name);
int		ft_setenv(t_list_env **env, const char *name, const char *value,
				int overwrite);

/*
// errno_gestion.c
*/
char		*errno_return_str(int errnocode, char *return_value);
int			errno_return_int(int errnocode, int return_value);
void		split_destructor(char **split);
char		*destroy_split_errno_ret_str(char **split, int errnocode, char *ret);

/*
// env_list_gestion.c
*/
void		env_variable_destructor(t_list_env *env);
t_list_env	*new_env_variable(char *str);
void		ft_lstadd_front_env(t_list_env **alst, t_list_env *env);
void		ft_list_remove_if_env(t_list_env **begin_list, void *content_ref,
				int (*cmp)(), void (*free_fct)(t_list_env *));
t_list_env	*ft_list_find_env(t_list_env *begin_list, void *content_ref,
				int (*cmp)());
/*
// builtin_env.c
*/
int			builtin_env(t_shell *glob, int fd, char **arg);

/*
// builtin_pwd.c
*/
int			builtin_pwd(t_shell *glob, int fd, char **arg);

/*
// builtin_echo.c
*/
int			builtin_echo(t_shell *glob, int fd, char **arg);

/*
// builtin_export.c
*/
int			builtin_export(t_shell *glob, int fd, char **arg);

/*
// builtin_unset.c
*/
int			builtin_unset(t_shell *glob, int fd, char **arg);

/*
// builtin_cd.c
*/
int			builtin_cd(t_shell *glob, int fd, char **arg);
int			cd_error(char *str, int ret, char *oldpath, char *newpath);
int			cd_home(t_list_env *env);
int			cd_back(t_list_env *env, int fd);
int			cd_abs_path(t_list_env *env, char *newpath);

/*
// builtin_exit.c
*/
int builtin_exit(t_shell *glob, int fd, char **arg);

/*
// env_create_array.c
*/
char	**env_create_array(t_list_env *env, char **envirron);
char	*create_str_env(char *name, char *value);
char	**destroy_and_errno_ret(char **ret, char **envirron, int errnb);
void	env_destroy_array(char **envirron);
int		ft_list_env_size(t_list_env *begin_list);

/*
**change_rel_to_abs.c
*/
char		*change_rel_to_abs(char *rel);

/*
**change_rel_to_abs_utils.c
*/
char		*path_free_data(t_list *list, char **str_array, char *ret);
char		*path_create_data(char *rel, char ***relative, t_list **absolute);
void		delete_list_first_elem(t_list **beginlist);
int			create_path_list(t_list **abs, char **rel);
char		*create_abs_str(t_list *absolute);

/*
** ft_run_commands.c
*/
int ft_run_commands(t_shell *glob);

/*
** ft_run_simple_command.c
*/
int		check_and_run_builtin(t_shell *glob, char **arg);
char	*create_command_path(char *env_path, char *command);
char	*ft_search_env_path(char *env_paths, char *command);
int		path_for_execve(char *file, char **path, char *env_path);
int		ft_run_simple_command(t_shell *glob, int i, char *env_path);

/*
** ft_run_simple_command2.c
*/
int		not_a_command(char *command, char *str);
void	ft_change_case_instruction(char *instruction);
int		nbr_of_path(char **paths);
char 	*free_path_null(char **path);

/*
** check_redir_simple_command.c
*/
void	check_stdout_simple(t_shell *glob, int i);
void 	check_stdin_simple(t_shell *glob, int i);
void	simple_redirection(t_shell *glob, int i);
void	restore_in_out_simple(t_shell *glob);

/*
**var_env.c
*/
char	*find_value(char *str);
char	*find_name(char *str);
void	sort_envp(char **envp, t_shell *glob);

/*
** lexer.c
*/
int		lexe_line(char *line, t_shell *glob);
void	clean_lexer(t_shell *glob);
int			nbr_words(char const *s, t_shell *glob);

/*
** funct_lexer.c
*/
void	put_pipe(int *index, char *s, t_shell *glob);
void	put_input(int *index, char *s, t_shell *glob);
void	put_output(int *index, char *s, t_shell *glob);
void	put_semicolon(int *index, char *s, t_shell *glob);
void	put_append(int *index, char *s, t_shell *glob);

/*
** lexer_s_quote.c
*/
void	put_string(int *idx, char *s, t_shell *glob);

/*
** funct_normal.c
*/
void	put_normal(int *idx, char *s, t_shell *glob);
char	*env_finder(char *s, int i, t_shell *glob);

/*
** lexer_d_quote.c
*/
void	put_d_quote(int *idx, char *s, t_shell *glob, char c);
char	*join_env(int *idx, char *s, t_shell *glob, char *str);
char	*manage_end(char *str, int *idx, char *s, int *j);

/*
** manage_array.c
*/
int		ft_strlen_array(char **s);
char	**add_to_array(char **s1, char *s2);
char	**add_front_to_array(char **s1, char *s2);

/*
** parsing.c
*/
int		parser(t_shell *glob, int cmd_index);

/*
** validate_line.c
*/
int		validate(t_shell *glob, int *cmd_count);

/*
** init.c
*/
void	init_lex(t_shell *glob, char *line);
void	init_cmd(t_shell *glob, int cmd_count);

int			lex_and_parse(char *line, t_shell *glob);

int		fork_and_run_cmd(t_shell *glob, char *path, int i, char **env);

char		*ft_strjoin_free(char *s1, char *s2);

#endif
