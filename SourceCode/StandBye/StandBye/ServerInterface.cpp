#include "ServerInterface.h"

using System::Net::WebClient;
using System::Uri;
using System::String;


void ServerInterface::reportInstance()
{
	//Joins Data
	String^ data = String::Format("?count={0}", 1);

	//Builds URL
	Uri^ url = gcnew Uri(reportURL + data);

	//Opens Site
	WebClient^ web = gcnew WebClient();
	web->OpenReadAsync(url);
}

void ServerInterface::reportError(System::String^ error, System::String^ log)
{
	//Joins and escapes data
	String^ data = String::Format("?error={0}&log={1}", error, log);
	data = Uri::EscapeDataString(data);
	Uri^ url = gcnew Uri(reportURL + data);

	//Opens Website
	WebClient^ wb = gcnew WebClient();
	wb->OpenReadAsync(url);
}







