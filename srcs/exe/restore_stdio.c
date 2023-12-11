/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_stdio.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 01:13:22 by uminomae          #+#    #+#             */
/*   Updated: 2023/02/24 23:26:33 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "exe.h"

int	get_cur_stdio_fd(int before_fd[3])
{
	before_fd[0] = dup(STDIN_FILENO);
	if (before_fd[0] == ERROR)
		return (ERROR);
	before_fd[1] = dup(STDOUT_FILENO);
	if (before_fd[1] == ERROR)
		return (ERROR);
	before_fd[2] = dup(STDERR_FILENO);
	if (before_fd[2] == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	set_back_stdio_fd(int before_fd[3])
{
	if (before_fd[0] != STDIN_FILENO)
	{
		if (dup2(before_fd[0], STDIN_FILENO) == ERROR)
			return (ERROR);
		if (close(before_fd[0]) == ERROR)
			return (ERROR);
	}
	if (before_fd[1] != STDOUT_FILENO)
	{
		if (dup2(before_fd[1], STDOUT_FILENO) == ERROR)
			return (ERROR);
		if (close(before_fd[1]) == ERROR)
			return (ERROR);
	}
	if (before_fd[2] != STDERR_FILENO)
	{
		if (dup2(before_fd[2], STDERR_FILENO) == ERROR)
			return (ERROR);
		if (close(before_fd[2]) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
