/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 01:13:18 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/09 09:20:15 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_st_node	*new_node(t_shell *sh, char *data)
{
	t_st_node	*node;

	node = (t_st_node *)ft_sh_malloc(&sh->line_alloc, sizeof(t_st_node));
	if (node == NULL)
		return (NULL);
	ft_memset(node, 0, sizeof(t_st_node));
	node->data = ft_sh_strdup(&sh->line_alloc, data);
	if (node == NULL)
		return (NULL);
	return (node);
}

t_st_node	*new_binary(t_shell *sh, char *data, t_st_node *l, t_st_node *r)
{
	t_st_node	*node;

	node = new_node(sh, data);
	node->left = l;
	if (l)
		l->parent = node;
	node->right = r;
	if (r)
		r->parent = node;
	return (node);
}
