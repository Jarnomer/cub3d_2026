/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_trans.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_vec2	trans_world_to_cam(t_camera *cam, t_vec2 pos)
{
	t_vec2	rel;
	t_vec2	trans;
	t_f32	inv;
	t_f32	det;

	rel = vec2_sub(pos, cam->pos);
	det = cam->plane.x * cam->dir.y - cam->dir.x * cam->plane.y;
	inv = 1.0f / det;
	trans.x = inv * (cam->dir.y * rel.x - cam->dir.x * rel.y);
	trans.y = inv * (-cam->plane.y * rel.x + cam->plane.x * rel.y);
	return (trans);
}

bool	trans_behind_camera(t_f32 trans_y)
{
	return (trans_y <= EPSILON);
}

t_vec2	trans_ray_dir(t_camera *cam, t_i32 x, t_i32 scr_w)
{
	t_f32	cam_x;

	cam_x = CAM_X_SCALE * x / (t_f32)scr_w - 1.0f;
	return (vec2_add(cam->dir, vec2_mul(cam->plane, cam_x)));
}

t_i32	trans_sprite_tex_x(t_proj *proj, t_i32 scr_x, t_i32 tex_w)
{
	t_i32	spr_x;
	t_i32	tex_x;

	spr_x = scr_x - (proj->screen.x - proj->size.x / 2);
	tex_x = spr_x * tex_w / proj->size.x;
	return (clampi(tex_x, 0, tex_w - 1));
}

t_i32	trans_sprite_tex_y(t_proj *proj, t_i32 scr_y, t_i32 tex_h)
{
	t_i32	spr_y;
	t_i32	tex_y;

	spr_y = scr_y - (proj->screen.y - proj->size.y / 2);
	tex_y = spr_y * tex_h / proj->size.y;
	return (clampi(tex_y, 0, tex_h - 1));
}
