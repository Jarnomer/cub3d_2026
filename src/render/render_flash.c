/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_flash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	flash_init(t_flash *flash)
{
	*flash = (t_flash){0};
}

void	flash_trigger(t_flash *flash, t_u32 color, t_f32 duration)
{
	flash->color = color;
	flash->duration = duration;
	flash->timer = duration;
	flash->active = true;
}

void	flash_update(t_flash *flash, t_f32 dt)
{
	if (!flash->active)
		return ;
	flash->timer -= dt;
	if (flash->timer <= 0.0f)
	{
		flash->timer = 0.0f;
		flash->active = false;
	}
}

void	render_flash(t_game *game, t_flash *flash)
{
	t_f32	alpha_f;
	t_u8	alpha;
	t_u32	color;

	if (!flash->active || flash->duration <= 0.0f)
		return ;
	alpha_f = (flash->timer / flash->duration) * FLASH_MAX_ALPHA;
	alpha = (t_u8)clampf(alpha_f, 0.0f, COLOR_MAX);
	if (alpha < 10)
		return ;
	color = (flash->color & 0x00FFFFFF) | ((t_u32)alpha << 24);
	overlay_fill(&game->render, color);
}
