/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_prod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_f32	vec2_dot(t_vec2 a, t_vec2 b)
{
	return (a.x * b.x + a.y * b.y);
}

t_f32	vec2_len(t_vec2 v)
{
	return (sqrtf(vec2_len_sq(v)));
}

t_f32	vec2_len_sq(t_vec2 v)
{
	return (v.x * v.x + v.y * v.y);
}
