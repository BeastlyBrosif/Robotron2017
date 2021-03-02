#include "Family.h"

void Family::updateRandomDir() //override to allow diagonals, as the base class version does not
{

    if ((getTimeWithOffSet() - dirChangeStartTime) > dirUpdateInterval)
    {
        setDir(rand() % (cfg.NUM_DIRECTIONS));
        dirChangeStartTime = getTimeWithOffSet();
    }
}
