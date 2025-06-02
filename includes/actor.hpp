#pragma once

#include <sparkle.hpp>

#include "world.hpp"

#include "serializable_object.hpp"

class Actor : public SerializableObject
{
private:
	spk::Vector2 position;
	float rotation;
	spk::Vector2 scale;

	spk::SafePointer<Chunk> _bindedChunk;

public:
	void setPosition(const spk::Vector2& p_position) { position = p_position; }
	spk::Vector2 position() const { return position; }
	void setRotation(float p_rotation) { rotation = p_rotation; }
	float rotation() const { return rotation; }
	void setScale(const spk::Vector2& p_scale) { scale = p_scale; }
	spk::Vector2 scale() const { return scale; }

	void serialize(spk::Message& p_message) const override;
	void deserialize(spk::Message& p_message) override;

	spk::SafePointer<Chunk> bindedChunk() const { return _bindedChunk; }
	void setBindedChunk(spk::SafePointer<Chunk> p_chunk) { _bindedChunk = p_chunk; }
};