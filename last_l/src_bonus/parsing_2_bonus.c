/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:25:48 by ylahssin          #+#    #+#             */
/*   Updated: 2025/02/15 19:33:44 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid_chars(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P' ||  c == 'T');
}

int	check_valid_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
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

int	is_check(char **map, char c, t_position *pos)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
			{
				if (map[i][j] == PLA_CHAR)
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

int	is_check_collectible(char **map, char c, int *num)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
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
