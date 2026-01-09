/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	input_init(t_input *input)
{
	*input = (t_input){0};
}

static void	update_mouse_delta(t_game *game)
{
	t_vec2	center;

	if (!game->input.mouse_captured)
	{
		game->input.mouse_delta = vec2_zero();
		return ;
	}
	center.x = (t_f32)(game->render.width / 2);
	center.y = (t_f32)(game->render.height / 2);
	game->input.mouse_delta = vec2_sub(game->input.mouse_pos, center);
	input_mouse_center(game);
}

void	input_update(t_game *game)
{
	int	i;

	i = 0;
	while (i < MAX_KEYS)
	{
		game->input.keys_prev[i] = game->input.keys[i];
		game->input.keys[i] = mlx_is_key_down(game->mlx, i);
		i++;
	}
	i = 0;
	while (i < MAX_MOUSE_KEYS)
	{
		game->input.mouse_prev[i] = game->input.mouse[i];
		game->input.mouse[i] = mlx_is_mouse_down(game->mlx, i);
		i++;
	}
	update_mouse_delta(game);
}

static void	cursor_callback(double xpos, double ypos, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->input.mouse_pos.x = (t_f32)xpos;
	game->input.mouse_pos.y = (t_f32)ypos;
}

void	input_mouse_init(t_game *game)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(game->mlx, &x, &y);
	game->input.mouse_pos.x = (t_f32)x;
	game->input.mouse_pos.y = (t_f32)y;
	game->input.mouse_captured = false;
	mlx_cursor_hook(game->mlx, cursor_callback, game);
}
