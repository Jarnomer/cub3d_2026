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

/* ************************************************************************** */
/*    FORWARD DECLARATIONS                                                    */
/* ************************************************************************** */

typedef struct s_game	t_game;

/* ************************************************************************** */
/*    CELL GRID STRUCTURE                                                     */
/* ************************************************************************** */
/*
** Grid for O(1) entity lookup by map cell
** - cells:  2D array of entity indices (CELL_VOID = -1)
** - types:  2D array of cell types (wall, door, empty)
** - axes:   2D array of door orientations (only valid for doors)
** - width:  Grid width (matches map width)
** - height: Grid height (matches map height)
*/

typedef struct s_grid
{
	t_i32		*cells;
	t_u8		*types;
	t_u8		*axes;
	t_i32		width;
	t_i32		height;
}	t_grid;

/* ************************************************************************** */
/*    FUNCTION PROTOTYPES                                                     */
/* ************************************************************************** */
/*
** See source files for function details
*/

void		grid_init(t_grid *grid, t_i32 width, t_i32 height);
void		grid_destroy(t_grid *grid);
bool		grid_valid(t_grid *grid, t_i32 x, t_i32 y);
t_i32		grid_index(t_grid *grid, t_i32 x, t_i32 y);
t_cell		grid_check_cell(t_game *game, t_vec2i grid, t_i32 *entity);

void		grid_cell_fill(t_game *game);

void		grid_set(t_grid *grid, t_i32 x, t_i32 y, t_i32 entity);
t_i32		grid_get(t_grid *grid, t_i32 x, t_i32 y);
void		grid_set_type(t_grid *grid, t_i32 x, t_i32 y, t_cell type);
t_cell		grid_get_type(t_grid *grid, t_i32 x, t_i32 y);
void		grid_set_axis(t_grid *grid, t_i32 x, t_i32 y, t_axis a);
t_axis		grid_get_axis(t_grid *grid, t_i32 x, t_i32 y);

#endif
