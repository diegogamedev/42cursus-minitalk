/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dienasci <dienasci@student.42sp.org.br >   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:06:53 by dienasci          #+#    #+#             */
/*   Updated: 2021/09/14 10:41:15 by dienasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "ft_printf.h"

static int	parse_string(char *s)
{
	int		l;

	if (!s)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(s, 1);
	l = ft_strlen(s);
	return (l);
}

static int	parse_numbers(char flag, va_list *arg)
{
	unsigned int	u;
	int				i;

	if (flag == 'i' || flag == 'd' )
	{
		i = va_arg(*arg, int);
		ft_putnbr_fd(i, 1);
		return (count(i, 10));
	}
	else
	{
		u = va_arg(*arg, unsigned int);
		if (flag != 'x' && flag != 'X')
		{
			ft_putunbr(u);
			return (count(u, 10));
		}
		else
		{
			put_hex(u, flag == 'X');
			return (count(u, 16));
		}
	}
}

static int	parse(char flag, va_list *arg)
{
	if (ft_strchr("iduxX", flag))
	{
		return (parse_numbers(flag, &*arg));
	}
	else
	{
		if (flag == 's')
			return (parse_string(va_arg(*arg, char *)));
		else if (flag == 'p')
			return (print_address_hex(va_arg(*arg, void *)));
		else if (flag == 'c')
			ft_putchar_fd(va_arg(*arg, int), 1);
		else if (flag == '%')
			ft_putchar_fd(flag, 1);
		return (1);
	}
}

int	ft_printf(const char *c, ...)
{
	va_list	args;
	int		i;
	int		cnt;

	if (c == NULL)
		return (-1);
	va_start(args, c);
	cnt = 0;
	i = 0;
	while (c[i] != '\0')
	{
		if (c[i] != '%')
		{
			ft_putchar_fd(c[i], 1);
			cnt++;
		}
		else
		{
			i++;
			cnt += parse(c[i], &args);
		}
		i++;
	}
	va_end(args);
	return (cnt);
}
