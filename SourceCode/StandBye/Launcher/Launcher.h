#pragma once

#include "resource.h"
#include <string>

std::wstring getExePath();

int showErrorMessage();

void tryToLaunch(std::wstring path);

BOOL launchMainExe(std::wstring path);