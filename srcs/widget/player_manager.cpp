#include "widget/player_manager.hpp"

#include "structure/context.hpp"

void PlayerManager::_assignPlayerID(const spk::Server::ClientID& p_clientID)
{
	std::unique_ptr<Actor> newActor = std::make_unique<Actor>();

	newActor->setPosition(spk::Vector2(0, 0));
	newActor->setRotation(0.0f);
	newActor->setScale(spk::Vector2(1, 1));
	newActor->setMoveSpeed(0.1);

	ActorMap::ActorID playerID = Context::instance()->actorMap.addActor(std::move(newActor));

	_clientIDToActorID[p_clientID] = playerID;

	spk::Message message = spk::Message(static_cast<spk::Message::Header::Type>(MessageType::PlayerIDAssignation));

	message << playerID;

	Context::instance()->server.sendTo(p_clientID, message);
}

void PlayerManager::_unassignPlayerID(const spk::Server::ClientID& p_clientID)
{
	ActorMap::ActorID playerID = _clientIDToActorID[p_clientID];

	Context::instance()->actorMap.removeActor(playerID);

	_clientIDToActorID.erase(p_clientID);

	spk::Message message = spk::Message(static_cast<spk::Message::Header::Type>(MessageType::ActorRemoval));

	message << playerID;

	Context::instance()->server.sendToAll(message);
}

void PlayerManager::_treatPlayerMotionRequest(const spk::Server::ClientID& p_clientID, const spk::Message& p_msg)
{
	spk::Vector2 requestedMotionDirection = p_msg.get<spk::Vector2>();

	spk::SafePointer<Actor> actorToMove = Context::instance()->actorMap.actor(_clientIDToActorID[p_clientID]);

	if (actorToMove->isMoving() == false)
	{
		actorToMove->move(requestedMotionDirection);
	}
}

void PlayerManager::_treatPlayerRotationRequest(const spk::Server::ClientID& p_clientID, const spk::Message& p_msg)
{
	float requestedRotation = p_msg.get<float>();

	spk::SafePointer<Actor> actorToMove = Context::instance()->actorMap.actor(_clientIDToActorID[p_clientID]);

	actorToMove->setRotation(requestedRotation);
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

	Context::instance()->server.subscribe(MessageType::PlayerMotionRequest, [this](const spk::Server::ClientID& p_clientID, const spk::Message& p_message) {
		_treatPlayerMotionRequest(p_clientID, p_message);
	}).relinquish();

	Context::instance()->server.subscribe(MessageType::PlayerRotationRequest, [this](const spk::Server::ClientID& p_clientID, const spk::Message& p_message) {
		_treatPlayerRotationRequest(p_clientID, p_message);
	}).relinquish();
}