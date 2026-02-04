#ifndef TIME_H
#define TIME_H

typedef struct {
  double delta;
  double now;
  double last;
} time_t;

void time_init(void);
void time_update(void);

#endif
