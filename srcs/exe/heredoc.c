/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:42:29 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/13 10:16:36 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "exe.h"
#include "g_sig.h"

static char	*expansion_dollar_heredoc(t_shell *sh, char *line)
{
	char	*content;

	content = ft_sh_strdup(&sh->line_alloc, line);
	free(line);
	sh->heredoc = true;
	if (sh->delimiter_quote == false)
	{
		content = expansion_dollar_mark(sh, content);
		sh->heredoc = false;
		if (content == NULL)
			return (NULL);
	}
	sh->heredoc = false;
	return (content);
}

static int	make_content(t_shell *sh, char *delimiter, int tmp_file_fd)
{
	char	*line;
	char	*content;

	if (delimiter == NULL)
		return (ERROR);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (g_sig || ft_strncmp(line, delimiter, \
			ft_strlen(delimiter) + 1) == SAME_STRING)
		{
			free(line);
			break ;
		}
		content = expansion_dollar_heredoc(sh, line);
		if (content == NULL)
			return (ERROR);
		ft_putstr_fd(content, tmp_file_fd);
		ft_putstr_fd("\n", tmp_file_fd);
	}
	if (close(tmp_file_fd) == ERROR || g_sig)
		return (ERROR);
	return (0);
}

int	open_heredoc(t_shell *sh, char *word)
{
	int		tmp_file_fd;

	(void)sh;
	tmp_file_fd = open(HEREDOC_FILE, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (tmp_file_fd == ERROR)
		return (ERROR);
	if (make_content(sh, word, tmp_file_fd) == ERROR)
		return (ERROR);
	tmp_file_fd = open(HEREDOC_FILE, O_RDONLY);
	if (tmp_file_fd == ERROR)
		return (ERROR);
	if (unlink(HEREDOC_FILE) == ERROR)
		return (ERROR);
	return (tmp_file_fd);
}

int	count_heredoc(t_shell *sh, t_st_node *node)
{
	if (node->kind == ST_HEREDOC_DELIMITER)
		sh->count_heredoc++;
	if (node->left != NULL)
		if (count_heredoc(sh, node->left) == ERROR)
			return (ERROR);
	if (node->right != NULL)
		if (count_heredoc(sh, node->right) == ERROR)
			return (ERROR);
	return (SUCCESS);
}

int	get_heredoc(t_shell *sh, t_st_node *node)
{
	if (node->left != NULL)
		if (get_heredoc(sh, node->left) == ERROR)
			return (ERROR);
	if (node->kind == ST_HEREDOC_DELIMITER)
	{
		sh->delimiter_quote = false;
		if (node->data[0] == SINGLE_QUOTE || node->data[0] == DOUBLE_QUOTE)
			sh->delimiter_quote = true;
		node->data = dequote(sh, node);
		if (node->data == NULL)
			return (ERROR);
		node->red_fd = open_heredoc(sh, node->data);
		if (node->red_fd == ERROR)
			return (ERROR);
	}
	if (node->right != NULL)
		if (get_heredoc(sh, node->right) == ERROR)
			return (ERROR);
	return (SUCCESS);
}
