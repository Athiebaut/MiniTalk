/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:02:19 by athiebau          #+#    #+#             */
/*   Updated: 2023/10/03 15:54:31 by athiebau         ###   ########.fr       */
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
		usleep(500);
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;
	
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while(argv[2][i])
		{
			ft_atob(argv[2][i], pid);
			i++;
		}
		ft_atob('\0', pid);
	}
	else
		write(2, "Error\n", 6);
}