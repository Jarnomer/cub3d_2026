/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cellgrid_populate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_axis	detect_axis(t_map *map, t_i32 x, t_i32 y)
{
	bool	wall_north;
	bool	wall_south;
	bool	wall_east;
	bool	wall_west;

	wall_north = map_is_wall(map, x, y - 1);
	wall_south = map_is_wall(map, x, y + 1);
	wall_east = map_is_wall(map, x + 1, y);
	wall_west = map_is_wall(map, x - 1, y);
	if (wall_north && wall_south)
		return (AXIS_NS);
	if (wall_east && wall_west)
		return (AXIS_EW);
	if (wall_north || wall_south)
		return (AXIS_NS);
	return (AXIS_EW);
}

static void	populate_entity(t_game *game, t_entity *ent, t_i32 ent_idx)
{
	t_i32	cell_x;
	t_i32	cell_y;
	t_axis	axis;

	cell_x = (t_i32)ent->pos.x;
	cell_y = (t_i32)ent->pos.y;
	if (ent->type == ENTITY_DOOR)
	{
		axis = detect_axis(game->map, cell_x, cell_y);
		cellgrid_set_type(&game->cellgrid, cell_x, cell_y, CELLTYPE_DOOR);
		cellgrid_set_axis(&game->cellgrid, cell_x, cell_y, axis);
		cellgrid_set(&game->cellgrid, cell_x, cell_y, ent_idx);
	}
}

static void	populate_entities(t_game *game)
{
	t_entity	*ent;
	size_t		i;

	i = 0;
	while (i < game->entities.size)
	{
		ent = darray_get(&game->entities, i);
		if (ent->active)
			populate_entity(game, ent, (t_i32)i);
		i++;
	}
}

static void	populate_walls(t_game *game)
{
	t_i32	x;
	t_i32	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (map_is_wall(game->map, x, y))
				cellgrid_set_type(&game->cellgrid, x, y, CELLTYPE_WALL);
			x++;
		}
		y++;
	}
}

void	cellgrid_populate(t_game *game)
{
	populate_walls(game);
	populate_entities(game);
}
