/*
  05/30/2017

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
  MA 02110-1301, USA.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char *str = NULL, buf[1000];
  char *ptr = buf;
  int x = 1, z = 0;

  if (1 == argc) {
    return EXIT_FAILURE;
  }

  for (; x < argc; x++, z++) {
    for (str = argv[x]; *str; str++, z++) {
      if (998 < z) {
        goto out;
      }
      if ('\\' == *str && ('e' == *(str+1))) { // the '\e' sequence
        *ptr++ = '\x1B';
        str++;
        continue;
      }
      *ptr++ = *str;
    }
    *ptr++ = ' ';
  }

out:
  *(--ptr) = '\0';

  if (!puts(buf)) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
