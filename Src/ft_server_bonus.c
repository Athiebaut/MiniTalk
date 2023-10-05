/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:36:41 by athiebau          #+#    #+#             */
/*   Updated: 2023/10/05 18:53:18 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minitalk.h"

void	ft_btoa(int signal, siginfo_t *caca, void *ptr)
{
	static int	c = 0;
	static int	bit = 1;
	static char	*str = NULL;

	(void)ptr;
	if (signal == -1)
		(free(str), exit(0));
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
			free(str);
			str = NULL;
			kill(caca->si_pid, SIGUSR1);
		}	
		bit = 1;
		c = 0;
	}
}

void	ft_exit(int signal)
{
	ft_btoa(-1, NULL, NULL);
}

int	main(int argc, char **argv)
{
	int	pid;
	struct sigaction ssa;

	(void)argv;
	if (argc == 1)
	{
		pid = getpid();
		ft_printf("SERVER PID : %d\n", pid);
		ssa.sa_sigaction = ft_btoa;
		sigemptyset(&ssa.sa_mask);
		ssa.sa_flags = SA_SIGINFO;
		while (1)
		{
			sigaction(SIGUSR1, &ssa, NULL);
			sigaction(SIGUSR2, &ssa, NULL);
			signal(SIGINT, &ft_exit);
			pause();
		}
	}
	else
	{
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);	
}
