/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_io_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 01:13:22 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/04 18:57:18 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "exe.h"

static int	open_and_dup_infile(t_shell *sh, t_st_node *node)
{
	sh->file_fd[0] = open(node->data, O_RDONLY);
	if (sh->file_fd[0] == ERROR)
		return (ERROR);
	if (dup2(sh->file_fd[0], node->red_fd) == ERROR)
		return (ERROR);
	if (close(sh->file_fd[0]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	open_and_dup_outfile(t_shell *sh, t_st_node *node)
{
	sh->file_fd[1] = open(node->data, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (sh->file_fd[1] == ERROR)
		return (ERROR);
	if (dup2(sh->file_fd[1], node->red_fd) == ERROR)
		return (ERROR);
	if (close(sh->file_fd[1]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	open_and_dup_heredoc(t_shell *sh, t_st_node *node)
{
	sh->file_fd[0] = node->red_fd;
	if (sh->file_fd[0] == ERROR)
		return (ERROR);
	if (dup2(sh->file_fd[0], STDIN_FILENO) == ERROR)
		return (ERROR);
	if (close(sh->file_fd[0]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	open_and_dup_add_file(t_shell *sh, t_st_node *node)
{
	sh->file_fd[1] = open(node->data, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (sh->file_fd[1] == ERROR)
		return (ERROR);
	if (dup2(sh->file_fd[1], node->red_fd) == ERROR)
		return (ERROR);
	if (close(sh->file_fd[1]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	open_io_file(t_shell *sh, t_st_node *node)
{
	if (node->kind == ST_IN_FILENAME)
		if (open_and_dup_infile(sh, node) == ERROR)
			return (ERROR);
	if (node->kind == ST_OUT_FILENAME)
		if (open_and_dup_outfile(sh, node) == ERROR)
			return (ERROR);
	if (node->kind == ST_HEREDOC_DELIMITER)
		if (open_and_dup_heredoc(sh, node) == ERROR)
			return (ERROR);
	if (node->kind == ST_OUT_ADD_FILENAME)
		if (open_and_dup_add_file(sh, node) == ERROR)
			return (ERROR);
	return (SUCCESS);
}
