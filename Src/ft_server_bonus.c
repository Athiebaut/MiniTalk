/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:36:41 by athiebau          #+#    #+#             */
/*   Updated: 2023/10/11 13:38:06 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minitalk.h"

char	*ft_string_handler(int c, char *str, siginfo_t *info)
{
	if (c != '\0')
	{
		str = ft_strjoin(str, c);
		if (!str)
			exit(1);
	}
	else
	{
		if (kill(info->si_pid, SIGUSR2) == -1)
		{
			ft_printf("Error while sending a signal.\n");
			(free(str), exit(1));
		}
		(ft_printf("%s\n", str), free(str));
		str = NULL;
	}
	return (str);
}

void	ft_btoa(int signal, siginfo_t *info, void *ptr)
{
	static int	c = 0;
	static int	bit = 1;
	static char	*str = NULL;

	(void)ptr;
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
		ft_printf("str : %s\n", str);
		str = ft_string_handler(c, str, info);
		bit = 1;
		c = 0;
	}
}

void	ft_exit(int signal)
{
	if (signal == 0)
		ft_printf("Error while initializing sigaction structure.\n");
	if (signal == 1)
		ft_printf("Error while installing a signal handler.\n");
	ft_btoa(-1, NULL, NULL);
	exit(1);
}

void	signal_handler(struct sigaction ssa)
{
	if (sigaction(SIGUSR1, &ssa, NULL) == -1)
		ft_exit(1);
	if (sigaction(SIGUSR2, &ssa, NULL) == -1)
		ft_exit(1);
	if (signal(SIGINT, &ft_exit) == SIG_ERR)
		ft_exit(1);
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	ssa;

	(void)argv;
	if (argc == 1)
	{
		pid = getpid();
		ft_printf("SERVER PID : %d\n", pid);
		ssa.sa_sigaction = ft_btoa;
		if (sigemptyset(&ssa.sa_mask) == -1)
			ft_exit(0);
		ssa.sa_flags = SA_SIGINFO;
		while (1)
		{
			signal_handler(ssa);
		}
	}
	else
	{
		write(2, "Error\n", 6);
		return (-1);
	}
	return (0);
}
