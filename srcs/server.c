/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dienasci <dienasci@student.42sp.org.br >   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 10:27:25 by dienasci          #+#    #+#             */
/*   Updated: 2021/11/15 11:54:10 by dienasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	power(int base, int a)
{
	if (a != 0)
		return (base * power(base, a - 1));
	else
		return (1);
}

void	decode(char *bits)
{
	unsigned char	c;
	int				index;

	index = 0;
	c = 0;
	while (bits[index])
	{
		if (bits[index] == '1')
			c += power(2, 7 - index);
		index++;
	}
	ft_printf("%c", c);
}

void	listener(int sig, siginfo_t *info, void *context)
{
	static int	count = 0;
	static char	bits[8];

	(void)context;
	if (sig == SIGUSR1)
		bits[count] = '0';
	if (sig == SIGUSR2)
		bits[count] = '1';
	count++;
	if (count == 8)
	{
		decode(bits);
		count = 0;
	}
	kill(info->si_pid, SIGCONT);
}

int	main(void)
{
	struct sigaction	a;

	ft_printf("PID: %d\nWaiting for Signals\n", getpid());
	a.sa_flags = SA_SIGINFO;
	a.sa_sigaction = listener;
	sigaction(SIGUSR1, &a, 0);
	sigaction(SIGUSR2, &a, 0);
	while (1)
	{
		pause();
	}
}
