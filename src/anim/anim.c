/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/06 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	anim_init(t_anim *anim, t_u16 def_id)
{
	*anim = (t_anim){.def_id = def_id};
}

void	anim_play(t_anim *anim, t_u16 def_id)
{
	*anim = (t_anim){.def_id = def_id, .playing = true};
}

void	anim_stop(t_anim *anim)
{
	anim->playing = false;
}

void	anim_reset(t_anim *anim)
{
	anim->frame = 0;
	anim->timer = 0.0f;
	anim->finished = false;
}
