/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 00:02:11 by uminomae          #+#    #+#             */
/*   Updated: 2023/02/26 18:35:26 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_sh_strdup(t_ptr_list *alc, const char *src)
{
	char	*p_cpy;
	size_t	len_src;

	if (src == NULL)
		return (NULL);
	len_src = ft_strlen(src);
	p_cpy = (char *) ft_sh_malloc(alc, sizeof(char) * (len_src + 1));
	if (p_cpy == NULL)
		return (NULL);
	ft_strlcpy(p_cpy, src, len_src + 1);
	return (p_cpy);
}

static size_t	ft_strnlen_s(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (len < maxlen && s[len] != '\0')
		len++;
	return (len);
}

char	*ft_sh_substr(t_ptr_list *alc, char const *s, size_t len)
{
	char	*p_cpy;
	size_t	m_size;

	if (s == NULL)
		return (NULL);
	if (s[0] == '\0' || len == 0)
		return (ft_sh_strdup(alc, ""));
	m_size = ft_strnlen_s(s, len);
	p_cpy = (char *) ft_sh_malloc(alc, sizeof(char) * (m_size + 1));
	if (p_cpy == NULL)
		return (NULL);
	ft_strlcpy(p_cpy, s, m_size + 1);
	return (p_cpy);
}

char	*ft_sh_strjoin(t_ptr_list *alc, char const *s1, char const *s2)
{
	char	*p_cpy;
	size_t	len_s1;
	size_t	len_s2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	p_cpy = (char *)ft_sh_malloc(alc, sizeof(char) * (len_s1 + len_s2 + 1));
	if (p_cpy == NULL)
		return (NULL);
	ft_strlcpy(p_cpy, s1, len_s1 + 1);
	ft_strlcat(p_cpy, s2, len_s1 + len_s2 + 1);
	return (p_cpy);
}
