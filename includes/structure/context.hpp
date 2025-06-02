#pragma once

#include <sparkle.hpp>

#include "network/network_override.hpp"

#include "structure/world.hpp"
#include "structure/actor_map.hpp"

struct Context : public spk::Singleton<Context>
{
	Server server;

	NodeMap nodeMap;
	Tilemap tilemap;
	ActorMap actorMap;
};
