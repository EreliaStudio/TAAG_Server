#include "actor.hpp"

void Actor::serialize(spk::Message& p_message) const
{

	p_message << actor->position();
	p_message << actor->rotation();
	p_message << actor->scale();
}

void Actor::deserialize(spk::Message& p_message)
{
	
}