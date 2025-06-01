#pragma once

#include <sparkle.hpp>

#include "world.hpp"

class Actor
{
private:
	spk::SafePointer<Chunk> _bindedChunk;

public:
	spk::SafePointer<Chunk> bindedChunk() const { return _bindedChunk; }
	void setBindedChunk(spk::SafePointer<Chunk> p_chunk) { _bindedChunk = p_chunk; }
};