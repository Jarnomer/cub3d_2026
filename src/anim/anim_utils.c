/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_i32	anim_get_frame(t_anim *anim, const t_anidef *def)
{
	if (!def || def->total == 0)
		return (0);
	if (def->reverse)
		return (def->start + def->total - 1 - anim->frame);
	return (def->start + anim->frame);
}

bool	anim_is_playing(t_anim *anim)
{
	return (anim->is_playing && !anim->is_finished);
}
