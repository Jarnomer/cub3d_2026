/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	render_destroy(t_render *render)
{
	if (!render)
		return ;
	ft_bzero(render, sizeof(t_render));
}

void	render_init(t_game *game)
{
	game->render.width = WIN_WIDTH;
	game->render.height = WIN_HEIGHT;
	game->render.frame = safe_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	safe_image_to_window(game->mlx, game->render.frame, 0, 0);
}

static void	put_pixel(t_mimg *img, t_i32 x, t_i32 y, t_color c)
{
	t_u32	color;

	if (x < 0 || x >= (t_i32)img->width)
		return ;
	if (y < 0 || y >= (t_i32)img->height)
		return ;
	color = color_to_u32(c);
	mlx_put_pixel(img, x, y, color);
}

void	render_vline(t_game *game, int x, int *y, t_color c)
{
	while (y[0] <= y[1])
	{
		put_pixel(game->render.frame, x, y[0], c);
		y[0]++;
	}
}

void	render_background(t_game *game)
{
	t_i32	x;
	t_i32	y;
	t_i32	half_h;

	half_h = game->render.height / 2;
	y = 0;
	while (y < game->render.height)
	{
		x = 0;
		while (x < game->render.width)
		{
			if (y < half_h)
				put_pixel(game->render.frame, x, y, game->map->ceiling);
			else
				put_pixel(game->render.frame, x, y, game->map->floor);
			x++;
		}
		y++;
	}
}
