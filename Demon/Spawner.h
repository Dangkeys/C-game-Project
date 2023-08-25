#include "raylib.h"

#include "Little.h"
#include "Super.h"
#include "Normal.h"
#include "Runner.h"
#include "Strong.h"
#define ENEMYMAX 50
class Spawner
{
public:
    void UpdateSpawn(float deltaTime);
private:
    float waveUpdateTime{};   
    float waveRunningTime{waveUpdateTime};
    int enemySize{};
    Little littles[ENEMYMAX];
    Normal normals[ENEMYMAX];
    Runner runners[ENEMYMAX];
    Strong strongs[ENEMYMAX];
    Super super[ENEMYMAX];
}