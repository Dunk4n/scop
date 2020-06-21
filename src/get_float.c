/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_float.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 17:04:56 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 17:56:41 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static uint	get_float_exponent(char *line, float *nb)
{
	int		tmp;
	uint	i;

	if (*line != 'e' && *line != 'E')
		return (0);
	i = get_int(line + 1, &tmp);
	if (i == 0)
		return (0);
	if (tmp == 0)
		return (i + 1);
	if (nb && tmp < 0)
		*nb /= ft_pow(10, -tmp);
	else if (nb)
		*nb *= ft_pow(10, tmp);
	return (i + 1);
}

static uint	get_uint_float(char *str, uint *nb)
{
	uint			i;

	i = 0;
	*nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (i < 9)
			*nb = *nb * 10 + str[i] - '0';
		++i;
	}
	return (i);
}

uint		get_float(char *line, float *nb)
{
	int		neg;
	uint	i;
	uint	j;
	uint	tmp;

	neg = 1;
	i = 0;
	if (*line == '-')
	{
		neg = -1;
		++i;
	}
	i += get_uint_float(line + i, &tmp);
	if (nb)
		*nb = tmp;
	if (!i || line[i] != '.')
		return (i + get_float_exponent(line + i, nb));
	++i;
	if (line[i] < '0' || line[i] > '9')
		return (i + get_float_exponent(line + i, nb));
	j = get_uint_float(line + i, &tmp);
	if (nb)
		*nb = (*nb + tmp / (double)ft_pow(10, (j > 9) ? 9 : j)) * neg;
	return (i + j + get_float_exponent(line + i + j, nb));
}
