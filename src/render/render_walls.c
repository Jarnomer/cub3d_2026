/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

/*
** Draws a single vertical texture strip for a wall
*/
static void	draw_wall_column(t_game *game, t_i32 x, t_slice *s, t_tex *tex)
{
	t_i32	y;
	t_i32	tex_y;
	t_u32	color;
	t_u8	fog;

	fog = lookup_fog(&game->lookup, s->dist);
	if (fog == FOG_FULL)
		return ((void)fog_fill_column(game, x, s->start, s->end));
	slice_calc_texstep(s, tex->height);
	y = s->start;
	while (y <= s->end)
	{
		tex_y = clampi((t_i32)s->tex_pos, 0, tex->height - 1);
		color = texture_sample(tex, s->tex_x, tex_y);
		render_pixel(game->render.frame, x, y, fog_apply(color, fog));
		s->tex_pos += s->tex_step;
		y++;
	}
}

/*
** Renders a wall and updates z-buffer
*/
static void	render_wall(t_game *game, t_hit *hit, t_i32 x)
{
	t_slice	slice;
	t_tex	*tex;

	tex = &game->assets.textures[hit->dir];
	slice = slice_from_hit(hit, game->render.height, tex->width);
	slice_apply_pitch(&slice, &game->camera, game->render.height);
	game->render.z_buffer[x] = hit->dist;
	draw_wall_column(game, x, &slice, tex);
}

/*
** Calculates ray direction for a screen column
*/
static t_vec2	calc_ray_dir(t_camera *cam, t_i32 x, t_i32 screen_w)
{
	t_f32	cam_x;

	cam_x = CAM_X_SCALE * x / (t_f32)screen_w - 1.0f;
	return (vec2_add(cam->dir, vec2_mul(cam->plane, cam_x)));
}

/*
** Handles door rendering with proper occlusion and z-buffer logic
**
** Occlusion is stored when door is animating (opening OR closing)
** so sprites can fade in/out through transparent door pixels.
**
** Z-buffer is only written for blocking doors (closed/closing)
** to prevent sprites behind from rendering at column level.
*/
static void	handle_door(t_game *game, t_hit *door_hit, t_i32 x)
{
	t_entity	*ent;

	if (door_hit->entity < 0)
		return ;
	ent = darray_get(&game->entities, door_hit->entity);
	if (!ent || !ent->active)
		return ;
	if (door_is_animating(ent))
		occlude_store_door(game, door_hit, x);
	if (door_is_blocking(ent))
		game->render.z_buffer[x] = door_hit->dist;
	render_door_column(game, door_hit, x);
}

/*
** Renders a single screen column: wall + optional door overlay
**
** Uses passthrough DDA to handle open doors:
**   1. Ray continues through non-blocking doors
**   2. First door hit saved for overlay rendering
**   3. Final hit is solid wall or blocking door
*/

void	render_wall_column(t_game *game, t_i32 x)
{
	t_ray	ray;
	t_hit	wall_hit;
	t_hit	door_hit;

	occlude_clear_column(game, x);
	ray_init(&ray, game->camera.pos,
		calc_ray_dir(&game->camera, x, game->render.width));
	wall_hit = passthr_dda(&ray, game, RAY_MAX_DIST, &door_hit);
	if (!wall_hit.hit && door_hit.entity == ENTITY_VOID)
		return ;
	if (wall_hit.hit && wall_hit.cell != CELL_DOOR)
		render_wall(game, &wall_hit, x);
	if (door_hit.entity != ENTITY_VOID)
		handle_door(game, &door_hit, x);
	else if (wall_hit.hit && wall_hit.cell == CELL_DOOR)
		handle_door(game, &wall_hit, x);
}
