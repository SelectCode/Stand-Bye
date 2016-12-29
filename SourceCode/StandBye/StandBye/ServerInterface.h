#pragma once
#include "stdafx.h"

ref class ServerInterface
{
private:
	//Static URL to the report script
	static System::Uri^ reportURL = gcnew System::Uri("http://www.stand-bye.de/report.php?");

	//Escapes the given data and sends it to the server (async)
	static void sendDataToServer(System::String^ Data);

public:

	//Reports the used version of Stand-Bye!
	static void reportVersion();

	//Reports the current Instance to the servers
	static void reportInstance();

	//Reports an error to the server
	static void reportError(System::String^ error, System::String^ log);

	//Reports the current Usage Time to the server
	static void reportUsageTime(System::TimeSpan^ time);
}
;
