/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:40 by ktombola          #+#    #+#             */
/*   Updated: 2025/10/13 13:50:49 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int count_elements(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
        i++;
    return (i);
}

int parse_ratio(char *str, float *ratio)
{
    if (!is_float(str))
        return (print_error("Wrong ratio"));
    *ratio = s_to_f(str);
    if (*ratio >= 0 && *ratio <= 1)
        return (1);
    else
        return (print_error("Wrong ratio"));
    return (1);
}

void    free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        free(tab[i++]);
    free(tab);
}