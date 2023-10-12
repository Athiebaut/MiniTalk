/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:02:19 by athiebau          #+#    #+#             */
/*   Updated: 2023/10/12 13:47:02 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minitalk.h"

void	ft_error(int signal)
{
	if (signal == 0)
		ft_printf("Error while sending a signal.\n");
	exit(1);
}

void	ft_atob(char c, int pid)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c >> bit & 1) == 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				ft_error(0);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				ft_error(0);
		}
		bit++;
		usleep(200);
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid < 1)
		{
			ft_printf("Error, wrong pid.\n");
			return (-1);
		}
		while (argv[2][i])
		{
			ft_atob(argv[2][i], pid);
			i++;
		}
		ft_atob('\0', pid);
	}
	else
	{
		ft_printf("Error\n");
		return (-1);
	}
}
