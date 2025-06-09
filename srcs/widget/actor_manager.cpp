#include "widget/actor_manager.hpp"

#include "structure/context.hpp"

void ActorManager::_parseActorRequest(const spk::Server::ClientID& p_clientID, const spk::Message& p_message)
{
	spk::Message awnser = spk::Message(static_cast<int>(MessageType::ActorData));

	while (p_message.empty() == false)
	{
		ActorMap::ActorID actorID = p_message.get<ActorMap::ActorID>();

		if (Context::instance()->actorMap.contains(actorID))
		{
			spk::SafePointer<Actor> actor = Context::instance()->actorMap.actor(actorID);
			
			awnser << actorID;
			
			actor->serialize(awnser);
		}
	}

	Context::instance()->server.sendTo(p_clientID, awnser);
}

void ActorManager::_pushActorList()
{
	spk::Message message(static_cast<spk::Message::Header::Type>(MessageType::ActorList));

	for (const auto& [actorID, actor] : Context::instance()->actorMap.actors())
	{
		message << actorID;

		actor->serialize(message);
	}

	Context::instance()->server.sendToAll(message);
}

void ActorManager::_onUpdateEvent(spk::UpdateEvent& p_event)
{
	if (p_event.deltaTime.milliseconds == 0)
	{
		return ;
	}

	for (const auto& [actorID, actor] : Context::instance()->actorMap.actors())
	{
		actor->update(p_event.deltaTime.milliseconds);
	}

	if (_pushActorTimer.state() != spk::Timer::State::Running)
	{
		_pushActorList();
		
		_pushActorTimer.start();
	}
}

ActorManager::ActorManager(const std::wstring& p_name, spk::SafePointer<spk::Widget> p_parent) :
	spk::Widget(p_name, p_parent)
{
	Context::instance()->server.subscribe(MessageType::ActorRequest, [this](const spk::Server::ClientID& p_clientID, const spk::Message& p_message) {
		_parseActorRequest(p_clientID, p_message);
	}).relinquish();
}