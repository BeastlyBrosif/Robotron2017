#ifndef BORDER_H
#define BORDER_H

#include "Entity.h"
#include "../graphics/Shader.h"
#include "../graphics/Camera.h"


class Border : public Entity
{
    public:
        Border(float r, float g, float b, float a, bool usesGapForText):Entity(){
        m_red = r;
        m_green = g;
        m_blue = b;
        m_alpha = a;
        m_usesGapForText = usesGapForText;
        dir = cfg.NO_DIR;
        transform.GetPos()->x = 0;
        transform.GetPos()->y = 0;
        scale = 1;

        init();
        };
        void init();
        void update(Camera * camera, Shader * shader);
        ~Border(){};
    protected:
    float m_red;
    float m_green;
    float m_blue;
    float m_alpha;
    bool m_usesGapForText;
    private:

};

#endif // BORDER_H
