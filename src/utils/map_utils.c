/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	map_destroy(t_map *map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < 4)
	{
		free(map->textures[i]);
		i++;
	}
	free_arr(map->grid);
	free(map);
}

bool	map_is_wall(t_map *map, t_i32 x, t_i32 y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (true);
	if (!map->grid[y] || x >= (t_i32)ft_strlen(map->grid[y]))
		return (true);
	return (map->grid[y][x] == CHAR_WALL);
}
