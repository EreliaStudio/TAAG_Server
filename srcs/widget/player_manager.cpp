#include "widget/player_manager.hpp"

#include "structure/context.hpp"

void PlayerManager::_assignPlayerID(const spk::Server::ClientID& p_clientID)
{

	std::unique_ptr<Actor> newActor = std::make_unique<Actor>();

	newActor->setPosition(spk::Vector2(0, 0)); // Set initial position
	newActor->setRotation(0.0f); // Set initial rotation
	newActor->setScale(spk::Vector2(1, 1)); // Set initial scale

	ActorMap::ActorID playerID = Context::instance()->actorMap.addActor(std::move(newActor));

	spk::cout << "Assigning player ID for client: " << p_clientID << " -> " << playerID << std::endl;

	spk::Message message = spk::Message(static_cast<spk::Message::Header::Type>(MessageType::PlayerIDAssignation));

	message << playerID;

	Context::instance()->server.sendTo(p_clientID, message);
}

void PlayerManager::_unassignPlayerID(const spk::Server::ClientID& p_clientID)
{
	
}

PlayerManager::PlayerManager(const std::wstring& p_name, spk::SafePointer<spk::Widget> p_parent) :
	spk::Widget(p_name, p_parent)
{
	Context::instance()->server.addOnConnectionCallback([this](spk::Server::ClientID p_clientID) {
		_assignPlayerID(p_clientID);
	}).relinquish();

	Context::instance()->server.addOnDisconnectionCallback([this](spk::Server::ClientID p_clientID) {
		_unassignPlayerID(p_clientID);
	}).relinquish();
}