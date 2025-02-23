#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <stdlib.h>

typedef struct {
	int32_t* buffer; // Buffer to hold the data points
	uint16_t window_size; // Size of the moving average window
	int32_t threshold; // Threshold of delta to filter using a ramp up/down value
	size_t index; // Index of the current data point in the buffer
	int32_t sum; // Sum of the data points in the buffer
	int32_t average; // Moving average
} MovingAverageFilter;

void moving_average_init(MovingAverageFilter* filter, size_t window_size, uint32_t threshold);
int32_t moving_average_update(MovingAverageFilter* filter, int32_t new_data);
void moving_average_cleanup(MovingAverageFilter* filter);

#define ROUND_TO_NEAREST(value, nearest) (((value + (nearest / 2)) / nearest) * nearest)

#endif
