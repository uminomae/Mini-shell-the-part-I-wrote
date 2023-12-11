/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 00:11:16 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/13 20:23:47 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "g_sig.h"

static t_map	*cpy_env_list(t_map *dst, t_map *src, t_ptr_list *alc)
{
	while (src != NULL)
	{
		dst->next = ft_sh_malloc(alc, sizeof(t_map));
		ft_memset(dst->next, 0, sizeof(t_map));
		dst->next->key = ft_sh_strdup(alc, src->key);
		dst->next->value = ft_sh_strdup(alc, src->value);
		src = src->next;
		dst = dst->next;
	}
	dst->next = NULL;
	return (dst);
}

static t_map	*reset_env_list(t_shell *sh)
{
	t_map		head_tmp;
	t_map		head_env;
	t_map		*node_env;
	t_map		*node_tmp;
	t_ptr_list	tmp_alloc;

	ft_memset(&head_tmp, 0, sizeof(t_map));
	ft_memset(&head_env, 0, sizeof(t_map));
	ft_memset(&tmp_alloc, 0, sizeof(t_ptr_list));
	node_tmp = &head_tmp;
	node_env = sh->env.env_list;
	cpy_env_list(node_tmp, node_env, &tmp_alloc);
	free_alloc_list(&sh->sh_alloc);
	ft_memset(&sh->sh_alloc, 0, sizeof(t_ptr_list));
	node_env = &head_env;
	node_tmp = head_tmp.next;
	cpy_env_list(node_env, node_tmp, &sh->sh_alloc);
	sh->env.env_list = head_env.next;
	free_alloc_list(&tmp_alloc);
	remake_environ(sh, &sh->env);
	return (node_env);
}

void	end_line(t_shell *sh, char *line)
{
	if (g_sig)
	{
		sh->sh_prev_status = 128 + g_sig;
		g_sig = 0;
	}
	add_history(line);
	free(line);
	free_alloc_list(&sh->line_alloc);
	reset_env_list(sh);
}
