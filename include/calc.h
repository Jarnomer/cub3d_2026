/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
# define CALC_H

# include <vector.h>
# include <types.h>

# define PI			3.14159265358979323846f
# define TAU		6.28318530717958647692f
# define DEG2RAD	0.01745329251994329577f
# define RAD2DEG	57.2957795130823208768f
# define INFINITE	1e30f
# define EPSILON	0.0001f

t_color	color_new(t_u8 r, t_u8 g, t_u8 b, t_u8 a);
t_color	color_from_u32(t_u32 val);
t_u32	color_to_u32(t_color c);
t_color	color_mul(t_color c, t_f32 factor);
t_color	color_lerp(t_color a, t_color b, t_f32 t);

t_f32	angle_normalize(t_f32 angle);
t_f32	deg_to_rad(t_f32 deg);
t_f32	rad_to_deg(t_f32 rad);

t_f32	minf(t_f32 a, t_f32 b);
t_f32	maxf(t_f32 a, t_f32 b);
t_f32	clampf(t_f32 val, t_f32 lo, t_f32 hi);
t_f32	absf(t_f32 val);
t_f32	iabsf(t_f32 val);

t_i32	mini(t_i32 a, t_i32 b);
t_i32	maxi(t_i32 a, t_i32 b);
t_i32	clampi(t_i32 val, t_i32 lo, t_i32 hi);
t_i32	absi(t_i32 val);

t_f32	lerpf(t_f32 a, t_f32 b, t_f32 t);

#endif
