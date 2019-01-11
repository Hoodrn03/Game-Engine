#pragma once

#include "IEngineCore.h"

#include "GameObject.h"
#include "ModelComponent.h"
#include "TransformComponent.h"

class Renderer
{

public: 

	Renderer();

	~Renderer(); 

	// Data Members 

private:


	// Member Functions

public:

	void m_Render(GameObject *drawable, IEngineCore *core);

	void m_Render(std::vector<GameObject> &drawable, IEngineCore *core);
};