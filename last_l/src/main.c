/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:37:32 by ylahssin          #+#    #+#             */
/*   Updated: 2025/02/13 11:28:25 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
char	*find_name(char *str)
{
	char	*find;

	find = ft_strchr(str, '/');
	if ((find && find[1] == '.') || str[0] == '.')
		return (NULL);
	return (ft_strstr(str, EXTENSION));
}

void	ft_check_map(char *str, t_map *map)
{
	map->name = find_name(str);
	if (!map->name || ft_strlen(map->name) != ft_strlen(EXTENSION))
		ft_error(INV_FILE, &map);
	map->fd_map = open(str, O_RDONLY);
	if (map->fd_map == -1)
		ft_error(PR_DENIED, &map);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac < 2)
		ft_error(NO_MAP, NULL);
	game.map = malloc(sizeof(t_map));
	if (!game.map)
		ft_error("Memory allocation failed!", NULL);
	ft_check_map(av[1], game.map);
	ft_read_map(game.map);
	execute_game(&game);
	ft_lst_free(&game.map);
	return (SUCCESS);
}
