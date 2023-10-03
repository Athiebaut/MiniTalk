/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:26:34 by athiebau          #+#    #+#             */
/*   Updated: 2023/10/03 16:21:16 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include <stdio.h>

char	*ft_strjoin(char *s1, char c)
{
	int		i;
	char	*str;

	i = 0;
	if (!s1)
	{
		s1 = ft_calloc(2, 1);
		if (!s1)
			return (NULL);
	}
	str = malloc((sizeof(char)) * (ft_strlen(s1) + 2));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	free(s1);
	return (str);
}
