//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: Updater.h
 * Author: Florian Baader
 * Contact: flobaader@web.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "stdafx.h"
#include "MessageWindow.h"

ref class mainApplication;

namespace StandBye {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	///	A dialogForm to show the download progress
	/// </summary>
	public ref class DownloadDialog : public System::Windows::Forms::Form
	{
	private:
		String^ link;
		String^ filePath;
		bool completed = false;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
			 Net::WebClient^ downloadClient;

	public:
		DownloadDialog(System::String^ downloadPath, System::String^ target)
		{
			link = downloadPath;
			filePath = target;
			InitializeComponent();
		}

	protected:
		~DownloadDialog()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::ComponentModel::Container ^components;
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::Button^  buttonCancel;
	private: System::Windows::Forms::Label^  labelBytes;

#pragma region Windows Form Designer generated code

			 void InitializeComponent(void)
			 {
				 this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
				 this->buttonCancel = (gcnew System::Windows::Forms::Button());
				 this->labelBytes = (gcnew System::Windows::Forms::Label());
				 this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->tableLayoutPanel1->SuspendLayout();
				 this->SuspendLayout();
				 //
				 // progressBar1
				 //
				 this->progressBar1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->progressBar1->Location = System::Drawing::Point(3, 36);
				 this->progressBar1->Name = L"progressBar1";
				 this->progressBar1->Size = System::Drawing::Size(361, 27);
				 this->progressBar1->TabIndex = 0;
				 //
				 // buttonCancel
				 //
				 this->buttonCancel->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->buttonCancel->Location = System::Drawing::Point(150, 69);
				 this->buttonCancel->Margin = System::Windows::Forms::Padding(150, 3, 150, 3);
				 this->buttonCancel->Name = L"buttonCancel";
				 this->buttonCancel->Size = System::Drawing::Size(67, 29);
				 this->buttonCancel->TabIndex = 1;
				 this->buttonCancel->Text = L"Cancel";
				 this->buttonCancel->UseVisualStyleBackColor = true;
				 this->buttonCancel->Click += gcnew System::EventHandler(this, &DownloadDialog::button1_Click);
				 //
				 // labelBytes
				 //
				 this->labelBytes->AutoSize = true;
				 this->labelBytes->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->labelBytes->Location = System::Drawing::Point(3, 0);
				 this->labelBytes->Name = L"labelBytes";
				 this->labelBytes->Size = System::Drawing::Size(361, 33);
				 this->labelBytes->TabIndex = 2;
				 this->labelBytes->Text = L"Please be patient...";
				 this->labelBytes->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 //
				 // tableLayoutPanel1
				 //
				 this->tableLayoutPanel1->ColumnCount = 1;
				 this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 100)));
				 this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
					 20)));
				 this->tableLayoutPanel1->Controls->Add(this->labelBytes, 0, 0);
				 this->tableLayoutPanel1->Controls->Add(this->buttonCancel, 0, 2);
				 this->tableLayoutPanel1->Controls->Add(this->progressBar1, 0, 1);
				 this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
				 this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
				 this->tableLayoutPanel1->RowCount = 3;
				 this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
				 this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
				 this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
				 this->tableLayoutPanel1->Size = System::Drawing::Size(367, 101);
				 this->tableLayoutPanel1->TabIndex = 3;
				 //
				 // DownloadDialog
				 //
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(367, 101);
				 this->ControlBox = false;
				 this->Controls->Add(this->tableLayoutPanel1);
				 this->DoubleBuffered = true;
				 this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
				 this->MaximizeBox = false;
				 this->MinimizeBox = false;
				 this->Name = L"DownloadDialog";
				 this->ShowIcon = false;
				 this->ShowInTaskbar = false;
				 this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
				 this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				 this->Text = L"Downloading...";
				 this->Load += gcnew System::EventHandler(this, &DownloadDialog::DownloadDialog_Load);
				 this->tableLayoutPanel1->ResumeLayout(false);
				 this->tableLayoutPanel1->PerformLayout();
				 this->ResumeLayout(false);
			 }
#pragma endregion
	private: System::Void DownloadDialog_Load(System::Object^  sender, System::EventArgs^  e);

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
			 void OnDownloadFileCompleted(System::Object ^sender, System::ComponentModel::AsyncCompletedEventArgs ^e);
			 void OnDownloadProgressChanged(System::Object ^sender, System::Net::DownloadProgressChangedEventArgs ^e);
	};

	//To avoid cross linking

	ref class Updater
	{
	private:
		int cleanVersionString(System::String^ version);
		System::String^ getNewestVersionString();
		int getNewestVersion();

		int NEW_VERSION = 0;
		String^ NEW_VERSION_STRING = "";

	public:
		System::String^ RELEASE_LINK = "https://github.com/flobaader/Stand-Bye/releases/download/{0}/Install_Stand-Bye.msi";
		System::String^ VERSION_LINK = "https://raw.githubusercontent.com/flobaader/Stand-Bye/download/version.txt";

		Updater();
		bool IsUpdateAvailable();
		void UpdateApplication(mainApplication^ parent);
	};
}
