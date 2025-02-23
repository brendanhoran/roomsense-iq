#include "utilities.h"

// Function to initialize the moving average filter
void moving_average_init(MovingAverageFilter *filter, size_t window_size, uint32_t threshold)
{
	filter->buffer = (int32_t*) calloc(window_size, sizeof(int32_t));
	filter->window_size = window_size;
	filter->threshold = threshold;
	filter->index = 0;
	filter->sum = 0;
	filter->average = 0;
}

// Function to update the moving average filter with a new data point and return the filtered output
int32_t moving_average_update(MovingAverageFilter *filter, int32_t new_data)
{
	// Subtract the oldest data point from the sum
	filter->sum -= filter->buffer[filter->index];

	if (filter->threshold) {
		int32_t delta = new_data - filter->average;

		if (delta > filter->threshold)
		{
			new_data = filter->average + filter->threshold;
		}
		else if (delta < -filter->threshold)
		{
			new_data = filter->average - filter->threshold;
		}
	}

	// Add the new data point to the sum
	filter->sum += new_data;

	// Update the buffer with the new data point
	filter->buffer[filter->index] = new_data;

	// Increment the index circularly
	filter->index = (filter->index + 1) % filter->window_size;

	filter->average = filter->sum / filter->window_size;

	// Calculate and return the moving average
	return filter->average;
}

// Function to free the memory used by the moving average filter
void moving_average_cleanup(MovingAverageFilter *filter)
{
	free(filter->buffer);
}
