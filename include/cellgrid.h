/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cellgrid.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CELLGRID_H
# define CELLGRID_H

# include <types.h>
# include <defs.h>

/* ************************************************************************** */
/*    CONSTANTS                                                               */
/* ************************************************************************** */

# define CELL_EMPTY		-1

/* ************************************************************************** */
/*    FORWARD DECLARATIONS                                                    */
/* ************************************************************************** */

typedef struct s_game	t_game;
typedef struct s_map	t_map;
typedef struct s_entity	t_entity;

/* ************************************************************************** */
/*    CELL TYPE ENUM                                                          */
/* ************************************************************************** */
/*
** Type of content in a map cell for raycasting
*/

typedef enum e_cell
{
	CELLTYPE_EMPTY,
	CELLTYPE_WALL,
	CELLTYPE_DOOR,
	CELLTYPE_COUNT
}	t_cell;

/* ************************************************************************** */
/*    CELL GRID STRUCTURE                                                     */
/* ************************************************************************** */
/*
** Grid for O(1) entity lookup by map cell
** - cells:  2D array of entity indices (CELL_EMPTY = -1)
** - types:  2D array of cell types (wall, door, empty)
** - axes:   2D array of door orientations (only valid for doors)
** - width:  Grid width (matches map width)
** - height: Grid height (matches map height)
*/

typedef struct s_cellgrid
{
	t_i32		*cells;
	t_u8		*types;
	t_u8		*axes;
	t_i32		width;
	t_i32		height;
}	t_cellgrid;

/* ************************************************************************** */
/*    FUNCTION PROTOTYPES                                                     */
/* ************************************************************************** */
/*
** See source files for function details
*/

void		cellgrid_init(t_cellgrid *grid, t_i32 width, t_i32 height);
void		cellgrid_destroy(t_cellgrid *grid);
bool		cellgrid_valid(t_cellgrid *grid, t_i32 x, t_i32 y);
t_i32		cellgrid_index(t_cellgrid *grid, t_i32 x, t_i32 y);
t_cell		cellgrid_check_cell(t_game *game, t_vec2i grid, t_i32 *ent_idx);

void		cellgrid_populate(t_game *game);

void		cellgrid_set(t_cellgrid *grid, t_i32 x, t_i32 y, t_i32 ent_idx);
t_i32		cellgrid_get(t_cellgrid *grid, t_i32 x, t_i32 y);
void		cellgrid_set_type(t_cellgrid *grid, t_i32 x, t_i32 y, t_cell type);
t_cell		cellgrid_get_type(t_cellgrid *grid, t_i32 x, t_i32 y);
void		cellgrid_set_axis(t_cellgrid *grid, t_i32 x, t_i32 y, t_axis a);
t_axis		cellgrid_get_axis(t_cellgrid *grid, t_i32 x, t_i32 y);

#endif
