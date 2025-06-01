#include "world_manager.hpp"

#include "context.hpp"

void WorldManager::_onUpdateEvent(spk::UpdateEvent& p_event)
{
	// Handle update events for the world manager here
}

void WorldManager::_sendChunk(const Server::ClientID& p_clientID, const spk::Message& p_message)
{
	spk::Message awnser(static_cast<spk::Message::Header::Type>(MessageType::ChunkAwnser));

	while (p_message.empty() == false)
	{
		spk::SafePointer<Chunk> chunk = Context::instance()->tilemap.requestChunk(p_chunkPosition);

		awnser << chunk->contentArray();
	}

	Context::instance()->server.sendTo(p_clientID, awnser);
}

void WorldManager::_loadNodeMap()
{
	Context::instance()->nodeMap.addNode(' ', Node{ false }); // Add empty node
	Context::instance()->nodeMap.addNode('W', Node{ true }); // Add wall node
}

WorldManager::WorldManager(const std::wstring& p_name, spk::SafePointer<spk::Widget> p_parent) :
	spk::Widget(p_name, p_parent)
{
	Context::instance()->server.subscribe(MessageType::ChunkRequest, [this](const spk::Server::ClientID& p_clientID, const spk::Message& p_message) {
		_sendChunk(p_clientID, p_message);
	}).relinquish();
}