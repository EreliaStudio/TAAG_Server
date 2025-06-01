#pragma once

#include "network_override.hpp"

#include "world.hpp"

struct Context : public spk::Singleton<Context>
{
	Server server;

	NodeMap nodeMap;
	Tilemap tilemap;
};
