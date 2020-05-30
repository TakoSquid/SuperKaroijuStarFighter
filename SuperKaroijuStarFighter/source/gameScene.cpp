#include "gameScene.hpp"

#include "C_simpleController.hpp"
#include "C_sprite.hpp"
#include "C_animation.hpp"

#include "tinyxml2.h"

namespace squid
{
    GameScene::GameScene(SceneStateMachine &sceneStateMachine, SpriteAllocator &spriteAllocactor)
        : m_sceneStateMachine{sceneStateMachine},
          m_spriteAllocator{spriteAllocactor},
          test("romfs:/gfx/jungle.t3x"),
          mapParser(test)
    {
    }

    void GameScene::OnCreate()
    {

        /*tinyxml2::XMLDocument xmlDoc;
        tinyxml2::XMLError eResult = xmlDoc.LoadFile("romfs:/map.xml");

        //tinyxml2::XMLNode *pRoot = xmlDoc.FirstChild();
        tinyxml2::XMLElement *map = xmlDoc.FirstChildElement("map");

        int width;
        map->QueryIntAttribute("width", &width);
        int height;
        map->QueryIntAttribute("height", &height);

        std::vector<std::string> layerNames;
        std::vector<std::string> content;

        for (tinyxml2::XMLElement *e = map->FirstChildElement("layer"); e != NULL; e = e->NextSiblingElement("layer"))
        {
            layerNames.emplace_back(e->Attribute("name"));
            std::string c = e->FirstChildElement("data")->GetText();
            c.erase(std::remove(c.begin(), c.end(), '\r'), c.end());
            c.erase(std::remove(c.begin(), c.end(), '\n'), c.end());

            std::stringstream ss(c);
            std::vector<int> vect;

            for (int i; ss >> i;)
            {
                vect.push_back(i);
                if (ss.peek() == ',')
                    ss.ignore();
            }

            clean.emplace_back(vect);
        }

        for (size_t i = 0; i < clean[0].size(); i++)
        {
            auto obj = std::make_shared<Object>();
            auto sprite = obj->AddComponent<C_Sprite>();
            sprite->setAllocator(&test);
            sprite->Load(clean[0][i] - 1);
            int x = i % width;
            int y = i / width;
            float scale = 10.f / 32.0f;
            sprite->setScale(m3d::Vector2f{scale, scale});
            obj->transform->SetPosition(5 + x * 32 * scale, 5 + y * 32 * scale);
            m_Objects.Add(obj);
        }*/

        std::vector<std::shared_ptr<Object>> levelTiles = mapParser.Parse("romfs:/map.xml", m3d::Vector2f{16.0f, 16.0f});

        for (auto &obj : levelTiles)
        {
            m_Objects.Add(obj);
        }

        auto player = std::make_shared<Object>();
        player->transform->SetPosition(200, 120);

        auto sprite = player->AddComponent<C_Sprite>();
        sprite->setAllocator(&m_spriteAllocator);
        sprite->Load(10);
        sprite->flipX(true);

        auto animation = player->AddComponent<C_Animation>();

        player->AddComponent<C_SimpleController>();

        std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>();

        idleAnimation->AddFrame(9, 0.2f);
        idleAnimation->AddFrame(10, 0.2f);

        animation->AddAnimation(squid::AnimationState::Idle, idleAnimation);

        std::shared_ptr<Animation> slowAnimation = std::make_shared<Animation>();

        slowAnimation->AddFrame(11, 0.2f);
        slowAnimation->AddFrame(12, 0.2f);
        slowAnimation->AddFrame(13, 0.2f);

        animation->AddAnimation(squid::AnimationState::SlowFly, slowAnimation);

        m_Objects.Add(player);
    }
    void GameScene::OnDestroy() {}

    void GameScene::OnActivate()
    {
        C2D_Fade(C2D_Color32(0, 0, 0, 0));
    }
    void GameScene::OnDeactivate() {}

    void GameScene::Update(float deltaTime)
    {
        m_Objects.ProcessRemovals();
        m_Objects.ProcessNewObjects();

        m_Objects.Update(deltaTime);
    }

    void GameScene::LateUpdate(float deltaTime)
    {
        m_Objects.LateUpdate(deltaTime);
    }
    void GameScene::Draw(Window &window)
    {
        std::cout << "SCENE 2 !!" << std::endl;
        std::cout << "Il y a : " << m_Objects.getNumberObjects() << " objets dans la scene." << std::endl;
        m_Objects.Draw(window);
    }
} // namespace squid