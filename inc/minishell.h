/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 14:41:54 by htizi             #+#    #+#             */
/*   Updated: 2022/02/26 11:55:16 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <limits.h>

# define SPACE_FOUND		10
# define QUOTES_UNCLOSED	-1
# define MALLOC_ERR 		-2
# define EXT				-3
# define VAR_FOUND			-4
# define BRACKETS_UNCLOSED	 1
# define SYNTAX_ERR			-7

# define COMMAND_WORK 0
# define WRONG_ARG 1
# define PERMISSION_DENIED 126
# define COMMAND_NOT_FOUND 127
# define PARSING_ERROR 2
# define INVALID_ARG 128
# define MALLOC_ERROR 3
# define HEREDOC ".heredoc"

enum
{
	WORD,
	SL_REDIRECTION,
	DL_REDIRECTION,
	SR_REDIRECTION,
	DR_REDIRECTION,
	PIPE,
	VAR,
	DISPLAY_ONLY,
	ARGS
};

enum e_builtin
{
	NO,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

typedef enum e_export
{
	F_CONCAT,
	F_TRUNC,
	E_TRUNC,
	NONE
}	t_export;

typedef struct s_list
{
	char			*value;
	int				type;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

typedef struct s_args
{
	char			**args_tab;
	int				redir_in;
	int				redir_out;
	t_list			*infiles;
	t_list			*outfiles;
	int				outfile;
	int				infile;
	enum e_builtin	is_builtin;
	int				nb_pipes;
}	t_args;

typedef struct s_node
{
	t_args			*args;
	int				type;
	int				*fd;
	int				fork;
	int				status;
	pid_t			pid;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_main_var
{
	t_list			*list;
	t_node			*nodes;
	char			*line;
}	t_main_var;

typedef struct s_env
{
	char			*key;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	int		exit_status;
	int		last_return;
	pid_t	pid;
	t_env	*env;
	t_env	*export_env;
	char	**envi;
}	t_data;

extern t_data	g_data;

int					lst_delone(t_list **tmp, t_list **list);
char				*get_cmd_path(char *cmd, char **path);
char				**get_paths_tab(char **env);
char				*ft_strcat(char *dest, char *src);
char				*ft_strndup(char *src, int n);
char				*get_opt(char *str);
char				*get_cmd(char *str);
char				*get_cmd_path(char *cmd, char **path);
t_list				*ft_create_elem(char *value);
int					ft_list_push_back(t_list **begin_list, char *value);
void				ft_list_clear(t_list **list);
char				*ms_substr(char const *s, unsigned int start, size_t len);
int					ft_strlen(char *str);
void				print_list(t_list *list);
int					is_op(char *line, int *i, int *len);
int					str_is_valid(char *line);
int					expanser(t_list **list);
int					create_list(t_list **list, char *line);
int					ft_is_space(char c);
char				*ms_strcpyt(char *str, char c);
char				**create_tab(char *line, int *brackets_unclosed);
void				free_tab(char **tab);
void				ft_free_elem(t_list **list);
int					patch_list(t_list **list, int pos, int *brackets_unclosed);
int					closed_quotes(char *line);
int					char_is_valid(char c);
int					is_curly_bracket(char c);
int					del_quotes(t_list **list);
char				*del_quotes_or_brackets(char *str, int *brackets_unclosed);
int					isolate_var_in_list(t_list **list);
int					char_is_valid(char c);
int					is_var(char *line, int *i, int *len);
int					is_pipe(char *line, int *i, int *len);
int					is_redirection(char *line, int *i, int *len);
int					is_quote(char *line, int *i, int *len);
void				clear_type(t_list **patch, int type);
int					type(char *value);
int					fill_tab(char **tab, char *str, int *brackets_unclosed);
int					count_lines(char *line);
char				*del_curly_brackets(char **str);
int					print_brackets_err_msg(int open, int closed);
int					check_curly_brackets(char *str);
int					check_syntax(t_list **list);
int					check_strings_to_merge(t_list **list);
t_list				*ft_list_last(t_list *begin_list);
int					type_is_op(int type);
int					parser(t_list **list, t_node **nodes);
int					ft_node_push_back(t_node **begin_node, int type);
void				ft_clear_nodes(t_node **nodes);
int					init_nodes(t_list **list, t_node **nodes);
int					set_redir(t_node **nodes, t_list **list);
int					set_args_tab(t_node **nodes, t_list **list);
int					ft_list_push_front(t_list **begin_list, char *value);
int					isolate_redir(t_list **list, t_node **nodes);
int					set_fd_lists(t_node **nodes, t_list **list);
int					execve_error(t_node **tmp, t_node **nodes);
int					ft_shlvl(char *cmd);
char				*ft_strchr(const char *s, int c);
void				ft_signal(int signal);
void				ft_putstr_fd(char *s, int fd);
int					reset_types(t_list **list);
int					check_err(int *ret);
int					lexer(char *line, t_list **list, t_node **nodes,
						char **env);
/************** FORKING.C **********************/
int					forking_loop(t_node **nodes, char **env);
int					wait_childs(t_node **nodes);
int					first_fork(t_node *tmp, char **env, t_node **nodes);
int					mid_fork(t_node *tmp, char **env, t_node **nodes);
int					last_fork(t_node *tmp, char **env, t_node **nodes);
int					close_files(t_node **nodes);
/*********** BUILTIN.C **************************************************/
enum e_builtin		type_builtin(int i);
enum e_builtin		is_builtin(char *cmd);
int					exec_builtin(t_args *args, t_node **nodes);
int					find_builtin(t_node **node);
/************ LIBFT.C ***************************************************/
int					ft_strcmp(char *s1, char *s2);
char				*ft_strdup(char *s1);
int					ft_strlen(char *str);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_substr(char *s, int start, size_t len);
/*************************** LIBFT_2.C **********************************/
int					ft_strcpy(char *dst, char *src);
int					ft_strncpy(char *dst, char *src, int len);
/************* PWD_BUILTIN.C *******************************************/
int					exec_pwd(t_args *args);
/************************ DATA.C *******************/
void				init_data(char **envp);
/*********************** CD_BUILTIN.C *********************************/
int					exec_cd_home(t_args *args);
int					exec_cd_path(char *path);
int					exec_cd(t_args *args);
int					exec_cd_old_path(t_args *args);
int					exec_cd_current(t_env *env);
/******************** CD_UTILS.C **********************************/
int					check_error_cd(char *path);
/*************** ECHO_BUILTIN.C **********************************/
int					check_n_option(char **cmds);
void				echo_option_n(t_args *args, int i);
void				echo_no_option(t_args *args, int i);
int					exec_echo(t_args *args);
/******************** ENV_BUILTIN.C  *****************************/
int					exec_env(t_env *env, enum e_builtin type);
/************************ EXIT_UTILS.C ***************************/
int					atoi_exit(char *nbr);
int					is_num(char *nbr);
int					exec_exit(t_args *args);
int					check_format(char *args);
/************************* FILES.C ***********************************/
int					open_files(t_node **node);
int					open_file(t_node **node);
int					open_infile(t_args *args);
int					open_outfile(t_args *args);
/****************** PRINT_UTILS.****************************************/
void				fd_print(char *str, int fd);
void				fd_printnl(char *str, int fd);
/************* CMDS_UTILS.C *******************************************/
char				**get_path(void);
int					is_cmd(char *cmd);
/*************** FT_SPLIT.C ******************************************/
size_t				is_sep(char schar, char sep);
size_t				count_word(char *s_bis, char c_sep);
size_t				length_word(char *s_b, char spec, size_t i);
void				*free_double_tab(char **tab);
char				**ft_split(char *s, char c);
/*********************** MS_ITOA.C **********************************/
int					len_number(int nbr, int base_len);
char				*ms_itoa(int nbr);
/********************** ENV.C ******************************/
char				*ms_getenv(char *key, t_env *env);
t_env				*add_env_element_bottom(t_env *env, char *key,
						char *content);
