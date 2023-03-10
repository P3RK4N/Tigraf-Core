#include "Tigraf/Renderer/Camera/EditorCamera.h"

#include "Tigraf/Input/sdlInput.h"

namespace Tigraf
{
	EditorCamera::EditorCamera
	(
		float aspectRatio, 
		float nearPlane, 
		float farPlane, 
		const glm::vec3& position,
		const glm::vec3& forward,
		const glm::vec3& up,
		float FOV
	)
		: Camera(ProjectionType::PERSPECTIVE, aspectRatio, nearPlane, farPlane, position, forward, up, FOV)
	{
		recalculateView();
		recalculateProjection();
	}

	EditorCamera::~EditorCamera()
	{
	
	}

	void EditorCamera::onUpdate(const TimeStep& ts)
	{
		updateTransform(ts);

		recalculateView();
		recalculateViewProjection();
	}

	void EditorCamera::updateTransform(const TimeStep& ts)
	{
		float moveFactor = ts * m_MoveSpeed;
		glm::vec3 forwardOffset = m_Forward * moveFactor;
		glm::vec3 sideVector = glm::normalize(glm::cross(m_Forward, { 0, 1, 0 }));
		glm::vec3 sideOffset = sideVector * moveFactor;
		glm::vec3 upOffset{ 0,moveFactor,0 };

		if(sdlInput::isKeyDown(TIGRAF_KEY_A)) m_Position -= sideOffset;
		if(sdlInput::isKeyDown(TIGRAF_KEY_D)) m_Position += sideOffset;
		if(sdlInput::isKeyDown(TIGRAF_KEY_S)) m_Position -= forwardOffset;
		if(sdlInput::isKeyDown(TIGRAF_KEY_W)) m_Position += forwardOffset;
		if(sdlInput::isKeyDown(TIGRAF_KEY_SPACE)) m_Position += upOffset;
		if(sdlInput::isKeyDown(TIGRAF_KEY_LSHIFT)) m_Position -= upOffset;

		auto& [dx, dy] = sdlInput::getCursorRelPos();

		if(sdlInput::isMouseButtonDown(TIGRAF_MOUSE_BUTTON_LEFT))
		{
			float rotateFactor = ts * m_RotateSpeed;

			glm::mat4 rotationMat{ 1.0f };
			rotationMat = glm::rotate(glm::radians(-dy * rotateFactor), sideVector) * glm::rotate(glm::radians(-dx * rotateFactor), glm::vec3{ 0,1,0 });

			m_Forward = glm::vec3(rotationMat * glm::vec4(m_Forward, 1.0f));
			m_Forward = glm::normalize(m_Forward);
		
			m_Up = glm::vec3(rotationMat * glm::vec4(m_Up, 1.0f));
			m_Up = glm::normalize(m_Up);
		}
	}

}