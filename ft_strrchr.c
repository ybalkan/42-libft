/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 21:13:04 by ybalkan           #+#    #+#             */
/*   Updated: 2026/01/31 12:43:52 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	ch;
	char			*r;

	ch = (unsigned char)c;
	r = NULL;
	while (*s)
	{
		if (*s == ch)
			r = (char *)s;
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (r);
}
