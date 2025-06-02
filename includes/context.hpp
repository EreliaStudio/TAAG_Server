#pragma once

#include "network_override.hpp"

#include "world.hpp"
#include "actor_map.hpp"

struct Context : public spk::Singleton<Context>
{
	Server server;

	NodeMap nodeMap;
	Tilemap tilemap;
	ActorMap actorMap;
};
