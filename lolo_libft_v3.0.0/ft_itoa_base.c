/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 09:41:28 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/01/31 11:00:25 by lcoiffie         ###   ########.fr       */
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

static int			count_and_check(int n, char *base)
{
	int				i;
	unsigned int	base_length;
	unsigned int	nbr;

	base_length = ft_strlen(base);
	if (basechecking(base, base_length) == 0)
		return (-1);
	i = 1;
	if (n < 0)
	{
		i = 2;
		nbr = -n;
	}
	else
		nbr = n;
	while ((nbr / base_length) != 0)
	{
		i++;
		nbr = nbr / base_length;
	}
	return (i);
}

char				*ft_itoa_base(int n, char *base)
{
	unsigned int	nb;
	int				len;
	char			*nbr;

	len = count_and_check(n, base);
	if ((len < 0) || (!(nbr = (char *)malloc(sizeof(char) * (len + 1)))))
		return (NULL);
	nbr[len] = '\0';
	if (n < 0)
	{
		nbr[0] = '-';
		nb = -n;
	}
	else
		nb = n;
	len = len - 1;
	while ((nb / ft_strlen(base)) != 0)
	{
		nbr[len] = base[nb % ft_strlen(base)];
		nb = nb / ft_strlen(base);
		len--;
	}
	nbr[len] = base[nb % ft_strlen(base)];
	return (nbr);
}
