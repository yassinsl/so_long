/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:53:49 by ylahssin          #+#    #+#             */
/*   Updated: 2025/02/14 13:58:23 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//check_the_img xpm free;
#include "so_long.h"

void free_all_img(t_texture *textures, t_game *game)
{
    mlx_destroy_image(game->mlx_ptr, textures->wall);
    mlx_destroy_image(game->mlx_ptr, textures->player_up);
    mlx_destroy_image(game->mlx_ptr, textures->player_do);
    mlx_destroy_image(game->mlx_ptr, textures->player_lf);
    mlx_destroy_image(game->mlx_ptr, textures->player_rg);
    mlx_destroy_image(game->mlx_ptr, textures->collect);
    mlx_destroy_image(game->mlx_ptr, textures->exit);
    mlx_destroy_image(game->mlx_ptr, textures->exit_open);
    mlx_destroy_image(game->mlx_ptr, textures->space);
}
void	get_size_map(char **map, int *rows, int *cols)
{
	*cols = 0;
	*rows = 0;
	while (map[*rows])
		(*rows)++;
	while (map[0][*cols])
		(*cols)++;
}

void	check_texture(t_game **game, t_texture *texture)
{
	if (!texture->wall)
		free_windows(WALL_FAILED, game);
	else if (!texture->exit || !texture->exit_open)
		free_windows(EXIT_FAILED, game);
	else if (!texture->collect)
		free_windows(COLLECT_FAILED, game);
	else if (!texture->player_up || !texture->player_do || !texture->player_lf
		|| !texture->player_rg)
		free_windows(PLAYER_FAILED, game);
	else if (!texture->space)
		free_windows(SPACE_FAILED, game);
}

void	ft_load_textures(t_game **game, t_texture *texture)
{
	texture->wall = mlx_xpm_file_to_image((*game)->mlx_ptr, WALL_XPM,
			&texture->width, &texture->hight);
	texture->player_up = mlx_xpm_file_to_image((*game)->mlx_ptr, PLAYER_UP,
			&texture->width, &texture->hight);
	texture->player_do = mlx_xpm_file_to_image((*game)->mlx_ptr, PLAYER_DO,
			&texture->width, &texture->hight);
	texture->player_lf = mlx_xpm_file_to_image((*game)->mlx_ptr, PLAYER_LF,
			&texture->width, &texture->hight);
	texture->player_rg = mlx_xpm_file_to_image((*game)->mlx_ptr, PLAYER_RG,
			&texture->width, &texture->hight);
	texture->collect = mlx_xpm_file_to_image((*game)->mlx_ptr, COLLECT_XPM,
			&texture->width, &texture->hight);
	texture->exit = mlx_xpm_file_to_image((*game)->mlx_ptr, EXIT_XPM,
			&texture->width, &texture->hight);
	texture->exit_open = mlx_xpm_file_to_image((*game)->mlx_ptr, EXITOP_XPM,
			&texture->width, &texture->hight);
	texture->space = mlx_xpm_file_to_image((*game)->mlx_ptr, SPACE_XPM,
			&texture->width, &texture->hight);
	check_texture(game, texture);
}

void	manage_window(t_game *game)
{
	get_size_map(game->map->map_2d, &game->rows, &game->cols);
	game->texture.width = game->cols * 64;
	game->texture.hight = game->rows * 64;
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		ft_error(INV_WND, &game->map);
	game->mlx_win = mlx_new_window(game->mlx_ptr, game->texture.width,
			game->texture.hight, MSG);
	if (!game->mlx_win)
		free_windows(MLX_FAILED, &game);
	ft_load_textures(&game, &game->texture);
	ft_render_map(&game, &game->texture, FALSE, RIGHT_KEY);
	mlx_key_hook(game->mlx_win, manage_key, game);
	mlx_loop(game->mlx_ptr);
}

void	execute_game(t_game *game)
{
	manage_window(game);
}
