/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:44:27 by revieira          #+#    #+#             */
/*   Updated: 2023/01/05 17:31:42 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

char	*add_char_in_str(char *str, char c)
{
	char	*new_str;
	int		i;

    i = -1;
	if (!str)
		str = ft_strdup("");
	new_str = ft_calloc(1, ft_strlen(str) + 2);
	if (!new_str)
		ft_exit_program("Error: malloc failed", 1);
    while (str[++i])
        new_str[i] = str[i];
    new_str[i] = c;
    new_str[i + 1] = '\0';
	free(str);
	return (new_str);
}

char    *print_msg(char *msg)
{
    ft_printf("%s\n", msg);
    if (ft_strncmp(msg, "exit", 4) == 0)
    {
        free(msg);
        ft_exit_program("Server stopped", 0);
    }
    free(msg);
    return (NULL);
}

void	signal_handler(int sig, siginfo_t *info, void *other)
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
			msg = print_msg(msg);
			kill(pid, SIGUSR1);
            pid = 0;
		}
		else
        {
			msg = add_char_in_str(msg, c);
            kill(pid, SIGUSR2);
        }    
		i = 0;
		c = 0;
	}
}

void	inicialize_sigaction(struct sigaction *sa)
{
	sigset_t	sigset;

	sigemptyset(&sigset);
	//sigaddset(&sigset, SIGUSR1);
	//sigaddset(&sigset, SIGUSR2);
	sa->sa_mask = sigset;
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = signal_handler;
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
