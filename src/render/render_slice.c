/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_slice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

/*
** Calculates the X coordinate in texture from ray hit position
**
** wall_x is the fractional position along the wall (0.0 to 1.0)
** We need to flip the texture for certain directions to maintain
** consistent visual orientation:
**
**     hit from WEST  (AXIS_X, step > 0) -> WALL_WEST  -> no flip
**     hit from EAST  (AXIS_X, step < 0) -> WALL_EAST  -> flip
**     hit from NORTH (AXIS_Y, step > 0) -> WALL_SOUTH -> flip  
**     hit from SOUTH (AXIS_Y, step < 0) -> WALL_NORTH -> no flip
*/

t_i32	slice_calc_tex_x(t_hit *hit, t_i32 tex_width)
{
	t_i32	tex_x;
	bool	flip;

	tex_x = (t_i32)(hit->wall_x * (t_f32)tex_width);
	flip = (hit->axis == AXIS_X && hit->dir == WALL_EAST)
		|| (hit->axis == AXIS_Y && hit->dir == WALL_SOUTH);
	if (flip)
		tex_x = tex_width - tex_x - 1;
	return (clampi(tex_x, 0, tex_width - 1));
}

/*
** Applies camera pitch offset and clamps slice bounds to screen
**
** Pitch creates vertical camera rotation:
**   - Positive pitch = looking up (walls shift down)
**   - Negative pitch = looking down (walls shift up)
**
**       Normal view:        Looking up (pitch > 0):
**       +----------+        +----------+
**       |  ceiling |        | ceiling  |
**       |==========| <- horizon shifts down
**       |   wall   |        |   wall   |
**       |  floor   |        |  floor   |
**       +----------+        +----------+
*/

void	slice_apply_pitch(t_slice *slice, t_camera *cam, t_i32 screen_h)
{
	slice->offset = (t_i32)(cam->pitch * screen_h);
	slice->start = clampi(slice->top + slice->offset, 0, screen_h - 1);
	slice->end = clampi(slice->bottom + slice->offset, 0, screen_h - 1);
}

/*
** Calculates vertical slice dimensions for a wall or door at given distance
**
** The wall height is inversely proportional to distance:
**   - Closer objects appear taller
**   - Further objects appear shorter
**
** Formula: height = screen_height / perpendicular_distance
**
** The slice is centered on the horizon line (screen_height / 2)
*/

t_slice	slice_from_hit(t_hit *hit, t_i32 screen_h, t_i32 tex_width)
{
	t_slice	slice;

	slice = (t_slice){0};
	slice.dist = hit->dist;
	slice.height = (t_i32)(screen_h / hit->dist);
	slice.top = screen_h / 2 - slice.height / 2;
	slice.bottom = screen_h / 2 + slice.height / 2;
	slice.tex_x = slice_calc_tex_x(hit, tex_width);
	return (slice);
}

/*
** Calculates texture step and initial position for vertical sampling
**
** The step determines how much to advance in texture space for each
** screen pixel. When wall is larger than screen, we skip texture rows.
** When wall is smaller, we stretch texture rows.
**
**       tex_height = 64        wall_height = 128 (2x scale)
**       +--------+             +--------+
**       |   0    |             |  0-1   | <- each tex row spans 2 pixels
**       |   1    |             |  2-3   |
**       |  ...   |             |  ...   |
**       |   63   |             |126-127 |
**       +--------+             +--------+
**
** Initial tex_pos accounts for:
**   - start may be clamped (top of wall off-screen)
**   - pitch offset shifts everything vertically
*/

void	slice_calc_texstep(t_slice *slice, t_i32 tex_height)
{
	slice->tex_step = (t_f32)tex_height / (t_f32)slice->height;
	slice->tex_pos = (slice->start - slice->top - slice->offset)
		* slice->tex_step;
}
