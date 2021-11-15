/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dienasci <dienasci@student.42sp.org.br >   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 10:27:23 by dienasci          #+#    #+#             */
/*   Updated: 2021/11/15 11:54:47 by dienasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	feedback(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if(sig == SIGCONT)
		ft_printf(".");
}

void send_char(int *bits, int PID)
{
	int	index;

	index = 0;
	while (index < 8)
	{
		if (bits[index] == 0)
		{
			kill(PID, SIGUSR1);
			pause();
			usleep(50000);
			index++;
		}
		else
		{
			kill(PID, SIGUSR2);
			pause();
			usleep(50000);
			index++;
		}
	}
}

void	codify(int PID, char *text)
{
	int	binary[8];
	int	i;
	int	j;
	unsigned char	c;

	i = 0;
	while(text[i])
	{
		c = text[i];
		j = 0;
		while(j < 8)
		{
			binary[7 - j] = (c >> j) & 1;
			j++;
		}
		binary[j] = '\0';
		send_char(binary, PID);
		i++;
	}
}

int main(int argc, char **argv)
{
	int					PID;
	char				*text;
	struct sigaction	a;

	if (argc != 3)
	{
		ft_printf("Wrong Usage: ./client [PID] [text]");
		exit(0);
	}
	a.sa_flags = SA_SIGINFO;
	a.sa_sigaction = feedback;
	sigaction(SIGCONT, &a, 0);
	PID = ft_atoi(argv[1]);
	text = argv[2];
	ft_printf("Sending \"%s\" to %d", text, PID);
	codify(PID, text);
	exit(0);
}
