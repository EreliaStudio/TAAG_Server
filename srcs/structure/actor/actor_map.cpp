#include "structure/actor_map.hpp"

ActorMap::ActorID ActorMap::addActor(std::unique_ptr<Actor>&& p_actor)
{
	ActorID newID = _nextID++;
	_actors[newID] = std::move(p_actor);
	return newID;
}

bool ActorMap::contains(const ActorID& p_id) const
{
	return _actors.find(p_id) != _actors.end();
}

spk::SafePointer<Actor> ActorMap::actor(const ActorID& p_id) const
{
	auto it = _actors.find(p_id);
	if (it != _actors.end())
		return it->second.get();
	return nullptr;
}

void ActorMap::removeActor(const ActorID& p_id)
{
	_actors.erase(p_id);
}

void ActorMap::removeActor(const spk::SafePointer<Actor>& p_actor)
{
	for (auto it = _actors.begin(); it != _actors.end(); ++it)
	{
		if (it->second.get() == p_actor.get())
		{
			_actors.erase(it);
			return;
		}
	}
}

const std::unordered_map<ActorMap::ActorID, std::unique_ptr<Actor>>& ActorMap::actors() const
{
	return _actors;
}

std::unordered_map<ActorMap::ActorID, std::unique_ptr<Actor>>& ActorMap::actors()
{
	return _actors;
}