/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include <vector.h>
# include <types.h>

typedef struct s_map	t_map;
typedef struct s_game	t_game;

typedef enum e_axis
{
	AXIS_X,
	AXIS_Y
}	t_axis;

typedef enum e_dir
{
	WALL_NORTH,
	WALL_SOUTH,
	WALL_EAST,
	WALL_WEST
}	t_dir;

/* ************************************************************************** */
/*    RAY STRUCTURE                                                           */
/* ************************************************************************** */

/*
** Core ray structure for DDA algorithm
** - origin:    Ray starting (player) position
** - dir:       Normalized ray direction
** - delta:     Distance to travel to cross one grid cell
** - dist:      Distance from origin to next grid line
** - grid:      Current grid cell being checked
** - step:      Direction to step in grid (-1 or +1)
*/

typedef struct s_ray
{
	t_vec2		origin;
	t_vec2		dir;
	t_vec2		delta;
	t_vec2		dist;
	t_vec2i		grid;
	t_vec2i		step;
}	t_ray;

/* ************************************************************************** */
/*    HIT RESULT STRUCTURE                                                    */
/* ************************************************************************** */

/*
** Result of a ray cast operation
** - hit:   	True if ray hit something
** - pos:   	World position of hit point
** - dist:  	Perpendicular distance
** - wall_x:	Fractional position along wall (0.0 - 1.0) for texture mapping
** - axis:  	Which axis was crossed (0 = vertical, 1 = horizontal)
** - dir:   	Cardinal direction wall faces (texture selection)
** - grid:  	Grid cell that was hit
*/

typedef struct s_hit
{
	bool	hit;
	t_vec2	pos;
	t_f32	dist;
	t_f32	wall_x;
	int		axis;
	t_dir	dir;
	t_vec2i	grid;
}	t_hit;

/* ************************************************************************** */
/*    WALL RENDER STRUCTURE                                                   */
/* ************************************************************************** */

/*
** Calculated wall slice for a single screen column
** - begin: 	Top pixel of wall on screen
** - end:   	Bottom pixel of wall on screen
** - height:	Total height of wall slice (can exceed screen)
** - tex_x: 	X coordinate in texture (0 to tex_width - 1)
** - dir:   	Which texture to use
** - dist:  	For z-buffer
*/

typedef struct s_wall
{
	t_i32	begin;
	t_i32	end;
	t_i32	height;
	t_i32	tex_x;
	t_dir	dir;
	t_f32	dist;
}	t_wall;

/* ************************************************************************** */
/*    DDA FUNCTIONS                                                           */
/* ************************************************************************** */

void	ray_init(t_ray *ray, t_vec2 origin, t_vec2 dir);
t_hit	ray_cast(t_ray *ray, t_map *map, t_f32 max_dist);
bool	ray_check_los(t_vec2 from, t_vec2 to, t_map *map);

/* ************************************************************************** */
/*    WALL RENDERING                                                          */
/* ************************************************************************** */

void	raycast_walls(t_game *game);
t_wall	raycast_get_wall(t_hit *hit, t_i32 screen_h, t_i32 tex_w);

#endif
