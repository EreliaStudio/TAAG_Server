#include "world.hpp"

void Tilemap::_onChunkGeneration(const ChunkCoordinate& p_coordinates, spk::SafePointer<Chunk> p_chunk)
{
	for (size_t i = 0; i < Chunk::Size.x; i++)
	{
		for (size_t j = 0; j < Chunk::Size.y; j++)
		{
			for (size_t h = 0; h < Chunk::Size.z; h++)
			{
				if (h != 0)
				{
					continue;
				}

				char value = (i == 0 || j == 0 ? 'W' : ' ');

				p_chunk->setContent(i, j, h, value);
			}	
		}
	}
}

Tilemap::Tilemap() :
	spk::ITilemap<Chunk>()
{
	requestChunk({0, 0});
}