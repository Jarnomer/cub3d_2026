/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_rand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_u32	g_prng_state = 1;

void	rand_seed(t_u32 seed)
{
	if (seed == 0)
		seed = 1;
	g_prng_state = seed;
}

t_u32	rand_next(void)
{
	g_prng_state ^= g_prng_state << 13;
	g_prng_state ^= g_prng_state >> 17;
	g_prng_state ^= g_prng_state << 5;
	return (g_prng_state);
}

t_f32	rand_float(void)
{
	return ((t_f32)rand_next() / (t_f32)U32_MAX);
}

t_f32	rand_range(t_f32 lo, t_f32 hi)
{
	return (lo + rand_float() * (hi - lo));
}

t_i32	rand_rangei(t_i32 lo, t_i32 hi)
{
	if (lo >= hi)
		return (lo);
	return (lo + (t_i32)(rand_next() % (t_u32)(hi - lo)));
}
