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
typedef struct s_texture	t_tex;

typedef struct s_ray
{
	t_vec2	origin;
	t_vec2	dir;
	t_vec2	delta;
	t_vec2	dist;
	t_vec2i	grid;
	t_vec2i	step;
}	t_ray;

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
	t_dir	dir;
	t_i32	offset;
}	t_slice;

typedef struct s_floor
{
	t_vec2	left;
	t_vec2	right;
	t_f32	dist;
	t_vec2	step;
	t_vec2	grid;
	t_i32	horizon;
}	t_floor;

typedef struct s_door
{
	t_sheet	*sheet;
	t_i32	frame;
	bool	is_blocking;
}	t_door;

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

typedef struct s_occlude
{
	bool	has_door;
	t_f32	door_dist;
	t_i32	entity_idx;
	t_f32	wall_x;
	int		axis;
	t_dir	dir;
}	t_occlude;

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
void	slice_calc_tex_step(t_slice *slice, t_i32 tex_height);
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

/* ************************************************************************** */
/*    PIXEL UTILS (render_pixel_utils.c)                                      */
/* ************************************************************************** */

bool	pixel_in_bounds(t_mlxi *frame, t_i32 x, t_i32 y);
void	pixel_put_safe(t_mlxi *frame, t_i32 x, t_i32 y, t_u32 color);
t_u32	pixel_get(t_mlxi *frame, t_i32 x, t_i32 y);
void	pixel_blend(t_mlxi *frame, t_i32 x, t_i32 y, t_u32 color);
void	pixel_fill_rect(t_mlxi *frame, t_vec2i pos, t_vec2i size, t_u32 color);

/* ************************************************************************** */
/*    COLUMN UTILS (render_column_utils.c)                                    */
/* ************************************************************************** */

bool	column_is_visible(t_i32 x, t_i32 width);
void	column_clamp_bounds(t_i32 height, t_i32 *start, t_i32 *end);
void	column_fill(t_mlxi *frame, t_i32 x, t_i32 y1, t_i32 y2, t_u32 color);
void	column_fill_fog(t_mlxi *frame, t_i32 x, t_i32 y1, t_i32 y2);
void	column_clear(t_mlxi *frame, t_i32 x, t_i32 height);

/* ************************************************************************** */
/*    SAMPLING (render_sample.c)                                              */
/* ************************************************************************** */

t_u32	sample_texture_uv(t_tex *tex, t_f32 u, t_f32 v);
t_u32	sample_sheet_frame(t_sheet *sheet, t_i32 frame, t_i32 x, t_i32 y);
bool	sample_is_transparent(t_u32 color);
bool	sample_is_opaque(t_u32 color);
t_u32	sample_texture_wrap(t_tex *tex, t_f32 u, t_f32 v);

/* ************************************************************************** */
/*    PROJECTION (render_project.c)                                           */
/* ************************************************************************** */

t_i32	project_wall_height(t_f32 dist, t_i32 screen_h);
t_i32	project_screen_x(t_f32 trans_x, t_f32 trans_y, t_i32 screen_w);
t_i32	project_z_offset(t_f32 z_offset, t_f32 dist, t_i32 screen_h);
t_vec2i	project_sprite_size(t_f32 scale, t_f32 dist, t_i32 w, t_i32 h);
t_i32	project_apply_pitch(t_i32 y, t_f32 pitch, t_i32 screen_h);

/* ************************************************************************** */
/*    Z-BUFFER (render_zbuffer.c)                                             */
/* ************************************************************************** */

void	zbuf_write(t_render *render, t_i32 x, t_f32 dist);
t_f32	zbuf_read(t_render *render, t_i32 x);
bool	zbuf_test(t_render *render, t_i32 x, t_f32 dist);
void	zbuf_clear(t_render *render);
void	zbuf_clear_column(t_render *render, t_i32 x);

/* ************************************************************************** */
/*    TRANSFORM (render_transform.c)                                          */
/* ************************************************************************** */

t_vec2	trans_world_to_cam(t_camera *cam, t_vec2 world_pos);
t_vec2	trans_ray_dir(t_camera *cam, t_i32 x, t_i32 screen_w);
t_i32	trans_screen_to_tex(t_i32 screen, t_i32 sprite_start,
			t_i32 sprite_size, t_i32 tex_size);
bool	trans_behind_camera(t_f32 trans_y);
t_f32	trans_inv_det(t_camera *cam);

/* ************************************************************************** */
/*    BOUNDS (render_bounds.c)                                                */
/* ************************************************************************** */

bool	bounds_sprite_visible(t_proj *proj, t_i32 width);
void	bounds_calc_sprite(t_proj *proj, t_i32 w, t_i32 h);
bool	bounds_rect_visible(t_vec2i start, t_vec2i end, t_i32 w, t_i32 h);
t_i32	bounds_clamp_x(t_i32 x, t_i32 width);
t_i32	bounds_clamp_y(t_i32 y, t_i32 height);

/* ************************************************************************** */
/*    SLICE (render_slice.c)                                                  */
/* ************************************************************************** */

t_i32	slice_calc_tex_x(t_hit *hit, t_i32 tex_w);
t_slice	slice_from_hit(t_hit *hit, t_i32 screen_h, t_i32 tex_w);
void	slice_apply_pitch(t_slice *s, t_camera *cam, t_i32 screen_h);
void	slice_calc_tex_step(t_slice *s, t_i32 tex_h);
bool	slice_is_visible(t_slice *s, t_i32 screen_h);

#endif