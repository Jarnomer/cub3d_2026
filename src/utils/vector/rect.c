/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/15 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_rect	rect_new(t_i32 x, t_i32 y, t_i32 w, t_i32 h)
{
	return ((t_rect){x, y, w, h});
}

t_rect	rect_centered(t_vec2i center, t_vec2i size)
{
	return ((t_rect){
		.x = center.x - size.x / 2,
		.y = center.y - size.y / 2,
		.w = size.x,
		.h = size.y
	});
}
