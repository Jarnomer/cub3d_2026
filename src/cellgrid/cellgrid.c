/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cellgrid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	cellgrid_init(t_cellgrid *grid, t_i32 width, t_i32 height)
{
	t_i32	total;
	t_i32	i;

	total = width * height;
	*grid = (t_cellgrid){.width = width, .height = height};
	grid->cells = safe_calloc(sizeof(t_i32) * total);
	grid->types = safe_calloc(sizeof(t_u8) * total);
	grid->axes = safe_calloc(sizeof(t_u8) * total);
	i = 0;
	while (i < total)
	{
		grid->cells[i] = CELL_EMPTY;
		grid->types[i] = CELLTYPE_EMPTY;
		i++;
	}
}

void	cellgrid_destroy(t_cellgrid *grid)
{
	if (!grid)
		return ;
	free(grid->cells);
	free(grid->types);
	free(grid->axes);
	*grid = (t_cellgrid){0};
}

bool	cellgrid_valid(t_cellgrid *grid, t_i32 x, t_i32 y)
{
	if (x < 0 || x >= grid->width)
		return (false);
	if (y < 0 || y >= grid->height)
		return (false);
	return (true);
}

t_i32	cellgrid_index(t_cellgrid *grid, t_i32 x, t_i32 y)
{
	return (y * grid->width + x);
}

t_cell	cellgrid_check_cell(t_game *game, t_vec2i grid, t_i32 *ent_idx)
{
	t_cell		type;
	t_entity	*ent;

	*ent_idx = CELL_EMPTY;
	if (map_is_wall(game->map, grid.x, grid.y))
		return (CELLTYPE_WALL);
	type = cellgrid_get_type(&game->cellgrid, grid.x, grid.y);
	if (type == CELLTYPE_DOOR)
	{
		*ent_idx = cellgrid_get(&game->cellgrid, grid.x, grid.y);
		if (*ent_idx >= 0)
		{
			ent = darray_get(&game->entities, *ent_idx);
			if (ent && ent->state == STATE_OPEN)
				return (CELLTYPE_EMPTY);
		}
		return (CELLTYPE_DOOR);
	}
	return (CELLTYPE_EMPTY);
}
