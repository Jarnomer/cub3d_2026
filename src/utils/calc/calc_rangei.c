/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_rangei.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/16 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <calc.h>

t_rangei	rangei_new(t_i32 min, t_i32 max)
{
	return ((t_rangei){min, max});
}

t_i32	rangei_lerp(t_rangei r, t_f32 t)
{
	return ((t_i32)lerpf((t_f32)r.min, (t_f32)r.max, t));
}

t_i32	rangei_random(t_rangei r)
{
	return (rand_rangei(r.min, r.max));
}

t_i32	rangei_clamp(t_rangei r, t_i32 val)
{
	return (clampi(val, r.min, r.max));
}

bool	rangei_contains(t_rangei r, t_i32 val)
{
	return (val >= r.min && val <= r.max);
}
