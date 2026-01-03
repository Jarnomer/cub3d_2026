/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	input_init(t_input *input)
{
	ft_bzero(input, sizeof(t_input));
}

void	input_update(t_game *game)
{
	int	i;

	i = 0;
	while (i < 512)
	{
		game->input.keys_prev[i] = game->input.keys[i];
		game->input.keys[i] = mlx_is_key_down(game->mlx, i);
		i++;
	}
}

bool	input_key_down(t_input *input, int key)
{
	if (key < 0 || key >= 512)
		return (false);
	return (input->keys[key]);
}

bool	input_key_pressed(t_input *input, int key)
{
	if (key < 0 || key >= 512)
		return (false);
	return (input->keys[key] && !input->keys_prev[key]);
}

bool	input_key_released(t_input *input, int key)
{
	if (key < 0 || key >= 512)
		return (false);
	return (!input->keys[key] && input->keys_prev[key]);
}
