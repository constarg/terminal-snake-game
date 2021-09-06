#include <equations.h>
#include <math.h>


int calculate_distance(int x1, int y1, int x2, int y2) {
    int part_1 = (int) (x1 - x2) * (x1 - x2);
    int part_2 = (int) (y1 - y2) * (y1 - y2);

    return (int) sqrt(part_1 + part_2);
}
