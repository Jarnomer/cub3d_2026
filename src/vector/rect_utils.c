/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/15 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

bool	rect_is_offscreen(t_rect rect)
{
	if (rect.w <= 0 || rect.h <= 0)
		return (true);
	return (false);
}

bool	rect_is_valid(t_rect rect)
{
	return (rect.w > 0 && rect.h > 0);
}

t_i32	rect_bottom(t_rect rect)
{
	return (rect.y + rect.h);
}

t_i32	rect_right(t_rect rect)
{
	return (rect.x + rect.w);
}
