//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: Updater.cpp
 * Author: Florian Baader
 * Contact: flobaader@web.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Updater.h"
#include "standbye_main.h"

using namespace StandBye;

Updater::Updater()
{
	NEW_VERSION_STRING = getNewestVersionString();
	NEW_VERSION = cleanVersionString(NEW_VERSION_STRING);
}

int StandBye::Updater::cleanVersionString(System::String^ version_string)
{
	String^ version;
	version = version_string->Trim();
	version = version->Replace("v", "");
	version = version->Replace(".", "");
	try {
		LOG("Got '" + version + "' as version number from '" + version_string + "'");
		return System::Convert::ToInt32(version);
	}
	catch (System::Exception^) {
		LOG("Could not convert '" + version_string + "' to int");
		return 0;
	}
}

System::String ^ StandBye::Updater::getNewestVersionString()
{
	using namespace System::Net;
	System::String^ filePath = System::IO::Path::Combine(BasicFunc::getStandByeAppDataFolderPath(), "version.txt");

	//Downloads File
	WebClient^ webClient = gcnew WebClient();
	try {
		webClient->DownloadFile(gcnew Uri(VERSION_LINK), filePath);

		//Reads File (vX.X.X)
		System::String^ version = System::IO::File::ReadAllText(filePath);

		version = version->Trim();

		//Deletes File
		System::IO::File::Delete(filePath);

		LOG("Got '" + version + "' as versionString from " + VERSION_LINK);

		return version;
	}
	catch (Exception^ e) {
		LOG("Could not download version!");
		LOG(e->Message);
		return "v.0.0.0";
	}
}

int StandBye::Updater::getNewestVersion()
{
	//Converts version to int
	int newest_version = cleanVersionString(getNewestVersionString());

	return newest_version;
}

bool Updater::IsUpdateAvailable()
{
	//Gets current version
	int current_version = cleanVersionString(gcnew System::String(APP_VERSION));

	bool result = (NEW_VERSION > current_version);

	LOG("New Version is available == [" + Convert::ToString(result) + "] ");

	//Compares results
	return result;
}

void StandBye::Updater::UpdateApplication(mainApplication ^ parent)
{
	if (NEW_VERSION_STRING == "") {
		LOG("Tried to update, but no version number was available!");
		return;
	}

	//inserts new version
	String^ downloadLink = String::Format(gcnew String(RELEASE_LINK), NEW_VERSION_STRING);
	LOG("Downloading File from " + downloadLink);
	String^ targetFile = System::IO::Path::Combine(BasicFunc::getStandByeAppDataFolderPath(), "installer.msi");
	LOG("Saving File to " + targetFile);

	//Shows Dialog
	DownloadDialog^ downloadDialog = gcnew DownloadDialog(downloadLink, targetFile);

	LOG("Starting DownloadDialog");
	//Starts Downloading
	if (downloadDialog->ShowDialog() == Windows::Forms::DialogResult::OK) {
		//Quits application
		LOG("Download succeeded");
		LOG("Closing Application");
		parent->Quit(nullptr, nullptr);
	}
	else {
		LOG("Download did not succeed or was canceled!");
	}
}

System::Void StandBye::DownloadDialog::DownloadDialog_Load(System::Object ^, System::EventArgs ^)
{
	using namespace System::Net;

	downloadClient = gcnew WebClient();
	downloadClient->DownloadFileCompleted += gcnew System::ComponentModel::AsyncCompletedEventHandler(this, &StandBye::DownloadDialog::OnDownloadFileCompleted);
	downloadClient->DownloadProgressChanged += gcnew System::Net::DownloadProgressChangedEventHandler(this, &StandBye::DownloadDialog::OnDownloadProgressChanged);
	downloadClient->DownloadFileAsync(gcnew Uri(link), filePath);
}

System::Void StandBye::DownloadDialog::button1_Click(System::Object ^, System::EventArgs ^)
{
	downloadClient->CancelAsync();
	this->DialogResult = Windows::Forms::DialogResult::Cancel;
	this->Close();
}

void StandBye::DownloadDialog::OnDownloadFileCompleted(System::Object ^, System::ComponentModel::AsyncCompletedEventArgs ^)
{
	using namespace System::Diagnostics;

	if (completed) {
		// Prepare the process to run
		ProcessStartInfo^ start = gcnew ProcessStartInfo();
		// Enter the executable to run, including the complete path
		start->FileName = filePath;
		LOG("Download completed... starting installer");

		//Starts Installer
		Process::Start(start);

		this->DialogResult = Windows::Forms::DialogResult::OK;
		this->Close();
	}
}

void StandBye::DownloadDialog::OnDownloadProgressChanged(System::Object ^, System::Net::DownloadProgressChangedEventArgs ^ e)
{
	labelBytes->Text = String::Format("{0:0.00} MByte / {1:0.00} MByte", (double)e->BytesReceived / 1000000, (double)e->TotalBytesToReceive / 1000000);
	progressBar1->Value = e->ProgressPercentage;
	this->Text = String::Format("Downloading...{0}%", e->ProgressPercentage);

	if (e->ProgressPercentage == 100) {
		completed = true;
	}
}