#pragma once
#include "HotKeyMessageFilter.h"
#include "mainApplication.h"

//Constructor for MessageFilter that receives hotkey message
//Needs app reference to toggle presentation mode
HotKeyMessageFilter::HotKeyMessageFilter(mainApplication^ app) {
	application = app;
}

//Method that receives the hokey message and toggles presentation mode
bool HotKeyMessageFilter::PreFilterMessage(System::Windows::Forms::Message %m) {
	//check if the message is the hokey message
	if (m.Msg == WM_HOTKEY) {
		LOG("Processing Message" + m.ToString());

		//Toggle presentation mode
		application->setPresentationMode(!(application->isInPresentationMode()));

		return true;
	}

	return false;
}