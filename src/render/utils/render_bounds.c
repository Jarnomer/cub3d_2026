/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bounds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

bool	bounds_sprite_visible(t_proj *proj, t_i32 width)
{
	if (proj->end.x < 0)
		return (false);
	if (proj->start.x >= width)
		return (false);
	return (true);
}

void	bounds_calc_sprite(t_proj *proj, t_i32 width, t_i32 height)
{
	proj->start.x = proj->screen.x - proj->size.x / 2;
	proj->start.y = proj->screen.y - proj->size.y / 2;
	proj->end.x = proj->screen.x + proj->size.x / 2;
	proj->end.y = proj->screen.y + proj->size.y / 2;
	proj->start.x = maxi(proj->start.x, 0);
	proj->start.y = maxi(proj->start.y, 0);
	proj->end.x = mini(proj->end.x, width - 1);
	proj->end.y = mini(proj->end.y, height - 1);
}

bool	bounds_rect_visible(t_vec2i start,
		t_vec2i end, t_i32 width, t_i32 height)
{
	if (end.x < 0 || start.x >= width)
		return (false);
	if (end.y < 0 || start.y >= height)
		return (false);
	return (true);
}

t_i32	bounds_clamp_x(t_i32 x, t_i32 width)
{
	return (clampi(x, 0, width - 1));
}

t_i32	bounds_clamp_y(t_i32 y, t_i32 height)
{
	return (clampi(y, 0, height - 1));
}
