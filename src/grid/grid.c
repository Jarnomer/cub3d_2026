/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	grid_init(t_grid *grid, t_i32 width, t_i32 height)
{
	t_i32	total;
	t_i32	i;

	total = width * height;
	*grid = (t_grid){.width = width, .height = height};
	grid->cells = safe_calloc(sizeof(t_i32) * total);
	grid->types = safe_calloc(sizeof(t_u8) * total);
	grid->axes = safe_calloc(sizeof(t_u8) * total);
	i = 0;
	while (i < total)
	{
		grid->cells[i] = CELL_VOID;
		grid->types[i] = CELL_EMPTY;
		i++;
	}
}

void	grid_destroy(t_grid *grid)
{
	if (!grid)
		return ;
	free(grid->cells);
	free(grid->types);
	free(grid->axes);
	*grid = (t_grid){0};
}

bool	grid_valid(t_grid *grid, t_i32 x, t_i32 y)
{
	if (x < 0 || x >= grid->width)
		return (false);
	if (y < 0 || y >= grid->height)
		return (false);
	return (true);
}

t_i32	grid_index(t_grid *grid, t_i32 x, t_i32 y)
{
	return (y * grid->width + x);
}
