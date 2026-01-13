/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/13 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	blit_row(t_blit *blit, t_mlxi *dst, t_i32 y)
{
	t_u32	color;
	t_i32	x;

	x = blit->start.x;
	while (x < blit->end.x)
	{
		color = blit_sample(blit, x, y);
		if (color_is_opaque(color))
			render_pixel(dst, x, y, color);
		x++;
	}
}

static bool	blit_is_valid(t_blit *blit)
{
	if (!blit->tex && !blit->sheet)
		return (false);
	if (blit->start.x >= blit->end.x)
		return (false);
	if (blit->start.y >= blit->end.y)
		return (false);
	return (true);
}

void	blit_render(t_blit *blit, t_mlxi *dst)
{
	t_i32	y;

	if (!blit_is_valid(blit) || !dst)
		return ;
	y = blit->start.y;
	while (y < blit->end.y)
	{
		blit_row(blit, dst, y);
		y++;
	}
}
