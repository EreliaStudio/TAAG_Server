#pragma once

#include <sparkle.hpp>

class WorldManager : public spk::Widget
{
private:
	void _sendChunk(const spk::Server::ClientID& p_clientID, const spk::Message& p_message);

	void _loadNodeMap();

public:
	WorldManager(const std::wstring& p_name, spk::SafePointer<spk::Widget> p_parent);
};