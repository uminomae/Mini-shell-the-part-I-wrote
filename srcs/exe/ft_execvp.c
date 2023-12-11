/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:57:47 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/13 19:38:22 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_abs_path(char *cmd, t_shell *sh, t_error_exe *err_info);

int	ft_execvp(char *cmd, char **args, t_shell *sh)
{
	char		*abs_path;
	int			errno_save;
	t_error_exe	err_info;

	if (cmd == NULL)
		exit(1);
	err_info.err_msg = NULL;
	err_info.err_num = 0;
	abs_path = get_abs_path(cmd, sh, &err_info);
	if (abs_path == NULL)
	{
		ft_putendl_fd(err_info.err_msg, STDERR_FILENO);
		exit(err_info.err_num);
	}
	else
	{
		execve(abs_path, args, sh->env.environ);
		errno_save = errno;
		ft_putstr_fd("execve error: you can check exit status.", STDERR_FILENO);
		ft_putendl_fd("It display exit() errno", STDERR_FILENO);
		ft_putendl_fd(strerror(errno_save), STDERR_FILENO);
		exit(errno_save);
	}
}
