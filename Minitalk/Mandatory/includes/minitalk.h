/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:52:30 by revieira          #+#    #+#             */
/*   Updated: 2023/01/07 16:34:08 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <signal.h>

char	*add_char_to_str(char *str, char c);
char	*print_msg(int pid, char *msg);
void	more_bits(int pid, char *msg);
void	signal_handler(int sig, siginfo_t *info, void *context);
int		send_null(int pid);
int		send_bit(int pid, char c, int bits_left, char *msg);
void	send_msg(int pid, char *msg);
void	handler(int sig);

#endif
