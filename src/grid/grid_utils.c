/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_i32	find_door(t_game *game, t_vec2i pos)
{
	t_entity	*ent;
	t_vec2i		grid;
	size_t		i;

	i = 0;
	while (i < game->entities.size)
	{
		ent = darray_get(&game->entities, i);
		if (ent->active && ent->type == ENTITY_DOOR)
		{
			grid.x = (t_i32)ent->pos.x;
			grid.y = (t_i32)ent->pos.y;
			if (grid.x == pos.x && grid.y == pos.y)
				return ((t_i32)i);
		}
		i++;
	}
	return (INVALID_ID);
}

t_cell	grid_check_cell(t_game *game, t_vec2i pos, t_i32 *entity)
{
	t_i32	door;

	*entity = INVALID_ID;
	if (map_is_wall(game->map, pos.x, pos.y))
		return (CELL_WALL);
	door = find_door(game, pos);
	if (door != INVALID_ID)
	{
		*entity = door;
		return (CELL_DOOR);
	}
	return (CELL_EMPTY);
}

void	grid_set(t_grid *grid, t_i32 x, t_i32 y, t_i32 entity)
{
	t_i32	idx;

	if (!grid_valid(grid, x, y))
		return ;
	idx = grid_index(grid, x, y);
	grid->cells[idx] = entity;
}

t_i32	grid_get(t_grid *grid, t_i32 x, t_i32 y)
{
	t_i32	idx;

	if (!grid_valid(grid, x, y))
		return (INVALID_ID);
	idx = grid_index(grid, x, y);
	return (grid->cells[idx]);
}

bool	grid_door_block(t_game *game, t_i32 entity)
{
	t_entity	*ent;

	if (entity == INVALID_ID)
		return (false);
	ent = darray_get(&game->entities, entity);
	if (!ent || !ent->active)
		return (false);
	return (ent->state == STATE_IDLE);
}
