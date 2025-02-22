#include "utilities.h"

// Function to initialize the moving average filter
void moving_average_init(MovingAverageFilter *filter, uint16_t window_size)
{
	filter->buffer = (uint16_t*) calloc(window_size, sizeof(uint16_t));
	filter->window_size = window_size;
	filter->index = 0;
	filter->sum = 0;
	filter->average = 0;
}

// Function to update the moving average filter with a new data point and return the filtered output
uint16_t moving_average_update(MovingAverageFilter *filter, uint16_t new_data)
{
	int delta;

	// Subtract the oldest data point from the sum
	filter->sum -= filter->buffer[filter->index];

	delta = new_data - filter->average;
	if (delta > 10)
	{

		new_data = filter->average + 10;
	}

	if (delta < -10)
	{

		new_data = filter->average - 10;
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
