#pragma once

#include <sparkle.hpp>

class PlayerManager : public spk::Widget
{
private:
	void _assignPlayerID(const spk::Server::ClientID& p_clientID);
	void _unassignPlayerID(const spk::Server::ClientID& p_clientID);

public:
	PlayerManager(const std::wstring& p_name, spk::SafePointer<spk::Widget> p_parent);
};