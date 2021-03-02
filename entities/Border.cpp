#include "Border.h"

void Border::init()
{
    float borderWidth = cfg.BORDER_WIDTH/2; //this is doubled down below as we are drawing from negative to positive, so half it

    float gapForText;

    if(m_usesGapForText)
    {
        gapForText = cfg.GAP_FOR_TEXT;
    }
    else
    {
        gapForText = 0;
    }

    float top = cfg.positiveYedge - borderWidth - gapForText;
    float bottom = cfg.negativeYedge + borderWidth;

    float left = cfg.positiveXedge - borderWidth;
    float right = cfg.negativeXedge + borderWidth;

    //top border
    vertexVec.push_back(glm::vec3(cfg.negativeXedge,top + borderWidth,0.1));
	vertexVec.push_back(glm::vec3(cfg.negativeXedge,top -borderWidth,0.1));
	vertexVec.push_back(glm::vec3(cfg.positiveXedge,top -borderWidth,0.1));
	vertexVec.push_back(glm::vec3(cfg.negativeXedge,top + borderWidth,0.1));
	vertexVec.push_back(glm::vec3(cfg.positiveXedge,top -borderWidth,0.1));
	vertexVec.push_back(glm::vec3(cfg.positiveXedge,top + borderWidth,0.1));

    //bottom border
    vertexVec.push_back(glm::vec3(cfg.negativeXedge,bottom + borderWidth,0.1));
	vertexVec.push_back(glm::vec3(cfg.negativeXedge,bottom -borderWidth,0.1));
	vertexVec.push_back(glm::vec3(cfg.positiveXedge,bottom -borderWidth,0.1));
	vertexVec.push_back(glm::vec3(cfg.negativeXedge,bottom + borderWidth,0.1));
	vertexVec.push_back(glm::vec3(cfg.positiveXedge,bottom -borderWidth,0.1));
	vertexVec.push_back(glm::vec3(cfg.positiveXedge,bottom + borderWidth,0.1));


    //left border
    vertexVec.push_back(glm::vec3(left-borderWidth,cfg.positiveYedge - gapForText,0.1));
	vertexVec.push_back(glm::vec3(left-borderWidth,cfg.negativeYedge,0.1));
	vertexVec.push_back(glm::vec3(left + borderWidth,cfg.negativeYedge,0.1));
	vertexVec.push_back(glm::vec3(left-borderWidth,cfg.positiveYedge - gapForText,0.1));
	vertexVec.push_back(glm::vec3(left + borderWidth,cfg.negativeYedge,0.1));
	vertexVec.push_back(glm::vec3(left + borderWidth,cfg.positiveYedge - gapForText,0.1));

    //right border
    vertexVec.push_back(glm::vec3(right-borderWidth,cfg.positiveYedge - gapForText,0.1));
	vertexVec.push_back(glm::vec3(right-borderWidth,cfg.negativeYedge,0.1));
	vertexVec.push_back(glm::vec3(right + borderWidth,cfg.negativeYedge,0.1));
	vertexVec.push_back(glm::vec3(right-borderWidth,cfg.positiveYedge - gapForText,0.1));
	vertexVec.push_back(glm::vec3(right + borderWidth,cfg.negativeYedge,0.1));
	vertexVec.push_back(glm::vec3(right + borderWidth,cfg.positiveYedge - gapForText,0.1));

    for(int i = 0; i < vertexVec.size();i++) //loop through and add the color for every vertex of the border
    {
        colorVec.push_back(glm::vec4(m_red, m_green, m_blue, m_alpha));
    }

	addMesh(new Mesh(vertexVec,  indexVec,colorVec, false , false, false), cfg.NO_DIR);
}

void Border::update(Camera * camera, Shader * shader)
{
    shader->Update(transform,*camera); //temporary for drawing the border
    draw(cfg.NO_DIR);
}
