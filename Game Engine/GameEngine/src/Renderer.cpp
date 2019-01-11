#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::m_Render(GameObject *drawable, IEngineCore * core)
{
	try
	{
		if (drawable->getComponent<ModelComponent>() != nullptr && drawable->getComponent<TransformComponent>() != nullptr)
		{
			core->drawModel(drawable->getComponent<ModelComponent>()->m_ThisModel, *&drawable->getComponent<TransformComponent>()->getModelMatrix());
		}
		else
		{
			std::cout << "Unable to draw " << drawable->m_id << "; it lacks either modelComponent or transformComopnent" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void Renderer::m_Render(std::vector<GameObject> &drawable, IEngineCore * core)
{
	if (drawable.size() > 0)
	{
		for (unsigned int i = 0; i < drawable.size(); i++)
		{
			try
			{
				if (drawable[i].getComponent<ModelComponent>() != nullptr && drawable[i].getComponent<TransformComponent>() != nullptr)
				{
					core->drawModel(drawable[i].getComponent<ModelComponent>()->m_ThisModel, *&drawable[i].getComponent<TransformComponent>()->getModelMatrix());
				}
				else
				{
					std::cout << "Unable to draw game object " << drawable[i].m_id << "; it lacks either modelComponent or transformComopnent" << std::endl;
				}
			}
			catch (const std::exception& e) 
			{
				std::cout << e.what() << std::endl;
			}
		
		}
	}
}
