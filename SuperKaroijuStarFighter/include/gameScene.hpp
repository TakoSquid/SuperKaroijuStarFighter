#pragma once

#include <memory>

#include "squid/engine/scene.hpp"
#include "squid/engine/sceneStateMachine.hpp"
#include "squid/engine/spriteAllocator.hpp"
#include "squid/engine/objectCollection.hpp"
#include "squid/engine/object.hpp"
#include "squid/engine/tileMapParser.hpp"
#include "squid/engine/camera.hpp"
#include "squid/engine/sharedContext.hpp"

///////////////////////////////////
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <sstream>

namespace squid
{
    class GameScene : public Scene
    {
    public:
        GameScene(SceneStateMachine &sceneStateMachine, SpriteAllocator &spriteAllocactor, Window &window);

        void OnCreate() override;
        void OnDestroy() override;

        void OnActivate() override;
        void OnDeactivate() override;

        void Update(float deltaTime) override;
        void LateUpdate(float deltaTime) override;
        void Draw(Window &window) override;

    private:
        SceneStateMachine &m_sceneStateMachine;
        SpriteAllocator &m_spriteAllocator;
        ObjectCollection m_Objects;
        std::vector<std::vector<int>> clean;
        SpriteAllocator test;
        squid::Camera *cam;
        std::shared_ptr<squid::Object> player;
        Window &window;
        SharedContext context;
        SharedContext tilesContext;
        TileMapParser mapParser;
    };
} // namespace squid