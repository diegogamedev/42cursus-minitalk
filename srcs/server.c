/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dienasci <dienasci@student.42sp.org.br >   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 10:27:25 by dienasci          #+#    #+#             */
/*   Updated: 2021/12/05 12:05:57 by dienasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void sig_handler(int sig, siginfo_t *siginfo, void *unused)
{
	static unsigned char c = 0x00;
	static int cnt = 0;
	static pid_t client_pid = 0;

	(void)unused;
	if (!client_pid)
		client_pid = siginfo->si_pid;
	c |= (sig == SIGUSR1);
	if (++cnt == 8)
	{
		cnt = 0;
		if (c == 0x00)
		{
			client_pid = 0;
			return;
		}
		ft_putchar_fd(c, 1);
		c = 0x00;
		kill(client_pid, SIGUSR1);
	}
	else
	{
		c <<= 1;
		kill(client_pid, SIGUSR2);
	}
}

int main(void)
{
	struct sigaction e;

	ft_printf("PID: %d", getpid());
	e.sa_flags = SA_SIGINFO;
	e.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &e, 0);
	sigaction(SIGUSR2, &e, 0);
	while (1)
		pause();
	return (0);
}
