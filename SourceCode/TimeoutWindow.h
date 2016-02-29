//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: TimeoutWindow.h
 * Author: Florian Baader
 * Contact: flobaader@web.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "stdafx.h"
#include <time.h>
#include "SettingsProvider.h"
#include "SystemAccess.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Threading;

/// <summary>
/// Summary for TimeoutWindow
/// </summary>
namespace StandBye {
	public ref class TimeoutWindow : public MetroFramework::Forms::MetroForm
	{
		int delay; // in milliseconds
		int startTime; //in milliseconds
		System::Windows::Forms::Timer^ timer;
		SettingsProvider* settings_provider;
		int counter;
	private: MetroFramework::Controls::MetroLabel^  metroLabel1;
	private: MetroFramework::Controls::MetroLabel^  metroLabelTime;
	private: MetroFramework::Controls::MetroProgressBar^  metroProgressBar1;
	private: MetroFramework::Controls::MetroButton^  metroButtonCancel;
	private: MetroFramework::Controls::MetroButton^  metroButtonOK;
	public:
		TimeoutWindow(const int duration, SettingsProvider* prov) {
			InitializeComponent();
			this->DoubleBuffered = true;
			delay = duration * 1000;
			startTime = Environment::TickCount;
			RefreshUI(gcnew Object, gcnew EventArgs);
			settings_provider = prov;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~TimeoutWindow()
		{
			if (components)
			{
				delete components;
			}
			delete timer, time, counter;
		}

	protected:

	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

#pragma region Windows Form Designer generated code
	/// <summary>
	/// Required method for Designer support - do not modify
	/// the contents of this method with the code editor.
	/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(TimeoutWindow::typeid));
			this->metroLabel1 = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroLabelTime = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroProgressBar1 = (gcnew MetroFramework::Controls::MetroProgressBar());
			this->metroButtonCancel = (gcnew MetroFramework::Controls::MetroButton());
			this->metroButtonOK = (gcnew MetroFramework::Controls::MetroButton());
			this->SuspendLayout();
			//
			// metroLabel1
			//
			this->metroLabel1->AutoSize = true;
			this->metroLabel1->FontSize = MetroFramework::MetroLabelSize::Tall;
			this->metroLabel1->Location = System::Drawing::Point(84, 75);
			this->metroLabel1->Name = L"metroLabel1";
			this->metroLabel1->Size = System::Drawing::Size(164, 25);
			this->metroLabel1->TabIndex = 0;
			this->metroLabel1->Text = L"Entering Standby in:";
			//
			// metroLabelTime
			//
			this->metroLabelTime->AutoSize = true;
			this->metroLabelTime->FontSize = MetroFramework::MetroLabelSize::Tall;
			this->metroLabelTime->FontWeight = MetroFramework::MetroLabelWeight::Regular;
			this->metroLabelTime->Location = System::Drawing::Point(254, 75);
			this->metroLabelTime->Name = L"metroLabelTime";
			this->metroLabelTime->Size = System::Drawing::Size(54, 25);
			this->metroLabelTime->TabIndex = 1;
			this->metroLabelTime->Text = L"0.00s";
			//
			// metroProgressBar1
			//
			this->metroProgressBar1->Location = System::Drawing::Point(84, 115);
			this->metroProgressBar1->Name = L"metroProgressBar1";
			this->metroProgressBar1->Size = System::Drawing::Size(246, 23);
			this->metroProgressBar1->Style = MetroFramework::MetroColorStyle::Green;
			this->metroProgressBar1->TabIndex = 2;
			//
			// metroButtonCancel
			//
			this->metroButtonCancel->Location = System::Drawing::Point(167, 154);
			this->metroButtonCancel->Name = L"metroButtonCancel";
			this->metroButtonCancel->Size = System::Drawing::Size(92, 35);
			this->metroButtonCancel->TabIndex = 3;
			this->metroButtonCancel->Text = L"Cancel";
			this->metroButtonCancel->UseSelectable = true;
			this->metroButtonCancel->Click += gcnew System::EventHandler(this, &TimeoutWindow::metroButtonCancel_Click);
			//
			// metroButtonOK
			//
			this->metroButtonOK->Location = System::Drawing::Point(276, 154);
			this->metroButtonOK->Name = L"metroButtonOK";
			this->metroButtonOK->Size = System::Drawing::Size(92, 35);
			this->metroButtonOK->TabIndex = 4;
			this->metroButtonOK->Text = L"OK";
			this->metroButtonOK->UseSelectable = true;
			this->metroButtonOK->Click += gcnew System::EventHandler(this, &TimeoutWindow::metroButtonOK_Click);
			//
			// TimeoutWindow
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->BackImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackImage")));
			this->BackImagePadding = System::Windows::Forms::Padding(0, 10, 0, 0);
			this->BackMaxSize = 50;
			this->ClientSize = System::Drawing::Size(400, 200);
			this->ControlBox = false;
			this->Controls->Add(this->metroButtonOK);
			this->Controls->Add(this->metroButtonCancel);
			this->Controls->Add(this->metroProgressBar1);
			this->Controls->Add(this->metroLabelTime);
			this->Controls->Add(this->metroLabel1);
			this->Location = System::Drawing::Point(100, 100);
			this->Name = L"TimeoutWindow";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Style = MetroFramework::MetroColorStyle::Green;
			this->Text = L"     Stand-Bye!";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &TimeoutWindow::TimeoutWindow_Load);
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
	private:
		System::Void TimeoutWindow_Load(System::Object^, System::EventArgs^);
		System::Void RefreshUI(System::Object^, System::EventArgs^);
		System::Void metroButtonOK_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void metroButtonCancel_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
