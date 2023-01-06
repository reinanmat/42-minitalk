/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:11:39 by revieira          #+#    #+#             */
/*   Updated: 2023/01/05 12:25:56 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include "libft.h"
# include <signal.h>

void	send_msg(int pid, char *msg);
void	signal_received(int sig);
char	*add_char_in_str(char *str, char c);
char	*print_msg(char *msg);
void	signal_handler(int sig, siginfo_t *info, void *other);
void	inincialize_sigaction(struct sigaction *sa);

#endif