t_env				*add_env_element_top(t_env *env, char *key, char *content);
t_env				*env_element_create(char *key, char *content);
t_env				*set_env(char **envp, int type);
t_data				*data_create(void);
void				update_char_env(t_data *data);
char				*create_content(char **split);
void				free_set_env(char **temp, char *content);
t_env				*set_basic_env(t_env *env, int type);
/************************ ENV_UTILS.C ************************/
char				**get_env_exec(t_env *env);
char				*ms_strcat_env(char *key, char *content);
char				*ms_strcat(char *dst, char *src, int type);
char				*ft_strcat(char *dst, char *src);
int					env_len(t_env *env);
void				free_env_element(t_env *env);
void				free_env(t_env *env);
/*************************** EXPORT_BUILTIN.C ************************/
int					update_env(char *key, char *content,
						t_env **env, t_export type);
int					delete_env(t_env **env, char *key);
int					is_env_exist(char *key, t_env *env);
int					exec_export(t_args *args);
void				export_full(char *key, char *content,
						t_env *env, t_export type);
int					check_equal_sign(char *var);
void				sort_alpha(t_env **env);
void				execute_export(char *key, char *content, t_export type);
char				*manage_key(char *args, t_export type);
char				*manage_content(char *args, t_export type, char *key);
t_export			define_type_export(char *args);
void				handle_sig(void);
/*************************** EXPORT_UTILS.C ************************/
int					is_valid_key(char *args, enum e_builtin type);
/*************************** EXIT_FREE.C *****************************/
void				free_data(t_data *data);
/*************************** HERE_DOC.C ****************************/
int					here_doc(t_list *infile);
void				exec_heredoc(int fd, t_list *infile);
int					create_heredoc(void);
/*************************** HEREDOC_UTILS.C ****************************/
void				free_limit_close(int fd, char *limit);
void				ctrl_d_heredoc(int fd, char *limit);
void				ctrl_c_heredoc(int fd, char *limit);
/*************************** FT_SIGNAL.C ****************************/
void				heredoc_handler(int sig);
/********************** GNL ****************************************/
int					get_next_line(int fd, char **line);
int					ft_strlen(char *tab);
char				*ft_strncat(char *dst, char *src, int len);
char				*gn_strcpy(char *dst, char *src);
int					begin(char **line, char *buffer,
						int *next_call_line, int *end_of_line);
int					manage_line(char **line, char *buffer,
						int *next_call_line, int *end_of_line);
void				manage_next(char *buffer, int *next,
						int *end_of_line, int i);
/*************************** UNSET.C ****************************/
int					exec_unset(t_args *args);
int					delete_env(t_env **env, char *key);

#endif
