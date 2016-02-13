#include "globals.h"

#define BUMPER_NO_COLLISION 0
#define BUMPER_SWAP_X 1
#define BUMPER_SWAP_Y 2

class Bumper
{
public:
    Bumper(double x, double y, double width);
    ~Bumper();
    int calculateCollision(double, double);
    double x, y, width;
}
