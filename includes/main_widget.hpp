#pragma once

#include <sparkle.hpp>

#include "network_widget.hpp"

#include "world_manager.hpp"

#include "actor_manager.hpp"

class MainWidget : public spk::Widget
{
private:
	ServerWidget _serverWidget;
	WorldManager _worldManager;
	ActorManager _actorManager;

public:
	MainWidget(const std::wstring& p_name, spk::SafePointer<spk::Widget> p_parent);
};