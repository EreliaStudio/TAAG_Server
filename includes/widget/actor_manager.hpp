#pragma once

#include <sparkle.hpp>

class ActorManager : public spk::Widget
{
private:
	spk::Timer _pushActorTimer = spk::Timer(5_ms);

	void _parseActorRequest(const spk::Server::ClientID& p_clientID, const spk::Message& p_message);
	void _pushActorList();

	void _onUpdateEvent(spk::UpdateEvent& p_event) override;

public:
	ActorManager(const std::wstring& p_name, spk::SafePointer<spk::Widget> p_parent);
};