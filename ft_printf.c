/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:34:22 by majosue           #+#    #+#             */
/*   Updated: 2019/11/13 20:31:21 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int isright(char c)
{
  if (c == '%'  || c == 's' || c == 'p' || c == 'd' || c == 'o' ) // надо дополнить или массив или еще чего еще не придумал
    return (1);
  else 
    return (0);
}

int ft_format(const char *str)
{
  int i;

  i = 1;
  while (str[i])
  {
    if (isright(str[i]))
        return (i);
    i++;
  }
  return (i);
}

void separator(const char *str)
{
  int tmp;
  
  while (*str)
    {
      if (*str == '%')
        {
          tmp = ft_format(str);
          ft_putchar('\n');
        }
      str +=tmp;        
      ft_putchar(*str);
    str++;
    }
}


int ft_printf(const char *restrict format, ...)
{
    char **istring;
    int i;

    i = 0;
    separator(format);
    return (0);
}
int main ()
{
    ft_printf("%%Test print string %parametr string");
   // printf("Проверка работы параметров %50.45f \n", 1.234567891011);
  //   printf("Проверка работы параметров %100.  10                   d                 \n", 5);
    return (0);
}