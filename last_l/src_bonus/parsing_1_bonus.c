/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:02:54 by ylahssin          #+#    #+#             */
/*   Updated: 2025/02/12 13:22:48 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_one(char *map)
{
	while (*map)
	{
		if (*map != '1')
			return (FALSE);
		map++;
	}
	return (TRUE);
}

int	is_check_one(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if ((i == 0 || i == (int)(ft_strlen(map) - 1)) && map[i] != '1')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	check_the_wall(char **map, int idx)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if ((i == 0 || i == idx - 1) && !is_one(map[i]))
			return (FALSE);
		else if (!is_check_one(map[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	check_all_map(t_map *map, int idx)
{
	t_position	position;

	position = (t_position){0};
	if (!check_the_wall(map->map_2d, idx))
		ft_error(INV_WALL, &map);
	else if (!check_is_rectangle(map->map_2d))
		ft_error(INV_REG, &map);
	else if (!check_valid_chars(map->map_2d))
		ft_error(INV_CH, &map);
	else if (!is_check(map->map_2d, EXIT_CHAR, &position))
		ft_error(INV_EX, &map);
	else if (!is_check(map->map_2d, PLA_CHAR, &position))
		ft_error(INV_PL, &map);
	else if (!is_check_collectible(map->map_2d, CL_CHAR,
			&position.total_collectibe))
		ft_error(INV_CL, &map);
	else if (!check_path(map->map_2d, position))
		ft_error(INV_PATH, &map);
}

void	ft_read_map(t_map *map)
{
	int		i;
	char	*line;
	char	*all_map;
	char	*tmp;

	i = 0;
	all_map = NULL;
	while (1)
	{
		tmp = all_map;
		line = get_next_line(map->fd_map);
		if (!line)
			break ;
		all_map = ft_strjoin(all_map, line);
		free(tmp);
		if (line[0] == '\n')
			free_all(line, all_map, &map);
		free(line);
	}
	map->map_2d = ft_split(all_map, '\n');
	free(all_map);
	close(map->fd_map);
	if (!map->map_2d)
		ft_error(NO_MAP, NULL);
	check_all_map(map, i - 1);
}
