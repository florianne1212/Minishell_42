/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:49:17 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 22:55:27 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Alloue et retourne une chaine de caractères représentant l’integer reçu en
** argument.
*/

#include "./includes/libft.h"

static int		count(int n)
{
	int		i;

	i = 1;
	if (n < 0)
		i = 2;
	while ((n / 10) != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	unsigned int	nb;
	int				len;
	char			*nbr;

	len = count(n);
	if (!(nbr = (char *)malloc(sizeof(char) * (len + 1))))
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
	while ((nb / 10) != 0)
	{
		nbr[len] = (nb % 10) + '0';
		nb = nb / 10;
		len--;
	}
	nbr[len] = (nb % 10) + '0';
	return (nbr);
}
