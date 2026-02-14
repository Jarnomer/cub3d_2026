/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_getset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	grid_set_type(t_grid *grid, t_i32 x, t_i32 y, t_cell type)
{
	t_i32	idx;

	if (!grid_valid(grid, x, y))
		return ;
	idx = grid_index(grid->width, x, y);
	grid->types[idx] = (t_u8)type;
}

t_cell	grid_get_type(t_grid *grid, t_i32 x, t_i32 y)
{
	t_i32	idx;

	if (!grid_valid(grid, x, y))
		return (CELL_WALL);
	idx = grid_index(grid->width, x, y);
	return ((t_cell)grid->types[idx]);
}

void	grid_set_axis(t_grid *grid, t_i32 x, t_i32 y, t_axis axis)
{
	t_i32	idx;

	if (!grid_valid(grid, x, y))
		return ;
	idx = grid_index(grid->width, x, y);
	grid->axes[idx] = (t_u8)axis;
}

t_axis	grid_get_axis(t_grid *grid, t_i32 x, t_i32 y)
{
	t_i32	idx;

	if (!grid_valid(grid, x, y))
		return (AXIS_NS);
	idx = grid_index(grid->width, x, y);
	return ((t_axis)grid->axes[idx]);
}
