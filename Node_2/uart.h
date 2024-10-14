#ifndef UART_H
#define UART_H

typedef struct {
	int x;
	int y;
} Point;

// Function to create a point
Point create_point(int x, int y);

// Function to move a point by (dx, dy)
void move_point(Point* p, int dx, int dy);

// Function to calculate the distance between two points
double distance_between_points(Point p1, Point p2);

// Function to print point details
void print_point(Point p);

#endif // UART_H
