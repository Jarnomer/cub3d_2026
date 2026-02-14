/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_range.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/16 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <calc.h>

t_range	range_new(t_f32 min, t_f32 max)
{
	return ((t_range){min, max});
}

t_f32	range_lerp(t_range r, t_f32 t)
{
	return (lerpf(r.min, r.max, t));
}

t_f32	range_random(t_range r)
{
	return (rand_range(r.min, r.max));
}

t_f32	range_clamp(t_range r, t_f32 val)
{
	return (clampf(val, r.min, r.max));
}

bool	range_contains(t_range r, t_f32 val)
{
	return (val >= r.min && val <= r.max);
}
