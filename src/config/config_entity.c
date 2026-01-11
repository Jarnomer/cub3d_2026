/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/10 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	process_entity(char **fields, void *ctx)
{
	t_entdef	*defs;
	t_entdef	def;
	t_i32		type;

	defs = (t_entdef *)ctx;
	type = config_str_to_id(fields[0]);
	if (type <= ENTITY_NONE || type >= ENTITY_COUNT)
		return ;
	def = (t_entdef){.type = type};
	def.spr_id = config_str_to_id(fields[1]);
	def.scale = ft_atof(fields[2]);
	def.z_offset = ft_atof(fields[3]);
	def.health = ft_atoi(fields[4]);
	def.is_solid = (ft_atoi(fields[5]) != 0);
	defs[type] = def;
}

void	config_load_entities(t_entdef *defs)
{
	t_cfgload	cfg;

	cfg = (t_cfgload){
		.path = PATH_CONFIG_ENTITY,
		.fields = ENTDEF_FIELD_COUNT,
		.process = process_entity,
		.ctx = defs
	};
	config_parse_file(&cfg);
}
