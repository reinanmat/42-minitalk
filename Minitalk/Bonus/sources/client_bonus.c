/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:10:14 by revieira          #+#    #+#             */
/*   Updated: 2023/01/04 16:50:51 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	error(char *s)
{
	ft_printf("%s\n", s);
	exit(1);
}

void	send_message(int pid, char *msg)
{
	int	i;
    int len_msg;
	int	bits_sent;
	int	kill_ret;

	i = 0;
    len_msg = ft_strlen(msg);
	while (i < len_msg + 1)
	{
		bits_sent = 0;
		while (bits_sent < 8)
		{
			if (msg[i] & (1 << bits_sent))
				kill_ret = kill(pid, SIGUSR1);
			else
				kill_ret = kill(pid, SIGUSR2);
			if (kill_ret == -1)
				error("Error: invalid PID");
			bits_sent++;
			usleep(700);
		}
		i++;
	}
}

void    signal_handler(int sig)
{
    if (sig == SIGUSR1)
        ft_printf("Message sent successfully!\n");
    else if (sig == SIGUSR2)
        error("Unexpected error");
    exit(0);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
    {
		ft_printf("Error: invalid number of arguments\n");
        error("usage: ./client [server pid] [message]");
    }
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
	send_message(ft_atoi(argv[1]), argv[2]);
    while (1)
        pause();
}
