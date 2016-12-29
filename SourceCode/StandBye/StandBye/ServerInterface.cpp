#include "ServerInterface.h"

using System::Net::WebClient;
using System::Uri;
using System::String;

void ServerInterface::sendDataToServer(String ^ Data)
{
	//Escapes Data
	Data = Uri::EscapeDataString(Data);

	//Builds URL
	Uri^ url = gcnew Uri(reportURL + Data);

	//Opens Site
	WebClient^ web = gcnew WebClient();
	web->OpenReadAsync(url);
}

void ServerInterface::reportVersion()
{
	String^ version = System::Convert::ToString(APP_VERSION);
	String^ data = String::Format("version={0}", version);
	sendDataToServer(data);
}

void ServerInterface::reportInstance()
{
	String^ data = "count=1";
	sendDataToServer(data);
}

void ServerInterface::reportError(System::String^ error, System::String^ log)
{
	String^ data = String::Format("error={0}&log={1}", error, log);
	sendDataToServer(data);
}

void ServerInterface::reportUsageTime(System::TimeSpan ^ time)
{
	double minutes = time->TotalMinutes;
	String^ data = String::Format("usageTime={0}", System::Convert::ToString(minutes));
	sendDataToServer(data);
}