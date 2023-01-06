/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:52:17 by revieira          #+#    #+#             */
/*   Updated: 2023/01/06 19:37:07 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

int	send_msg(int pid, char *msg)
{
	static int	i = 0;
	static int	len_msg = 0;
	static int	bits_left = 0;
	static int	saved_pid = 0;
	static char	*s_msg = NULL;

	if (saved_pid == 0)
		saved_pid = pid;
	if (s_msg == NULL)
		s_msg = ft_strdup(msg);
	if (len_msg == 0)
		len_msg = ft_strlen(msg);
	if (bits_left == 8)
	{
		bits_left = 0;
		i++;
	}
	if (i < len_msg + 1 && bits_left < 8)
		bits_left += send_bit(saved_pid, s_msg[i], bits_left, msg);
	else
	{
		free(s_msg);
		return (1);
	}
	return (0);
}

void	handler(int sig)
{
	if (sig == SIGUSR1)
		send_msg(0, 0);
	if (sig == SIGUSR2)
		ft_exit_program("Message sent successfully", 0);
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_str_is_num(argv[1]))
		ft_exit_program("Error: invalid number of arguments", 1);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	send_msg(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
}
