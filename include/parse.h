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
# include <defs.h>

typedef struct s_map	t_map;

# define MAP_MIN_SIZE		3
# define MAP_MAX_SIZE		256
# define CELL_CENTER		0.5f

# define ID_LEN_COLOR       2
# define ID_LEN_TEXTURE     3

# define PLAYER_DIR_N		'N'
# define PLAYER_DIR_S		'S'
# define PLAYER_DIR_E		'E'

# define ID_NORTH			"NO "
# define ID_SOUTH			"SO "
# define ID_EAST			"EA "
# define ID_WEST			"WE "
# define ID_FLOOR			"F "
# define ID_CEILING			"C "

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

typedef enum e_char
{
	CHAR_INVALID,
	CHAR_EMPTY = '0',
	CHAR_WALL = '1',
	CHAR_SPACE = ' ',
	CHAR_PLAYER,
	CHAR_SPAWN
}	t_char;

typedef struct s_parse
{
	int			fd;
	char		*line;
	bool		elements[ELEM_COUNT];
	int			elem_count;
	t_map		*map;
}	t_parse;

typedef struct s_charmap
{
	char	c;
	t_char	type;
	t_type	entity;
}	t_charmap;

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
t_i32	parse_count_fields(char **parts);

bool	charmap_is_valid(char c);
bool	charmap_is_player(char c);
bool	charmap_is_spawn(char c);
t_type	charmap_to_entity(char c);

#endif
