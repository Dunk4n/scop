/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 12:52:49 by niduches          #+#    #+#             */
/*   Updated: 2020/07/06 13:22:20 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

uint	pass_spaces(char *line)
{
	uint	i;

	i = 0;
	while (line[i] == ' ' || (line[i] >= '\t' && line[i] <= '\r'))
		++i;
	return (i);
}

uint	pass_word(char *line)
{
	uint	i;

	i = 0;
	while (line[i] && !(line[i] == ' ' || (line[i] >= '\t' && line[i] <= '\r')))
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
