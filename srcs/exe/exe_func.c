/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 01:13:22 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/13 19:50:24 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "exe.h"

ssize_t	strncmp_builtin_name(t_shell *sh, char **argv)
{
	ssize_t	i;

	i = 0;
	while (sh->bltin_name[i] != NULL)
	{
		if (ft_strncmp(argv[0], sh->bltin_name[i], ft_strlen(argv[0]) + 1) \
			== SAME_STR)
			return (i);
		i++;
	}
	return (NOT_FOUND);
}

int	exe_judge_func_type(t_shell *sh, t_st_node *node)
{
	node->bltin_id = strncmp_builtin_name(sh, node->argv);
	if (node->bltin_id == NOT_FOUND)
	{
		ft_execvp(node->argv[0], node->argv, sh);
		return (ERROR);
	}
	else if (node->bltin_id != NOT_FOUND)
	{
		sh->sh_prev_status = (*sh->exe_builtin[node->bltin_id])(sh, node->argv);
		sh->sh_status = sh->sh_prev_status;
		if (sh->sh_status == ERROR)
			return (ERROR);
		return (SUCCESS);
	}
	return (SUCCESS);
}
