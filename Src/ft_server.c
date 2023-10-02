/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:42:03 by athiebau          #+#    #+#             */
/*   Updated: 2023/10/02 15:42:57 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minitalk.h"

void	ft_btoa(int signal)
{
	static int	c;
	static int	bit;
	
	if (bit == 0)
	{
		bit = 1;
		c = 0;
	}
	if (signal == 10)
		c += bit;
	bit *= 2; 
	if (bit == 256)
	{
		ft_printf("%c", c);
		bit = 0;
		c = 0;
	}
}

int	main(int argc, char **argv)
{
	
	(void)argv;
	int	pid;

	if (argc == 1)
	{
		pid = getpid();
		ft_printf("%d\n", pid);
		while (1)
		{
			signal(SIGUSR1, &ft_btoa);	
			signal(SIGUSR2, &ft_btoa);
		}
	}
	else
		ft_printf("Error\n");
}