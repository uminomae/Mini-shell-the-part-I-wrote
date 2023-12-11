/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_classify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:42:56 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/03 18:22:21 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../include/minishell.h"

bool	is_name(char *str)
{
	size_t	i;

	if (str == NULL)
		return (false);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (false);
	i = 1;
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}

int	check_quote_closed(t_shell *sh, char *token)
{
	size_t	i;
	char	quote;

	i = 0;
	if (token == NULL)
		return (0);
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '\"')
		{
			quote = token[i];
			i++;
			while (token[i] && token[i] != quote)
				i++;
			if (token[i] == '\0')
			{
				sh->sh_status = 2;
				return (1);
			}
		}
		i++;
	}
	return (0);
}
