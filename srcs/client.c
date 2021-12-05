/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dienasci <dienasci@student.42sp.org.br >   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 10:27:23 by dienasci          #+#    #+#             */
/*   Updated: 2021/12/05 16:31:09 by dienasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	error_check(int argc, char ***argv)
{
	int	pid;

	if (argc != 3)
	{
		ft_printf("Insufficient arguments. (usage: ./client [PID] [Message]");
		return (0);
	}
	pid = ft_atoi((*argv)[1]);
	if (!(100 <= pid && pid <= 99998))
	{
		ft_printf("Invalid PID, value must be between 99 and 10000");
		return (0);
	}
	if (!(*argv)[2])
	{
		ft_printf("Invalid message!");
		return (0);
	}
	return (1);
}

void	connection_terminate(pid_t server_pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		usleep(50);
		kill(server_pid, SIGUSR2);
	}
	ft_putstr_fd("\nDone!", 1);
	exit(0);
}

void	send_bit(char *s, pid_t pid)
{
	static int				i = 8;
	static unsigned char	c;
	static char				*str;
	static pid_t			server_pid;

	if (s)
	{
		str = s;
		server_pid = pid;
		c = *str;
	}
	if (!i)
	{
		i = 8;
		c = *(++str);
		if (!c)
			connection_terminate(server_pid);
	}
	if (c >> --i & 0x01)
		kill(server_pid, SIGUSR1);
	else if (c)
		kill(server_pid, SIGUSR2);
}

void	sig_handler(int sig, siginfo_t *siginfo, void *unused)
{
	(void)siginfo;
	(void)unused;
	if (sig == SIGUSR1)
		ft_putstr_fd("\n", 1);
	if (sig == SIGUSR2)
		ft_putchar_fd('.', 1);
	send_bit(0, 0);
}

int	main(int argc, char **argv)
{
	struct sigaction	e;
	int					pid;

	if (!error_check(argc, &argv))
		return (1);
	pid = ft_atoi(argv[1]);
	e.sa_flags = SA_SIGINFO;
	e.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &e, 0);
	sigaction(SIGUSR2, &e, 0);
	send_bit(argv[2], pid);
	while (1)
		pause();
	return (0);
}
