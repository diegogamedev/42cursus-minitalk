/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dienasci <dienasci@student.42sp.org.br >   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:05:22 by dienasci          #+#    #+#             */
/*   Updated: 2021/09/14 14:18:45 by dienasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>

int		ft_printf(const char *c, ...);
int		print_address_hex(void *p0);
void	ft_putunbr(long n);
void	put_hex(unsigned int n, int upper);
int		count(long n, int base);
#endif
