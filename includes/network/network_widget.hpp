#pragma once

#include <sparkle.hpp>

#include "structure/context.hpp"

#include "network/network_override.hpp"

class ServerWidget : public spk::Widget
{
private:
	Context::Instanciator _contextInstanciator;

	void _onUpdateEvent(spk::UpdateEvent& p_event) override;

public:
	ServerWidget(const std::wstring& p_name, spk::SafePointer<spk::Widget> p_parent);
	~ServerWidget();
};