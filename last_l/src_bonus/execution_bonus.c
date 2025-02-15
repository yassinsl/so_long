/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:53:49 by ylahssin          #+#    #+#             */
/*   Updated: 2025/02/15 20:01:58 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//check_the_img xpm free;
#include "so_long_bonus.h"
#include <sys/time.h>
#include <stdio.h>
void free_all_img(t_texture *textures, t_game *game)
{
    //mlx_destroy_image(game->mlx_ptr, textures->wall);
    mlx_destroy_image(game->mlx_ptr, textures->player_up);
    mlx_destroy_image(game->mlx_ptr, textures->player_do);
    mlx_destroy_image(game->mlx_ptr, textures->player_lf);
    mlx_destroy_image(game->mlx_ptr, textures->player_rg);
    //mlx_destroy_image(game->mlx_ptr, textures->collect);
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
	//if (!texture->wall)
	//	free_windows(WALL_FAILED, game);
	 if (!texture->exit || !texture->exit_open)
		free_windows(EXIT_FAILED, game);
	//else if (!texture->collect)
	//	free_windows(COLLECT_FAILED, game);
	else if (!texture->player_up || !texture->player_do || !texture->player_lf
		|| !texture->player_rg)
		free_windows(PLAYER_FAILED, game);
	else if (!texture->space)
		free_windows(SPACE_FAILED, game);
}
void get_goins_xpm(t_texture *texture, t_game **game)
{
    texture->goins[0] = mlx_xpm_file_to_image((*game)->mlx_ptr, COLLECT_XPM_01,
			&texture->width, &texture->hight);
	texture->goins[1] = mlx_xpm_file_to_image((*game)->mlx_ptr, COLLECT_XPM_02,
			&texture->width, &texture->hight);
	texture->goins[2] = mlx_xpm_file_to_image((*game)->mlx_ptr, COLLECT_XPM_03,
			&texture->width, &texture->hight);
	texture->goins[3] = mlx_xpm_file_to_image((*game)->mlx_ptr, COLLECT_XPM_04,
			&texture->width, &texture->hight);
	texture->goins[4] = mlx_xpm_file_to_image((*game)->mlx_ptr, COLLECT_XPM_05,
			&texture->width, &texture->hight);
	texture->goins[5] = mlx_xpm_file_to_image((*game)->mlx_ptr, COLLECT_XPM_06,
			&texture->width, &texture->hight);
	texture->goins[6] = mlx_xpm_file_to_image((*game)->mlx_ptr, COLLECT_XPM_07,
			&texture->width, &texture->hight);
}
void get_traps_xpm(t_texture texture, t_game ** game)
{

	texture->traps[0] = mlx_xpm_file_to_image((*game)->mlx_ptr, WALL_XPM_FIRE_0,
			&texture->width, &texture->hight);
	texture->traps[1] = mlx_xpm_file_to_image((*game)->mlx_ptr, WALL_XPM_FIRE_0,
			&texture->width, &texture->hight);
	texture->traps[2] = mlx_xpm_file_to_image((*game)->mlx_ptr, WALL_XPM_FIRE_0,
			&texture->width, &texture->hight);
	texture->traps[3] = mlx_xpm_file_to_image((*game)->mlx_ptr, WALL_XPM_FIRE_0,
			&texture->width, &texture->hight);
	texture->wall[4] = mlx_xpm_file_to_image((*game)->mlx_ptr, WALL_XPM_FIRE_0,
			&texture->width, &texture->hight);
}
void	ft_load_textures(t_game **game, t_texture *texture)
{
    get_goins_xpm(texture, game);
    get_traps_xpm(textures, game);
	texture->wall[0] = mlx_xpm_file_to_image((*game)->mlx_ptr, WALL_XPM_FIRE_0,
			&texture->width, &texture->hight);
	texture->wall[1] = mlx_xpm_file_to_image((*game)->mlx_ptr, WALL_XPM_FIRE_1,
			&texture->width, &texture->hight);
	texture->wall[2] = mlx_xpm_file_to_image((*game)->mlx_ptr, WALL_XPM_FIRE_2,
			&texture->width, &texture->hight);
	texture->simple_wall = mlx_xpm_file_to_image((*game)->mlx_ptr, WALL_XPM,
			&texture->width, &texture->hight);
	texture->player_up = mlx_xpm_file_to_image((*game)->mlx_ptr, PLAYER_UP,
			&texture->width, &texture->hight);
	texture->player_do = mlx_xpm_file_to_image((*game)->mlx_ptr, PLAYER_DO,
			&texture->width, &texture->hight);
	texture->player_lf = mlx_xpm_file_to_image((*game)->mlx_ptr, PLAYER_LF,
			&texture->width, &texture->hight);
	texture->player_rg = mlx_xpm_file_to_image((*game)->mlx_ptr, PLAYER_RG,
			&texture->width, &texture->hight);
	texture->exit = mlx_xpm_file_to_image((*game)->mlx_ptr, EXIT_XPM,
			&texture->width, &texture->hight);
	texture->exit_open = mlx_xpm_file_to_image((*game)->mlx_ptr, EXITOP_XPM,
			&texture->width, &texture->hight);
	texture->space = mlx_xpm_file_to_image((*game)->mlx_ptr, SPACE_XPM,
			&texture->width, &texture->hight);
	check_texture(game, texture);
}
long get_time(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 * 1000 + time.tv_usec);
}
int update_walls(t_game *game)
{
    static long last_time;
    int static frame[100];
    long new_time;
    
    new_time = get_time();
    if(new_time - last_time > 200 * 1000)
    {
        last_time = get_time();
        frame[0] = (frame[0] + 1) % 3;
        frame[1] = (frame[1] + 1) % 6;
        game->current_frame_goins = frame[1];
        game->current_frame = frame[0];
        if(game->found_collect ==  game->total_collect)
            ft_render_map(&game, &game->texture, 1, game->key);
       else
           ft_render_map(&game, &game->texture, 0, game->key);
    }
    return (0);
}
void manage_window(t_game *game)
{
    get_size_map(game->map->map_2d, &game->rows, &game->cols);
    game->texture.width = game->cols * 64;
    game->texture.hight = game->rows * 64;
    game->current_frame = 0;
    game->current_frame_goins = 0;
    game->mlx_ptr = mlx_init();
    if (!game->mlx_ptr)
        ft_error(INV_WND, &game->map);
    game->mlx_win = mlx_new_window(game->mlx_ptr, game->texture.width,
    game->texture.hight, MSG);
    if (!game->mlx_win)
        free_windows(MLX_FAILED, &game);
    ft_load_textures(&game, &game->texture);
    ft_render_map(&game, &game->texture, FALSE, RIGHT_KEY);
    mlx_loop_hook(game->mlx_ptr, update_walls, game);
    mlx_key_hook(game->mlx_win, manage_key, game);
    mlx_loop(game->mlx_ptr);
}
void	execute_game(t_game *game)
{
	manage_window(game);
}
