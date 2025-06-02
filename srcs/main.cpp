#include <sparkle.hpp>

#include "main_widget.hpp"

int main()
{
	spk::ConsoleApplication app(L"TAAG server application");

	MainWidget mainWidget(L"MainWidget", app.centralWidget());
	mainWidget.activate();

	return (app.run());
}