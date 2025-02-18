/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:32:14 by ylahssin          #+#    #+#             */
/*   Updated: 2025/02/12 21:09:30 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
int	check_is_rectangle(char **map)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (map[i] && map[j])
	{
		if (ft_strlen(map[i]) != ft_strlen(map[j]))
			return (FALSE);
		i++;
		j++;
	}
	return (TRUE);
}

int	is_valid_path(char **map, int x, int y, t_position *pos)
{
	char	tmp;
	int		valid;

	if (x < 0 || y < 0 || !map[y] || !map[y][x] || map[y][x] == CL_WALL)
		return (0);
	if (map[y][x] == CL_CHAR)
		pos->found_collectible++;
	if (map[y][x] == EXIT_CHAR)
		pos->found_exit = 1;
	tmp = map[y][x];
	map[y][x] = CL_WALL;
	valid = is_valid_path(map, x - 1, y, pos) || is_valid_path(map, x + 1, y,
			pos) || is_valid_path(map, x, y - 1, pos) || is_valid_path(map, x, y
			+ 1, pos);
	(void)valid;
	map[y][x] = tmp;
	return (pos->found_collectible == pos->total_collectibe && pos->found_exit);
}

int	check_path(char **map, t_position current_pos)
{
	return (is_valid_path(map, current_pos.x, current_pos.y, &current_pos));
}
