/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:36:30 by athiebau          #+#    #+#             */
/*   Updated: 2023/10/05 18:53:26 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minitalk.h"

void	ft_atob(char c, int pid)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c >> bit & 1) == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit++;
		usleep(800);
	}
}

void	ft_message(int signal)
{
	if (signal == SIGUSR2)
		ft_printf("Message recieved !\n");
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i])
		{
			ft_atob(argv[2][i], pid);
			i++;
		}
		ft_atob('\0', pid);
		/*pause();
		ft_printf("oui\n");*/
		signal(SIGUSR1, &ft_message);
	}
	else
	{
		ft_printf("Error\n");
		return (1);
	}
}