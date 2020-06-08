#include "component.hpp"

namespace squid
{
    Component::Component(Object *owner)
        : owner_{owner}
    {
    }

    void Component::Awake(){};

    void Component::Start(){};

    void Component::Update(float deltaTime){};

    void Component::LateUpdate(float deltaTime){};

    void Component::Draw(Window &window){};
} // namespace squid