#pragma once

#include <sparkle.hpp>

#include "serializable_object.hpp"

struct Node
{
	bool isObstacle = false;
};

class NodeMap
{
public:
	using ID = char;

private:
	std::unordered_map<ID, Node> _nodes;

public:
	NodeMap() = default;

	void addNode(const ID& p_id, Node p_node);

	bool contains(const ID& p_id) const;

	const Node& node(const ID& p_id) const;
};

class Actor;

class Chunk : public spk::IChunk<NodeMap::ID, 16, 16, 3>, public SerializableObject
{
private:
	std::set<spk::SafePointer<Actor>> _bindedActors;

public:
	Chunk();

	void serialize(spk::Message& p_message) const override;
	void deserialize(spk::Message& p_message) override;

	void bindActor(spk::SafePointer<Actor> p_actor);
	void unbindActor(spk::SafePointer<Actor> p_actor);
};

class Tilemap : public spk::ITilemap<Chunk>
{
private:
	spk::Perlin _perlinGenerator;

	void _onChunkGeneration(const ChunkCoordinate& p_coordinates, spk::SafePointer<Chunk> p_chunk);

public:
	Tilemap();
};