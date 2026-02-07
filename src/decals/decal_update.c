/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decal_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/17 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	update_fade(t_decal *decal, t_decaldef *def)
{
	t_f32	fade_start;

	fade_start = def->fade_time;
	if (decal->life >= fade_start)
	{
		decal->opacity = 1.0f;
		return ;
	}
	if (fade_start <= 0.0f)
		decal->opacity = 0.0f;
	else
		decal->opacity = decal->life / fade_start;
	decal->opacity = clampf(decal->opacity, 0.0f, 1.0f);
}

static void	expire_decal(t_decalmgr *mgr, t_u32 index)
{
	t_decal	*decal;

	decal = decal_get(mgr, index);
	if (!decal)
		return ;
	decal->is_active = false;
	pool_free(&mgr->pool, index);
	if (mgr->active > 0)
		mgr->active--;
}

static void	update_decal(t_game *game, t_u32 index, t_f32 dt)
{
	t_decalmgr	*mgr;
	t_decal		*decal;
	t_decaldef	*def;

	mgr = &game->decals;
	decal = decal_get(mgr, index);
	if (!decal || !decal->is_active)
		return ;
	decal->life -= dt;
	if (decal->life <= 0.0f)
	{
		expire_decal(mgr, index);
		return ;
	}
	def = decal_get_def(mgr, decal->type);
	if (!def)
		return ;
	update_fade(decal, def);
	decal_update_anim(decal, def, game, dt);
}

void	decal_update_all(t_game *game, t_f32 dt)
{
	t_decalmgr	*mgr;
	t_u32		i;

	mgr = &game->decals;
	if (mgr->active == 0)
		return ;
	i = 0;
	while (i < mgr->pool.capacity)
	{
		if (mgr->pool.active_flags[i])
			update_decal(game, i, dt);
		i++;
	}
}
