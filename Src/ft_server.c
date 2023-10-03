/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:42:03 by athiebau          #+#    #+#             */
/*   Updated: 2023/10/03 17:24:23 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minitalk.h"

void	ft_btoa(int signal)
{
	static int	c = 0;
	static int	bit = 0;
	static char	*str = NULL;

	if (signal == -1)
		(free(str), exit(0));
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
		if (c != '\0')
			str = ft_strjoin(str, c);
		else
		{
			ft_printf("%s\n", str);
			str = NULL;
		}	
		bit = 0;
	}
}

void	ft_exit(int signal)
{
	ft_btoa(-1);
}

int	main(int argc, char **argv)
{
	int	pid;

	(void)argv;
	if (argc == 1)
	{
		pid = getpid();
		ft_printf("SERVER PID : ");
		ft_printf("%d\n", pid);
		while (1)
		{
			signal(SIGUSR1, &ft_btoa);
			signal(SIGUSR2, &ft_btoa);
			signal(SIGINT, &ft_exit);
			usleep(500);
		}
	}
	else
		write(2, "Error\n", 6);
}
