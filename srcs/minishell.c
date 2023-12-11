/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 00:11:16 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/13 20:22:19 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "g_sig.h"

static bool	init_line(t_shell *sh)
{
	ft_memset(&sh->line_alloc, 0, sizeof(t_ptr_list));
	ft_memset(&sh->arg, 0, sizeof(t_arg));
	sh->root_node = NULL;
	sh->st_lex.q_flag = false;
	sh->st_lex.dq_flag = false;
	ft_memset(sh->before_fd, 0, sizeof(int) * 3);
	ft_memset(&sh->pid_list, 0, sizeof(t_pid_list));
	sh->sh_status = 0;
	sh->count_heredoc = 0;
	set_signal_handler();
	return (true);
}

static char	*sh_readline(t_shell *sh)
{
	char	*line;

	line = readline("pretty_sh $ ");
	if (line == NULL)
	{
		free_alloc_list(&sh->bltin_alloc);
		free_alloc_list(&sh->line_alloc);
		free_alloc_list(&sh->sh_alloc);
		exit(sh->sh_prev_status);
	}
	return (line);
}

int	minishell(t_shell *sh)
{
	char	*line;
	t_token	*token_head;

	line = NULL;
	while (1)
	{
		init_line(sh);
		line = sh_readline(sh);
		token_head = lexer_line(&line);
		sh->root_node = set_cmdline(sh, token_head);
		free_token(token_head);
		if (sh->sh_status)
		{
			sh->sh_prev_status = sh->sh_status;
			ft_putstr_fd("parser: syntax ERROR\n", STDOUT_FILENO);
			end_line(sh, line);
			continue ;
		}
		if (exe_cmdline(sh, sh->root_node) == ERROR)
			ft_putstr_fd("exe_cmdline: ERROR\n", STDOUT_FILENO);
		end_line(sh, line);
	}
	return (0);
}

int	main(void)
{
	t_shell	sh;

	g_sig = 0;
	init_minishell(&sh);
	minishell(&sh);
	return (0);
}

// main() for debug
// int	main(void)
// {
// 	t_shell	sh;

// 	rl_outstream = stderr;
// 	g_sig = 0;
// 	init_minishell(&sh);
// 	minishell(&sh);
// 	return (0);
// }
