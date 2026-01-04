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

void	map_load_textures(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (map->tex_paths[i])
			texture_load(&map->textures[i], map->tex_paths[i]);
		i++;
	}
	texture_load(&map->floor_tex, TEX_FLOOR);
	texture_load(&map->ceil_tex, TEX_CEILING);
}

static void	map_destroy_textures(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		texture_destroy(&map->textures[i]);
		i++;
	}
	texture_destroy(&map->floor_tex);
	texture_destroy(&map->ceil_tex);
}

void	map_destroy(t_map *map)
{
	int	i;

	if (!map)
		return ;
	map_destroy_textures(map);
	ft_free_double((void ***)&map->grid);
	i = 0;
	while (i < 4)
	{
		ft_free_single((void **)&map->tex_paths[i]);
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
