/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:55:05 by ylahssin          #+#    #+#             */
/*   Updated: 2025/02/15 20:10:04 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../Libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <mlx.h>
# include <unistd.h>

enum			e_CHECK
{
	FALSE,
	TRUE,
};

# define KEY 2
# define NO_MAP "Error\nInvalid Map\n"
# define PLA_CHAR 'P'
# define CL_CHAR 'C'
# define CL_WALL '1'
# define EXIT_CHAR 'E'
# define FLOOR_CHAR '0'
# define UP_KEY 119
# define DOWN_KEY 115
# define LEFT_KEY 97
# define RIGHT_KEY 100
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define INV_FILE "Error\nInvalid File\n"
# define PR_DENIED "Error\nPermission Denied\n"
# define EXIT_FAILIRE 1
# define SUCCESS 0
# define EXTENSION ".ber"
# define INV_WALL "Error\nInvalid wall in the map\n"
# define INV_REG "Error\nThe map is not valid rectangle\n"
# define INV_CH "Error\nThe map contains invalid characters\n"
# define INV_PL "Error\nInvalid number of players in the map\n"
# define INV_EX "Error\nInvalid number of exits in the map\n"
# define INV_CL "Error\nInvalid number of collectibles in the map\n"
# define INV_PATH "Error\nNO valid path to exit and collectibles\n"
# define INV_ALC "Error\nMemory allocation failed\n"
# define INV_WND "Error\nMemory Failes to craete window\n"
# define HEIGHT 64
# define WIDTH 64
# define MSG "So_long Game ;)"
# define ESC 65307
# define GAME_OVER "GAME OVER\n"
# define WALL_XPM "textures/wall.xpm"
# define WALL_XPM_FIRE_0 "textures/fire2_wall_xpm/fire2_wall_00.xpm"
# define WALL_XPM_FIRE_1 "textures/fire2_wall_xpm/fire2_wall_01.xpm"
# define WALL_XPM_FIRE_2 "textures/fire2_wall_xpm/fire2_wall_02.xpm"
# define WALL_XPM_FIRE_3 "textures/fire2_wall_xpm/fire2_wall_03.xpm"
# define WALL_XPM_FIRE_4 "textures/fire2_wall_xpm/fire2_wall_04.xpm"
# define WALL_XPM_FIRE_5 "textures/fire2_wall_xpm/fire2_wall_05.xpm"
# define PLAYER_UP "textures/show_u.xpm"
# define PLAYER_DO "textures/show_d.xpm"
# define PLAYER_LF "textures/show_l.xpm"
# define PLAYER_RG "textures/show_r.xpm"
# define COLLECT_XPM_01 "textures/goins_xpm/goins_wall_00.xpm"
# define COLLECT_XPM_02 "textures/goins_xpm/goins_wall_01.xpm"
# define COLLECT_XPM_03 "textures/goins_xpm/goins_wall_02.xpm"
# define COLLECT_XPM_04 "textures/goins_xpm/goins_wall_03.xpm"
# define COLLECT_XPM_05 "textures/goins_xpm/goins_wall_04.xpm"
# define COLLECT_XPM_06 "textures/goins_xpm/goins_wall_05.xpm"
# define COLLECT_XPM_07 "textures/goins_xpm/goins_wall_06.xpm"
#define TRAPS_XPM_0 "/textures/traps_xpm/traps_wall_00.xpm"
#define TRAPS_XPM_1 "/textures/traps_xpm/traps_wall_01.xpm"
#define TRAPS_XPM_2 "/textures/traps_xpm/traps_wall_02.xpm"
#define TRAPS_XPM_3 "/textures/traps_xpm/traps_wall_03.xpm"
#define TRAPS_XPM_4 "/textures/traps_xpm/traps_wall_04.xpm"
# define EXIT_XPM "textures/exit.xpm"
# define EXITOP_XPM "textures/exit_open.xpm"
# define SPACE_XPM "textures/space.xpm"
# define EXIT_FAILED "Error\nExit Load Failed\n"
# define COLLECT_FAILED "Error\nCollectible Load Failed\n"
# define SPACE_FAILED "Error\nFloor Load Failed\n"
# define PLAYER_FAILED "Error\nPlayer Load Failed\n"
# define WALL_FAILED "Error\nWall Load Failed\n"
# define MLX_FAILED "Error\nMLX Window Failed\n"
# define ANIMATION_SPEED 10
# define TOTAL_FRAMES 6

typedef struct s_map
{
	char		*name;
	int			fd_map;
	char		**map_2d;
}				t_map;
typedef struct s_position
{
	int			x;
	int			y;
	int			new_x;
	int			new_y;
	int			found_collectible;
	int			total_collectibe;
	int			found_exit;
}				t_position;
typedef struct s_norm
{
	int			a;
	int			b;
}				t_norm;
typedef struct s_texture
{
    void *goins[7];
    void *traps[5];
    void * simple_wall;
	void		*wall[6];
	void		*space;
	void		*player_up;
	void		*player_lf;
	void		*player_do;
	void		*player_rg;
	void		*exit;
	void		*exit_open;
	int			width;
	int			hight;
}				t_texture;
typedef struct s_game
{
	void		*mlx_ptr;
	void		*mlx_win;
	int			rows;
	int			cols;
	t_map		*map;
	t_texture	texture;
    int found_collect;
    int total_collect;
    int key;
    int current_frame;
    int current_frame_goins;
}				t_game;

int				check_the_wall(char **map, int idx);
void			free_all(char *line, char *all_map, t_map **map);
void			ft_read_map(t_map *map);
void			check_all_map(t_map *map, int idx);
int				check_the_wall(char **map, int idx);
int				is_one(char *map);
int				is_check_one(char *map);
void			ft_lst_free(t_map **map);
void			ft_error(char *str, t_map **lst);
void			execute_game(t_game *game);
void			ft_error(char *str, t_map **lst);
int				is_check(char **map, char c, t_position *pos);
int				is_check_collectible(char **map, char c, int *num);
int				is_valid_chars(char c);
int				check_valid_chars(char **map);
int				is_check(char **map, char c, t_position *pos);
int				check_is_rectangle(char **map);
int				is_valid_path(char **map, int x, int y, t_position *pos);
int				check_path(char **map, t_position current_pos);
void			execute_game(t_game *game);
void			ft_load_textures(t_game **game, t_texture *texture);
void			check_texture(t_game **game, t_texture *texture);
void			get_size_map(char **map, int *rows, int *cols);
int				manage_key(int keycode, t_game *game);
void			start_game(t_game *game, int keycode);
void			ft_check_position(t_game *game, char **map, t_position *pos,
					int keycode);
void			check_win(t_game *game);
void			calcule_moves(int count);
void			ft_render_map(t_game **game, t_texture *texture, int is_finish,
					int keycode);
void free_windows(char *msg, t_game **game);
void free_all_img(t_texture *textures, t_game *game);
#endif
