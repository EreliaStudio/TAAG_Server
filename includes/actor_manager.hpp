#pragma once

#include <sparkle.hpp>

class ActorManager : public spk::Widget
{
private:
	void _parseActorRequest(const spk::Server::ClientID& p_clientID, const spk::Message& p_message);
	void _assignPlayerID(const spk::Server::ClientID& p_clientID);
	void _unassignPlayerID(const spk::Server::ClientID& p_clientID);

	void _pushActorList();

public:
	ActorManager(const std::wstring& p_name, spk::SafePointer<spk::Widget> p_parent);
};