#include "pch.h"
#include "GameObject.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(GameObject)

    GameObject::GameObject() :
        Attributed(GameObject::TypeIdClass())
    {

    }


    GameObject::GameObject(RTTI::IdType id) :
        Attributed(id)
    {

    }

    gsl::owner<GameObject*> GameObject::Clone() const
    {
        return new GameObject(*this);
    }

    bool GameObject::Equals(const RTTI* rhs) const
    {
        return rhs == this;
    }

    std::string GameObject::ToString() const
    {
        return mName;
    }

    void GameObject::Update(const GameTime& deltaTime)
    {
        Datum* datum = Find("Children"); 
        if (datum != nullptr)
        {
            Datum* childDatum = datum->GetScope()->Find("Children");
            size_t size = childDatum->Size();
            for (size_t i = 0; i < size; i++)
            {
                assert(childDatum->GetScope(i)->Is(GameObject::TypeIdClass()));
                static_cast<GameObject*>(childDatum->GetScope(i))->Update(deltaTime);
            }
        }

        datum = Find("Actions");
        if (datum != nullptr)
        {
            Datum* childDatum = datum->GetScope()->Find("Actions");
            size_t size = childDatum->Size();
            for (size_t i = 0; i < size; i++)
            {
                assert(childDatum->GetScope(i)->Is(Action::TypeIdClass()));
                static_cast<Action*>(childDatum->GetScope(i))->Update(deltaTime);
            }
        }

        if (GetParent()->GetParent() == nullptr)
        {
            GameState::CreateActions();
            GameState::DestroyActions();
        }
    }

    const Vector<Signature> GameObject::Signatures()
    {
        return Vector<Signature>
        {
            { "Name", Datum::DatumTypes::String, 1, offsetof(GameObject, mName) },
            { "Transform Position", Datum::DatumTypes::Vector, 1, offsetof(GameObject, mTransform.Position) },
            { "Transform Rotation", Datum::DatumTypes::Vector, 1, offsetof(GameObject, mTransform.Rotation) },
            { "Transform Scale", Datum::DatumTypes::Vector, 1, offsetof(GameObject, mTransform.Scale) },
            { "Children", Datum::DatumTypes::Table, 0, 0 },
            { "Actions", Datum::DatumTypes::Table, 0, 0 }
        };
    }

    void GameObject::CreateAction(const std::string& className, const std::string& instanceName)
    {
        Find("Actions")->GetScope()->Adopt(instanceName, *Factory<Scope>::Create(className));
    }

    const Datum& GameObject::Actions()
    {
        return *Find("Actions");
    }
}