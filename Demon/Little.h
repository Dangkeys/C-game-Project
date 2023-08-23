#include "raylib.h"
#include "Enemy.h"

class Little: public Enemy
{
public:
    Little();
private:
    int tileSize{32 * 4};
};

