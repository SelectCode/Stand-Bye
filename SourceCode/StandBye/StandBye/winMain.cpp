//////////////////////////////////////////////////////////////////////////
/*!
 * STAND-BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de or https://github.com/flobaader/Stand-Bye
 * Author: Florian Baader
 * Contact: contact@stand-bye.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#include "winMain.h"
#include "mainApplication.h"

[STAThread] //Because of FileDialog --> Application is single threaded - Windows needs that
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ PWSTR, _In_ int) {
	//Application
	mainApplication^ standbye;
	InstanceMonitor^ instance_monitor;

	//Count errors
	int errors_occured = 0;

	while (errors_occured < 3) {
		//Creates application
		try {
			standbye = gcnew mainApplication(hInstance);

			instance_monitor = gcnew InstanceMonitor(standbye);
			//If another instance is running --> exit
			if (instance_monitor->isAnotherInstanceRunning()) {
				LOG("Application quits because of other instance");
				break;
			}
			else {
				//No other instance is running
				standbye->Start(); //Synchronous
			}
		}
		catch (Exception^ e) {
			//Catching Exception
			LOG(e);
			System::Windows::Forms::MessageBox::Show("Exception occurred: " + e->Message, "Exception occurred!", System::Windows::Forms::MessageBoxButtons::OK);
			errors_occured++;
		}

		if (standbye->hasUserExited()) {
			//Application should not restart if user ends it
			break;
		}
		else {
			errors_occured++;
		}
	}
	delete instance_monitor;
	delete standbye;
	return 1;
}