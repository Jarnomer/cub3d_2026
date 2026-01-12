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
# define U32_MAX	4294967295U
# define INFINITE	1e30f
# define EPSILON	0.0001f
# define COLOR_MAX	255

t_u8	color_r(t_u32 c);
t_u8	color_g(t_u32 c);
t_u8	color_b(t_u32 c);
t_u8	color_a(t_u32 c);
t_u32	color_rgba(t_u8 r, t_u8 g, t_u8 b, t_u8 a);

t_u32	color_lerp(t_u32 c1, t_u32 c2, t_u8 factor);
t_u32	color_blend(t_u32 src, t_u32 dst, t_u8 alpha);
bool	color_is_opaque(t_u32 color);
bool	color_is_solid(t_u32 color);

t_f32	rad_to_deg(t_f32 rad);
t_f32	deg_to_rad(t_f32 deg);
t_f32	angle_normalize(t_f32 angle);

t_f32	minf(t_f32 a, t_f32 b);
t_f32	maxf(t_f32 a, t_f32 b);
t_f32	clampf(t_f32 val, t_f32 lo, t_f32 hi);
t_f32	absf(t_f32 val);
t_f32	iabsf(t_f32 val);

t_i32	mini(t_i32 a, t_i32 b);
t_i32	maxi(t_i32 a, t_i32 b);
t_i32	clampi(t_i32 val, t_i32 lo, t_i32 hi);
t_i32	absi(t_i32 val);

void	rand_seed(t_u32 seed);
t_u32	rand_next(void);
t_f32	rand_float(void);
t_f32	rand_range(t_f32 lo, t_f32 hi);
t_i32	rand_rangei(t_i32 lo, t_i32 hi);

#endif
