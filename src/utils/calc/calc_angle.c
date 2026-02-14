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
	if (angle < 0)
		angle += TAU;
	return (angle);
}
