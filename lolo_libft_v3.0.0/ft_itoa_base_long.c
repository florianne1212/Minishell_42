/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_long.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 09:41:28 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/01/31 11:00:16 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

static void			*ft_calloc2(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	if (!(ptr = malloc(size * count)))
		return (NULL);
	i = 0;
	while (i < (count * size))
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

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

static int			count_and_check(long int n, char *base)
{
	int					i;
	unsigned int		base_length;
	unsigned long int	nbr;

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

char				*ft_itoa_base_long(long int n, char *base)
{
	unsigned long int	nb;
	int					len;
	char				*nbr;
	int					len_base;

	len = count_and_check(n, base);
	if ((len < 0) || (!(nbr = ft_calloc2((len + 1), sizeof(char)))))
		return (NULL);
	if (n < 0)
	{
		nbr[0] = '-';
		nb = -n;
	}
	else
		nb = n;
	len = len - 1;
	len_base = ft_strlen(base);
	while (nb / len_base != 0)
	{
		nbr[len] = base[nb % len_base];
		nb = nb / len_base;
		len--;
	}
	nbr[len] = base[nb % len_base];
	return (nbr);
}
