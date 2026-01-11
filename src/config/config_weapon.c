/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/10 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	process_weapon(char **fields, void *ctx)
{
	t_wpndef	*defs;
	t_wpndef	def;
	t_i32		id;

	defs = (t_wpndef *)ctx;
	id = config_str_to_id(fields[0]);
	if (id <= WEAPON_NONE || id >= WEAPON_COUNT)
		return ;
	def = (t_wpndef){.id = id};
	def.sheet_id = config_str_to_id(fields[1]);
	def.anim_idle = config_str_to_id(fields[2]);
	def.anim_fire = config_str_to_id(fields[3]);
	def.anim_reload = config_str_to_id(fields[4]);
	def.ammo_type = config_str_to_id(fields[5]);
	def.damage = ft_atoi(fields[6]);
	def.pellets = ft_atoi(fields[7]);
	def.mag_size = ft_atoi(fields[8]);
	def.fire_rate = ft_atof(fields[9]);
	defs[def.id] = def;
}

void	config_load_weapons(t_wpndef *defs)
{
	t_cfgload	cfg;

	cfg = (t_cfgload){
		.path = PATH_CONFIG_WEAPON,
		.fields = WPNDEF_FIELD_COUNT,
		.process = process_weapon,
		.ctx = defs
	};
	config_parse_file(&cfg);
}
