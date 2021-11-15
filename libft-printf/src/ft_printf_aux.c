/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dienasci <dienasci@student.42sp.org.br >   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 00:25:15 by dienasci          #+#    #+#             */
/*   Updated: 2021/09/28 22:52:18 by dienasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft/libft.h"

int	print_address_hex(void *p0)
{
	int			i;
	uint64_t	p;
	size_t		len;

	p = (uint64_t)p0;
	len = 2;
	if (p == 0)
	{
		write(1, "0x0", 3);
		len++;
	}
	else
	{
		write(1, "0x", 2);
		i = (sizeof(p) << 3) - 4;
		while (((p >> i) & 0xf) == 0)
			i -= 4;
		while (i >= 0)
		{
			put_hex((p >> i) & 0xf, 0);
			i -= 4;
			len++;
		}
	}
	return (len);
}

void	ft_putunbr(long n)
{
	if (n > 4294967295)
	{
		ft_putchar_fd('0', 1);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		n = -n;
		ft_putunbr(n);
	}
	else
	{
		if (n > 9)
		{
			ft_putunbr(n / 10);
			ft_putchar_fd(n % 10 + '0', 1);
		}
		else
			ft_putchar_fd(n + '0', 1);
	}
}

void	put_hex(unsigned int n, int upper)
{
	char	*base;

	if (upper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n < 16)
		write(1, &base[n], 1);
	else
	{
		put_hex(n / 16, upper);
		put_hex(n % 16, upper);
	}
}

int	count(long n, int base)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= base;
		i++;
	}
	return (i);
}
