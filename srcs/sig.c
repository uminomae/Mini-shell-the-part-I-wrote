/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:32:37 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/13 15:13:26 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include "g_sig.h"

volatile sig_atomic_t	g_sig;

void	signal_handler(int sig)
{
	g_sig = sig;
}

int	signal_check(void)
{
	if (g_sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 1;
	}
	return (0);
}

//set_signal_handler 内で定義したlocal 変数でsigactionするとバグる
void	set_signal_handler(void)
{
	rl_event_hook = signal_check;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}
