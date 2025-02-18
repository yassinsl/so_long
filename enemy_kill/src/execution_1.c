/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:57:53 by ylahssin          #+#    #+#             */
/*   Updated: 2025/02/12 17:02:20 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_update_position(t_position *pos, char **map, int keycode)
{
	if ((keycode == UP_KEY || keycode == UP_ARROW)
		&& map[pos->y - 1][pos->x] != CL_WALL)
		pos->new_y--;
	else if ((keycode == DOWN_KEY || keycode == DOWN_ARROW)
		&& map[pos->y + 1][pos->x] != CL_WALL)
		pos->new_y++;
	else if ((keycode == RIGHT_KEY || keycode == RIGHT_ARROW)
		&& map[pos->y][pos->x + 1] != CL_WALL)
		pos->new_x++;
	else if ((keycode == LEFT_KEY || keycode == LEFT_ARROW)
		&& map[pos->y][pos->x - 1] != CL_WALL)
		pos->new_x--;
}

void	ft_process_movement(t_game *game, char **map, t_position *pos,
		int *count)
{
	if (pos->new_x != pos->x || pos->new_y != pos->y)
	{
		if (map[pos->new_y][pos->new_x] == CL_CHAR)
			pos->found_collectible++;
		if (map[pos->new_y][pos->new_x] == EXIT_CHAR
			&& pos->found_collectible == pos->total_collectibe)
			check_win(game);
		if (map[pos->new_y][pos->new_x] != EXIT_CHAR)
		{
			calcule_moves(++(*count));
			map[pos->y][pos->x] = FLOOR_CHAR;
			map[pos->new_y][pos->new_x] = PLA_CHAR;
		}
	}
}

void	ft_check_position(t_game *game, char **map, t_position *pos,
		int keycode)
{
	static int	count;

	ft_update_position(pos, map, keycode);
	ft_process_movement(game, map, pos, &count);
}

void	start_game(t_game *game, int keycode)
{
	t_position	pos;
	char		**map;
	int			key;

	map = game->map->map_2d;
	pos.found_collectible = 0;
	key = keycode;
	is_check_collectible(map, CL_CHAR, &pos.total_collectibe);
	is_check(map, PLA_CHAR, &pos);
	pos.new_x = pos.x;
	pos.new_y = pos.y;
	ft_check_position(game, map, &pos, keycode);
	ft_render_map(&game, &game->texture,
		(pos.found_collectible == pos.total_collectibe), key);
}

int	manage_key(int keycode, t_game *game)
{
	if (keycode == ESC)
    {
        free_all_img(&game->texture, game);
		free_windows(GAME_OVER, &game);
    }
	else if (keycode == UP_KEY || keycode == UP_ARROW || (keycode == DOWN_KEY
			|| keycode == DOWN_ARROW) || (keycode == LEFT_KEY
			|| keycode == LEFT_ARROW) || (keycode == RIGHT_KEY
			|| keycode == RIGHT_ARROW))
		start_game(game, keycode);
	return (0);
}
