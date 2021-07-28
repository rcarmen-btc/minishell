/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:24:31 by rcarmen           #+#    #+#             */
/*   Updated: 2021/07/28 21:24:33 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_N
# define TOKEN_N

typedef struct s_token
{
	enum
	{
		TOKEN_ID,
		TOKEN_DSTRING,
		TOKEN_SSTRING,
		TOKEN_IN_ONE_DSTRING,
		TOKEN_IN_ONE_SSTRING,
		TOKEN_PIPE,
		TOKEN_RREDIR,
		TOKEN_LREDIR,
		TOKEN_HERE_DOC,
		TOKEN_APPRDIR,
		TOKEN_NULL = 0
	}		type;

	char	*value;
}				t_token;

t_token	*init_token(int type, char *value);

#endif
