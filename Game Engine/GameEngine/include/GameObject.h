/*! \file This component will allow for a game object to be created within the game 
*			engine. 
*/

#pragma once

#include <unordered_map>
#include <typeindex>

#include "Component.h"

/*! \class This component will allow for other components to be added to the object. */
class GameObject
{

	// Data Members

public: 

	std::string m_id = "Null";

	// Member Functions 
public:

	void m_Update(float dt)
	{
		std::for_each(m_components.begin(), m_components.end(), [](std::pair<std::type_index, Component*> element) 
		{	
			element.second->OnUpdate(0.f); 
		}
		);
	}

	/*! \template This will be used to get another componet which may be attatched to the 
	*				game object; where type T is the component to find.  
	*/
	template <typename T>
	T* getComponent()
	{

		auto iter = m_components.find(typeid(T));

		if(iter != std::end(m_components))
		{
			// if found dynamic cast the component pointer and return it
			return dynamic_cast<T*>(iter->second);
		}
		
		// return null if we don't have a component of that type
		return nullptr;
		
	}

	/*! \template This will be used to add a new component onto this game object; where type T is 
	*				the component to add. 
	*/
	template <typename T>
	void addComponent(T* comp)
	{
		// add the component to unoreder map with hash of its typeid
		m_components[typeid(T)] = comp;
	}
	
private:

	/*! \var This is a map of components, the first item is a pointer to a data type and the 
	*			second is the type of component attacthed to the object. 
	*/
	std::unordered_map<std::type_index, Component*> m_components;
};
