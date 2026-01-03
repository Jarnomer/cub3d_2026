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

#include <calc.h>

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
	while (angle < 0)
		angle += TAU;
	while (angle >= TAU)
		angle -= TAU;
	return (angle);
}

t_f32	angle_diff(t_f32 from, t_f32 to)
{
	t_f32	diff;

	diff = to - from;
	while (diff > PI)
		diff -= TAU;
	while (diff < -PI)
		diff += TAU;
	return (diff);
}

t_f32	angle_lerp(t_f32 from, t_f32 to, t_f32 t)
{
	t_f32	diff;

	diff = angle_diff(from, to);
	return (angle_normalize(from + diff * t));
}
