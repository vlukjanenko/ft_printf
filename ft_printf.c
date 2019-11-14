/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:34:22 by majosue           #+#    #+#             */
/*   Updated: 2019/11/14 20:16:18 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int ft_endc() // тут проверяем чем заканчивается спец строка // 0 - валидный не конец 1 валидный конец -1 инвалидный конец
{
char fs[7];
char lm[4];
char cs[8];

ft_strcpy(fs, " %#0-+");
ft_strcpy(lm, "hlL");
ft_strcpy(cs, "dinouxX");
return (0);
}

int ft_printf(const char *restrict format, ...)
{
 // t_list *str;
 // t_list *con;
 // int i;
    if (!ft_strchr(format,'%'))
    {
      ft_putstr(format); 
      return (ft_strlen(format));
    }
  //  else
  //    readstr(format, &str, &con); // для универсальности всегда будем заполнять структуру вывода даже если с % начинается
    return (0);
  }
int main ()
{
  ft_endc();
  ft_printf("Test print string");

   // printf("Проверка работы параметров %50.45f \n", 1.234567891011);
   
   //  printf("Проверка работы параметров %-50.10%\n", 126112231231231);
    return (0);
}