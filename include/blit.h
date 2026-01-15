/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/15 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLIT_H
# define BLIT_H

# include <types.h>
# include <vector.h>

typedef struct s_texture	t_tex;
typedef struct s_sheet		t_sheet;

typedef struct s_blit
{
	t_vec2i		pos;
	t_vec2i		size;
	t_vec2i		offset;
	t_rect		bounds;
	t_vec2i		source;
	t_f32		scale;
	t_f32		inverse;
	t_i32		frame;
	t_sheet		*sheet;
	t_tex		*tex;
}	t_blit;

void	blit_set_position(t_blit *blit, t_vec2i pos);
void	blit_set_centered(t_blit *blit, t_vec2i pos);
void	blit_apply_offset(t_blit *blit, t_vec2i offset);
void	blit_clip_bounds(t_blit *blit, t_i32 scr_w, t_i32 scr_h);

void	blit_render(t_blit *blit, t_mlxi *img);

void	blit_from_tex(t_blit *blit, t_tex *tex, t_f32 scale);
void	blit_from_sheet(t_blit *blit, t_sheet *sheet, t_i32 frame, t_f32 scale);

#endif
