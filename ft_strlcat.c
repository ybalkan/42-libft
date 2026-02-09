/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 21:12:17 by ybalkan           #+#    #+#             */
/*   Updated: 2026/01/27 20:36:42 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] && i < size)
		++i;
	while (src[j] && (i + j + 1) < size)
	{
		dst[i + j] = src[j];
		++j;
	}
	if (i < size)
		dst[i + j] = '\0';
	while (src[j])
		++j;
	return (i + j);
}
