/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:44:27 by revieira          #+#    #+#             */
/*   Updated: 2023/01/04 16:56:09 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*char_add(char *str, char c)
{
	int		len;
	char	*new_str;

	if (!str)
		str = ft_strdup("");
	new_str = ft_calloc(1, ft_strlen(str) + 2);
	if (!new_str)
		exit(1);
	len = ft_strlen(str);
	ft_strlcpy(new_str, str, len + 1);
	new_str[len] = c;
	if (c == '\0')
		ft_printf("%s\n", new_str);
	free(str);
	return (new_str);
}

void	handler(int sig, siginfo_t *info, void *other)
{
	static int	i;
	static char	c;
	static char	*msg;
	static int	pid;

	other = NULL;
	if (pid == 0)
		pid = info->si_pid;
	if (sig == SIGUSR1)
		c += (1 << i);
	i++;
	if (i == 8)
	{
		if (c == 0)
		{
			ft_printf("%s\n", msg);
			kill(pid, SIGUSR1);
			if (ft_strncmp(msg, "exit", ft_strlen(msg)) == 0)
			{
				free(msg);
				exit(0);
			}
			free(msg);
			msg = NULL;
			pid = 0;
		}
		else
			msg = char_add(msg, c);
		i = 0;
		c = 0;
	}
}

void	inicialize_sigaction(struct sigaction *sa)
{
	sigset_t	sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, SIGUSR1);
	sigaddset(&sigset, SIGUSR2);
	sa->sa_mask = sigset;
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = handler;
	sigemptyset(&sa->sa_mask);
}

int	main(void)
{
	struct sigaction	sa;

	inicialize_sigaction(&sa);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server pid: %d\n", getpid());
	while (1)
		pause();
}
