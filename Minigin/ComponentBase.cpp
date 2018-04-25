#include "MiniginPCH.h"
#include "SceneObject.h"
#include "ComponentBase.h"

ComponentBase::ComponentBase()
	:m_pOwner{nullptr}
{

}

ComponentBase::~ComponentBase()
{

}


void ComponentBase::SetOwner(std::unique_ptr<dae::SceneObject> pOwner)
{
	m_pOwner = std::move(pOwner);
}

