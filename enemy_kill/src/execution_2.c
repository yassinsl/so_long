/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:34:56 by ylahssin          #+#    #+#             */
/*   Updated: 2025/02/12 15:38:15 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_windows(char *msg, t_game **game)
{
    mlx_destroy_window((*game)->mlx_ptr, (*game)->mlx_win);
    mlx_destroy_display((*game)-> mlx_ptr);
    free((*game)->mlx_ptr);
    if(msg)
        ft_error(msg, &(*game)->map);
}

static void	ft_put_tile(t_game *g, t_texture *t, char tile, t_norm norm)
{
	if (tile == CL_CHAR)
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win,
			t->collect, norm.b * WIDTH, norm.a * HEIGHT);
	else if (tile == CL_WALL)
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win,
			t->wall, norm.b * WIDTH, norm.a * HEIGHT);
	else if (tile == FLOOR_CHAR)
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win,
			t->space, norm.b * WIDTH, norm.a * HEIGHT);
}

static void	ft_put_player(t_game *g, t_texture *t, int key, t_norm norm)
{
	if (key == UP_KEY || key == UP_ARROW)
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win,
			t->player_up, norm.b * WIDTH, norm.a * HEIGHT);
	else if (key == DOWN_KEY || key == DOWN_ARROW)
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win,
			t->player_do, norm.b * WIDTH, norm.a * HEIGHT);
	else if (key == LEFT_KEY || key == LEFT_ARROW)
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win,
			t->player_lf, norm.b * WIDTH, norm.a * HEIGHT);
	else if (key == RIGHT_KEY || key == RIGHT_ARROW)
		mlx_put_image_to_window(g->mlx_ptr, g->mlx_win,
			t->player_rg, norm.b * WIDTH, norm.a * HEIGHT);
}

void	ft_render_map(t_game **game, t_texture *t, int is_finish, int key)
{
	t_game	*g;
	t_norm	norm;
	char	tile;

	g = *game;
	norm.a = -1;
	while (++norm.a < g->rows)
	{
		norm.b = -1;
		while (++norm.b < g->cols)
		{
			tile = g->map->map_2d[norm.a][norm.b];
			if (tile == PLA_CHAR)
				ft_put_player(g, t, key, norm);
			else if (tile == EXIT_CHAR && is_finish)
				mlx_put_image_to_window(g->mlx_ptr, g->mlx_win,
					t->exit_open, norm.b * WIDTH, norm.a * HEIGHT);
			else if (tile == EXIT_CHAR)
				mlx_put_image_to_window(g->mlx_ptr, g->mlx_win,
					t->exit, norm.b * WIDTH, norm.a * HEIGHT);
			else
				ft_put_tile(g, t, tile, norm);
		}
	}
}
