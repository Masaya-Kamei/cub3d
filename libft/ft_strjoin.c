/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 17:08:44 by mkamei            #+#    #+#             */
/*   Updated: 2020/10/24 13:41:02 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	pre_len;
	size_t	suf_len;
	char	*join;

	pre_len = ft_strlen(s1);
	suf_len = ft_strlen(s2);
	if (!(join = (char *)malloc((pre_len + suf_len + 1) * sizeof(char))))
		return (NULL);
	ft_strlcpy(join, s1, pre_len + 1);
	ft_strlcpy(join + pre_len, s2, suf_len + 1);
	return (join);
}
