#include "MiniginPCH.h"
#include "SceneObject.h"
#include "ComponentBase.h"

ComponentBase::ComponentBase()
	:m_pOwner{nullptr}
{

}

ComponentBase::~ComponentBase()
{
	std::cout << "BaseComponent Destructor Called!" << std::endl;
}


void ComponentBase::SetOwner(dae::SceneObject *pOwner)
{
	m_pOwner = pOwner;
}

