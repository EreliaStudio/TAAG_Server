#include "structure/world.hpp"

void Tilemap::_onChunkGeneration(const ChunkCoordinate& p_coordinates, spk::SafePointer<Chunk> p_chunk)
{
	for (size_t i = 0; i < Chunk::Size.x; i++)
	{
		for (size_t j = 0; j < Chunk::Size.y; j++)
		{
			for (size_t h = 0; h < Chunk::Size.z; h++)
			{
				p_chunk->setContent(i, j, h, -1);

				if (i == 0 || j == 0)
				{
					p_chunk->setContent(i, j, h, 2);
				}
			}	
		}
	}
	
	p_chunk->setContent(3, 3, 1, 0);
	p_chunk->setContent(6, 6, 1, 1);
}

Tilemap::Tilemap() :
	spk::ITilemap<Chunk>()
{

}