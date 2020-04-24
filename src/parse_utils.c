/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 12:52:49 by niduches          #+#    #+#             */
/*   Updated: 2020/04/24 17:34:15 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

uint	pass_spaces(char *line)
{
	uint	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		++i;
	return (i);
}

uint	pass_word(char *line)
{
	uint	i;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		++i;
	return (i);
}

uint	get_int(char *str, int *nb)
{
	uint	i;
	int		neg;
	long	tmp;

	i = 0;
	neg = 1;
	tmp = 0;
	if (str[i] == '-')
	{
		++i;
		neg = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
		tmp = (int)(tmp * 10 + str[i++] - '0');
	*nb = tmp * neg;
	return (i);
}

uint	get_uint(char *str, uint *nb)
{
	uint			i;

	i = 0;
	*nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
		*nb = *nb * 10 + str[i++] - '0';
	return (i);
}

uint	get_float(char *line, float *nb)
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
	i += get_uint(line + i, &tmp);
	*nb = tmp;
	if (!i || line[i] != '.')
		return (i);
	++i;
	if (line[i] < '0' || line[i] > '9')
		return (i);
	j = get_uint(line + i, &tmp);
	*nb += (float)tmp / (float)ft_pow(10, j);
	*nb *= neg;
	return (i + j);
}
