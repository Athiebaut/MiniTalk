/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:42:03 by athiebau          #+#    #+#             */
/*   Updated: 2023/10/10 15:49:40 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minitalk.h"

void	ft_btoa(int signal)
{
	static int	c = 0;
	static int	bit = 1;
	static char	*str = NULL;

	if (signal == -1)
	{
		if (str)
			free(str);
		return ;
	}
	if (signal == SIGUSR1)
		c += bit;
	bit *= 2;
	if (bit == 256)
	{
		if (c != '\0')
		{
			str = ft_strjoin(str, c);
			if (!str)
				exit(1);
		}
		else
		{
			ft_printf("%s\n", str);
			str = NULL;
		}	
		bit = 1;
		c = 0;
	}
}

void	ft_exit(int signal)
{
	if (signal == 0)
		ft_printf("Error while installing a signal handler.\n");
	ft_btoa(-1);
	exit(1);
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
			if(signal(SIGUSR1, &ft_btoa) == SIG_ERR)
				ft_exit(0);
			if(signal(SIGUSR2, &ft_btoa) == SIG_ERR)
				ft_exit(0);
			if(signal(SIGINT, &ft_exit) == SIG_ERR)
				ft_exit (0);
		}
	}
	else
	{
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);	
}
