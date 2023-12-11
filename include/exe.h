/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:42:36 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/09 09:20:15 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H

# include "minishell.h"
# include "builtin.h"

typedef struct s_exe
{
	int				pipe[2];
	int				next_pipe[2];
	bool			with_pipe;
}	t_exe;

# define GROUP_OF_CALLER	0
# define CHILD_PROCESS		0
# define LEFT				0
# define RIGHT				1
# define READ				0
# define WRITE				1
# define NEW_LINE			"\n"
# define HEREDOC_FILE		".tmp_heredoc"
# define SAME_STRING		0
# define FIRST_PIPE_VALUE	0

int		exe_cmd_elem(t_shell *sh, t_st_node *node, t_exe *exe);
int		exe_cmd_single(t_shell *sh, t_st_node *node);
int		exe_cmd_pipe(t_shell *sh, t_st_node *node, t_exe *exe);
int		exe_node(t_shell *sh, t_st_node *node, t_exe *exe);
int		exe_judge_func_type(t_shell *sh, t_st_node *node);
ssize_t	strncmp_builtin_name(t_shell *sh, char **argv);
int		open_io_file(t_shell *sh, t_st_node *node);
int		prepare_exe(t_shell *sh, t_st_node *node);
void	*add_pid_node(t_shell *sh, t_ptr_list *line_alloc);
int		wait_pid(t_shell *sh);
int		open_heredoc(t_shell *sh, char *word);
int		count_heredoc(t_shell *sh, t_st_node *node);

#endif