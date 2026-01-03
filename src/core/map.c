/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	map_destroy(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
		ft_free_double((void ***)&map->grid);
	i = 0;
	while (i < 4)
	{
		if (map->tex_paths[i])
			free(map->tex_paths[i]);
		map->tex_paths[i] = NULL;
		i++;
	}
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
