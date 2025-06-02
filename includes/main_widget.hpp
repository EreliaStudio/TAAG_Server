#pragma once

#include <sparkle.hpp>

#include "network/network_widget.hpp"

#include "widget/world_manager.hpp"

#include "widget/actor_manager.hpp"

#include "widget/player_manager.hpp"

class MainWidget : public spk::Widget
{
private:
	ServerWidget _serverWidget;
	WorldManager _worldManager;
	ActorManager _actorManager;
	PlayerManager _playerManager;

public:
	MainWidget(const std::wstring& p_name, spk::SafePointer<spk::Widget> p_parent);
};