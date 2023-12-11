/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_prepare.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 02:25:07 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/09 09:20:15 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "exe.h"

static char	**calloc_argv(t_shell *sh, size_t size)
{
	char	**argv;

	argv = (char **)ft_sh_malloc(&sh->line_alloc, size * sizeof(char *));
	if (argv == NULL)
	{
		sh->sh_status = 1;
		return (NULL);
	}
	ft_memset(argv, 0, size);
	return (argv);
}

static int	set_argv_redirect(t_shell *sh, t_st_node *node)
{
	if (node == NULL || node->kind == ST_PIPE || node->kind == ST_OP_LIST)
		return (SUCCESS);
	if (node->kind != ST_HEREDOC_DELIMITER && node->kind != ST_REDIRECT)
		node->data = expansion_dollar_mark(sh, node->data);
	if (node->data == NULL)
		return (ERROR);
	if (node->kind != ST_HEREDOC_DELIMITER && node->kind != ST_REDIRECT)
		node->data = dequote(sh, node);
	if (node->data == NULL)
		return (ERROR);
	if (open_io_file(sh, node) == ERROR)
		return (ERROR);
	if (node->kind == ST_WORD)
	{
		sh->arg.argv[node->idx] = ft_sh_strdup(&sh->line_alloc, node->data);
		if (sh->arg.argv[node->idx] == NULL)
			return (ERROR);
	}
	if (node->left == NULL)
		sh->arg.argv[sh->arg.argc] = NULL;
	return (set_argv_redirect(sh, node->parent));
}

static void	set_arg_idx(t_shell *sh, t_st_node *node)
{
	if (node == NULL || node->kind == ST_PIPE || node->kind == ST_OP_LIST)
		return ;
	if (node->kind == ST_WORD)
	{
		sh->arg.cnt += 1;
		node->word_num = sh->arg.cnt;
		node->idx = sh->arg.cnt - 1;
	}
	return (set_arg_idx(sh, node->parent));
}

int	prepare_exe(t_shell *sh, t_st_node *node)
{
	t_st_node	*leftmost;

	sh->arg.cnt = 0;
	leftmost = node;
	while (leftmost->left != NULL)
		leftmost = leftmost->left;
	set_arg_idx(sh, leftmost);
	sh->arg.argc = sh->arg.cnt;
	sh->arg.argv = calloc_argv(sh, sh->arg.argc + 1);
	if (sh->arg.argv == NULL)
		return (ERROR);
	if (set_argv_redirect(sh, leftmost) == ERROR)
		return (ERROR);
	node->argv = sh->arg.argv;
	return (0);
}
