/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 03:02:03 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/09 09:20:15 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "exe.h"

static int	dup_and_close_child_middle(t_exe *exe)
{
	if (dup2(exe->pipe[0], STDIN_FILENO) == ERROR)
		return (ERROR);
	if (close(exe->pipe[0]) == ERROR)
		return (ERROR);
	if (dup2(exe->next_pipe[1], STDOUT_FILENO) == ERROR)
		return (ERROR);
	if (close(exe->next_pipe[1]) == ERROR)
		return (ERROR);
	if (close(exe->next_pipe[0]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	dup_and_close_child(t_st_node *node, t_exe *exe)
{
	if (node->first_cmd == true)
	{
		if (dup2(exe->pipe[1], STDOUT_FILENO) == ERROR)
			return (ERROR);
		if (close(exe->pipe[1]) == ERROR)
			return (ERROR);
		if (close(exe->pipe[0]) == ERROR)
			return (ERROR);
	}
	if (node->first_cmd == false && node->last_cmd == false)
	{
		if (dup_and_close_child_middle(exe) == ERROR)
			return (ERROR);
	}
	if (node->last_cmd == true)
	{
		if (dup2(exe->pipe[0], STDIN_FILENO) == ERROR)
			return (ERROR);
		if (close(exe->pipe[0]) == ERROR)
			return (ERROR);
		if (close(exe->next_pipe[0]) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

static int	dup_and_close_parent(t_st_node *node, t_exe *exe)
{
	if (node->first_cmd == true)
	{
		if (close(exe->pipe[1]) == ERROR)
			return (ERROR);
	}
	if (node->first_cmd == false && node->last_cmd == false)
	{
		if (close(exe->next_pipe[1]) == ERROR)
			return (ERROR);
		if (close(exe->pipe[0]) == ERROR)
			return (ERROR);
		exe->pipe[0] = exe->next_pipe[0];
	}
	if (node->last_cmd == true)
	{
		if (close(exe->next_pipe[1]) == ERROR)
			return (ERROR);
		if (close(exe->pipe[0]) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

static int	set_parallel(t_shell *sh, t_st_node *node, t_exe *exe, pid_t *p_id)
{
	if (node->first_cmd == false)
	{
		if (pipe(exe->next_pipe) == ERROR)
		{
			sh->sh_status = ERROR;
			return (ERROR);
		}
	}
	ft_memset(sh->file_fd, 0, sizeof(int) * 2);
	*p_id = fork();
	if (*p_id == ERROR)
		return (ERROR);
	if (add_pid_node(sh, &sh->line_alloc) == NULL)
		return (ERROR);
	sh->pid_list.tail->p_id = *p_id;
	return (SUCCESS);
}

int	exe_cmd_elem(t_shell *sh, t_st_node *node, t_exe *exe)
{
	pid_t	p_id;

	if (set_parallel(sh, node, exe, &p_id) == ERROR)
		return (ERROR);
	if (p_id == CHILD_PROCESS)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		if (dup_and_close_child(node, exe) == ERROR)
			exit (ERROR);
		if (prepare_exe(sh, node) == ERROR)
			exit (ERROR);
		if (sh->arg.argc > 0)
			if (exe_judge_func_type(sh, node) == ERROR)
				exit (ERROR);
		exit (SUCCESS);
	}
	if (dup_and_close_parent(node, exe) == ERROR)
	{
		sh->sh_status = ERROR;
		return (ERROR);
	}
	return (SUCCESS);
}
