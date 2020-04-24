/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 22:00:32 by niduches          #+#    #+#             */
/*   Updated: 2020/04/25 00:53:17 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		parse_s(char *line, t_load_vertex *array, t_mega_obj *mega)
{
	(void)array;
	(void)mega;
	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	if (*line)
		return (0);
	return (1);
}
