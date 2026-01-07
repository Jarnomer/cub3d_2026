/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <types.h>

/* ************************************************************************** */
/*    FORWARD DECLARATIONS                                                    */
/* ************************************************************************** */

typedef struct s_map	t_map;

/* ************************************************************************** */
/*    CONSTANTS                                                               */
/* ************************************************************************** */

# define MAP_MIN_SIZE		3
# define MAP_MAX_SIZE		256

# define CHAR_EMPTY			'0'
# define CHAR_WALL			'1'
# define CHAR_SPACE			' '
# define CHAR_PLAYER_N		'N'
# define CHAR_PLAYER_S		'S'
# define CHAR_PLAYER_E		'E'
# define CHAR_PLAYER_W		'W'
# define CHAR_BARREL		'B'
# define CHAR_DOOR			'D'
# define CHAR_HEALTH		'H'
# define CHAR_ARMOR			'R'
# define CHAR_AMMO			'X'

# define CHARSET_VALID		"01 NSEWBDHRX"
# define CHARSET_PLAYER		"NSEW"
# define CHARSET_SPAWN		"BDHRX"

# define ID_NORTH			"NO "
# define ID_SOUTH			"SO "
# define ID_EAST			"EA "
# define ID_WEST			"WE "
# define ID_FLOOR			"F "
# define ID_CEILING			"C "

/* ************************************************************************** */
/*    ELEMENT  ENUMS                                                          */
/* ************************************************************************** */
/*
** Used to index parse elements
*/

typedef enum e_elem
{
	ELEM_NO,
	ELEM_SO,
	ELEM_WE,
	ELEM_EA,
	ELEM_F,
	ELEM_C,
	ELEM_COUNT
}	t_elem;

/* ************************************************************************** */
/*    PARSE  STRUCTURE                                                        */
/* ************************************************************************** */
/*
** [ADD DETAILS HERE LATER]
*/

typedef struct s_parse
{
	int			fd;
	char		*line;
	bool		elements[ELEM_COUNT];
	int			elem_count;
	t_map		*map;
}	t_parse;

/* ************************************************************************** */
/*    FUNCTION PROTOTYPES                                                     */
/* ************************************************************************** */
/*
** See source files for function details
*/

t_map	*parse(const char *filepath);

int		parse_file_open(const char *filepath, const char *ext);
void	parse_file_validate(const char *filepath, const char *ext);

void	parse_elements(t_parse *ctx);
void	parse_texture(t_parse *ctx, t_elem type);
void	parse_color(t_parse *ctx, t_elem type);

void	parse_map(t_parse *ctx);
void	parse_map_validate(t_parse *ctx);
void	parse_map_walls(t_parse *ctx);

char	*parse_skip_spaces(char *str);
bool	parse_skip_line(const char *line);
bool	parse_is_empty_line(const char *line);
void	parse_remove_newline(char *str);
t_i32	parse_count_parts(char **parts);

void	parse_save_spawn(t_parse *ctx, int x, int y, char c);

#endif
