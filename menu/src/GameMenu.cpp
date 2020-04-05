/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** GameMenu
*/

#include <string>
#include <vector>
#include <unordered_map>
#include "deps/keys.hpp"
#include "core/ICore.hpp"
#include "GameMenu.hpp"
#include "class/scene/Prompt.hpp"
#include "class/scene/Menu.hpp"

using namespace arcade;

GameMenu::GameMenu(ICore &core)
    : AGame(core)
    , _currScene(S_PROMPT)
{
    _scenes.emplace_back(std::make_unique<Prompt>(*this));
    _scenes.emplace_back(std::make_unique<Menu>(*this));

    if (_core.getUserName().empty())
        _currScene = S_PROMPT;
    else
        _currScene = S_MENU;

    _core.loadResourceFont(F_MENUS, "menu/assets/digitalt-regular.ttf");
    _core.loadResourceImage(I_ARROW, "menu/assets/arrow.png", "menu/assets/arrow");
}

ICore &GameMenu::getCore() const
{
    return (_core);
}

void GameMenu::setScene(const E_Scene scene)
{
    _currScene = scene;
}

void GameMenu::launch()
{
    std::unique_ptr<IClock> clock = _core.createClock();
    double elapsed = 0;

    _running = true;
    while (_running) {
        elapsed = clock->getElapsedTime();
        if (elapsed >= 1000 / 30) {
            clock->reset();
            _scenes[_currScene]->pollEvents();
            _core.clear();
            _scenes[_currScene]->draw();
            _core.render();
        }
    }
}