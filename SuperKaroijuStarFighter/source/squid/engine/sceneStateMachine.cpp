#include "sceneStateMachine.hpp"

namespace squid
{
    SceneStateMachine::SceneStateMachine() : scenes(0), curScene(0), insertedSceneID{0}, currentSceneID{0} {}

    void SceneStateMachine::Update(float deltaTime)
    {
        if (curScene)
        {
            curScene->Update(deltaTime);
        }
    }

    void SceneStateMachine::LateUpdate(float deltaTime)
    {
        if (curScene)
        {
            curScene->LateUpdate(deltaTime);
        }
    }

    void SceneStateMachine::Draw(Window &window)
    {
        if (curScene)
        {
            curScene->Draw(window);
        }
    }

    unsigned int SceneStateMachine::Add(std::shared_ptr<Scene> scene)
    {
        auto inserted = scenes.insert(std::make_pair(insertedSceneID, scene));

        insertedSceneID++;

        inserted.first->second->OnCreate();

        return insertedSceneID - 1;
    }

    void SceneStateMachine::SwitchTo(unsigned int id)
    {
        auto it = scenes.find(id);
        if (it != scenes.end())
        {
            if (curScene)
            {
                curScene->OnDeactivate();
            }

            curScene = it->second;

            curScene->OnActivate();
            currentSceneID = id;
        }
    }

    void SceneStateMachine::Remove(unsigned int id)
    {
        auto it = scenes.find(id);
        if (it != scenes.end())
        {
            if (curScene == it->second)
            {
                curScene = nullptr;
            }

            it->second->OnDestroy();

            scenes.erase(it);
        }
    }

    unsigned int SceneStateMachine::getCurrentSceneId()
    {
        return currentSceneID;
    }

} // namespace squid