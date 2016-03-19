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
	//Count errors
	int errors_occured = 0;
	mainApplication^ standbye;

	while (errors_occured < 3) {
		standbye = gcnew mainApplication(hInstance);

		if (standbye->hasUserExited()) {
			//Application should not restart if user ends it
			break;
		}
		else {
			errors_occured++;
		}
	}

	delete standbye;
	return 1;
}