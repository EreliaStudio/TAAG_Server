#include "widget/world_manager.hpp"

#include "structure/context.hpp"

void WorldManager::_sendChunk(const spk::Server::ClientID& p_clientID, const spk::Message& p_message)
{
	spk::Message awnser(static_cast<spk::Message::Header::Type>(MessageType::ChunkData));

	while (p_message.empty() == false)
	{
		spk::Vector2Int requestedChunkPosition = p_message.get<spk::Vector2Int>();

		awnser << requestedChunkPosition;

		Context::instance()->tilemap.requestChunk(requestedChunkPosition)->serialize(awnser);
	}

	Context::instance()->server.sendTo(p_clientID, awnser);
}

void WorldManager::_loadNodeMap()
{
	Context::instance()->nodeMap.addNode(0, Node(Node::Flag::None));
	Context::instance()->nodeMap.addNode(1, Node(Node::Flag::None));
}

WorldManager::WorldManager(const std::wstring& p_name, spk::SafePointer<spk::Widget> p_parent) :
	spk::Widget(p_name, p_parent)
{
	_loadNodeMap();

	Context::instance()->server.subscribe(MessageType::ChunkRequest, [this](const spk::Server::ClientID& p_clientID, const spk::Message& p_message) {
		_sendChunk(p_clientID, p_message);
	}).relinquish();
}