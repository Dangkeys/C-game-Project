#include "Spawner.h"

void Spawner::UpdateSpawn(float deltaTime)
{
    waveRunningTime += deltaTime;
    if(waveRunningTime >= waveUpdateTime)
    {
        waveRunningTime = 0;
        if(enemySize <= ENEMYMAX)
            enemySize++;
    }
    for (int i = 0; i < enemySize; i++)
    {
        
    }
}