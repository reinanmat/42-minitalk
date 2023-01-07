/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:52:17 by revieira          #+#    #+#             */
/*   Updated: 2023/01/07 16:28:21 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	send_null(int pid)
{
	if (kill(pid, SIGUSR1) == -1)
		ft_exit_program("Error: could not send signal to server", 1);
	return (1);
}

int	send_bit(int pid, char c, int bits_left, char *msg)
{
	if (c & (1 << bits_left))
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			if (msg)
				free(msg);
			ft_exit_program("Error: could not send signal to server", 1);
		}
	}
	else
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			if (!msg)
				free(msg);
			ft_exit_program("Error: could not send signal to server", 1);
		}
	}
	return (1);
}

void	send_msg(int pid, char *msg)
{
	static int	i = 0;
	static int	len_msg = 0;
	static int	bits_left = 0;
	static int	saved_pid = 0;
	static char	*saved_msg = NULL;

	if (!saved_pid)
		saved_pid = pid;
	if (!len_msg)
		len_msg = ft_strlen(msg);
	if (!saved_msg && len_msg > 0)
		saved_msg = ft_strdup(msg);
	if (bits_left == 8)
	{
		bits_left = 0;
		i++;
	}
	if (len_msg == 0 && i == 0)
		bits_left += send_null(saved_pid);
	else if (i < len_msg + 1)
		bits_left += send_bit(saved_pid, saved_msg[i], bits_left, saved_msg);
	else
		free(saved_msg);
}

void	handler(int sig)
{
	if (sig == SIGUSR1)
		send_msg(0, 0);
	else if (sig == SIGUSR2)
		ft_exit_program("Message sent successfully", 0);
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_str_is(argv[1], ft_isdigit))
	{
		ft_printf("Error: invalid arguments\n");
		ft_exit_program("Usage: ./client [server pid] [message]", 1);
	}
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	send_msg(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
}
