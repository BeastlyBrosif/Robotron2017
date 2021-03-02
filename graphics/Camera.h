/*
 * Camera.h
 *
 *  Created on: 29 Jan 2018
 *      Author: callum
 */
#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif
#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "../Config.h"

namespace std {

class Camera {
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_ortho = glm::ortho(cfg.negativeXedge, cfg.positiveXedge, cfg.negativeYedge, cfg.positiveYedge, 0.0f, 100.0f);
		m_position = pos;
		m_forward = glm::vec3(0,0,1);
		m_up = glm::vec3(0,1,0);

	}

	inline glm::mat4 GetViewProjection() const
	{
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
	}

	inline glm::mat4 GetOrthoViewProjection() const
	{
		return m_ortho * glm::lookAt(m_position, m_position + m_forward, m_up);
	}

	//virtual ~Camera();


private:
    Config cfg;
	glm::mat4 m_perspective;
	glm::mat4 m_ortho;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;

};

} /* namespace std */

#endif /* CAMERA_H_ */
