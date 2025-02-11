#include "so_long.h"
#include <stdio.h>

void ft_lst_free(t_map **map)
{
	int i = 0;

	if(!map)
		return;
	if((*map)->map_2d)
	{
		while((*map)->map_2d[i])
			free((*map)->map_2d[i++]);
		free((*map)->map_2d);
	}
	free(*map);
}
void ft_error(char *str, t_map **lst)
{
    write(2, str, ft_strlen(str));
    if (lst)
        ft_lst_free(lst);
    exit(EXIT_FAILURE);
}

void ft_check_map(char *str, t_map *map)
{
    map->name = ft_strstr(str, EXTENSION);
    if (!map->name || ft_strlen(map->name) != ft_strlen(EXTENSION))
            ft_error(INV_FILE, &map);
    map->fd_map = open(str, O_RDONLY);
    if (map->fd_map == -1)
        ft_error(PR_DENIED, &map);
}

int is_one(char *map)
{
    while (*map)
    {
        if (*map != '1')
            return (FALSE);
        map++;
    }
    return (TRUE);
}

int is_check_one(char *map)
{
    int i = 0;

    while (map[i])
    {
        if ((i == 0 || i == (int)(ft_strlen(map) - 1)) && map[i] != '1')
            return (FALSE);
        i++;
    }
    return (TRUE);
}

int check_the_wall(char **map, int idx)
{
    int i = 0;

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

int check_is_rectangle(char **map)
{
    int i = 0, j = 1;

    while (map[i] && map[j])
    {
        if (ft_strlen(map[i]) != ft_strlen(map[j]))
            return (FALSE);
        i++;
        j++;
    }
    return (TRUE);
}

int is_valid_chars(char c)
{
    return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}

int check_valid_chars(char **map)
{
    int i = 0, j;

    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (!is_valid_chars(map[i][j]))
                return (FALSE);
            j++;
        }
        i++;
    }
    return (TRUE);
}

int is_check(char **map, char c, t_position *pos)
{
    int i = 0, j, count = 0;

    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
        if (map[i][j] == c)
	    {
		if(map[i][j] == PLA_CHAR)
		{
			pos->y = i;
			pos->x = j;
		}
                count++;
	    }
            j++;
        }
        i++;
    }
    return (count == 1);
}

int is_check_collectible(char **map, char c, int *num)
{
    int i = 0, j, count = 0;

    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == c)
                count++;
            j++;
        }
        i++;
    }
    *num = count;
    return (count >= 1);
}
//here i use the Depth force search 😊 : backtrack 
int is_valid_path(char **map, int x, int y, t_position *pos)
{
	char tmp;

	if(x < 0 || y < 0 || !map[y] || !map[y][x] || map[y][x] == CL_WALL)
		return(0);
	if(map[y][x] == CL_CHAR)
		pos->found_collectible++;
	if(map[y][x] == EXIT_CHAR)
		pos->found_exit = 1;
	tmp = map[y][x];
	map[y][x] = CL_WALL;
	//this katakhod int chof liha lhal;
	int valid = is_valid_path(map, x - 1, y, pos)  ||
		    is_valid_path(map, x + 1, y, pos)  ||
		    is_valid_path(map, x , y - 1, pos) ||
		    is_valid_path(map, x, y + 1, pos);
	(void)valid;
	map[y][x] = tmp;
	return(pos->found_collectible == pos->total_collectibe && pos->found_exit);
}
int check_path(char **map, t_position current_pos)
{	
	return(is_valid_path(map, current_pos.x,current_pos.y, &current_pos));
}
void check_all_map(t_map *map, int idx)
{
    t_position position;

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
    else if (!is_check_collectible(map->map_2d, CL_CHAR, &position.total_collectibe))
        ft_error(INV_CL, &map);
    else if (!check_path(map->map_2d, position))
        ft_error(INV_PATH, &map);
}

void ft_read_map(t_map *map)
{
    char *line;
    int i = 0;
    char *all_map = NULL, *tmp;
    while (1)
    {
	tmp = all_map;
        line = get_next_line(map->fd_map);
        if (!line)
            break;
        all_map = ft_strjoin(all_map, line);
	free(tmp);
        free(line);
    }
    map->map_2d = ft_split(all_map, '\n');
    free(all_map);
    close(map->fd_map);
    if(!map->map_2d)
	    ft_error(NO_MAP, NULL);
    check_all_map(map, i - 1);
}


int main(int ac, char **av)
{
    t_game game;

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
