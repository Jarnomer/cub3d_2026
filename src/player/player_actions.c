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

static bool	is_moving_forward(t_game *game)
{
	if (SPRINT_ALLOW_STRAFE)
		return (input_key_down(&game->input, MLX_KEY_W)
			|| input_key_down(&game->input, MLX_KEY_A)
			|| input_key_down(&game->input, MLX_KEY_S)
			|| input_key_down(&game->input, MLX_KEY_D));
	return (input_key_down(&game->input, MLX_KEY_W));
}

static void	handle_sprint(t_game *game)
{
	t_motion	*motion;

	motion = &game->player.motion;
	if (input_key_down(&game->input, KEY_SPRINT) && is_moving_forward(game))
		sprint_start(motion);
	else
		sprint_stop(motion);
}

static void	handle_jump(t_game *game)
{
	t_motion	*motion;

	motion = &game->player.motion;
	if (input_key_pressed(&game->input, KEY_JUMP))
		jump_start(motion);
}

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
	handle_jump(game);
	handle_sprint(game);
}
