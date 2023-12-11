/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:33:04 by kakiba            #+#    #+#             */
/*   Updated: 2023/02/24 23:52:31 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int		builtin_cd(t_shell *sh, char **arg);
int		builtin_pwd(t_shell *sh, char **arg);
int		builtin_exit(t_shell *sh, char **arg);
int		builtin_echo(t_shell *sh, char **arg);
int		builtin_unset(t_shell *sh, char **arg);
int		builtin_env(t_shell *sh, char **arg);
int		builtin_export(t_shell *sh, char **arg);

#endif