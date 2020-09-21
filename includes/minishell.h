/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/09/13 23:53:55 by lcoiffie         ###   ########.fr       */
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

typedef enum			e_token_type
{
	TT_STRING = 0b0000001,
	TT_PIPE = 0b0000010,
	TT_APPEND = 0b0000100,
	TT_OUT = 0b0001000,
	TT_IN = 0b0010000,
	TT_SEMICOLOM = 0b0100000,
	TT_END = 0b1000000
}						t_token_type;

typedef struct			s_token
{
	t_token_type		type;
	size_t				start;
	size_t				end;
	char				*str;
}						t_token;

typedef struct			s_list_env
{
	char				*name;
	char				*value;
	struct s_list_env	*next;
}						t_list_env;

typedef struct			s_lex
{
	int					nb_words;
	int					count;
	int					e;
	int					j;
	t_token				**tokens;
}						t_lex;

typedef enum			e_bool
{
	FALSE,
	TRUE
}						t_bool;

typedef struct			s_file
{
	char				*path;
	int					fd;
	int					error;
}						t_file;

typedef struct			s_command
{
	char				*exec;
	char				**argv;
	char				**cmd_arg;
	pid_t				pid;
	t_bool				pipe;
	t_file				in;
	t_file				out;
	t_bool				append;
	int					error;
}						t_command;

typedef struct			s_shell
{
	int					tmpin;
	int					tmpout;
	int					fdin;
	int					fdout;
	int					infile;
	int					outfile;
	int					back;
	int					tmp_cmd_index;
	int					cmd_index;
	int					piping_index;
	int					running;
	unsigned char		exit_code;
	int					return_code;
	char				**envirron;
	int					retour;
	char				**line;
	int					error;
	t_lex				*lex;
	t_list_env			*list_env;
	t_command			*cmd;
	int					fd;
	int					signal;
	int					parser_error;
}						t_shell;

int						g_retour;

/*
** control.c
*/
void					manage_control();
void					control_c(int i);
void					control_back(int i);

/*
** var_env.c
*/
t_list_env				*add_link(t_list_env *list, char *str);
void					print_list(t_list_env *list);

/*
** ft_environ_utils.c.c
*/
int						ft_isalnumunderscore(int c);
int						ft_isabashname(char *name);

/*
** ft_environ.c.c
*/
char					*ft_getenv(t_list_env *env, const char *name);
int						ft_putenv(t_list_env **env, char *string);
int						ft_unsetenv(t_list_env **env, const char *name);
int						ft_setenv(t_list_env **env, const char *name,
						const char *value, int overwrite);

/*
** errno_gestion.c
*/
char					*errno_return_str(int errnocode, char *return_value);
int						errno_return_int(int errnocode, int return_value);
void					split_destructor(char **split);
char					*destroy_split_errno_ret_str(char **split,
						int errnocode, char *ret);

/*
** env_list_gestion.c
*/
void					env_variable_destructor(t_list_env *env);
t_list_env				*new_env_variable(char *str);
void					ft_lstadd_front_env(t_list_env **alst, t_list_env *env);
void					ft_list_remove_if_env(t_list_env **begin_list,
						void *content_ref,
						int (*cmp)(), void (*free_fct)(t_list_env *));
t_list_env				*ft_list_find_env(t_list_env *begin_list,
						void *content_ref, int (*cmp)());
/*
** builtin_env.c
*/
int						builtin_env(t_shell *glob, int fd, char **arg);

/*
** builtin_pwd.c
*/
int						builtin_pwd(t_shell *glob, int fd, char **arg);

/*
** builtin_echo.c
*/
int						builtin_echo(t_shell *glob, int fd, char **arg);

/*
** builtin_export.c
*/
int						builtin_export(t_shell *glob, int fd, char **arg);
void					print_value(char *str, int fd);

/*
** builtin_export_2.c
*/
int						check_argi(char *str);
int						check_argi_bis(char *str);
int						ft_putenv_append(t_list_env **env, char *string);
char					*find_name_bis(char *str);

/*
** builtin_export_3.c
*/
void					ft_swap(char **s1, char **s2);
void					ft_list_sort_env(t_list_env **begin_list, int (*cmp)());
void					env_sorted(t_shell *glob, int fd);

/*
** builtin_unset.c
*/
int						builtin_unset(t_shell *glob, int fd, char **arg);

/*
** builtin_cd.c
*/
int						builtin_cd(t_shell *glob, int fd, char **arg);
int						cd_error(char *str, int ret, char *oldpath,
						char *newpath);
int						cd_home(t_list_env **env);
int						cd_back(t_list_env **env, int fd);
int						cd_abs_path(t_list_env **env, char *newpath,
						char *arg_path);

/*
** builtin_cd2.c
*/
int						cd_pipe(char **arg);

/*
** builtin_exit.c
*/
int						builtin_exit(t_shell *glob, int fd, char **arg);

