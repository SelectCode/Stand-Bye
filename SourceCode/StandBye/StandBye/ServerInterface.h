#pragma once

ref class ServerInterface
{
private:
	//Static URL to the report script
	static System::Uri^ reportURL = gcnew Uri("http://www.stand-bye.de/report.php");

public:
	
	//Reports the current Instance to the servers
	static void reportInstance();

	//Reports an error to the server
	static void reportError(System::String^ error, System::String^ log);
};

