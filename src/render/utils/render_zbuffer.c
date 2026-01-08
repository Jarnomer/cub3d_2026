/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_zbuffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	zbuf_write(t_render *render, t_i32 x, t_f32 dist)
{
	if (x >= 0 && x < render->width)
		render->z_buffer[x] = dist;
}

t_f32	zbuf_read(t_render *render, t_i32 x)
{
	if (x < 0 || x >= render->width)
		return (INFINITE);
	return (render->z_buffer[x]);
}

bool	zbuf_test(t_render *render, t_i32 x, t_f32 dist)
{
	if (x < 0 || x >= render->width)
		return (false);
	return (dist < render->z_buffer[x]);
}

void	zbuf_clear(t_render *render)
{
	t_i32	i;

	i = 0;
	while (i < render->width)
	{
		render->z_buffer[i] = INFINITE;
		i++;
	}
}

void	zbuf_clear_column(t_render *render, t_i32 x)
{
	if (x >= 0 && x < render->width)
		render->z_buffer[x] = INFINITE;
}
