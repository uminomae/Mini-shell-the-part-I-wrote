/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:46:00 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/13 19:26:00 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "exe.h"
#include "g_sig.h"

static t_pid	*init_pid_node(t_ptr_list *line_alloc)
{
	t_pid	*node;

	node = (t_pid *)ft_sh_malloc(line_alloc, sizeof(t_pid));
	if (node == NULL)
		return (NULL);
	ft_memset(node, 0, sizeof(t_pid));
	return (node);
}

void	*add_pid_node(t_shell *sh, t_ptr_list *line_alloc)
{
	t_pid	*node;

	node = init_pid_node(line_alloc);
	if (node == NULL)
		return (NULL);
	if (sh->pid_list.head == NULL)
	{
		sh->pid_list.head = node;
		sh->pid_list.tail = node;
	}
	else
	{
		sh->pid_list.tail->next = node;
		sh->pid_list.tail = node;
	}
	return (node);
}

int	wait_pid(t_shell *sh)
{
	t_pid	*node;

	node = sh->pid_list.head;
	while (node != NULL)
	{
		if (waitpid(-1, &node->child_status, GROUP_OF_CALLER) == ERROR)
			return (ERROR);
		if (WIFEXITED(node->child_status))
		{
			sh->sh_prev_status = WEXITSTATUS(node->child_status);
			sh->sh_status = sh->sh_prev_status;
		}
		else if (WIFSIGNALED(node->child_status))
		{
			sh->sh_prev_status = WTERMSIG(node->child_status) + 128;
			sh->sh_status = sh->sh_prev_status;
		}
		node = node->next;
	}
	if (g_sig)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (SUCCESS);
}
