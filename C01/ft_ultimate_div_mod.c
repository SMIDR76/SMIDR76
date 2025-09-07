/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_div_mod.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:36:25 by marvin            #+#    #+#             */
/*   Updated: 2025/09/06 11:36:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_ultimate_div_mod(int *a, int *b)
{
    int	div;
    int	mod;

    if (*b != 0)
    {
        div = *a / *b;
        mod = *a % *b;
        *a = div;
        *b = mod;
    }
}

int main(void)
{
    int a = 10;
    int b = 3;

    ft_ultimate_div_mod(&a, &b);
    return 0;
}
