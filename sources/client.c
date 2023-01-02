/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:10:14 by revieira          #+#    #+#             */
/*   Updated: 2023/01/02 18:50:29 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void    send_message(int pid, char *msg)
{
    int i;
    int j;

    i = 0;
    while (msg[i])
    {
        j = 0;
        while (j < 8)
        {
            if (msg[i] & (1 << j))
                kill(pid, SIGUSR1);
            else
                kill(pid, SIGUSR2);
            j++;
            usleep(800);
        }
        i++;
    }
}


int main(int argc, char **argv)
{
    int pid;

    if (argc != 3)
    {
        ft_printf("Usage: ./client [server pid] [message]");
        exit(0);
    }
    pid = ft_atoi(argv[1]);
    send_message(pid, argv[2]);
    return (0);
}
