#pragma once

#include <sparkle.hpp>

enum class MessageType
{
	ChunkRequest = 0,
	ChunkData = 1,
	ActorRequest = 2,
	ActorData = 3,
	ActorList = 4,
	PlayerIDAssignation = 5
};

std::string toString(MessageType p_type);
std::wstring toWString(MessageType p_type);

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