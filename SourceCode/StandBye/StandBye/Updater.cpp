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
#include "stdafx.h"
#include "Updater.h"
#include "mainApplication.h"

using namespace StandBye;

Updater::Updater()
{
	downloadInformation();
	NEW_VERSION = cleanVersionString(NEW_VERSION_STRING);
}

int StandBye::Updater::cleanVersionString(System::String^ version_string)
{
	String^ version;
	version = version_string->Trim();
	version = version->Replace("v", "");
	version = version->Replace(".", "");
	LOG("Got '" + version + "' as version number from '" + version_string + "'");
	try {
		return System::Convert::ToInt32(version);
	}
	catch (System::Exception^) {
		LOG("Could not convert '" + version_string + "' to int");
		return 0;
	}
}

void StandBye::Updater::downloadInformation()
{
	using namespace System::Net;

	System::String^ filePath = System::IO::Path::Combine(SystemAccess::getStandByeFolderPath(), "version.txt");

	//Downloads File
	WebClient^ webClient = gcnew WebClient();
	try {
		webClient->DownloadFile(gcnew Uri(VERSION_FILE_PATH), filePath);

		//Reads File (vX.X.X)

		IO::StreamReader^ fileReader = IO::File::OpenText(filePath);

		try
		{
			//Reads first line
			NEW_VERSION_STRING = fileReader->ReadLine()->Trim();
		}
		catch (Exception^ e)
		{
			LOG("Could not get version string from version.txt");
			LOG(e);
		}

		try
		{
			//Reads second line
			DOWNLOAD_LINK = fileReader->ReadLine()->Trim();
		}
		catch (Exception^ e)
		{
			LOG("Could not get download string from version.txt");
			LOG(e);
		}

		//Closes FileStream
		fileReader->Close();

		//Deletes File
		System::IO::File::Delete(filePath);

		LOG("Got '" + NEW_VERSION_STRING + "' as versionString from " + VERSION_FILE_PATH);
		LOG("The Downloadlink is set to: '" + DOWNLOAD_LINK + "'");
	}
	catch (Exception^ e) {
		LOG("Could not download version.txt!");
		LOG(e);
	}
}

int StandBye::Updater::getNewestVersion()
{
	//Converts version to int
	int newest_version = cleanVersionString(NEW_VERSION_STRING);

	return newest_version;
}

bool Updater::IsUpdateAvailable()
{
	if (DOWNLOAD_LINK == "") {
		LOG("Did not ask to update because of link error!");
		return false;
	}
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
	String^ downloadLink = String::Format(gcnew String(DOWNLOAD_LINK), NEW_VERSION_STRING);
	LOG("Downloading File from " + downloadLink);
	String^ targetFile = System::IO::Path::Combine(SystemAccess::getStandByeFolderPath(), "installer.msi");
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

void StandBye::Updater::deleteInstallFile()
{
	using System::IO::File;
	String^ filepath = System::IO::Path::Combine(SystemAccess::getStandByeFolderPath(), "installer.msi");
	if (File::Exists(filepath)) {
		File::Delete(System::IO::Path::Combine(SystemAccess::getStandByeFolderPath(), "installer.msi"));
		LOG("Deleted old updater file");
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