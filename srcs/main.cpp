#include <sparkle.hpp>

#include "network_override.hpp"

#include "context.hpp"

#include "network_widget.hpp"

#include "main_widget.hpp"

int main()
{
	spk::ConsoleApplication app(L"TAAG server application");

	MainWidget mainWidget(L"MainWidget", app.centralWidget());
	mainWidget.activate();

	return (app.run());
}