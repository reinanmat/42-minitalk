/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:10:14 by revieira          #+#    #+#             */
/*   Updated: 2023/01/05 17:50:49 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	check_pid(char *pid)
{
	int	i;

	i = 0;
	while (pid[i])
	{
		if (!ft_isdigit(pid[i]))
			return (0);
		i++;
	}
	return (1);
}

void	send_msg(int pid, char *msg)
{
	int	i;
	int	msg_len;
	int	bits_sent;
	int	kill_ret;

	i = 0;
	msg_len = ft_strlen(msg);
	while (i < msg_len + 1)
	{
		bits_sent = 0;
		while (bits_sent < 8)
		{
			if (msg[i] & (1 << bits_sent))
				kill_ret = kill(pid, SIGUSR1);
			else
				kill_ret = kill(pid, SIGUSR2);
			if (kill_ret == -1)
				ft_exit_program("Error: invalid PID", 1);
			bits_sent++;
			usleep(900);
		}
		i++;
	}
}

void	signal_received(int sig)
{
	if (sig == SIGUSR1)
		ft_exit_program("Message received", 0);
	else if (sig == SIGUSR2)
		ft_exit_program("Unexpected error", 1);
	exit(0);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("Error: invalid number of arguments\n");
		ft_exit_program("Usage: ./client [server pid] [message]", 1);
	}
	if (!check_pid(argv[1]))
		ft_exit_program("Error: invalid PID", 1);
	signal(SIGUSR1, signal_received);
	signal(SIGUSR2, signal_received);
	send_msg(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
