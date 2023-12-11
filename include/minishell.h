/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:04:46 by hioikawa          #+#    #+#             */
/*   Updated: 2023/03/09 18:20:36 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdbool.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/param.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "err.h"
# include "struct.h"

extern char	**environ;

enum e_error_type
{
	ERR_TOKEN = 0,
	ERR_TYPE_ENV_NULL,
	ERR_TYPE_ARGV_NULL,
	ERR_TYPE_ARGC,
	ERR_TYPE_ARGC_HEREDOC,
	ERR_TYPE_FT,
	ERR_TYPE_PERROR,
	ERR_TYPE_CMD_NOT_FOUND,
	ERR_TYPE_MALLOC,
	ERR_TYPE_SH,
	ERR_TYPE_RL,
	ERR_TYPE_PARSE,
	ERR_TYPE_QUOTE_UNCLOSE,
	ERR_TYPE_BUILTIN,
	ERR_TYPE_OPEN,
	ERR_TYPE_PIPE,
	ERR_TYPE_FORK,
	ERR_TYPE_CLOSE,
	ERR_TYPE_DUP2,
	ERR_TYPE_WAIT,
	ERR_TYPE_END,
};

# define MAX_LINE	1024
# define SAME_STR	0
# define NOT_FOUND	-1
# define SUCCESS	0
# define ERROR		-1
# define EXE_NUM	1
# define READ	0
# define WRITE	1
# define CONTROL_OPE	0
# define ERR_MSG_ENVIRON		"error"
# define ERR_MSG_ARGV			"error"
# define ERR_MSG_ARGC			"error"
# define ERR_MSG_ARGC_HEREDOC	"error"
# define ERR_MSG_FT				"error"
# define ERR_MSG_OTHER			"error"
# define ERR_MSG_CMD_NOT_FOUND	"error"

bool		init_minishell(t_shell *sh);
char		*parse_lexical(t_shell *sh, char *line);
void		parse_recursive_descent(t_shell *sh, t_token_list *token_list);
int			exe_cmdline(t_shell *sh, t_st_node *node);
int			get_cur_stdio_fd(int before_fd[3]);
int			set_back_stdio_fd(int before_fd[3]);
int			get_heredoc(t_shell *sh, t_st_node *node);
void		*ft_sh_malloc(t_ptr_list *ptr_list, size_t size);
bool		free_alloc_list(t_ptr_list *alc);
bool		free_lex_list(t_shell *sh);
void		set_builtin_name(t_shell *sh);
void		set_builtin_func_ptr(t_shell *sh);
char		*ft_sh_strdup(t_ptr_list *line_alloc, const char *src);
char		*ft_sh_substr(t_ptr_list *line_alloc, char const *s, size_t len);
char		*ft_sh_strjoin(t_ptr_list *line_alloc, \
							char const *s1, char const *s2);
t_token		*lexer_line(char **line);
void		free_token(t_token *tok);
bool		is_name(char *str);
void		print_tree2(t_st_node *node);
int			ft_execvp(char *cmd, char **args, t_shell *sh);
t_st_node	*set_cmdline(t_shell *sh, t_token *token);
t_map		*ft_getenv(t_shell *sh, char *key);
void		signal_handler(int sig);
int			signal_check(void);
void		set_signal_handler(void);
void		end_line(t_shell *sh, char *line);

//debug
char		*debug_stx_tree_to_line(t_shell *sh, t_st_node *node);
void		debug_inorder_stx_tree(t_st_node *node);
void		debug_convert_char_dp(size_t count, size_t cmd_id, char **argv);
void		debug_exe_cmdline(t_shell *sh, t_st_node *node);
int			test_unit_env(void);
void		test_unit_cd(void);
void		debug_restore_fd(void);
void		print_token(t_token *tok);

#endif
