/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:27:11 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/05 10:20:38 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libft/libft.h"
# include <stdbool.h>
# include "struct.h"

# define META_SET		"|&;()<> \t"
# define QUOTE_ERROR	-2
# define ERROR			-1
# define SUCCESS		0

bool	is_operation(char *line, size_t *index);
bool	is_meta(char c);
bool	is_blank(char c);
bool	is_redirection(char *line, size_t *index);
int		conv_op_kind(char *op);
t_token	*make_token(char *line, size_t start, size_t len, int kind);
t_token	*lexer_line2(char *line);
void	free_token(t_token *tok);
void	print_token(t_token *tok);
void	consume_blank(char *line, size_t *index);
int		consume_quote(char **line, size_t *index, char quote_type);

#endif