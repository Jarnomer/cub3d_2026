/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/15 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	init_sprite_ctx(t_thread *thread, t_game *game, t_proj *projs,
	t_u32 count)
{
	t_i32	cols_per_thread;
	t_i32	i;

	cols_per_thread = game->render.width / THREAD_COUNT;
	i = 0;
	while (i < THREAD_COUNT)
	{
		thread[i] = (t_thread){.game = game, .projs = projs, .id = i};
		thread[i].count = count;
		thread[i].start = i * cols_per_thread;
		if (i == THREAD_COUNT - 1)
			thread[i].end = game->render.width;
		else
			thread[i].end = (i + 1) * cols_per_thread;
		i++;
	}
}

static void	render_column_range(t_thread *thread, t_proj *proj, t_i32 x)
{
	t_i32	end;

	end = mini(rect_right(proj->bounds), thread->end);
	while (x < end)
	{
		if (zbuf_test(&thread->game->render, x, proj->dist))
		{
			if (proj->use_sheet)
				render_sheet_column(thread->game, proj, x);
			else
				render_sprite_column(thread->game, proj, x);
		}
		x++;
	}
}

static void	*sprite_worker(void *arg)
{
	t_thread	*thread;
	t_proj		*proj;
	t_i32		x;
	t_u32		i;

	thread = (t_thread *)arg;
	i = 0;
	while (i < thread->count)
	{
		proj = &thread->projs[i];
		x = maxi(proj->bounds.x, thread->start);
		render_column_range(thread, proj, x);
		i++;
	}
	return (NULL);
}

static void	thread_sprites(t_game *game, t_proj *projs, t_u32 count)
{
	pthread_t	threads[THREAD_COUNT];
	t_thread	thread[THREAD_COUNT];
	int			err;
	t_i32		i;

	init_sprite_ctx(thread, game, projs, count);
	i = 0;
	while (i < THREAD_COUNT)
	{
		err = pthread_create(&threads[i], NULL, sprite_worker, &thread[i]);
		if (err != 0)
			err_exit_context(MSG_THREAD, strerror(err));
		i++;
	}
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	render_sprites(t_game *game)
{
	t_proj	*projs;
	t_u32	count;
	size_t	bytes;

	if (game->entities.size == 0)
		return ;
	bytes = sizeof(t_proj) * game->entities.size;
	projs = arena_alloc(&game->arena, bytes);
	if (!projs)
		return ;
	count = sprites_collect(game, projs);
	if (count == 0)
		return ;
	sprites_sort(projs, count);
	thread_sprites(game, projs, count);
}
