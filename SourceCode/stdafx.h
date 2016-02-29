//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: stdafx.h
 * Author: Florian Baader
 * Contact: flobaader@web.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#pragma once

//INCLUDES
#include <windows.h>
#include "BasicFunc.h"

//APP VALUES
#define APP_NAME "Stand-Bye!"
#define APP_VERSION "0.5.2"

//////////////////////////////////////////////////////////////////////////
///VERSION CHANGES HAVE TO BE MADE IN
///APP_VERSION
///SmartLogout.rc
///Installer
///MetroSettingsForm Label
//////////////////////////////////////////////////////////////////////////

//LOG SYSTEM
#define LOG(s) BasicFunc::Log(s)
