/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <vector.h>
# include <types.h>
# include <defs.h>

/* ************************************************************************** */
/*    FORWARD DECLARATIONS                                                    */
/* ************************************************************************** */

typedef struct s_game		t_game;
typedef struct s_entity		t_entity;
typedef struct s_camera		t_camera;
typedef struct s_sheet		t_sheet;

/* ************************************************************************** */
/*    RAY STRUCTURE                                                           */
/* ************************************************************************** */
/*
** Core ray structure for DDA (Digital Differential Analysis) algorithm
**
**                      delta.y
**                    +---+
**                    |   |     Ray marches through grid cells
**            +-------+   +---->  step by step until hitting wall
**            |       |  /
**   delta.x  |  cell | / ray_dir
**            |       |/
**            +-------+
**
** - origin:  Ray starting position (player location)
** - dir:     Normalized ray direction vector
** - delta:   Distance to cross one full grid cell in each axis
**            delta.x = |1 / dir.x|, delta.y = |1 / dir.y|
** - dist:    Accumulated distance to next grid line in each axis
** - grid:    Current grid cell coordinates being checked
** - step:    Direction to step in grid (-1 or +1 for each axis)
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
**            wall_x = 0.3
**                |
**                v
**       +--------*-----------+
**       |        ^           |  <- Grid cell that was hit
**       |        | dist      |
**       |        |           |
**       +--------+-----------+
**                ^
**                |
**            ray origin
**
** - hit:     True if ray hit a solid surface
** - dist:    Perpendicular distance (avoids fisheye distortion)
** - wall_x:  Fractional position along wall [0.0, 1.0) for texture mapping
** - axis:    Which axis boundary was crossed (AXIS_X or AXIS_Y)
** - dir:     Cardinal direction of hit surface (for texture selection)
** - grid:    Grid cell coordinates of the hit
** - cell:    Type of cell hit (CELL_WALL, CELL_DOOR, CELL_EMPTY, ... )
** - entity:  Entity index if door was hit, ENTITY_VOID otherwise
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
	t_u8	cell;
	t_i32	entity;
}	t_hit;

/* ************************************************************************** */
/*    SLICE STRUCTURE                                                         */
/* ************************************************************************** */
/*
** Vertical slice data for wall/door rendering
**
**       screen_height
**       +------------+
**       |            |  <- top (may be off-screen)
**       |============|  <- start (clamped to screen)
**       |   SLICE    |  <- visible portion
**       |============|  <- end (clamped to screen)  
**       |            |  <- bottom (may be off-screen)
**       +------------+
**
** - top/bottom:  Unclamped slice bounds (can exceed screen)
** - start/end:   Clamped bounds for actual rendering
** - height:      Total slice height (for texture scaling)
** - tex_x:       Texture X coordinate (0 to tex_width - 1)
** - tex_step:    Texture Y increment per screen pixel
** - tex_pos:     Current texture Y position (accumulator)
** - dist:        Distance for fog calculation
** - offset:      Vertical pixel shift from camera pitch
*/

typedef struct s_slice
{
	t_i32	top;
	t_i32	bottom;
	t_i32	start;
	t_i32	end;
	t_i32	height;
	t_i32	tex_x;
	t_f32	tex_step;
	t_f32	tex_pos;
	t_f32	dist;
	t_i32	offset;
}	t_slice;

/* ************************************************************************** */
/*    FLOOR RENDER STRUCTURE                                                  */
/* ************************************************************************** */
/*
** Context for floor/ceiling rendering using horizontal scanlines
**
**       Camera looking forward:
**
**                left_ray           right_ray
**                     \                /
**                      \      ^       /
**                       \     |dir   /
**                        \    |     /
**                         \   |    /
**                          \  |   /
**           -plane <--------\-+-/--------> +plane
**                             pos
**
** - left/right: Ray directions at screen edges
** - step:       World coordinate increment per pixel horizontally
** - grid:       Current world position being sampled
** - dist:       Distance from camera to floor at current row
** - horizon:    Screen Y coordinate of horizon line
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
/*    DOOR RENDER CONTEXT                                                     */
/* ************************************************************************** */
/*
** Temporary context for door rendering
**
** - sheet:       Sprite sheet containing door animation frames
** - frame:       Current animation frame index
** - is_blocking: True if door should write to z-buffer
**                (closed doors block, open/opening doors don't)
*/

typedef struct s_door
{
	t_sheet	*sheet;
	t_i32	frame;
	bool	is_blocking;
}	t_door;

/* ************************************************************************** */
/*    SPRITE PROJECTION STRUCTURE                                             */
/* ************************************************************************** */
/*
** Sprite projection data for billboard rendering
**
**       World space:           Screen space:
**
**         sprite                  +--------+
**           *                     |        |
**          /|\         ==>        | sprite |
**         / | \                   |  img   |
**        camera                   +--------+
**
** - trans:     Camera-space coordinates
**              trans.x = horizontal offset, trans.y = depth
** - screen:    Screen center position of sprite
** - size:      Rendered size in pixels (scaled by distance)
** - start/end: Clipped draw bounds (clamped to screen)
** - tex_id:    Texture ID for static sprites
** - sheet_id:  Sheet ID for animated sprites
** - frame:     Current animation frame
** - dist:      Distance for z-buffer and fog
** - use_sheet: True to use sprite sheet
*/

