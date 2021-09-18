/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:24:31 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/17 21:01:05 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_token
{
	enum
	{
		TOKEN_CMD,
		TOKEN_DSTRING,
		TOKEN_SSTRING,
		TOKEN_PIPE,
		TOKEN_RREDIR,
		TOKEN_LREDIR,
		TOKEN_HERE_DOC,
		TOKEN_APPRDIR,
		TOKEN_CMD_ARGS,
		TOKEN_NULL
	}		e_type;
	enum
	{
		ARG_ALONE,
		ARG_IN_ONE_WITH_NEXT
	}	e_str_position;
	char	*value;
}				t_token;

#endif
