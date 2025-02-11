#include "so_long.h"
#include <stdio.h>
#include "mlx.h"
//here function to free anything :)
void ft_render_map(t_game **game, t_texture *texture, int is_finish, int keycode)
{
    t_game *g = *game;
    int y = 0, x;
    char tile;
    
    while (y < g->rows)
    {
        x = 0;
        while (x < g->cols)
        {
            tile = g->map->map_2d[y][x];

            if (tile == PLA_CHAR && (keycode == UP_KEY || keycode == UP_ARROW))
            {
                mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, texture->player_up, x * WIDTH, y * HEIGHT);
            }
            else if (tile == PLA_CHAR && (keycode == DOWN_KEY || keycode == DOWN_ARROW))
                mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, texture->player_do, x * WIDTH, y * HEIGHT);
            else if (tile == PLA_CHAR && (keycode == LEFT_KEY || keycode == LEFT_ARROW))
                mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, texture->player_lf, x * WIDTH, y * HEIGHT);
            else if (tile == PLA_CHAR && (keycode == RIGHT_KEY || keycode == RIGHT_ARROW))
                mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, texture->player_rg, x * WIDTH, y * HEIGHT);
            else if (tile == CL_CHAR)
                mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, texture->collect, x * WIDTH, y * HEIGHT);
            else if (tile == CL_WALL)
                mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, texture->wall, x * WIDTH, y * HEIGHT);
            else if (tile == EXIT_CHAR && is_finish)
                mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, texture->exit_open, x * WIDTH, y * HEIGHT);
            else if (tile == EXIT_CHAR)
                mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, texture->exit, x * WIDTH, y * HEIGHT);
            else if (tile == FLOOR_CHAR)
                mlx_put_image_to_window(g->mlx_ptr, g->mlx_win, texture->space, x * WIDTH, y * HEIGHT);

            x++;
        }
        y++;
    }
}
void start_game(t_game *game, int keycode)
{
    t_position pos;
    char **map = game->map->map_2d;
    pos.found_collectible = 0;
    //int y = 0, x;
    int key = keycode;
    static int count = 0;

    is_check_collectible(map, CL_CHAR, &pos.total_collectibe);
    is_check(map, PLA_CHAR, &pos);

    int new_x = pos.x;
    int new_y = pos.y;

    if ((keycode == UP_KEY || keycode == UP_ARROW) && map[pos.y - 1][pos.x] != CL_WALL)
        new_y--;
    else if ((keycode == DOWN_KEY || keycode == DOWN_ARROW) && map[pos.y + 1][pos.x] != CL_WALL)
        new_y++;
    else if ((keycode == RIGHT_KEY || keycode == RIGHT_ARROW) && map[pos.y][pos.x + 1] != CL_WALL)
        new_x++;
    else if ((keycode == LEFT_KEY || keycode == LEFT_ARROW) && map[pos.y][pos.x - 1] != CL_WALL)
        new_x--;

    if (new_x != pos.x || new_y != pos.y) 
    {
        count++; 
        if (map[new_y][new_x] == CL_CHAR)
            pos.found_collectible++;

        if (map[new_y][new_x] == EXIT_CHAR && pos.found_collectible == pos.total_collectibe)
        {
            ft_render_map(&game, &game->texture, TRUE, FALSE);
            printf("Congratulations! You won!\n");
            exit(0);
        }
        if (map[new_y][new_x] != EXIT_CHAR)
        {
        ft_putnbr_fd(count, 1);
        write(1, "\n", 1);
            map[pos.y][pos.x] = FLOOR_CHAR;
            map[new_y][new_x] = PLA_CHAR;
        }

    }
    ft_render_map(&game, &game->texture, (pos.found_collectible == pos.total_collectibe), key);
}

int manage_key(int keycode, t_game *game)
{
    if (keycode == ESC)
    {
        mlx_destroy_window(game->mlx_ptr, game->mlx_win);
        mlx_destroy_display(game->mlx_ptr);
        free(game->mlx_ptr);
        ft_error(GAME_OVER, &game->map);
    }
    else if(keycode == UP_KEY || keycode == UP_ARROW || (keycode == DOWN_KEY || keycode == DOWN_ARROW) 
            || (keycode == LEFT_KEY || keycode == LEFT_ARROW) 
            || (keycode == RIGHT_KEY || keycode == RIGHT_ARROW))
            start_game(game, keycode);
    return (0);
}

void get_size_map(char **map, int *rows, int *cols)
{
    *cols = 0;
    *rows = 0;
    while (map[*rows])
        (*rows)++;
    while (map[0][*cols])
        (*cols)++;
}
void check_texture(t_game ** game, t_texture *texture)
{
    //herre function to free any thing dont forg
   if(!texture->wall)
       ft_error(WALL_FAILED, &(*game)->map);
   else if(!texture->exit || !texture->exit_open)
       ft_error(EXIT_FAILED, &(*game)->map);
   else if(!texture->collect)
       ft_error(COLLECT_FAILED, &(*game)->map);
   else if(!texture->player_up || !texture->player_do || !texture->player_lf || !texture->player_rg)
       ft_error(PLAYER_FAILED, &(*game)->map);
   else if(!texture->space)
       ft_error(SPACE_FAILED, &(*game)->map);
}
void ft_load_textures(t_game **game, t_texture *texture)
{ 
    texture->wall = mlx_xpm_file_to_image((*game)->mlx_ptr, WALL_XPM, &texture->width, &texture->hight);
    texture->player_up = mlx_xpm_file_to_image((*game)->mlx_ptr, PLAYER_UP,&texture->width,&texture->hight);
    texture->player_do = mlx_xpm_file_to_image((*game)->mlx_ptr, PLAYER_DO,&texture->width,&texture->hight);
    texture->player_lf = mlx_xpm_file_to_image((*game)->mlx_ptr, PLAYER_LF,&texture->width,&texture->hight);
    texture->player_rg = mlx_xpm_file_to_image((*game)->mlx_ptr, PLAYER_RG,&texture->width,&texture->hight);
    texture->collect = mlx_xpm_file_to_image((*game)->mlx_ptr, COLLECT_XPM, &texture->width, &texture->hight);
    texture->exit = mlx_xpm_file_to_image((*game)->mlx_ptr, EXIT_XPM, &texture->width, &texture->hight);
    texture->exit_open = mlx_xpm_file_to_image((*game)->mlx_ptr, EXITOP_XPM, &texture->width, &texture->hight);
    texture->space = mlx_xpm_file_to_image((*game)->mlx_ptr, SPACE_XPM, &texture->width, &texture->hight);
    check_texture(game, texture);
}

void create_key(t_game *game)
{
    mlx_key_hook(game->mlx_win, manage_key, game);
}
void manage_window(t_game *game)
{
    get_size_map(game->map->map_2d, &game->rows, &game->cols);
    game->texture.width =  game->cols*64;
    game->texture.hight = game->rows*64;
    game->mlx_ptr = mlx_init();
    if (!game->mlx_ptr)
        ft_error(INV_WND, &game->map);

    game->mlx_win = mlx_new_window(game->mlx_ptr,game->texture.width, game->texture.hight, MSG);
    if (!game->mlx_win)
    {
        mlx_destroy_window(game->mlx_ptr, NULL);
        return;
    }
    ft_load_textures(&game, &game->texture);
    ft_render_map(&game, &game->texture, FALSE, RIGHT_KEY);
    create_key(game);
    mlx_loop(game->mlx_ptr);
}

void execute_game(t_game *game)
{
    manage_window(game); 
}

