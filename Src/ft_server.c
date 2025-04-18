/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:42:03 by athiebau          #+#    #+#             */
/*   Updated: 2025/04/18 21:35:03 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minitalk.h"

/**
 * @brief Handles the concatenation of a character to a string.
 * 
 * This function appends a character to the given string by using
 * the `ft_strjoin` function. If memory allocation fails during
 * the process, the program will terminate with an exit code of 1.
 * 
 * @param c The character to be appended to the string.
 * @param str The string to which the character will be appended.
 * 
 * @return A pointer to the newly concatenated string.
 * 
 * @note The input string `str` must be dynamically allocated, as
 *       the function may reallocate memory for the concatenated result.
 *       The caller is responsible for freeing the returned string.
 */
char	*ft_string_handler(int c, char *str)
{
	str = ft_strjoin(str, c);
	if (!str)
		exit(1);
	return (str);
}

/**
 * @brief Converts a series of signals into a string representation.
 * 
 * This function processes signals (SIGUSR1 or SIGUSR2) to construct a string
 * by interpreting the signals as binary data. It uses static variables to
 * maintain state across multiple calls. When a null character ('\0') is
 * encountered, the constructed string is printed and freed.
 * 
 * @param signal The signal received. 
 *               - SIGUSR1: Represents a binary '1'.
 *               - SIGUSR2: Represents a binary '0'.
 *               - -1: Frees the allocated string and resets the state.
 * 
 * @note The function assumes that signals are received in the correct order
 *       to form valid characters. It uses a static buffer to accumulate the
 *       binary representation of characters.
 * 
 * @warning Ensure that the function is called with proper synchronization
 *          when used in a multi-threaded or signal-handling context.
 */
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
			str = ft_string_handler(c, str);
		else
		{
			(ft_printf("%s\n", str), free(str));
			str = NULL;
		}	
		bit = 1;
		c = 0;
	}
}

/**
 * @brief Handles program termination in case of a signal or error.
 *
 * This function is called when a signal is received or when an error occurs
 * during the installation of a signal handler. It prints an error message
 * if the signal parameter is 0, performs a custom operation using `ft_btoa`,
 * and then terminates the program with an exit code of 1.
 *
 * @param signal The signal number that triggered the termination. If 0, it
 *               indicates an error during signal handler installation.
 */
void	ft_exit(int signal)
{
	if (signal == 0)
		ft_printf("Error while installing a signal handler.\n");
	ft_btoa(-1);
	exit(1);
}

/**
 * @file ft_server.c
 * @brief Server program for MiniTalk that handles incoming signals and processes them.
 *
 * This program initializes a server that listens for specific signals (SIGUSR1, SIGUSR2, and SIGINT)
 * and processes them using custom signal handlers. It prints the server's PID to allow clients
 * to send signals to it.
 *
 * @details
 * - The server expects no arguments. If arguments are provided, it will display an error message.
 * - The server continuously listens for signals in an infinite loop.
 * - Signal handlers:
 *   - SIGUSR1 and SIGUSR2 are handled by the `ft_btoa` function.
 *   - SIGINT is handled by the `ft_exit` function, which terminates the program.
 * - If setting up any signal handler fails, the program exits with an error.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 *
 * @return Returns 0 on successful execution, or -1 if an error occurs.
 */
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
			if (signal(SIGUSR1, &ft_btoa) == SIG_ERR)
				ft_exit(0);
			if (signal(SIGUSR2, &ft_btoa) == SIG_ERR)
				ft_exit(0);
			if (signal(SIGINT, &ft_exit) == SIG_ERR)
				ft_exit (0);
		}
	}
	else
	{
		write(2, "Error\n", 6);
		return (-1);
	}
	return (0);
}
