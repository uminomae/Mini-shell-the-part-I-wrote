/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:06:46 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/07 19:14:49 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_st_node	*set_cmd_pipe(t_shell *sh, t_token **token);
static t_st_node	*set_cmd_element(\
						t_shell *sh, t_token **token, t_st_node *node);
int					check_quote_closed(t_shell *sh, char *token);

t_st_node	*set_cmdline(t_shell *sh, t_token *token)
{
	t_st_node	*node;
	bool		is_semi_colon;
	char		*data;

	node = NULL;
	node = set_cmd_pipe(sh, &token);
	if (token == NULL || sh->sh_status)
		return (node);
	if (token->kind == TK_OP_LIST)
	{
		data = token->data;
		if (data[0] == ';' && data[1] == '\0')
			is_semi_colon = true;
		else
			is_semi_colon = false;
		token = token->next;
		if (token == NULL && !is_semi_colon)
			sh->sh_status = 2;
		else if (token && token->kind != TK_RED && token->kind != TK_WORD)
			sh->sh_status = 2;
		node = new_binary \
			(sh, data, node, set_cmdline(sh, token));
		node->kind = ST_OP_LIST;
	}
	return (node);
}

static t_st_node	*set_cmd_pipe(t_shell *sh, t_token **token)
{
	t_st_node	*node;
	char		*op_pipe;

	node = NULL;
	node = set_cmd_element(sh, token, node);
	if ((*token) == NULL || sh->sh_status)
		return (node);
	if ((*token)->kind == TK_OP_PIPE)
	{
		if ((*token)->next == NULL || (*token)->next->kind == TK_OP_PIPE || \
			(*token)->next->kind == TK_OP_LIST)
			sh->sh_status = 2;
		else
		{
			op_pipe = (*token)->data;
			*token = (*token)->next;
			node = new_binary(sh, op_pipe, node, set_cmd_pipe(sh, token));
			node->kind = ST_PIPE;
		}
	}
	return (node);
}

static int	conv_file_kind(char *redirect)
{
	size_t	digit;

	digit = 0;
	while (ft_isdigit(redirect[digit]))
		digit++;
	if (redirect[digit] == '\0')
		return (ERROR);
	if (ft_strncmp(&redirect[digit], "<", 2) == 0)
		return (ST_IN_FILENAME);
	else if (ft_strncmp(&redirect[digit], "<<", 3) == 0)
		return (ST_HEREDOC_DELIMITER);
	else if (ft_strncmp(&redirect[digit], ">", 2) == 0)
		return (ST_OUT_FILENAME);
	else if (ft_strncmp(&redirect[digit], ">>", 3) == 0)
		return (ST_OUT_ADD_FILENAME);
	else
		return (ERROR);
}

static int	get_fd_from_red(char *redirect)
{
	size_t	digit;
	char	*buf;
	int		redirect_fd;

	digit = 0;
	while (ft_isdigit(redirect[digit]))
		digit++;
	if (digit != 0)
	{
		buf = ft_substr(redirect, 0, digit);
		redirect_fd = ft_atoi(buf);
		free (buf);
		return (redirect_fd);
	}
	else
	{
		if (redirect[0] == '<')
			return (STDIN_FILENO);
		else if (redirect[0] == '>')
			return (STDOUT_FILENO);
		else
			return (ERROR);
	}
}

static t_st_node	*set_cmd_element(
						t_shell *sh, t_token **token, t_st_node *node)
{
	if ((*token) == NULL || sh->sh_status)
		return (node);
	else if ((*token)->kind == TK_WORD)
	{
		check_quote_closed(sh, (*token)->data);
		node = new_binary(sh, (*token)->data, node, NULL);
		if (node->left && node->left->kind == ST_REDIRECT)
		{
			node->kind = conv_file_kind(node->left->data);
			node->red_fd = get_fd_from_red(node->left->data);
		}
		else
			node->kind = ST_WORD;
	}
	else if ((*token)->kind == TK_RED)
	{
		if ((*token)->next == NULL || (*token)->next->kind != TK_WORD)
			sh->sh_status = 2;
		node = new_binary(sh, (*token)->data, node, NULL);
		node->kind = ST_REDIRECT;
	}
	else
		return (node);
	(*token) = (*token)->next;
	return (set_cmd_element(sh, token, node));
}
