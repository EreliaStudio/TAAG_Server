#include "network_widget.hpp"

void ServerWidget::_onUpdateEvent(spk::UpdateEvent& p_event)
{
	Context::instance()->server.update();
}

ServerWidget::ServerWidget(const std::wstring& p_name, spk::SafePointer<spk::Widget> p_parent) :
	spk::Widget(p_name, p_parent)
{
	Context::instance()->server.start(26500);

	Context::instance()->server.addOnConnectionCallback([this](spk::Server::ClientID p_clientID) {
			spk::cout << "Client ID [" << p_clientID << "] connected." << std::endl;
		}
	).relinquish();
}

ServerWidget::~ServerWidget()
{
	Context::instance()->server.stop();
}