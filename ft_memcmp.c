/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 21:13:39 by ybalkan           #+#    #+#             */
/*   Updated: 2026/02/04 18:46:26 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*dest;
	const unsigned char	*src;
	size_t				i;

	i = 0;
	src = (unsigned char *)s2;
	dest = (unsigned char *)s1;
	while (i < n)
	{
		if (dest[i] - src[i] < 0)
			return (dest[i] - src[i]);
		else if (dest[i] - src[i] > 0)
			return (dest[i] - src[i]);
		i++;
	}
	return (0);
}
