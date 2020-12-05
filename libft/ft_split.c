/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:14:01 by mkamei            #+#    #+#             */
/*   Updated: 2020/10/24 13:43:29 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_str_count(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (count);
}

static void	*release(char **strs, int strs_index)
{
	int i;

	i = 0;
	while (i < strs_index)
		free(strs[i++]);
	free(strs);
	return (NULL);
}

static char	**split_str(const char *s, char c, char **strs)
{
	int		i;
	int		len;
	int		strs_index;

	i = 0;
	strs_index = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			len = 0;
			while (s[i + len] != c && s[i + len] != '\0')
				len++;
			if (!(strs[strs_index] = (char *)malloc((len + 1) * sizeof(char))))
				return (release(strs, strs_index));
			ft_strlcpy(strs[strs_index++], &s[i], len + 1);
			i += len;
		}
		else
			i++;
	}
	strs[strs_index] = NULL;
	return (strs);
}

char		**ft_split(char const *s, char c)
{
	char	**strs;

	if (!(strs = (char **)malloc((get_str_count(s, c) + 1) * sizeof(char *))))
		return (NULL);
	if (!(strs = split_str(s, c, strs)))
		return (NULL);
	return (strs);
}
