/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 00:34:33 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/05 23:02:57 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"

typedef struct s_exp
{
	bool	s_flag;
	bool	d_flag;
	char	*quote_start;
	char	*quote_end;
	char	*data_start;
	char	*clip_l;
	char	*clip_c;
	char	*clip_r;
	char	*env_val;
	char	*l_and_c;
}	t_exp;

typedef struct s_exp_quotes
{
	bool	s_flag;
	bool	d_flag;
	char	*quote_start;
	char	*quote_end;
	char	*d_quote_start;
	char	*d_quote_end;
	char	*data_start;
	size_t	next_idx;
	char	*clip_l;
	char	*clip_r;
	bool	continue_flag;
}	t_exp_qt;

# define DOLLAR		36
# define EMPTY_STR	""

char	*dequote(t_shell *sh, t_st_node *node);
char	*expansion_dollar_mark(t_shell *sh, char *s);
char	*join_env_val(t_shell *sh, t_ptr_list *alc, t_exp *e, char *s);
char	*join_status(t_shell *sh, t_ptr_list *alc, t_exp *e, char *s);
#endif
