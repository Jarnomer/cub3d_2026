/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cellgrid_access.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	cellgrid_set(t_cellgrid *grid, t_i32 x, t_i32 y, t_i32 ent_idx)
{
	t_i32	idx;

	if (!cellgrid_valid(grid, x, y))
		return ;
	idx = cellgrid_index(grid, x, y);
	grid->cells[idx] = ent_idx;
}

t_i32	cellgrid_get(t_cellgrid *grid, t_i32 x, t_i32 y)
{
	t_i32	idx;

	if (!cellgrid_valid(grid, x, y))
		return (CELL_EMPTY);
	idx = cellgrid_index(grid, x, y);
	return (grid->cells[idx]);
}

void	cellgrid_set_type(t_cellgrid *grid, t_i32 x, t_i32 y, t_cell type)
{
	t_i32	idx;

	if (!cellgrid_valid(grid, x, y))
		return ;
	idx = cellgrid_index(grid, x, y);
	grid->types[idx] = (t_u8)type;
}

t_cell	cellgrid_get_type(t_cellgrid *grid, t_i32 x, t_i32 y)
{
	t_i32	idx;

	if (!cellgrid_valid(grid, x, y))
		return (CELLTYPE_WALL);
	idx = cellgrid_index(grid, x, y);
	return ((t_cell)grid->types[idx]);
}

void	cellgrid_set_axis(t_cellgrid *grid, t_i32 x, t_i32 y, t_axis axis)
{
	t_i32	idx;

	if (!cellgrid_valid(grid, x, y))
		return ;
	idx = cellgrid_index(grid, x, y);
	grid->axes[idx] = (t_u8)axis;
}

t_axis	cellgrid_get_axis(t_cellgrid *grid, t_i32 x, t_i32 y)
{
	t_i32	idx;

	if (!cellgrid_valid(grid, x, y))
		return (AXIS_NS);
	idx = cellgrid_index(grid, x, y);
	return ((t_axis)grid->axes[idx]);
}
