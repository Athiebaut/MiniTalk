/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:42:03 by athiebau          #+#    #+#             */
/*   Updated: 2023/10/03 15:56:26 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minitalk.h"

void	ft_btoa(int signal)
{
	static int	c;
	static int	bit;
	static char	str[4000];
	int i;

	if (bit == 0)
	{
		bit = 1;
		c = 0;
	}
	if (signal == SIGUSR1)
		c += bit;
	bit *= 2;
	if (bit == 256)
	{
		if (str[0] == '\0')
			str[0] = c;
		else
		{
			i = ft_strlen(str);
			str[i] = c; 
		}
		if (c == 0)
		{
			ft_printf("%s\n", str);
			ft_bzero(str, ft_strlen(str));
		}
		bit = 0;
	}
}

int	main(int argc, char **argv)
{
	
	(void)argv;
	int	pid;

	if (argc == 1)
	{
		pid = getpid();
		ft_printf("SERVER PID : ");
		ft_printf("%d\n", pid);
		while (1)
		{
			signal(SIGUSR1, &ft_btoa);	
			signal(SIGUSR2, &ft_btoa);
			usleep(500);
		}
	}
	else
		write(2, "Error\n", 6);
}