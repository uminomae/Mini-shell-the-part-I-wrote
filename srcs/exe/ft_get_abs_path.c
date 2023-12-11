/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_abs_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:54:36 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/13 16:15:37 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_error_msg(t_shell *sh, char *cmd, char *error_msg)
{
	char	*ret_msg;

	ret_msg = ft_sh_strjoin(&sh->line_alloc, cmd, ": ");
	if (ret_msg == NULL)
		exit(EXIT_FAILURE);
	ret_msg = ft_sh_strjoin(&sh->line_alloc, ret_msg, error_msg);
	if (ret_msg == NULL)
		exit(EXIT_FAILURE);
	return (ret_msg);
}

bool	is_file_exectable(char *abs_cmd, \
	t_shell *sh, t_error_exe *err_info)
{
	char		*cmd_start;
	struct stat	st;

	if (stat(abs_cmd, &st) != 0)
	{
		err_info->err_msg = make_error_msg(sh, abs_cmd, strerror(errno));
		err_info->err_num = ERR_NUM_NO_SUCH_FILE_OR_DIRECTORY;
		return (false);
	}
	cmd_start = ft_strrchr(abs_cmd, '/') + 1;
	if (*cmd_start == '\0')
	{
		err_info->err_msg = make_error_msg(sh, abs_cmd, "Is a directory");
		err_info->err_num = ERR_NUM_IS_A_DIRECTORY;
		return (false);
	}
	if (access(abs_cmd, X_OK) == 0)
		return (true);
	err_info->err_msg = make_error_msg(sh, abs_cmd, strerror(errno));
	err_info->err_num = ERR_NUM_PERMISSION_DENIED;
	return (false);
}

static char	*sub_search_file_from_path(char *start, \
	char *cmd_attached_slash, t_shell *sh, t_error_exe *err_info)
{
	char		*abs_path;
	struct stat	st;
	size_t		len;

	len = 0;
	while (start[len] && start[len] != ':')
		len++;
	abs_path = ft_sh_substr(&sh->line_alloc, start, len);
	abs_path = ft_sh_strjoin(&sh->line_alloc, abs_path, cmd_attached_slash);
	if (abs_path == NULL)
		exit(EXIT_FAILURE);
	if (stat(abs_path, &st) != 0)
		return (NULL);
	if (access(abs_path, X_OK) != 0)
	{
		if (err_info->err_num == 0)
		{
			err_info->err_msg = make_error_msg(sh, abs_path, strerror(errno));
			err_info->err_num = ERR_NUM_PERMISSION_DENIED;
		}
		return (NULL);
	}
	return (abs_path);
}

char	*search_file_from_path(char *cmd, char *path, \
	t_shell *sh, t_error_exe *err_info)
{
	char	*buf;
	char	*cmd_attached_slash;
	size_t	path_start;

	if (cmd[0] == '\0')
		return (NULL);
	cmd_attached_slash = ft_sh_strjoin(&sh->line_alloc, "/", cmd);
	if (cmd_attached_slash == NULL)
		exit(EXIT_FAILURE);
	path_start = 0;
	while (path[path_start])
	{
		buf = sub_search_file_from_path(&path[path_start], \
			cmd_attached_slash, sh, err_info);
		if (buf != NULL)
			return (buf);
		while (path[path_start] && path[path_start] != ':')
			path_start++;
		if (path[path_start] == ':')
			path_start++;
	}
	return (NULL);
}

char	*get_abs_path(char *cmd, t_shell *sh, t_error_exe *err_info)
{
	const t_map	*path_node = ft_getenv(sh, "PATH");
	char		*abs_path;

	if (ft_strchr(cmd, '/'))
	{
		if (is_file_exectable(cmd, sh, err_info) == true)
			return (cmd);
		return (NULL);
	}
	if (path_node == NULL || path_node->value == NULL)
		return (NULL);
	abs_path = search_file_from_path(cmd, path_node->value, sh, err_info);
	if (abs_path == NULL)
	{
		if (err_info->err_num == 0)
		{
			err_info->err_msg = make_error_msg(sh, cmd, "command not found");
			err_info->err_num = ERR_NUM_CMD_NOT_FOUND;
		}
		return (NULL);
	}
	return (abs_path);
}
