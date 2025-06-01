#include "network_override.hpp"

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
			spk::cout << L"Unhandled message type: " << static_cast<int>(message->header().type) << std::endl;
		}
	}
}