#pragma once

#include <sparkle.hpp>

#include "network_override.hpp"

class WorldManager : public spk::Widget
{
private:
	void _onUpdateEvent(spk::UpdateEvent& p_event) override;

	void _sendChunk(const Server::ClientID& p_clientID, const spk::Message& p_message);

	void _loadNodeMap();

public:
	WorldManager(const std::wstring& p_name, spk::SafePointer<spk::Widget> p_parent);
};