/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:30:49 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/13 12:14:36 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

void	init_env(t_shell *sh, t_env *env);
void	remake_environ(t_shell *sh, t_env *env);
void	add_env(t_shell *sh, char *key, char *value);
void	edit_env(t_shell *sh, t_map *node, char *new_value);
void	delete_env(t_shell *sh, char *key);
char	*make_key(t_shell *sh, char *key_and_value);
char	*make_value(t_shell *sh, char *key_and_value);
int		check_key(char *arg);
t_map	*make_hash_node(t_shell *sh, char *key, char *value);
t_map	*ft_getenv(t_shell *sh, char *key);
int		declare(t_shell *sh, t_env *env);
int		sort_env_list(t_shell *sh, size_t num);
size_t	count_node(t_map *node);

// KEY_INVALID, //9KEY not NAME
// KEY_ONLY, //KEY    VALUE=NULL
// KEY_AND_EQUAL, //KEY=   VALUE=""
// KEY_AND_EQUAL_AND_VALUE, //KEY=VALUE   VALUE=VALUE

enum e_key_kind
{
	KEY_NONE = 0,
	KEY_INVALID,
	KEY_ONLY,
	KEY_AND_EQUAL,
	KEY_AND_EQUAL_AND_VALUE,
};

#endif