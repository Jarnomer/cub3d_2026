/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_trans.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_vec2	trans_world_to_cam(t_camera *cam, t_vec2 world_pos)
{
	t_vec2	rel;
	t_vec2	trans;
	t_f32	inv_det;

	rel = vec2_sub(world_pos, cam->pos);
	inv_det = 1.0f / (cam->plane.x * cam->dir.y - cam->dir.x * cam->plane.y);
	trans.x = inv_det * (cam->dir.y * rel.x - cam->dir.x * rel.y);
	trans.y = inv_det * (-cam->plane.y * rel.x + cam->plane.x * rel.y);
	return (trans);
}

t_vec2	trans_ray_dir(t_camera *cam, t_i32 x, t_i32 screen_w)
{
	t_f32	cam_x;

	cam_x = CAM_X_SCALE * x / (t_f32)screen_w - 1.0f;
	return (vec2_add(cam->dir, vec2_mul(cam->plane, cam_x)));
}

t_i32	trans_screen_to_tex(t_i32 screen, t_i32 sprite_start,
		t_i32 sprite_size, t_i32 tex_size)
{
	t_i32	sprite_pos;
	t_i32	tex_coord;

	sprite_pos = screen - sprite_start;
	if (sprite_size <= 0)
		return (0);
	tex_coord = sprite_pos * tex_size / sprite_size;
	return (clampi(tex_coord, 0, tex_size - 1));
}

bool	trans_behind_camera(t_f32 trans_y)
{
	return (trans_y <= EPSILON);
}

t_f32	trans_inv_det(t_camera *cam)
{
	t_f32	det;

	det = cam->plane.x * cam->dir.y - cam->dir.x * cam->plane.y;
	if (absf(det) < EPSILON)
		return (0.0f);
	return (1.0f / det);
}
