/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:31:30 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/09 09:20:15 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "parse.h"
#include "env.h"

static void	set_state_quotes(t_exp *exp, char c)
{
	if (c == DOUBLE_QUOTE)
	{
		if (exp->s_flag == false)
			exp->d_flag = !exp->d_flag;
	}
	if (c == SINGLE_QUOTE)
	{
		if (exp->d_flag == false)
			exp->s_flag = !exp->s_flag;
	}
}

static void	init_expansion_dollar_mark(t_exp *exp, char *s, size_t *i)
{
	exp->data_start = &s[0];
	exp->s_flag = false;
	exp->d_flag = false;
	*i = 0;
}

static char	*convert_dollar(t_shell *sh, t_exp *exp, char *s, size_t i)
{
	if (s[i + 1] == '?')
		s = join_status(sh, &sh->line_alloc, exp, &s[i]);
	else
		s = join_env_val(sh, &sh->line_alloc, exp, &s[i]);
	return (s);
}

char	*expansion_dollar_mark(t_shell *sh, char *s)
{
	t_exp	exp;
	size_t	i;

	ft_memset(&exp, 0, sizeof(t_exp));
	i = 0;
	init_expansion_dollar_mark(&exp, s, &i);
	while (s[i] != '\0')
	{
		set_state_quotes(&exp, s[i]);
		if (exp.s_flag == false || sh->heredoc == true)
		{
			if (s[i] == DOLLAR)
			{
				if (s[i + 1] == '\0')
					break ;
				s = convert_dollar(sh, &exp, s, i);
				if (s == NULL)
					return (NULL);
				init_expansion_dollar_mark(&exp, s, &i);
				continue ;
			}
		}
		i++;
	}
	return (s);
}
