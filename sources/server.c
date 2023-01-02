/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:44:27 by revieira          #+#    #+#             */
/*   Updated: 2023/01/02 16:56:21 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void    handle_message(int sig)
{
    static char c = 0;
    static int i = 0;

    if (sig == SIGUSR1)
        c += (1 << i);
    i++;
    if (i == 8)
    {
        if (c == 0)
            ft_printf("\n");
        else
            ft_printf("%c", c);
        c = 0;
        i = 0;
    }
}

int main(void)
{
    ft_printf("Server PID: %d\n", getpid());
    signal(SIGUSR1, handle_message);
    signal(SIGUSR2, handle_message);
    while (1)
        pause();
    return (0);
}
