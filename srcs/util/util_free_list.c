/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_free_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:11:49 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/09 18:20:21 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	free_alloc_list_ptr(t_ptr_list *alc);
static bool	free_alloc_list_node(t_ptr_list *alc);

bool	free_alloc_list(t_ptr_list *alc)
{
	if (!free_alloc_list_ptr(alc))
		return (false);
	if (!free_alloc_list_node(alc))
		return (false);
	return (true);
}

static bool	free_alloc_list_ptr(t_ptr_list *alc)
{
	t_ptr_node	*node;

	if (alc == NULL)
		return (false);
	if (alc->head == NULL)
		return (false);
	node = alc->head;
	while (node != NULL)
	{
		free(node->ptr);
		node->ptr = NULL;
		node = node->next;
	}
	return (true);
}

static bool	free_alloc_list_node(t_ptr_list *alc)
{
	t_ptr_node	*node;
	t_ptr_node	*tmp;

	if (alc == NULL)
		return (false);
	if (alc->head == NULL)
		return (false);
	node = alc->head;
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		free(tmp);
		tmp = NULL;
	}
	return (true);
}
