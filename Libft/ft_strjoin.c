/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:26:34 by athiebau          #+#    #+#             */
/*   Updated: 2025/04/18 21:28:06 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"


/**
 * ft_strjoin - Concatenates a string with a character, creating a new string.
 *
 * @s1: The original string. If NULL, a new string is allocated.
 * @c: The character to append to the string.
 *
 * This function appends the character `c` to the end of the string `s1`.
 * If `s1` is NULL, it allocates a new string with `c` as its first character.
 * The function allocates memory for the new string, which includes the
 * original string `s1`, the character `c`, and a null-terminator.
 * The original string `s1` is freed before returning the new string.
 *
 * Return: A pointer to the newly created string, or NULL if memory allocation fails.
 */
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
