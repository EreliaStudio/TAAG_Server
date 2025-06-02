#include "network/network_override.hpp"

std::string toString(MessageType p_type)
{
    switch (p_type)
    {
        case MessageType::ChunkRequest:        return "ChunkRequest";
        case MessageType::ChunkData:           return "ChunkData";
        case MessageType::ActorRequest:        return "ActorRequest";
        case MessageType::ActorData:           return "ActorData";
        case MessageType::ActorList:           return "ActorList";
        case MessageType::PlayerIDAssignation: return "PlayerIDAssignation";
        default:                               return "Unknown";
    }
}

std::wstring toWString(MessageType p_type)
{
    switch (p_type)
    {
        case MessageType::ChunkRequest:        return L"ChunkRequest";
        case MessageType::ChunkData:           return L"ChunkData";
        case MessageType::ActorRequest:        return L"ActorRequest";
        case MessageType::ActorData:           return L"ActorData";
        case MessageType::ActorList:           return L"ActorList";
        case MessageType::PlayerIDAssignation: return L"PlayerIDAssignation";
        default:                               return L"Unknown";
    }
}

Server::Server() : spk::Server()
{

}

Server::Contract Server::subscribe(MessageType p_type, const Job& p_job)
{
	return _messageHandlers[p_type].subscribe(p_job);
}

void Server::update()
{
	while (messages().empty() == false)
	{
		spk::Server::MessageObject message = messages().pop();

		auto it = _messageHandlers.find(static_cast<MessageType>(message->header().type));
		if (it != _messageHandlers.end())
		{
			it->second.trigger(message->header().emitterID, *message);
		}
		else
		{
			spk::cout << L"Unhandled message type: " << toWString(static_cast<MessageType>(message->header().type)) << std::endl;
		}
	}
}