/*
** env_create_array.c
*/
char					**env_create_array(t_list_env *env, char **envirron);
char					*create_str_env(char *name, char *value);
char					**destroy_and_errno_ret(char **ret,
						char **envirron, int errnb);
void					env_destroy_array(char **envirron);
int						ft_list_env_size(t_list_env *begin_list);

/*
** change_rel_to_abs.c
*/
char					*change_rel_to_abs(char *rel);

/*
** change_rel_to_abs_utils.c
*/
char					*path_free_data(t_list *list, char **str_array,
						char *ret);
char					*path_create_data(char *rel, char ***relative,
						t_list **absolute);
void					delete_list_first_elem(t_list **beginlist);
int						create_path_list(t_list **abs, char **rel);
char					*create_abs_str(t_list *absolute);

/*
** control2.c
*/
void					control_c_parent_piped(int n);
void					control_back_parent_piped(int n);
void					control_child_piped(int n);

/*
** run_commands.c
*/
void					run_commands(int i, t_shell *glob);
int						pipe_and_run(t_shell *glob, int i, char *env_path);
int						prepare_cmd(t_shell *glob, char **arg, char *env_path,
						char **path);
int						fork_exec_piped_cmd(t_shell *glob, char *path, int i);
int						piped_child_process(char *path, char **arg, char **env);
int						redir_one_piped_cmd(t_shell *glob, int j, int i);
int						tube_output_init(t_shell *glob);
int						restore_in_out_wait_and_return(t_shell *glob, int back,
						int ret, int i);
int						get_piping_index_and_initialize_redirection_in(
						t_shell *glob, int i);
void					initialise_pid(t_shell *glob, int i);

/*
** ft_run_simple_command.c
*/
int						check_and_run_builtin(t_shell *glob, char **arg);
char					*create_command_path(char *env_path, char *command);
char					*ft_search_env_path(char *env_paths, char *command);
int						path_for_execve(char *file, char **path,
						char *env_path);

/*
** ft_run_simple_command2.c
*/
int						not_a_command(char *command, char *str, int ret);
void					ft_change_case_instruction(char *instruction);
int						nbr_of_path(char **paths);
char					*free_path_null(char **path);

/*
** check_redir_simple_command.c
*/
void					check_stdout_simple(t_shell *glob, int i);
void					check_stdin_simple(t_shell *glob, int i);
void					simple_redirection(t_shell *glob, int i);
void					restore_in_out_simple(t_shell *glob);

/*
**gnl2.c
*/
int						gnl2(int fd, char **out);
void					gnl_case_zero(char **line, char **before_eof, int *ret);
char					*recurs(int depth, int *ret, int fd);

/*
**var_env.c
*/
char					*find_value(char *str);
char					*find_name(char *str);
void					sort_envp(char **envp, t_shell *glob);

/*
** lexer.c
*/
int						lexe_line(char *line, t_shell *glob);
void					clean_lexer(t_shell *glob);
int						nbr_words(char const *s, t_shell *glob);

/*
** funct_lexer.c
*/
void					put_pipe(int *index, char *s, t_shell *glob);
void					put_input(int *index, char *s, t_shell *glob);
void					put_output(int *index, char *s, t_shell *glob);
void					put_semicolon(int *index, char *s, t_shell *glob);
void					put_append(int *index, char *s, t_shell *glob);

/*
** lexer_s_quote.c
*/
void					put_string(int *idx, char *s, t_shell *glob);
void					**add_to_2d(void ***of, void *ptr);
char					*add_to_1d(char *of, char ptr);
char					*manage_end(char *str, int *idx, char *s, int *j);

/*
** funct_normal.c
*/
char					*manage_normal(char *s, int *idx, t_shell *glob,
						char *str);
char					*env_finder(char *s, int *i, t_shell *glob);

/*
** lexer_d_quote.c
*/

char					*manage_d_quote(char *s, int *idx, t_shell *glob,
						char *str);
char					*join_env(int *idx, char *s, t_shell *glob, char *str);

/*
** manage_array.c
*/
int						ft_strlen_array(void **s);
char					**add_to_array(char **s1, char *s2);
char					**add_front_to_array(char **s1, char *s2);
char					*ft_strjoin_free(char *s1, char *s2);

/*
** parsing.c
*/
int						parser(t_shell *glob, int cmd_index);

/*
** validate_line.c
*/
int						validate(t_shell *glob, int *cmd_count);

/*
** init.c
*/
void					init_lex(t_shell *glob, char *line);
void					init_cmd(t_shell *glob, int cmd_count);
void					init_and_clean(t_shell *glob, int cmd_count);

/*
** shell_level.c
*/

void					manage_shlvl(t_shell *glob);

int						lex_and_parse(char *line, t_shell *glob);

int						fork_and_run_cmd(t_shell *glob, char *path,
						int i, char **env);
void					clean_cmd(t_shell *glob, int cmd_count);

#endif
