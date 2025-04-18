/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:36:30 by athiebau          #+#    #+#             */
/*   Updated: 2025/04/18 21:31:13 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minitalk.h"

/**
 * @brief Handles errors related to signal operations and exits the program.
 *
 * This function is used to handle errors that occur during signal operations.
 * It prints an appropriate error message based on the signal parameter and
 * terminates the program with an exit status of 1.
 *
 * @param signal An integer representing the type of error:
 *               - 0: Error while sending a signal.
 *               - 1: Error while installing a signal handler.
 */
void	ft_error(int signal)
{
	if (signal == 0)
		ft_printf("Error while sending a signal.\n");
	if (signal == 1)
		ft_printf("Error while installing a signal handler.\n");
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
 * @brief Handles the reception of a signal and prints a message if the signal is SIGUSR2.
 *
 * This function is designed to be used as a signal handler. When the specified
 * signal is received, it checks if the signal is SIGUSR2 and, if so, prints
 * a confirmation message indicating that the message has been received.
 *
 * @param signal The signal number received by the handler.
 */
void	ft_message(int signal)
{
	if (signal == SIGUSR2)
		ft_printf("Message recieved !\n");
}

/**
 * @file ft_client_bonus.c
 * @brief This file contains the implementation of the client-side program
 *        for the MiniTalk project. It sends messages to a server process
 *        using signals.
 *
 * @details The program takes two arguments: the server's PID and the message
 *          to be sent. It converts each character of the message into binary
 *          and sends it bit by bit to the server using the SIGUSR1 and SIGUSR2
 *          signals. A null character ('\0') is sent at the end to indicate
 *          the end of the message.
 *
 * @function main
 * @param argc The number of arguments passed to the program.
 * @param argv The array of arguments. argv[1] is the server PID, and argv[2]
 *             is the message to be sent.
 * @return Returns 0 on success, or -1 on error.
 *
 * @error
 * - If the number of arguments is not 3, an error message is printed, and the
 *   program exits with -1.
 * - If the PID is invalid (less than 1), an error message is printed, and the
 *   program exits with -1.
 * - If the signal handler for SIGUSR2 cannot be set, the program calls
 *   `ft_error(1)` to handle the error.
 *
 * @note
 * - The function `ft_atoi` is used to convert the PID from a string to an
 *   integer.
 * - The function `ft_atob` is used to convert each character of the message
 *   into binary and send it to the server.
 * - The function `ft_message` is used as the signal handler for SIGUSR2.
 * - The function `ft_printf` is used to print error messages.
 */
int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = -1;
	if (signal(SIGUSR2, &ft_message) == SIG_ERR)
		ft_error(1);
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid < 1)
		{
			ft_printf("Error, wrong pid.\n");
			return (-1);
		}
		while (argv[2][++i])
			ft_atob(argv[2][i], pid);
		ft_atob('\0', pid);
	}
	else
	{
		ft_printf("Error\n");
		return (-1);
	}
	return (0);
}
