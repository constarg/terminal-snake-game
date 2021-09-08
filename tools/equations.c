#include <equations.h>
#include <math.h>
#include <stdio.h>


double calculate_distance(int x1, int y1, int x2, int y2) {
    double part_1 = pow(x2 - x1, 2);
    double part_2 = pow(y2 - y1, 2);

    return (double) sqrt(part_1 + part_2);
}
