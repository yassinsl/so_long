/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:02:59 by ylahssin          #+#    #+#             */
/*   Updated: 2025/02/12 16:55:07 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_lst_free(t_map **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	if ((*map)->map_2d)
	{
		while ((*map)->map_2d[i])
			free((*map)->map_2d[i++]);
		free((*map)->map_2d);
	}
	free(*map);
}

void	ft_error(char *str, t_map **lst)
{
	write(2, str, ft_strlen(str));
	if (lst)
		ft_lst_free(lst);
	exit(EXIT_FAILURE);
}

void	free_all(char *line, char *all_map, t_map **map)
{
	free(line);
	free(all_map);
	ft_error(NO_MAP, map);
}

void	calcule_moves(int count)
{
	ft_putstr_fd("Move count: ", 1);
	ft_putnbr_fd(count, 1);
	write(1, "\n", 1);
}

void	check_win(t_game *game)
{
	ft_render_map(&game, &game->texture, TRUE, FALSE);
    free_all_img(&game->texture, game);
    free_windows(NULL, &game);
    ft_lst_free(&game->map);
	ft_putstr_fd("Congratulations! You won!\n", 1);
	exit(0);
}
