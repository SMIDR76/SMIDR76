/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:14:55 by marvin            #+#    #+#             */
/*   Updated: 2025/09/06 11:14:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_div_mod(int a, int b, int *div, int *mod)
{
    if (b != 0) 
    {
        *div = a / b;
        *mod = a % b;
    }

    else
    {
        *div = 0; 
        *mod = 0; 
    }
}

int main(void)
{
    int x;
    int y;
    int division;
    int modulus;

    x = 42;
    y = 5;
    ft_div_mod(x, y, &division, &modulus);

    return (0);
}