typedef struct s_proj
{
	t_vec2		trans;
	t_vec2i		screen;
	t_vec2i		size;
	t_vec2i		start;
	t_vec2i		end;
	t_u32		tex_id;
	t_u32		sheet_id;
	t_i32		frame;
	t_f32		dist;
	bool		use_sheet;
}	t_proj;

/* ************************************************************************** */
/*    DOOR OCCLUSION STRUCTURE                                                */
/* ************************************************************************** */
/*
** Per-column door occlusion data for sprite rendering
**
** When a non-blocking door (open/opening) is in front of a wall,
** we store its hit info so sprites can check per-pixel visibility
** against the door's current animation frame.
**
**     Without occlusion:           With occlusion:
**     Door opens -> sprite         Door opens -> sprite fades in
**     instantly visible            through transparent door pixels
**
** - has_door:   True if non-blocking door exists in this column
** - door_dist:  Distance to door (for depth comparison with sprites)
** - entity_idx: Entity index to get animation frame
** - wall_x:     Texture U coordinate (0.0 - 1.0)
** - axis:       Hit axis for texture flip logic
** - dir:        Hit direction for texture flip logic
*/

typedef struct s_occlude
{
	bool	has_door;
	t_f32	door_dist;
	t_i32	entity_idx;
	t_f32	wall_x;
	int		axis;
	t_dir	dir;
}	t_occlude;

/* ************************************************************************** */
/*    UPDATED RENDER STRUCTURE                                                */
/* ************************************************************************** */
/*
** Core rendering context for the raycasting engine
**
**     Screen (1280 x 720 example)
**     +------------------------------------------+
**     |  frame[0]  frame[1]  ...  frame[1279]    |  <- row 0
**     |  frame[1280] ...                         |  <- row 1
**     |  ...                                     |
**     +------------------------------------------+
**
**     Per-column buffers:
**     [z_buffer[0]] [z_buffer[1]] ... [z_buffer[width-1]]
**     [occlude[0]]  [occlude[1]]  ... [occlude[width-1]]
**
** - frame:    Pixel buffer (RGBA, row-major)
** - z_buffer: Depth per column for wall/sprite occlusion
** - occlude:  Door occlusion data per column for animated visibility
** - width:    Screen width in pixels
** - height:   Screen height in pixels
*/

typedef struct s_render
{
	t_mlxi		*frame;
	t_f32		*z_buffer;
	t_occlude	*occlude;
	t_i32		width;
	t_i32		height;
}	t_render;

/* ************************************************************************** */
/*    RAYCAST FUNCTIONS                                                       */
/* ************************************************************************** */

void	ray_init(t_ray *ray, t_vec2 origin, t_vec2 dir);
void	ray_step(t_ray *ray, int *axis);

t_hit	perform_dda(t_ray *ray, t_game *game, t_f32 max_dist);
t_hit	passthr_dda(t_ray *ray, t_game *game, t_f32 max_dist, t_hit *door_out);
bool	hitscan_dda(t_vec2 from, t_vec2 to, t_game *game);

t_f32	calc_dist(t_ray *ray, int axis);

/* ************************************************************************** */
/*    RENDER CORE FUNCTIONS                                                   */
/* ************************************************************************** */

void	render_init(t_game *game);
void	render_destroy(t_render *render);
void	render_pixel(t_mlxi *img, t_i32 x, t_i32 y, t_u32 color);

/* ************************************************************************** */
/*    SLICE CALCULATION FUNCTIONS                                             */
/* ************************************************************************** */

t_slice	slice_from_hit(t_hit *hit, t_i32 screen_h, t_i32 tex_width);
void	slice_apply_pitch(t_slice *slice, t_camera *cam, t_i32 screen_h);
void	slice_calc_texstep(t_slice *slice, t_i32 tex_height);
t_i32	slice_calc_tex_x(t_hit *hit, t_i32 tex_width);

/* ************************************************************************** */
/*    RENDER PASS FUNCTIONS                                                   */
/* ************************************************************************** */

void	render_floor_row(t_game *game, t_i32 y);
void	render_wall_column(t_game *game, t_i32 x);
void	render_door_column(t_game *game, t_hit *hit, t_i32 x);
void	render_sprite_column(t_game *game, t_proj *proj, t_i32 x);
void	render_sheet_column(t_game *game, t_proj *proj, t_i32 x);

/* ************************************************************************** */
/*    FOG FUNCTIONS                                                           */
/* ************************************************************************** */

t_u32	fog_color(t_u8 alpha);
t_u32	fog_apply(t_u32 color, t_u8 fog_alpha);
void	fog_fill_row(t_game *game, t_i32 y);
void	fog_fill_column(t_game *game, t_i32 x, t_i32 start, t_i32 end);

/* ************************************************************************** */
/*    SPRITE FUNCTIONS                                                        */
/* ************************************************************************** */

bool	project_sprite(t_game *game, t_entity *ent, t_proj *proj);
t_u32	collect_sprites(t_game *game, t_proj *projs);
void	sort_sprites(t_proj *projs, t_u32 count);

/* ************************************************************************** */
/*    OCCLUSION FUNCTION PROTOTYPES                                           */
/* ************************************************************************** */

void	occlude_store_door(t_game *game, t_hit *door_hit, t_i32 x);
void	occlude_clear_column(t_game *game, t_i32 x);
bool	occlude_check_door(t_game *game, t_i32 x, t_i32 y, t_f32 sprite_dist);

#endif