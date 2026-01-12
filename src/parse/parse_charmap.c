/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_charmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/12 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static const t_charmap	g_charmap[] = {
{'0', CHAR_EMPTY, ENTITY_NONE},
{'1', CHAR_WALL, ENTITY_NONE},
{' ', CHAR_SPACE, ENTITY_NONE},
{'N', CHAR_PLAYER, ENTITY_PLAYER},
{'S', CHAR_PLAYER, ENTITY_PLAYER},
{'E', CHAR_PLAYER, ENTITY_PLAYER},
{'W', CHAR_PLAYER, ENTITY_PLAYER},
{'B', CHAR_SPAWN, ENTITY_BARREL},
{'D', CHAR_SPAWN, ENTITY_DOOR},
{'H', CHAR_SPAWN, ENTITY_HEALTH},
{'R', CHAR_SPAWN, ENTITY_ARMOR},
{'X', CHAR_SPAWN, ENTITY_AMMO},
{'\0', CHAR_INVALID, ENTITY_NONE}
};

static const t_charmap	*charmap_lookup(char c)
{
	int	i;

	i = 0;
	while (g_charmap[i].c != '\0')
	{
		if (g_charmap[i].c == c)
			return (&g_charmap[i]);
		i++;
	}
	return (NULL);
}

bool	charmap_is_valid(char c)
{
	return (charmap_lookup(c) != NULL);
}

bool	charmap_is_player(char c)
{
	const t_charmap	*entry;

	entry = charmap_lookup(c);
	if (!entry)
		return (false);
	return (entry->type == CHAR_PLAYER);
}

bool	charmap_is_spawn(char c)
{
	const t_charmap	*entry;

	entry = charmap_lookup(c);
	if (!entry)
		return (false);
	return (entry->type == CHAR_SPAWN);
}

t_type	charmap_to_entity(char c)
{
	const t_charmap	*entry;

	entry = charmap_lookup(c);
	if (!entry)
		return (ENTITY_NONE);
	return (entry->entity);
}
