/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 00:34:33 by uminomae          #+#    #+#             */
/*   Updated: 2023/02/26 19:29:07 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "struct.h"
# include "stdlib.h"
# include "../libft/libft.h"

# define ERROR -1

bool		is_meta(char c);
void		get_token(t_shell *sh, int kind, char *start, char *last);
char		*lex_mode_none(t_shell *sh, char *start, int *mode, char *c);
char		*lex_mode_string(t_shell *sh, char *start, int *mode, char *c);
char		*lex_mode_meta(t_shell *sh, char *start, int *mode, char *c);
void		set_lexical_func(char *(*lex_mode[])());
t_st_node	*new_node(t_shell *sh, char *data);
t_st_node	*new_binary(t_shell *sh, char *data, \
						t_st_node *left, t_st_node *right);
int			is_io_file(t_token_list *list);
bool		is_cmd_element(t_token_list *list);

#endif