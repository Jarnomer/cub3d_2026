/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_overlay.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	overlay_clear(t_render *render)
{
	t_u32	*pixels;
	t_i32	total;
	t_i32	i;

	if (!render->overlay)
		return ;
	pixels = (t_u32 *)render->overlay->pixels;
	total = render->width * render->height;
	i = 0;
	while (i < total)
	{
		pixels[i] = 0x00000000;
		i++;
	}
}
