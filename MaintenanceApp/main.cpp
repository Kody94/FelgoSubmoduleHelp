
#include <QApplication>
#include <FelgoApplication>

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "CEosSerialMonitor.h"
#include <FelgoLiveClient>


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	FelgoApplication felgo;
	QQmlApplicationEngine engine;
	felgo.initialize(&engine);
	felgo.setLicenseKey(PRODUCT_LICENSE_KEY);
	qmlRegisterType<CEosSerialMonitor>("com.fawkesengineering.MaintenanceApp", 1, 0, "SerialMonitor");

	// use this instead of the above call to avoid deployment of the qml files and compile them into the binary with qt's resource system qrc
	// this is the preferred deployment option for publishing games to the app stores, because then your qml files and js files are protected
	// to avoid deployment of your qml files and images, also comment the DEPLOYMENTFOLDERS command in the .pro file
	// also see the .pro file for more details

	// felgo.setMainQmlFileName(QStringLiteral("qrc:/qml/Main.qml"));
	// engine.load(QUrl(felgo.mainQmlFileName()));

	FelgoLiveClient liveClient (&engine);

	return app.exec();
}
