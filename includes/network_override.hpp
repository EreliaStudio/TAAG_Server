#pragma once

#include <sparkle.hpp>

enum class MessageType
{
	ChunkRequest = 0,
	ChunkAwnser = 1,
	ChunkUpdate = 2,
	ActorRequest = 3,
	ActorAwnser = 4,
	ActorUpdate = 5,
	PlayerIDAssignation = 6
};

class Server : public spk::Server
{
private:
	using ContractProvider = spk::TContractProvider<const spk::Server::ClientID&, const spk::Message&>;
	using Contract = ContractProvider::Contract;
	using Job = ContractProvider::Job;

private:
	std::unordered_map<MessageType, ContractProvider> _messageHandlers;

public:
	Server();

	Contract subscribe(MessageType p_type, const Job& p_job);

	void update();
};