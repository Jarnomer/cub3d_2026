/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <vector.h>
# include <types.h>

typedef struct s_proj	t_proj;

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
/*    TEXTURE STRUCTURE                                                       */
/* ************************************************************************** */

typedef struct s_texture
{
	t_mlxt	*mlx_tex;
	t_u32	*pixels;
	t_i32	width;
	t_i32	height;
}	t_tex;

/* ************************************************************************** */
/*    RENDER STRUCTURE                                                        */
/* ************************************************************************** */

typedef struct s_render
{
	t_mlxi	*frame;
	t_f32	*z_buffer;
	t_i32	width;
	t_i32	height;
	t_tex	barrel;
}	t_render;

/* ************************************************************************** */
/*    RAY CALC STRUCTURE                                                      */
/* ************************************************************************** */

/*
** Core ray structure for DDA algorithm
**
** - origin:	Ray starting (player) position
** - dir:   	Normalized ray direction
** - delta: 	Distance to travel to cross one grid cell
** - dist:  	Distance from origin to next grid line
** - grid:  	Current grid cell being checked
** - step:  	Direction to step in grid (-1 or +1)
*/

typedef struct s_ray
{
	t_vec2	origin;
	t_vec2	dir;
	t_vec2	delta;
	t_vec2	dist;
	t_vec2i	grid;
	t_vec2i	step;
}	t_ray;

/* ************************************************************************** */
/*    HIT RESULT STRUCTURE                                                    */
/* ************************************************************************** */

/*
** Result of a ray cast operation
**
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
**
** - top:   	Top pixel of wall on screen (before pitch)
** - end:   	Bottom pixel of wall on screen (before pitch)
** - start: 	Actual top pixel after pitch offset
** - end:   	Actual bottom pixel after pitch offset
** - height:	Total height of wall slice (can exceed screen)
** - tex_x: 	X coordinate in texture (0 to tex_width - 1)
** - dir:   	Which texture to use
** - dist:  	For z-buffer
** - offset:	Vertical offset from camera pitch
*/

typedef struct s_wall
{
	t_i32	top;
	t_i32	bottom;
	t_i32	start;
	t_i32	end;
	t_i32	height;
	t_i32	tex_x;
	t_dir	dir;
	t_f32	dist;
	t_i32	offset;
}	t_wall;

/* ************************************************************************** */
/*    FLOOR RENDER STRUCTURE                                                  */
/* ************************************************************************** */

/*
** Context for floor/ceiling rendering using horizontal scanlines
**
** - left:		Ray direction at left edge of screen (dir - plane)
** - right:		Ray direction at right edge of screen (dir + plane)
** - step:		World coordinate increment per pixel horizontally
** - grid:		Current world position being sampled for texture
** - dist:		Perpendicular distance from camera to current row's plane
** - horizon:	Screen Y coordinate of horizon line (with pitch offset)
*/

typedef struct s_floor
{
	t_vec2	left;
	t_vec2	right;
	t_f32	dist;
	t_vec2	step;
	t_vec2	grid;
	t_i32	horizon;
}	t_floor;

/* ************************************************************************** */
/*    FUNCTIONS                                                               */
/* ************************************************************************** */

void	ray_init(t_ray *ray, t_vec2 origin, t_vec2 dir);

t_hit	perform_dda(t_ray *ray, t_map *map, t_f32 max_dist);
bool	hitscan_dda(t_vec2 from, t_vec2 to, t_map *map);

void	render_init(t_game *game);
void	render_destroy(t_render *render);
void	render_pixel_safe(t_mlxi *img, t_i32 x, t_i32 y, t_color c);
void	render_pixel(t_mlxi *img, t_i32 x, t_i32 y, t_u32 color);

void	render_floor_row(t_game *game, t_i32 y);
void	render_wall_column(t_game *game, t_i32 x);
void	render_sprite_column(t_game *game, t_proj *proj, t_i32 x);

t_u32	fog_blend(t_u32 color, t_f32 factor);
t_f32	fog_factor(t_f32 dist);

void	texture_load(t_tex *tex, const char *path);
void	texture_destroy(t_tex *tex);
t_u32	texture_sample(t_tex *tex, t_i32 x, t_i32 y);
t_color	texture_sample_color(t_tex *tex, t_i32 x, t_i32 y);

#endif
