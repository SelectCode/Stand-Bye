//////////////////////////////////////////////////////////////////////////
/*!
 * STAND-BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de or https://github.com/flobaader/Stand-Bye
 * Author: Matthias Weirich
 * Contact: contact@stand-bye.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////

using System::Windows::Forms::Application;

#pragma once
#include "stdafx.h"

ref class mainApplication;

ref class HotKeyMessageFilter : public System::Windows::Forms::IMessageFilter {
public:
	HotKeyMessageFilter(mainApplication^ app);
	virtual bool PreFilterMessage(System::Windows::Forms::Message % m);

private:
	mainApplication^ application;
};
