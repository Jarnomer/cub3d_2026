/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_angle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_f32	deg_to_rad(t_f32 deg)
{
	return (deg * DEG2RAD);
}

t_f32	rad_to_deg(t_f32 rad)
{
	return (rad * RAD2DEG);
}

t_f32	angle_normalize(t_f32 angle)
{
	angle = fmodf(angle, TAU);
	if (angle < 0.0f)
		angle += TAU;
	return (angle);
}

t_f32	angle_diff(t_f32 from, t_f32 to)
{
	t_f32	diff;

	diff = fmodf(to - from, TAU);
	if (diff > PI)
		diff -= TAU;
	else if (diff < -PI)
		diff += TAU;
	return (diff);
}

t_f32	angle_lerp(t_f32 from, t_f32 to, t_f32 t)
{
	t_f32	diff;

	diff = angle_diff(from, to);
	return (angle_normalize(from + diff * t));
}
