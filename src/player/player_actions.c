/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/13 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	handle_crouch(t_game *game)
{
	t_motion	*motion;

	motion = &game->player.motion;
	if (input_key_down(&game->input, KEY_CROUCH))
	{
		if (!motion->is_crouching)
			crouch_start(motion);
	}
	else
	{
		if (motion->is_crouching)
			crouch_end(motion);
	}
}

void	player_actions(t_game *game)
{
	handle_crouch(game);
}
