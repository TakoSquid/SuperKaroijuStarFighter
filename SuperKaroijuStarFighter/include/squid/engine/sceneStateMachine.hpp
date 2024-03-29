#pragma once

#include <memory>
#include <unordered_map>

#include "scene.hpp"
#include "window.hpp"

namespace squid
{
    class SceneStateMachine
    {
    public:
        SceneStateMachine();

        void Update(float deltaTime);
        void LateUpdate(float deltaTime);
        void Draw(Window &window);

        unsigned int Add(std::shared_ptr<Scene> scene);

        void SwitchTo(unsigned int id);

        void Remove(unsigned int id);

        unsigned int getCurrentSceneId();

    private:
        std::unordered_map<unsigned int, std::shared_ptr<Scene>> scenes;

        std::shared_ptr<Scene> curScene;

        unsigned int insertedSceneID;
        unsigned int currentSceneID;
    };
} // namespace squid