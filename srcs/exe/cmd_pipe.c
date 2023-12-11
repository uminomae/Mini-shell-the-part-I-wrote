/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 03:00:34 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/02 22:53:26 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "exe.h"

static int	end_pipe(t_shell *sh, t_st_node *node, t_exe *exe)
{
	if (node->right->right == NULL)
	{
		if (wait_pid(sh) == ERROR)
			return (ERROR);
		sh->pid_list.head = NULL;
		if (exe->pipe[0] != 0)
			ft_memset(exe->pipe, 0, sizeof(int) * 2);
		if (exe->next_pipe[0] != 0)
			if (close(exe->next_pipe[0]) == ERROR)
				return (ERROR);
		exe->with_pipe = false;
		return (SUCCESS);
	}
	return (SUCCESS);
}

int	exe_cmd_pipe(t_shell *sh, t_st_node *node, t_exe *exe)
{
	exe->with_pipe = true;
	if (exe->pipe [0] == FIRST_PIPE_VALUE)
	{
		if (pipe(exe->pipe) == ERROR)
			return (ERROR);
	}
	if (node->left != NULL)
	{
		if (node->parent == NULL || node->parent->kind == ST_OP_LIST)
			node->left->first_cmd = true;
		if (exe_node(sh, node->left, exe) == ERROR)
			return (ERROR);
	}
	if (node->right != NULL)
	{
		if (node->right->right == NULL)
			node->right->last_cmd = true;
		if (exe_node(sh, node->right, exe) == ERROR)
			return (ERROR);
		if (end_pipe(sh, node, exe) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
