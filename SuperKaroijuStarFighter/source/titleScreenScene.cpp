// #include "titleScreenScene.hpp"

// #include "squid/tools/color.hpp"

// namespace squid
// {
//     TitleScreenScene::TitleScreenScene(SceneStateMachine &sceneStateMachine, SpriteAllocator &spriteAllocator)
//         : m_sceneStateMachine{sceneStateMachine},
//           m_spriteAllocator{spriteAllocator},
//           m_sceneAfterStart{0},
//           m_fade{0},
//           m_music{"romfs:/titleScreenMusic.mp3"},
//           m_sound{"romfs:/bbb.wav"}
//     {
//     }

//     void TitleScreenScene::SceneAfterStart(unsigned int id)
//     {
//         m_sceneAfterStart = id;
//     }

//     void TitleScreenScene::OnCreate()
//     {

//         //Background
//         auto bgObj = std::make_shared<Object>(context);
//         bgObj->transform->SetPosition(200, 120);

//         auto scrollCompo = bgObj->AddComponent<C_ScrollingBackground>();
//         scrollCompo->setAllocator(&m_spriteAllocator);
//         scrollCompo->SetSpriteId(3);
//         scrollCompo->SetSpeed(200.0f);

//         //Karo Géante
//         auto karoObj = std::make_shared<Object>();
//         karoObj->transform->SetPosition(75, 120);

//         auto karoOffset = karoObj->AddComponent<C_OffsetPad>();
//         karoOffset->setMagnitude(10.0f);

//         karoFollowTrail = karoObj->AddComponent<C_FollowTrail>();
//         karoFollowTrail->setAllocator(&m_spriteAllocator);

//         //Title
//         titleObj = std::make_shared<Object>();

//         auto titleSprite = titleObj->AddComponent<C_Sprite>();
//         // titleSprite->setAllocator(&m_spriteAllocator);
//         titleSprite->Load(0);

//         auto titleGoTowards = titleObj->AddComponent<C_GoTowards>();

//         //Press Start
//         pressStartObj = std::make_shared<Object>();

//         auto titleSpriteJr = pressStartObj->AddComponent<C_Sprite>();
//         // titleSpriteJr->setAllocator(&m_spriteAllocator);
//         titleSpriteJr->Load(5);

//         auto titleGoTowardsJr = pressStartObj->AddComponent<C_GoTowards>();

//         pressStartBling = pressStartObj->AddComponent<C_Blinking>();

//         //Adding all objs
//         m_Objects.Add(bgObj);
//         m_Objects.Add(titleObj);
//         m_Objects.Add(pressStartObj);
//         m_Objects.Add(karoObj);
//     }

//     void TitleScreenScene::OnDestroy()
//     {
//     }

//     void TitleScreenScene::OnActivate()
//     {
//         m_music.setVolume(1.0f);
//         m_music.play();

//         karoFollowTrail->Load(1);

//         titleObj->transform->SetPosition(270, -titleObj->GetComponent<C_Sprite>()->getSize().v / 2.0f);
//         titleObj->GetComponent<C_GoTowards>()->setGoal(m3d::Vector2f{270, 140});
//         titleObj->GetComponent<C_GoTowards>()->setSpeed(250.0f);

//         pressStartObj->transform->SetPosition(240, 400 + pressStartObj->GetComponent<C_Sprite>()->getSize().v / 2.0f);
//         pressStartObj->GetComponent<C_GoTowards>()->setGoal(m3d::Vector2f{240, 180});
//         pressStartObj->GetComponent<C_GoTowards>()->setSpeed(250.0f);
//         pressStartBling->setTimeGoal(0.5f);

//         m_fade = 0.0f;
//     }

//     void TitleScreenScene::OnDeactivate()
//     {
//         m_music.stop();
//     }

//     void TitleScreenScene::Update(float deltaTime)
//     {
//         m_Objects.ProcessRemovals();
//         m_Objects.ProcessNewObjects();

//         if (m_fade >= 1.0f)
//             m_sceneStateMachine.SwitchTo(m_sceneAfterStart);

//         if (m3d::buttons::buttonPressed(m3d::buttons::Start) && m_fade == 0.0f)
//         {
//             m_fade += 1.0f * deltaTime;
//             m_sound.play();
//             pressStartBling->setTimeGoal(0.05f);
//         }

//         if (m_fade != 0.0f)
//         {
//             m_fade += 1.0f * deltaTime;
//             m_music.setVolume(1.0f - m_fade);
//         }

//         m_Objects.Update(deltaTime);
//     }

//     void TitleScreenScene::LateUpdate(float deltaTime)
//     {
//         m_Objects.LateUpdate(deltaTime);
//     }

//     void TitleScreenScene::Draw(Window &window)
//     {
//         m_Objects.Draw(window);
//         std::cout << "GameObject amount : " << m_Objects.getNumberObjects() << std::endl;
//         C2D_Fade(C2D_Color32f(0, 0, 0, m_fade));
//     }
// } // namespace squid