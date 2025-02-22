#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <stdlib.h>

typedef struct {
	uint16_t* buffer; // Buffer to hold the data points
	uint16_t window_size; // Size of the moving average window
	uint16_t index; // Index of the current data point in the buffer
	uint16_t sum; // Sum of the data points in the buffer
	uint16_t average; // Moving average
} MovingAverageFilter;

void moving_average_init(MovingAverageFilter* filter, uint16_t window_size);
uint16_t moving_average_update(MovingAverageFilter* filter, uint16_t new_data);
void moving_average_cleanup(MovingAverageFilter* filter);

#endif
