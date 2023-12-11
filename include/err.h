/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:28:18 by kakiba            #+#    #+#             */
/*   Updated: 2023/02/22 17:39:28 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

enum {
	ERR_STATUS_NO_SUCH_FILE_OR_DIRECTORY = 1,
	ERR_STATUS_BUILTIN_INVALID_USE = 2,
	ERR_STATUS_INVALID_OPTION = 126,
	ERR_STATUS_PERMISSION_DENIED = 126,
	ERR_STATUS_CMD_NOT_FOUND = 127,
};

#endif