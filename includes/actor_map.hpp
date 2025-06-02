#pragma once

#include <unordered_map>

#include "actor.hpp"

class ActorMap
{
public:
	using ActorID = long;

private:
	std::unordered_map<ActorID, std::unique_ptr<Actor>> _actors;

public:
	void addActor(const ActorID& p_id, std::unique_ptr<Actor>&& p_actor)
	{
		_actors[p_id] = std::move(p_actor);
	}

	bool contains(const ActorID& p_id) const
	{
		return _actors.find(p_id) != _actors.end();
	}

	spk::SafePointer<Actor> actor(const ActorID& p_id) const
	{
		auto it = _actors.find(p_id);
		if (it != _actors.end())
			return it->second.get();
		return nullptr;
	}

	void removeActor(const ActorID& p_id)
	{
		_actors.erase(p_id);
	}

	const std::unordered_map<ActorID, std::unique_ptr<Actor>>& actors() const
	{
		return _actors;
	}

	std::unordered_map<ActorID, std::unique_ptr<Actor>>& actors()
	{
		return _actors;
	}
};