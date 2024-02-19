/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_substr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:06:34 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/19 23:04:33 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	free_qte(t_qte *qte)
{
	free(qte->new);
	free(qte->arg);
	free(qte);
}

void	change_dlr_sub(t_qte *qte, int *start, int *i, t_data *d)
{
	char	*sub;

	sub = NULL;
	qte->new = add_in_front(qte, *start, *i - *start);
	if (qte->flag_err == 1)
		return ;
	*start = *i + 1;
	*i = ft_go_end_dollar(qte->arg, *i + 1);
	sub = ft_substr(qte->arg, *start, *i - *start);
	if (!sub)
	{
		free(qte->new);
		qte->flag_err = 1;
		return ;
	}
	gt_dollar(sub, d, qte);
	free(sub);
	*start = *i;
}

void	is_qte_sub(t_qte *qte, int *start, int *i, t_data *d)
{
	qte->new = add_in_front(qte, *start, *i - *start);
	if (qte->flag_err == 1)
		return ;
	if (qte->arg[*i + 1] != qte->arg[*i])
	{
		qte->new = del_simple_quotes(qte, i, *start, d);
		if (qte->flag_err == 1)
			return ;
	}
	else
		*i += 2;
	*start = *i;
	return ;
}
