/*
  11/16/2016

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
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRZIZE(x) ((sizeof(x) / sizeof(char)))

static inline void update_line(const char *);
static inline void check_n_update(void);

int main(void) {
  struct timespec tc = { 0L, 500L * 1000000L };

  while (1) {
    check_n_update();
    if (-1 == (nanosleep(&tc, NULL))) {
      exit(EXIT_FAILURE);
    }
  }
  return EXIT_SUCCESS;
}

static inline void 
check_n_update(void) {
  static char buf[1000] = "Hello World";

  if (NULL != fgets(buf, 999, stdin)) {
    update_line(buf);
  }
}

static inline void 
update_line(const char *buf) {
  static char x = 0, newbuf[1000] = "Hello World";
  static const char cursor[] = "\0337\033[1;1H\033[K";
  static const char second_end[] = "\0338";
  static char *const first_end = newbuf + STRZIZE(cursor)-1;
  size_t buflen = strlen(buf);

  if (0 == x) {
    memcpy(newbuf, cursor, STRZIZE(cursor)-1);
    x = 1;
  }
  memcpy(first_end, buf, buflen);
  memcpy(first_end + buflen, second_end, STRZIZE(second_end));

  fputs(newbuf, stdout);
  if (0 != (fflush(stdout))) {
    exit(EXIT_FAILURE);
  }
}
