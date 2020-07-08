/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 11:18:57 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/01/31 11:02:21 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

static unsigned int	basechecking(char *base, unsigned int nb)
{
	int i;
	int j;

	i = 0;
	if (nb <= 1)
		return (0);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		j = 1;
		while (base[i + j])
		{
			if (base[i + j] == base[i])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void				ft_putnbr_base(int nbr, char *base)
{
	unsigned int	nb;
	unsigned int	base_length;

	base_length = ft_strlen(base);
	if (basechecking(base, base_length) == 0)
		return ;
	if (nbr >= 0)
		nb = nbr;
	if (nbr < 0)
	{
		nb = (unsigned int)-nbr;
		ft_putchar_fd('-', 1);
	}
	if (nb >= base_length)
	{
		ft_putnbr_base(nb / base_length, base);
		ft_putchar_fd(base[nb % base_length], 1);
	}
	else
		ft_putchar_fd(base[nb % base_length], 1);
}
