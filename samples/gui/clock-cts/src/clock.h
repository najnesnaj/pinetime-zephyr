#include <time.h>

void clock_init();
void clock_loop();

time_t clock_get_ticks();
struct tm* clock_get_datetime();
void clock_set_datetime(struct tm* datetime);
