/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_single.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 03:00:34 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/13 19:31:50 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "exe.h"

static int	single_external_func(t_shell *sh, t_st_node *node, int pipe_fd[2])
{
	pid_t	p_id;

	p_id = fork();
	if (p_id == ERROR)
		return (ERROR);
	if (add_pid_node(sh, &sh->line_alloc) == NULL)
		return (ERROR);
	sh->pid_list.tail->p_id = p_id;
	if (p_id == CHILD_PROCESS)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		if (close(pipe_fd[0]) == ERROR)
			exit (ERROR);
		ft_execvp(node->argv[0], node->argv, sh);
		exit (ERROR);
	}
	if (close(pipe_fd[1]) == ERROR || wait_pid(sh) == ERROR || \
		close(pipe_fd[0]) == ERROR)
	{
		sh->sh_status = ERROR;
		return (ERROR);
	}
	sh->pid_list.head = NULL;
	return (SUCCESS);
}

static int	exe_judge_func_type_single(t_shell *sh, t_st_node *node)
{
	int		pipe_fd[2];

	node->bltin_id = strncmp_builtin_name(sh, node->argv);
	if (node->bltin_id == NOT_FOUND)
	{
		if (pipe(pipe_fd) == ERROR)
		{
			sh->sh_status = ERROR;
			return (ERROR);
		}
		return (single_external_func(sh, node, pipe_fd));
	}
	else if (node->bltin_id != NOT_FOUND)
	{
		sh->sh_status = (*sh->exe_builtin[node->bltin_id])(sh, node->argv);
		sh->sh_prev_status = sh->sh_status;
		if (sh->sh_status == ERROR)
			return (ERROR);
		return (SUCCESS);
	}
	return (SUCCESS);
}

int	exe_cmd_single(t_shell *sh, t_st_node *node)
{
	if (prepare_exe(sh, node) == ERROR)
		return (ERROR);
	if (sh->arg.argc > 0)
		if (exe_judge_func_type_single(sh, node) == ERROR)
			return (ERROR);
	return (SUCCESS);
}
