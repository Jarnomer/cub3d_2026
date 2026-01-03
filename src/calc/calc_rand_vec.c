/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_rand_vec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_vec2	rand_unit_vec2(void)
{
	t_f32	angle;

	angle = rand_float() * TAU;
	return (vec2_from_angle(angle));
}

t_vec2	rand_in_circle(t_f32 radius)
{
	t_f32	r;
	t_f32	angle;

	r = sqrtf(rand_float()) * radius;
	angle = rand_float() * TAU;
	return (vec2_mul(vec2_from_angle(angle), r));
}
