//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: stdafx.h
 * Author: Florian Baader
 * Contact: contact@stand-bye.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#pragma once

//INCLUDES
#include <windows.h>
#include "BasicFunc.h"

//APP VALUES
#define APP_NAME "Stand-Bye!"
#define APP_VERSION "0.5.7"
#define PORTABLE_VERSION false

//////////////////////////////////////////////////////////////////////////
///VERSION CHANGES HAVE TO BE MADE IN
///APP_VERSION
///StandBye.rc
///Installer
///MetroSettingsForm Label
//////////////////////////////////////////////////////////////////////////

//LOG SYSTEM
#define LOG(s) BasicFunc::Log(s)
