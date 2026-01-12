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

static void	update_keys(t_game *game)
{
	int	i;

	i = 0;
	while (i < MAX_KEYS)
	{
		game->input.keys_prev[i] = game->input.keys[i];
		game->input.keys[i] = mlx_is_key_down(game->mlx, i);
		i++;
	}
}

static void	update_mouse(t_game *game)
{
	int	i;

	i = 0;
	while (i < MAX_MOUSE_KEYS)
	{
		game->input.mouse_prev[i] = game->input.mouse[i];
		game->input.mouse[i] = mlx_is_mouse_down(game->mlx, i);
		i++;
	}
	input_mouse_update(game);
}

void	input_update(t_game *game)
{
	update_keys(game);
	update_mouse(game);
}
