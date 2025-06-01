#include "main_widget.hpp"

MainWidget::MainWidget(const std::wstring& p_name, spk::SafePointer<spk::Widget> p_parent) :
	spk::Widget(p_name, p_parent),
	_serverWidget(p_name + L"/ServerWidget", this),
	_actorManager(p_name + L"/ActorManager", this),
	_worldManager(p_name + L"/WorldManager", this)
{
	_worldManager.activate();
	_actorManager.activate();
	_serverWidget.activate();
}