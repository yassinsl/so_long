#ifndef SO_LONG_H
#define SO_LONG_H

#include "../Libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include "../minilibx-linux/mlx.h"
enum e_CHECK
{
	FALSE,
	TRUE
};

#define NO_MAP "Error: Invalid Map\n"
#define PLA_CHAR 'P'
#define CL_CHAR 'C'
#define CL_WALL '1'
#define EXIT_CHAR 'E'
#define FLOOR_CHAR '0'
#define UP_KEY 119
#define DOWN_KEY 115
#define LEFT_KEY 97
#define RIGHT_KEY 100
#define UP_ARROW 65362
#define DOWN_ARROW 65364
#define LEFT_ARROW 65361
#define RIGHT_ARROW 65363
#define INV_FILE "Error\nInvalid File\n"
#define PR_DENIED "Error\nPermission Denied\n"
#define EXIT_FAILIRE 1
#define SUCCESS 0 
#define EXTENSION ".ber"
#define INV_WALL "Error\nInvalid wall in the map\n"
#define INV_REG "Error\nThe map is not valid rectangle\n"
#define INV_CH "Error\nThe map contains invalid characters\n"
#define INV_PL "Error\nInvalid number of players in the map\n"
#define INV_EX "Error\nInvalid number of exits in the map\n"
#define INV_CL "Error\nInvalid number of collectibles in the map\n"
#define INV_PATH "Error\nNO valid path to exit and collectibles\n"
#define INV_ALC "Error\nMemory allocation failed\n"
#define INV_WND "Error\nMemory Failes to craete window\n"
#define HEIGHT 64
#define WIDTH 64
#define MSG "So_long Game ;)"
#define ESC 65307
#define GAME_OVER "GAME OVER\n"
#define WALL_XPM "textures/wall.xpm"
#define PLAYER_UP "textures/show_u.xpm"
#define PLAYER_DO "textures/show_d.xpm"
#define PLAYER_LF "textures/show_l.xpm"
#define PLAYER_RG "textures/show_r.xpm"
#define COLLECT_XPM "textures/collect.xpm"
#define EXIT_XPM "textures/exit.xpm"
#define EXITOP_XPM "textures/exit_open.xpm"
#define SPACE_XPM "textures/space.xpm"

#define EXIT_FAILED "Error\nExit Load Failed\n"
#define COLLECT_FAILED "Error\nCollectible Load Failed\n"
#define SPACE_FAILED "Error\nFloor Load Failed\n"
#define PLAYER_FAILED "Error\nPlayer Load Failed\n"
#define WALL_FAILED "Error\nWall Load Failed\n"
typedef struct s_map
{
	char *name;
	int fd_map;
	char **map_2d;
} t_map;
typedef struct s_position
{
    int x;
    int y;
    int found_collectible;
    int total_collectibe;
    int found_exit;
} t_position;

typedef struct s_texture
{
    void    *wall;
    void    *space;    
    void    *player_up;
    void    *player_lf;
    void    *player_do;
    void    *player_rg;
    void    *collect;
    void    *exit;
    void    *exit_open;
    int     width;
    int    hight; 
}   t_texture;
//this is the struct the game
typedef struct s_game
{
	void *mlx_ptr;
	void *mlx_win;
	int rows;
	int cols;
	t_map *map;
	t_texture texture;
} t_game;
//Prototypes the function
void execute_game(t_game *game);
void ft_error(char *str, t_map **lst);
int is_check(char **map, char c, t_position *pos);
int is_check_collectible(char **map, char c, int *num);
#endif
