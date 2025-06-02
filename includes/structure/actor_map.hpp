#pragma once

#include <unordered_map>

#include "structure/actor.hpp"

class ActorMap
{
public:
	using ActorID = long;

private:
	std::unordered_map<ActorID, std::unique_ptr<Actor>> _actors;
	ActorID _nextID = 1;

public:
	ActorID addActor(std::unique_ptr<Actor>&& p_actor);

	bool contains(const ActorID& p_id) const;

	spk::SafePointer<Actor> actor(const ActorID& p_id) const;

	void removeActor(const ActorID& p_id);
	void removeActor(const spk::SafePointer<Actor>& p_actor);

	const std::unordered_map<ActorID, std::unique_ptr<Actor>>& actors() const;
	std::unordered_map<ActorID, std::unique_ptr<Actor>>& actors();
};