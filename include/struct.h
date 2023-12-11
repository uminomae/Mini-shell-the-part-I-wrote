/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 07:37:20 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/13 10:52:15 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <signal.h>
# include <stdbool.h>
# include <stdio.h>

typedef struct s_ptr_node
{
	void				*ptr;
	struct s_ptr_node	*next;
}t_ptr_node;

typedef struct s_ptr_list
{
	struct s_ptr_node	*head;
	struct s_ptr_node	*tail;
}t_ptr_list;

typedef struct s_token_node
{
	char				*data;
	int					kind;
	struct s_token_node	*next;
	struct s_token_node	*prev;
}t_token;

typedef struct s_syntax_tree_node
{
	int							kind;
	char						*data;
	size_t						idx;
	size_t						word_num;
	ssize_t						bltin_id;
	char						**argv;
	bool						first_cmd;
	bool						last_cmd;
	int							red_fd;
	struct s_syntax_tree_node	*left;
	struct s_syntax_tree_node	*right;
	struct s_syntax_tree_node	*parent;
}t_st_node;

typedef struct s_token_list
{
	t_token	*head;
	t_token	*tail;
}t_token_list;

typedef struct s_lex
{
	bool	q_flag;
	bool	dq_flag;
}t_lex;

typedef struct s_signal
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;
}t_sig;

typedef struct s_hashmap {
	char				*key;
	char				*value;
	struct s_hashmap	*next;
}t_map;

typedef struct s_env {
	t_map	*env_list;
	char	**environ;
	int		len;
}t_env;

typedef struct s_argment
{
	size_t	argc;
	size_t	cnt;
	size_t	idx;
	char	**argv;
}t_arg;

typedef struct s_pid
{
	pid_t			p_id;
	int				child_status;
	struct s_pid	*next;
}t_pid;

typedef struct s_error_exe{
	char	*err_msg;
	int		err_num;
}	t_error_exe;

typedef struct s_pid_list
{
	struct s_pid	*head;
	struct s_pid	*tail;
}t_pid_list;

typedef struct s_shell
{
	t_ptr_list		bltin_alloc;
	t_ptr_list		line_alloc;
	t_ptr_list		sh_alloc;
	t_st_node		*root_node;
	char			*bltin_name[8];
	int				(*exe_builtin[8])();
	t_lex			st_lex;
	t_sig			sig;
	t_arg			arg;
	t_pid_list		pid_list;
	int				before_fd[3];
	int				file_fd[2];
	int				sh_status;
	int				sh_prev_status;
	t_env			env;
	bool			heredoc;
	bool			delimiter_quote;
	size_t			count_heredoc;
}t_shell;

enum e_syntax_tree_node_kind
{
	ST_WORD = 0,
	ST_PIPE,
	ST_REDIRECT,
	ST_IN_FILENAME,
	ST_OUT_FILENAME,
	ST_HEREDOC_DELIMITER,
	ST_OUT_ADD_FILENAME,
	ST_OP_LIST,
	ST_EOF,
	ST_TYPE_END,
};

enum e_io_type {
	IO_NONE = 0,
	IO_INFILE,
	IO_OUTFILE,
	IO_HEREDOC,
	IO_OUT_ADD,
	IO_TYPE_END,
};

enum e_mode_type {
	MODE_NONE = 0,
	MODE_STRING,
	MODE_META,
	MODE_QUOTE,
	MODE_D_QUOTE,
	MODE_TYPE_END,
};

enum e_error
{
	E_SYNTAX = 2,
};

enum e_token_kind
{
	TK_NONE = 0,
	TK_WORD,
	TK_OP,
	TK_OP_PIPE,
	TK_OP_LIST,
	TK_RED,
	TK_QUOTE,
	TK_DQUOTE,
	TK_EOF,
	TK_TYPE_END,
};

# define SINGLE_QUOTE	39
# define DOUBLE_QUOTE	34
# define ERR_NUM_IS_A_DIRECTORY 126
# define ERR_NUM_PERMISSION_DENIED 126
# define ERR_NUM_NO_SUCH_FILE_OR_DIRECTORY 127
# define ERR_NUM_CMD_NOT_FOUND 127

#endif