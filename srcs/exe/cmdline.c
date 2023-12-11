/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 03:00:34 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/13 18:03:03 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "exe.h"

static int	exe_cmd_op(t_shell *sh, t_st_node *node, t_exe *exe)
{
	exe_node(sh, node->left, exe);
	if (node->data[0] == '|' && sh->sh_status != 0)
		exe_node(sh, node->right, exe);
	else if (node->data[0] == '&' && sh->sh_status == 0)
		exe_node(sh, node->right, exe);
	else if (node->data[0] == ';')
		exe_node(sh, node->right, exe);
	return (SUCCESS);
}

int	exe_node(t_shell *sh, t_st_node *node, t_exe *exe)
{
	if (node == NULL)
		return (SUCCESS);
	else if (node->kind == ST_PIPE)
		return (exe_cmd_pipe(sh, node, exe));
	else if (node->kind == ST_OP_LIST)
		return (exe_cmd_op(sh, node, exe));
	else if (sh->root_node->kind != ST_PIPE && \
				sh->root_node->kind != ST_OP_LIST)
		return (exe_cmd_single(sh, node));
	else if (exe->with_pipe == false)
		return (exe_cmd_single(sh, node));
	else if (exe->with_pipe == true)
		return (exe_cmd_elem(sh, node, exe));
	return (SUCCESS);
}

static int	begin_exe(t_shell *sh, t_st_node *root, t_exe *exe)
{
	ft_memset(exe, 0, sizeof(t_exe));
	if (root == NULL)
		return (SUCCESS);
	if (count_heredoc(sh, sh->root_node) == ERROR)
		return (ERROR);
	if (sh->count_heredoc > 16)
		return (ERROR);
	if (get_heredoc(sh, root) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	exe_cmdline(t_shell *sh, t_st_node *root)
{
	t_exe	exe;

	if (get_cur_stdio_fd(sh->before_fd) == ERROR)
		return (ERROR);
	if (begin_exe(sh, root, &exe) == ERROR)
		return (ERROR);
	if (exe_node(sh, root, &exe) == ERROR)
		return (ERROR);
	if (set_back_stdio_fd(sh->before_fd) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
