/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:36:41 by athiebau          #+#    #+#             */
/*   Updated: 2025/04/18 21:33:59 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/minitalk.h"

/**
 * @brief Handles the construction of a string from received characters and 
 *        processes the string when a null character ('\0') is received.
 * 
 * @param c The character to be appended to the string. If it is '\0', the 
 *          string is considered complete and processed.
 * @param str The current string being constructed. It is dynamically allocated 
 *            and may be modified or freed within the function.
 * @param info A pointer to a siginfo_t structure containing information about 
 *             the signal sender, including the sender's process ID (si_pid).
 * 
 * @return A pointer to the updated string. If the string is complete (when 
 *         '\0' is received), the function returns NULL after freeing the string.
 * 
 * @note If memory allocation fails during string concatenation, the program 
 *       exits with a status of 1. Similarly, if sending a signal back to the 
 *       sender fails, the program exits with a status of 1 after freeing the 
 *       allocated string.
 */
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

/**
 * @brief Converts a signal into a character and processes it.
 * 
 * This function handles incoming signals (SIGUSR1 or SIGUSR2) to construct
 * a character bit by bit. Once a full character is constructed (8 bits),
 * it processes the character using the `ft_string_handler` function.
 * 
 * @param signal The signal received (SIGUSR1 or SIGUSR2).
 *               If signal is -1, it frees the allocated string and exits.
 * @param info   Pointer to a `siginfo_t` structure containing signal information.
 * @param ptr    Unused parameter (void pointer).
 * 
 * @note The function uses static variables to maintain state across calls:
 *       - `c`: Stores the current character being constructed.
 *       - `bit`: Tracks the current bit position (powers of 2).
 *       - `str`: Pointer to the string being constructed.
 * 
 * @details
 * - If `signal` is SIGUSR1, the current bit is added to `c`.
 * - The `bit` is doubled after each signal to move to the next bit position.
 * - Once 8 bits are processed (`bit == 256`), the character is passed to
 *   `ft_string_handler`, and the state is reset for the next character.
 * - If `signal` is -1, the function frees the memory allocated for `str`.
 */
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
		str = ft_string_handler(c, str, info);
		bit = 1;
		c = 0;
	}
}

/**
 * @brief Handles program termination in case of errors related to signals.
 *
 * This function is called to handle errors during signal-related operations.
 * It prints an appropriate error message based on the signal parameter and
 * performs cleanup before exiting the program with a failure status.
 *
 * @param signal An integer indicating the type of error:
 *               - 0: Error while initializing the sigaction structure.
 *               - 1: Error while installing a signal handler.
 *
 * @note The function calls `ft_btoa` with specific arguments for cleanup
 *       and then terminates the program using `exit(1)`.
 */
void	ft_exit(int signal)
{
	if (signal == 0)
		ft_printf("Error while initializing sigaction structure.\n");
	if (signal == 1)
		ft_printf("Error while installing a signal handler.\n");
	ft_btoa(-1, NULL, NULL);
	exit(1);
}

/**
 * @brief Sets up signal handlers for the server.
 * 
 * This function configures the signal handling for the server by associating
 * the provided signal action structure (`ssa`) with the SIGUSR1 and SIGUSR2
 * signals. Additionally, it sets up a handler for the SIGINT signal to ensure
 * proper cleanup and termination when the program is interrupted.
 * 
 * @param ssa A `struct sigaction` containing the signal handling configuration
 *            to be applied to SIGUSR1 and SIGUSR2.
 * 
 * @note If any of the signal handling setup fails, the program will terminate
 *       by calling `ft_exit(1)`.
 */
void	signal_handler(struct sigaction ssa)
{
	if (sigaction(SIGUSR1, &ssa, NULL) == -1)
		ft_exit(1);
	if (sigaction(SIGUSR2, &ssa, NULL) == -1)
		ft_exit(1);
	if (signal(SIGINT, &ft_exit) == SIG_ERR)
		ft_exit(1);
}

/**
 * @file ft_server_bonus.c
 * @brief Server implementation for handling signals in the MiniTalk project.
 *
 * This file contains the main function for the server-side of the MiniTalk project.
 * The server waits for incoming signals and processes them using a custom signal handler.
 *
 * @details
 * - The program retrieves the server's process ID (PID) and displays it.
 * - It sets up a signal handler using the `sigaction` structure to handle incoming signals.
 * - The server runs indefinitely in a loop, waiting for and processing signals.
 * - If the program is executed with arguments, it displays an error message and exits.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 *
 * @return Returns 0 on successful execution, or -1 if an error occurs.
 */
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
