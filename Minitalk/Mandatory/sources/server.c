/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:00:50 by revieira          #+#    #+#             */
/*   Updated: 2023/01/06 19:27:09 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*add_char_to_str(char *str, char c)
{
	int		i;
	char	*new_str;

	if (!str)
		str = (ft_strdup(""));
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new_str)
		return (NULL);
	i = -1;
	while (str[++i])
		new_str[i] = str[i];
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(str);
	return (new_str);
}

char	*print_msg(int pid, char *msg)
{
	ft_printf("%s\n", msg);
	if (kill(pid, SIGUSR2) == -1)
	{
		if (msg)
			free(msg);
		ft_exit_program("Error: could not send signal to client", 1);
	}
	if (!ft_strcmp(msg, "exit"))
	{
		free(msg);
		ft_exit_program("Server exiting\n", 0);
	}
	free(msg);
	return (NULL);
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static int	bits_received = 0;
	static int	pid = 0;
	static char	c = 0;
	static char	*msg = NULL;

	context = NULL;
	if (!pid)
		pid = info->si_pid;
	if (sig == SIGUSR2)
		c += (1 << bits_received);
	bits_received++;
	if (kill(pid, SIGUSR1) == -1)
		ft_exit_program("Error: could not send signal to client\n", 1);
	if (bits_received == 8)
	{
		if (c == 0)
		{
			msg = print_msg(pid, msg);
			pid = 0;
		}
		else
			msg = add_char_to_str(msg, c);
		c = 0;
		bits_received = 0;
	}
}

void	inict_signals(struct sigaction *s_sa)
{
	sigset_t	sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, SIGUSR1);
	sigaddset(&sigset, SIGUSR2);
	s_sa->sa_handler = NULL;
	s_sa->sa_mask = sigset;
	s_sa->sa_flags = SA_SIGINFO;
	s_sa->sa_sigaction = signal_handler;
}

int	main(void)
{
	struct sigaction	s_sa;

	inict_signals(&s_sa);
	sigaction(SIGUSR1, &s_sa, NULL);
	sigaction(SIGUSR2, &s_sa, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
}
