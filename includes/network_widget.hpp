#pragma once

#include <sparkle.hpp>

#include "network_override.hpp"

#include "context.hpp"

class ServerWidget : public spk::Widget
{
private:
	Context::Instanciator _contextInstanciator;

	void _onUpdateEvent(spk::UpdateEvent& p_event) override;

public:
	ServerWidget(const std::wstring& p_name, spk::SafePointer<spk::Widget> p_parent);
	~ServerWidget();
};