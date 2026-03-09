#ifndef TIME_H
#define TIME_H

typedef struct time
{
  double last;
  double delta;
} time_t;

void time_init(void);
void time_update(void);

#endif
