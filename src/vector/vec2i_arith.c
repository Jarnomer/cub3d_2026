/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2i_arith.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_vec2i	vec2i_add(t_vec2i a, t_vec2i b)
{
	return ((t_vec2i){a.x + b.x, a.y + b.y});
}

t_vec2i	vec2i_sub(t_vec2i a, t_vec2i b)
{
	return ((t_vec2i){a.x - b.x, a.y - b.y});
}
