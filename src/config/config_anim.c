/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_anim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/10 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	process_anim(char **fields, void *ctx)
{
	t_anidef	*defs;
	t_anidef	def;
	t_i32		id;

	defs = (t_anidef *)ctx;
	id = config_str_to_id(fields[0]);
	if (id <= ANIM_NONE || id >= ANIM_COUNT)
		return ;
	def = (t_anidef){.id = id};
	def.start = (t_u16)ft_atoi(fields[1]);
	def.total = (t_u16)ft_atoi(fields[2]);
	def.duration = ft_atof(fields[3]);
	def.next = (t_u16)ft_atoi(fields[4]);
	def.is_looping = (ft_atoi(fields[5]) != 0);
	def.is_reversed = (ft_atoi(fields[6]) != 0);
	defs[id] = def;
}

void	config_load_anims(t_anidef *defs)
{
	t_cfgload	cfg;

	cfg = (t_cfgload){
		.path = PATH_CONFIG_ANIM,
		.fields = ANIMDEF_FIELD_COUNT,
		.process = process_anim,
		.ctx = defs
	};
	config_parse_file(&cfg);
}
