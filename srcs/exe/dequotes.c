/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:31:30 by uminomae          #+#    #+#             */
/*   Updated: 2023/02/25 01:04:29 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "parse.h"

static char	*convert_quote(t_ptr_list *alc, t_exp_qt *qt, char *s)
{
	char	*str;

	qt->clip_l = ft_sh_substr(alc, qt->data_start, s - qt->data_start);
	if (qt->clip_l == NULL)
		return (NULL);
	qt->clip_r = ft_sh_substr(alc, &s[1], &s[ft_strlen(s)] - &s[0]);
	if (qt->clip_r == NULL)
		return (NULL);
	qt->next_idx = ft_strlen(qt->clip_l);
	str = ft_sh_strjoin(alc, qt->clip_l, qt->clip_r);
	return (str);
}

static char	*trim_quotes(t_shell *sh, t_exp_qt *qt, char *s, char quote_type)
{
	char	*data;

	data = convert_quote(&sh->line_alloc, qt, s);
	if (data == NULL)
		return (NULL);
	qt->data_start = &data[0];
	qt->quote_end = ft_strchr(&data[qt->next_idx], quote_type);
	if (qt->quote_end == NULL)
		return (NULL);
	data = convert_quote(&sh->line_alloc, qt, qt->quote_end);
	if (data == NULL)
		return (NULL);
	qt->data_start = &data[0];
	return (data);
}

static char	*trim_s_quote(t_shell *sh, t_exp_qt *qt, char *s, size_t *i)
{
	char	*data;

	data = NULL;
	if (qt->d_flag == false)
	{
		qt->s_flag = !qt->s_flag;
		if (qt->s_flag == true)
		{
			data = trim_quotes(sh, qt, s, SINGLE_QUOTE);
			if (data == NULL)
				return (NULL);
			*i = qt->next_idx;
			qt->s_flag = false;
			qt->next_idx = 0;
			qt->continue_flag = true;
		}
	}
	return (data);
}

static char	*trim_d_quote(t_shell *sh, t_exp_qt *qt, char *s, size_t *i)
{
	char	*data;

	data = NULL;
	if (qt->s_flag == false)
	{
		qt->d_flag = !qt->d_flag;
		if (qt->d_flag == true)
		{
			data = trim_quotes(sh, qt, s, DOUBLE_QUOTE);
			if (data == NULL)
				return (NULL);
			*i = qt->next_idx;
			qt->d_flag = false;
			qt->next_idx = 0;
			qt->continue_flag = true;
		}
	}
	return (data);
}

char	*dequote(t_shell *sh, t_st_node *node)
{
	t_exp_qt	qt;
	size_t		i;

	ft_memset(&qt, 0, sizeof(t_exp_qt));
	qt.data_start = &node->data[0];
	i = 0;
	while (node->data[i] != '\0')
	{
		qt.continue_flag = false;
		if (node->data[i] == DOUBLE_QUOTE)
		{
			node->data = trim_d_quote(sh, &qt, &node->data[i], &i);
			if (node->data == NULL)
				return (NULL);
		}
		if (node->data[i] == SINGLE_QUOTE)
		{
			node->data = trim_s_quote(sh, &qt, &node->data[i], &i);
			if (node->data == NULL)
				return (NULL);
		}
		if (!qt.continue_flag)
			i++;
	}
	return (node->data);
}
