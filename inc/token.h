/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:24:31 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/22 04:27:09 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_N
# define TOKEN_N

typedef struct s_token
{
	enum
	{
		TOKEN_CMD,
		TOKEN_DSTRING,
		TOKEN_SSTRING,
		TOKEN_IN_ONE_DSTRING,
		TOKEN_IN_ONE_SSTRING,
		TOKEN_PIPE,
		TOKEN_RREDIR,
		TOKEN_LREDIR,
		TOKEN_HERE_DOC,
		TOKEN_APPRDIR,
		TOKEN_CMD_ARGS,
		TOKEN_NULL
	}		type;
	enum
	{
		ARG_ALONE,
		ARG_IN_ONE_WITH_NEXT
	}	str_position;
	char	*value;
}				t_token;

t_token	*init_token(int type, char *value, char lexer_c);

#endif
