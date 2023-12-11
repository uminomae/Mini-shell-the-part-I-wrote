/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:31:30 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/13 19:29:56 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "parse.h"
#include "env.h"

static int	clip_l_c_original_str(t_ptr_list *alc, t_exp *e, char *s, size_t *j)
{
	while (s[*j] != '\0')
	{
		if (!ft_isalnum(s[*j]))
			break ;
		(*j)++;
	}
	e->clip_l = ft_sh_substr(alc, e->data_start, s - e->data_start);
	if (e->clip_l == NULL)
		return (ERROR);
	e->clip_c = ft_sh_substr(alc, s, &s[*j] - s);
	if (e->clip_c == NULL)
		return (ERROR);
	return (SUCCESS);
}

char	*join_env_val(t_shell *sh, t_ptr_list *alc, t_exp *e, char *s)
{
	size_t	j;
	t_map	*env_node;

	j = 1;
	if (clip_l_c_original_str(alc, e, s, &j) == ERROR)
		return (NULL);
	e->clip_r = ft_sh_substr(alc, &s[j], &s[ft_strlen(s)] - &s[j]);
	if (e->clip_r == NULL)
		return (NULL);
	env_node = ft_getenv(sh, &e->clip_c[1]);
	if (env_node == NULL || env_node->value == NULL)
		e->env_val = ft_sh_strdup(alc, EMPTY_STR);
	else
		e->env_val = ft_sh_strdup(alc, env_node->value);
	if (e->env_val == NULL)
		return (NULL);
	e->l_and_c = ft_sh_strjoin(alc, e->clip_l, e->env_val);
	if (e->l_and_c == NULL)
		return (NULL);
	s = ft_sh_strjoin(alc, e->l_and_c, e->clip_r);
	return (s);
}

char	*join_status(t_shell *sh, t_ptr_list *alc, t_exp *e, char *s)
{
	size_t	j;
	char	*buf;

	j = 1;
	if (clip_l_c_original_str(alc, e, s, &j) == ERROR)
		return (NULL);
	e->clip_r = ft_sh_substr(alc, &s[j + 1], &s[ft_strlen(s)] - &s[j]);
	if (e->clip_r == NULL)
		return (NULL);
	buf = ft_itoa(sh->sh_prev_status);
	if (buf == NULL)
		return (NULL);
	e->env_val = ft_sh_strdup(alc, buf);
	free (buf);
	if (e->env_val == NULL)
		return (NULL);
	e->l_and_c = ft_sh_strjoin(alc, e->clip_l, e->env_val);
	if (e->l_and_c == NULL)
		return (NULL);
	s = ft_sh_strjoin(alc, e->l_and_c, e->clip_r);
	return (s);
}
