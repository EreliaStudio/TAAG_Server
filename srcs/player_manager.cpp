#include "player_manager.hpp"

#include "context.hpp"

void PlayerManager::_assignPlayerID(const spk::Server::ClientID& p_clientID)
{

}

void PlayerManager::_unassignPlayerID(const spk::Server::ClientID& p_clientID)
{
	
}

PlayerManager::PlayerManager(const std::wstring& p_name, spk::SafePointer<spk::Widget> p_parent) :
	spk::Widget(p_name, p_parent)
{
	Context::instance()->server.subscribe(MessageType::ActorRequest, [this](const spk::Server::ClientID& p_clientID, const spk::Message& p_message) {
		_parseActorRequest(p_clientID, p_message);
	}).relinquish();

	Context::instance()->server.addOnConnectionCallback([this](spk::Server::ClientID p_clientID) {
		_assignPlayerID(p_clientID);
	}).relinquish();

	Context::instance()->server.addOnDisconnectionCallback([this](spk::Server::ClientID p_clientID) {
		_unassignPlayerID(p_clientID);
	}).relinquish();
}