/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/13 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	blit_calc_size(t_blit *blit, t_i32 src_w, t_i32 src_h, t_f32 scale)
{
	blit->source.x = src_w;
	blit->source.y = src_h;
	blit->scale = scale;
	blit->inverse = 1.0f / scale;
	blit->size.x = (t_i32)(src_w * scale);
	blit->size.y = (t_i32)(src_h * scale);
}

void	blit_from_tex(t_blit *blit, t_tex *tex, t_f32 scale)
{
	if (!tex || !tex->pixels)
		return ;
	*blit = (t_blit){.tex = tex};
	blit_calc_size(blit, tex->width, tex->height, scale);
}

void	blit_from_sheet(t_blit *blit, t_sheet *sheet, t_i32 frame, t_f32 scale)
{
	if (!sheet || !sheet->tex.pixels)
		return ;
	*blit = (t_blit){.sheet = sheet, .frame = frame};
	blit_calc_size(blit, sheet->width, sheet->height, scale);
}
