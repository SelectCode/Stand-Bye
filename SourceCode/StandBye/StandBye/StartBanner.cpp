#include "stdafx.h"
#include "StartBanner.h"

void StandBye::StartBanner::OnLoad(System::Object ^, System::EventArgs ^)
{
	metroLabelVersion->Text = (String^)APP_VERSION;
	if (SystemAccess::isPortable()) {
		metroLabelVersion->Text += " PORTABLE";
	}
	this->Update();
}