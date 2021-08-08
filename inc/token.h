/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:24:31 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/07 10:48:24 by rcarmen          ###   ########.fr       */
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
		TOKEN_EXEC_ARGS,
		TOKEN_NULL
	}		type;
	char	*value;
}				t_token;

t_token	*init_token(int type, char *value);

#endif
