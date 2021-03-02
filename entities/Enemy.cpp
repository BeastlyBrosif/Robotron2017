#include "Enemy.h"


bool Enemy::checkIfTimeTOShoot()
{

    if ((getTimeWithOffSet() - m_shotStartTime) > m_shotInterval) //if the enforcer has waited long enough to shoot set the hasShot variable to true, so enemy factory can shoot it
    {
        m_hasShot = true;
        m_shotStartTime = getTimeWithOffSet();
        return true;
    }
    else
    {
        m_hasShot = false;
        return false;
    }
}

