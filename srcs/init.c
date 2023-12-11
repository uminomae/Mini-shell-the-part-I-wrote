/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 00:36:28 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/09 22:01:50 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"
#include "exe.h"
#include "env.h"

void	set_builtin_name(t_shell *sh)
{
	sh->bltin_name[0] = ft_sh_strdup(&sh->bltin_alloc, "echo");
	sh->bltin_name[1] = ft_sh_strdup(&sh->bltin_alloc, "cd");
	sh->bltin_name[2] = ft_sh_strdup(&sh->bltin_alloc, "pwd");
	sh->bltin_name[3] = ft_sh_strdup(&sh->bltin_alloc, "export");
	sh->bltin_name[4] = ft_sh_strdup(&sh->bltin_alloc, "unset");
	sh->bltin_name[5] = ft_sh_strdup(&sh->bltin_alloc, "env");
	sh->bltin_name[6] = ft_sh_strdup(&sh->bltin_alloc, "exit");
}

void	set_builtin_func_ptr(t_shell *sh)
{
	sh->exe_builtin[0] = builtin_echo;
	sh->exe_builtin[1] = builtin_cd;
	sh->exe_builtin[2] = builtin_pwd;
	sh->exe_builtin[3] = builtin_export;
	sh->exe_builtin[4] = builtin_unset;
	sh->exe_builtin[5] = builtin_env;
	sh->exe_builtin[6] = builtin_exit;
}

//extern environ には KEY_ONLY が継承されない 発見。
void	init_env(t_shell *sh, t_env *env)
{
	t_map	head;
	t_map	*node;
	size_t	i;

	i = 0;
	head.next = NULL;
	node = &head;
	while (environ[i])
	{
		node->next = make_hash_node(sh, NULL, NULL);
		node->next->key = make_key(sh, environ[i]);
		node->next->value = make_value(sh, environ[i]);
		node = node->next;
		i++;
	}
	env->len = i;
	node->next = NULL;
	env->env_list = head.next;
	delete_env(sh, "_");
	remake_environ(sh, env);
}

bool	init_minishell(t_shell *sh)
{
	ft_memset(sh, 0, sizeof(t_shell));
	set_builtin_name(sh);
	set_builtin_func_ptr(sh);
	init_env(sh, &sh->env);
	return (true);
}
