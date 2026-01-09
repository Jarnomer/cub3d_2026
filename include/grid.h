/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRID_H
# define GRID_H

# include <types.h>
# include <defs.h>

typedef struct s_game	t_game;

typedef struct s_grid
{
	t_i32		*cells;
	t_u8		*types;
	t_u8		*axes;
	t_i32		width;
	t_i32		height;
}	t_grid;

void		grid_init(t_grid *grid, t_i32 width, t_i32 height);
void		grid_destroy(t_grid *grid);
bool		grid_valid(t_grid *grid, t_i32 x, t_i32 y);
t_i32		grid_index(t_grid *grid, t_i32 x, t_i32 y);

void		grid_cell_fill(t_game *game);

t_cell		grid_get_type(t_grid *grid, t_i32 x, t_i32 y);
void		grid_set_type(t_grid *grid, t_i32 x, t_i32 y, t_cell type);
t_axis		grid_get_axis(t_grid *grid, t_i32 x, t_i32 y);
void		grid_set_axis(t_grid *grid, t_i32 x, t_i32 y, t_axis a);

t_cell		grid_check_cell(t_game *game, t_vec2i pos, t_i32 *entity);
bool		grid_door_block(t_game *game, t_i32 entity);
t_i32		grid_get(t_grid *grid, t_i32 x, t_i32 y);
void		grid_set(t_grid *grid, t_i32 x, t_i32 y, t_i32 entity);

#endif
