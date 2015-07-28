#include <stdio.h>
#include "palindrome.h"

/**
 * @file main.c
 * @brief main file with functions used to find palindrome
 *
 * A palindrome number is a "mirror" number, example: 1234321 or 12344321
 *
 * @author ankirama
 * @version 1.0
 */

static int	_pow_ten[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

/**
 * @brief get result number size
 *
 * minimum: 100 x 100 x 100 = length 7
 * maximum: 999 x 999 x 999 = length 9
 * lower / higher number will get a bad length
 *
 * @param nb: number we want the size
 * @return number length
 */
static unsigned int	_len_nbr(unsigned int nb)
{
  if (nb >= 100000000)
    return (9);
  if (nb >= 10000000)
    return (8);
  return (7);
}

/**
 * @brief get nth digit in number
 *
 * example: _get_nth_nb(1234, 0, 4) will return 1
 * example: _get_nth_nb(1234, 3, 4) will return 4
 *
 * @param nb: number we will extract a digit
 * @param pos: position to extract
 * @param len: number length, used to don't calculate it twice or more
 * @return nth digit in number
 */
static unsigned int	_get_nth_nb(unsigned int nb, unsigned int pos, unsigned int len)
{
  return (nb % _pow_ten[len - pos] / _pow_ten[len - pos - 1]);
}

/**
 * @brief check if the current number is a palindrome number
 *
 * we will use 2 "pointers" to travel and check our number (start to position 0 until length - 1)
 * len_sub will start to number length / 2 - 1
 * len_add will start to number length / 2 (+ 1 if the number length is odd)
 * (example with 12345678: len_sub will start to 4 and len_add to 5)
 * (example with odd nbr 12345: len_sub will start to 2 and len_add will start to 4)
 *
 * @param nb: number we want to check
 * @param len_nbr: number length, used to don't calculate it twice or more
 * @return 1 if the number is a palindrome, else 0
 */
static char	_is_palindrome(unsigned int nb, unsigned int len_nbr)
{
  unsigned int	len;
  unsigned int	len_sub;
  unsigned int	len_add;

  len = len_nbr / 2;
  len_sub = len_nbr / 2;
  len_add = len_nbr / 2 - (len_nbr % 2 == 0 ? 1 : 0);
  while (--len_sub < len)
    {
      if (_get_nth_nb(nb, len_sub, len_nbr) != _get_nth_nb(nb, ++len_add, len_nbr))
	return (0);
    }
  return (1);
}

/**
 * @brief main function used to travel and try to find biggest palindrome
 *
 * We will travel in our 3 numbers (a b c) until they reach 100
 * To avoid duplicate calcul, we will calcul our palindrome if a <= b <= c
 *
 * @return 0 if no palindrome, else the result to a x b x c
 */
static unsigned int	_find_palindrome()
{
  int			a;
  int			b;
  int			c;
  int			res;
  int			bigger;

  bigger = 0;
  for (a = 999; a >= 100; --a)
    {
      for (b = 999; b >= 100; --b)
	{
	  for (c = 999; c >= 100; --c)
	    {
	      if (a <= b && b <= c)
		{
		  res = a * b * c;
		  if (_is_palindrome(res, _len_nbr(res)) && res > bigger)
		    bigger = res;
		}
	    }
	}
    }
  return (bigger);
}

/**
 * @brief print result from _find_palindrome
 *
 * @return 0
 */
int	main()
{
  printf("result: %d\n", _find_palindrome());
  return (0);
}
