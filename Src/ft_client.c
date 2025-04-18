/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:02:19 by athiebau          #+#    #+#             */
/*   Updated: 2025/04/18 21:32:45 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minitalk.h"

/**
 * @brief Handles errors related to signal sending and terminates the program.
 *
 * This function is called when an error occurs during signal sending. It prints
 * an error message to the standard output and exits the program with a status
 * code of 1.
 *
 * @param signal An integer representing the signal error type. If the value is 0,
 *               it indicates an error while sending a signal.
 */
void	ft_error(int signal)
{
	if (signal == 0)
		ft_printf("Error while sending a signal.\n");
	exit(1);
}

/**
 * @brief Sends a character to a server process as a series of binary signals.
 *
 * This function converts a character into its binary representation and sends
 * each bit to a server process identified by its PID using UNIX signals. The
 * function sends SIGUSR1 for a binary 1 and SIGUSR2 for a binary 0. If the
 * `kill` function fails to send a signal, it calls `ft_error` to handle the error.
 *
 * @param c The character to be sent as binary signals.
 * @param pid The process ID of the server to which the signals are sent.
 *
 * @note The function uses a delay of 200 microseconds between sending each bit
 *       to ensure proper signal handling by the server process.
 */
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

/**
 * @file ft_client.c
 * @brief Client program for sending messages to a server using signals.
 *
 * This program takes two arguments: a server PID and a message string. It converts
 * the message into binary format and sends it to the server process using signals.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv An array of arguments. argv[1] is the server PID, and argv[2] is the message.
 *
 * @return Returns 0 on success, or -1 on error (e.g., invalid PID or incorrect arguments).
 *
 * The program performs the following steps:
 * - Validates the number of arguments.
 * - Converts the server PID from string to integer and checks its validity.
 * - Iterates through each character of the message, converting it to binary and sending it.
 * - Sends a null character ('\0') at the end to indicate the end of the message.
 *
 * Error handling:
 * - Prints an error message and exits with -1 if the PID is invalid or the arguments are incorrect.
 *
 * Dependencies:
 * - ft_atoi: Converts a string to an integer.
 * - ft_printf: Prints formatted output to the console.
 * - ft_atob: Converts a character to binary and sends it to the server using signals.
 */
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
