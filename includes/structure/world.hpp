#pragma once

#include <sparkle.hpp>

#include "network/serializable_object.hpp"

struct Node
{
    enum class Flag : std::uint16_t
    {
        None         = 0,
        EastBlocked  = 1 << 0,
        WestBlocked  = 1 << 1,
        NorthBlocked = 1 << 2,
        SouthBlocked = 1 << 3,
        Obstacle     = EastBlocked | WestBlocked | NorthBlocked | SouthBlocked
    };

	using Flags = spk::Flags<Flag>;

    Flags flags;

	Node(Flags p_flags = Flag::None) :
		flags(p_flags)
	{

	}
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
	void deserialize(const spk::Message& p_message) override;
	static void skip(const spk::Message& p_message);

	void bindActor(spk::SafePointer<Actor> p_actor);
	void unbindActor(spk::SafePointer<Actor> p_actor);
	const std::set<spk::SafePointer<Actor>>& bindedActors() const;
};

class Tilemap : public spk::ITilemap<Chunk>
{
private:
	spk::Perlin _perlinGenerator;

	void _onChunkGeneration(const ChunkCoordinate& p_coordinates, spk::SafePointer<Chunk> p_chunk);

public:
	Tilemap();
};