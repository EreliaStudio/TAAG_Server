#include "actor_manager.hpp"

#include "context.hpp"

void ActorManager::_parseActorRequest(const spk::Server::ClientID& p_clientID, const spk::Message& p_message)
{

}

void ActorManager::_assignPlayerID(const spk::Server::ClientID& p_clientID)
{

}

void ActorManager::_unassignPlayerID(const spk::Server::ClientID& p_clientID)
{
	
}

void ActorManager::_pushActorList()
{

}

ActorManager::ActorManager(const std::wstring& p_name, spk::SafePointer<spk::Widget> p_parent) :
	spk::Widget(p_name, p_parent)
{
	Context::instance()->server.subscribe(MessageType::ActorRequest, [this](const spk::Server::ClientID& p_clientID, const spk::Message& p_message) {
		_parseActorRequest(p_clientID, p_message);
	}).relinquish();

	Context::instance()->server.addOnConnectionCallback([this](spk::Server::ClientID p_clientID) {
		_assignPlayerID(p_clientID);
	}).relinquish();

	Context::instance()->server.addOnDisconnectionCallback([this](spk::Server::ClientID p_clientID) {
		spk::cout << "Client ID [" << p_clientID << "] disconnected." << std::endl;
	}).relinquish();
}