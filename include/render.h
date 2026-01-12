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

# include <pthread.h>

# include <vector.h>
# include <types.h>
# include <defs.h>

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
	t_dir	dir;
	t_i32	top;
	t_i32	bottom;
	t_i32	start;
	t_i32	end;
	t_i32	height;
	t_i32	tex_x;
	t_f32	tex_y;
	t_f32	step;
	t_f32	dist;
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

typedef struct s_flash
{
	t_u32	color;
	t_f32	duration;
	t_f32	timer;
	bool	active;
}	t_flash;

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
	t_mlxi		*overlay;
	t_f32		*z_buffer;
	t_occlude	*occlude;
	t_i32		width;
	t_i32		height;
}	t_render;

typedef struct s_thread
{
	t_game	*game;
	t_proj	*projs;
	t_u32	count;
	t_i32	start;
	t_i32	end;
	t_i32	id;
}	t_thread;

t_hit	perform_dda(t_ray *ray, t_game *game, t_f32 max_dist);
bool	hitscan_dda(t_vec2 from, t_vec2 to, t_game *game);
t_hit	passthr_dda(t_ray *ray, t_game *game, t_f32 max_dist, t_hit *door);

void	ray_init(t_ray *ray, t_vec2 origin, t_vec2 dir);
void	ray_hit(t_hit *hit, t_ray *ray, int axis);
void	ray_step(t_ray *ray, int *axis);
t_f32	ray_dist(t_ray *ray, int axis);

void	render_init(t_game *game);
void	render_destroy(t_render *render);
void	render_pixel(t_mlxi *img, t_i32 x, t_i32 y, t_u32 color);
void	render_pixel_safe(t_mlxi *img, t_i32 x, t_i32 y, t_u32 color);

void	overlay_clear(t_render *render);
void	overlay_fill(t_render *render, t_u32 color);
void	overlay_apply(t_render *render);

bool	occlude_pixel(t_game *game, t_i32 x, t_i32 y, t_f32 sprite_dist);
void	occlude_clear(t_game *game, t_i32 x);
void	occlude_store(t_game *game, t_hit *door_hit, t_i32 x);

void	render_walls(t_game *game);
void	render_floor(t_game *game);
void	render_sprites(t_game *game);
void	render_weapon(t_game *game);

void	render_floor_row(t_game *game, t_i32 y);
void	render_wall_column(t_game *game, t_i32 x);
void	render_door_column(t_game *game, t_hit *hit, t_i32 x);
void	render_sprite_column(t_game *game, t_proj *proj, t_i32 x);
void	render_sheet_column(t_game *game, t_proj *proj, t_i32 x);

t_u32	fog_apply(t_u32 color, t_u32 fog);
void	fog_fill_row(t_game *game, t_i32 y);
void	fog_fill_column(t_game *game, t_i32 x, t_i32 start, t_i32 end);

void	flash_init(t_flash *flash);
void	flash_trigger(t_flash *flash, t_u32 color, t_f32 duration);
void	flash_update(t_flash *flash, t_f32 dt);
void	render_flash(t_game *game, t_flash *flash);

bool	sprite_project(t_game *game, t_entity *ent, t_proj *proj);
void	sprites_sort(t_proj *projs, t_u32 count);
t_u32	sprites_collect(t_game *game, t_proj *projs);

t_i32	proj_screen_x(t_proj *proj, t_render *render);
t_i32	proj_z_offset(t_entity *ent, t_proj *proj, t_render *render);
t_vec2i	proj_sprite_size(t_entity *ent, t_proj *proj, t_render *render);
t_i32	proj_apply_pitch(t_proj *proj, t_camera *cam, t_render *render);

t_slice	slice_from_hit(t_hit *hit, t_i32 scr_h, t_i32 tex_w);
void	slice_apply_pitch(t_slice *slice, t_camera *cam, t_i32 scr_h);
void	slice_calc_tex_step(t_slice *slice, t_i32 tex_h);

t_vec2	trans_world_to_cam(t_camera *cam, t_vec2 pos);
bool	trans_behind_camera(t_f32 trans_y);
t_vec2	trans_ray_dir(t_camera *cam, t_i32 x, t_i32 scr_w);
t_i32	trans_sprite_tex_x(t_proj *proj, t_i32 scr_x, t_i32 tex_w);
t_i32	trans_sprite_tex_y(t_proj *proj, t_i32 scr_y, t_i32 tex_h);

t_f32	zbuf_read(t_render *render, t_i32 x);
void	zbuf_write(t_render *render, t_i32 x, t_f32 dist);
bool	zbuf_test(t_render *render, t_i32 x, t_f32 dist);

#endif