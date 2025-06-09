#pragma once

#include <sparkle.hpp>

#include "structure/actor_map.hpp"

class PlayerManager : public spk::Widget
{
private:
	std::unordered_map<spk::Server::ClientID, ActorMap::ActorID> _clientIDToActorID;

	void _assignPlayerID(const spk::Server::ClientID& p_clientID);
	void _unassignPlayerID(const spk::Server::ClientID& p_clientID);

	void _treatPlayerMotionRequest(const spk::Server::ClientID& p_clientID, const spk::Message& p_msg);
	void _treatPlayerRotationRequest(const spk::Server::ClientID& p_clientID, const spk::Message& p_msg);

public:
	PlayerManager(const std::wstring& p_name, spk::SafePointer<spk::Widget> p_parent);
};