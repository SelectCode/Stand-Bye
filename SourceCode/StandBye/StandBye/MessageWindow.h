//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: MessageWindow.h
 * Author: Florian Baader
 * Contact: contact@stand-bye.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "stdafx.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Threading;
using System::Windows::Forms::MessageBoxButtons;
/// <summary>
/// Summary for TimeoutWindow
/// </summary>
namespace StandBye {
	public ref class MessageWindow : public MetroFramework::Forms::MetroForm
	{
	private:
		MessageBoxButtons buttons;

	public:
		MessageWindow(String^ text, MessageBoxButtons butt) {
			InitializeComponent();
			metroLabel1->Text = text;
			buttons = butt;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MessageWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::ComponentModel::IContainer^  components;
	private: MetroFramework::Controls::MetroButton^  metroButtonCancel;
	private: MetroFramework::Controls::MetroLabel^  metroLabel1;
	private: MetroFramework::Controls::MetroButton^  metroButtonOK;
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
			this->metroButtonCancel = (gcnew MetroFramework::Controls::MetroButton());
			this->metroButtonOK = (gcnew MetroFramework::Controls::MetroButton());
			this->metroLabel1 = (gcnew MetroFramework::Controls::MetroLabel());
			this->SuspendLayout();
			//
			// metroButtonCancel
			//
			this->metroButtonCancel->Location = System::Drawing::Point(167, 154);
			this->metroButtonCancel->Name = L"metroButtonCancel";
			this->metroButtonCancel->Size = System::Drawing::Size(92, 35);
			this->metroButtonCancel->TabIndex = 3;
			this->metroButtonCancel->Text = L"No";
			this->metroButtonCancel->UseSelectable = true;
			this->metroButtonCancel->Click += gcnew System::EventHandler(this, &MessageWindow::metroButtonCancel_Click);
			//
			// metroButtonOK
			//
			this->metroButtonOK->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->metroButtonOK->Location = System::Drawing::Point(276, 154);
			this->metroButtonOK->Name = L"metroButtonOK";
			this->metroButtonOK->Size = System::Drawing::Size(92, 35);
			this->metroButtonOK->TabIndex = 4;
			this->metroButtonOK->Text = L"Yes";
			this->metroButtonOK->UseSelectable = true;
			this->metroButtonOK->Click += gcnew System::EventHandler(this, &MessageWindow::metroButtonOK_Click);
			//
			// metroLabel1
			//
			this->metroLabel1->AutoSize = true;
			this->metroLabel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLabel1->FontSize = MetroFramework::MetroLabelSize::Tall;
			this->metroLabel1->Location = System::Drawing::Point(20, 60);
			this->metroLabel1->Name = L"metroLabel1";
			this->metroLabel1->Size = System::Drawing::Size(324, 75);
			this->metroLabel1->TabIndex = 6;
			this->metroLabel1->Text = L"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r"
				L"\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
			this->metroLabel1->WrapToLine = true;
			//
			// MessageWindow
			//
			this->AcceptButton = this->metroButtonOK;
			this->AeroWindowSnapActive = false;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->BackImagePadding = System::Windows::Forms::Padding(0, 10, 0, 0);
			this->BackMaxSize = 50;
			this->CancelButton = this->metroButtonOK;
			this->ClientSize = System::Drawing::Size(400, 200);
			this->ControlBox = false;
			this->Controls->Add(this->metroLabel1);
			this->Controls->Add(this->metroButtonOK);
			this->Controls->Add(this->metroButtonCancel);
			this->Location = System::Drawing::Point(100, 100);
			this->Name = L"MessageWindow";
			this->Resizable = false;
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Style = MetroFramework::MetroColorStyle::Green;
			this->Text = L"     Stand-Bye!";
			this->TopMost = true;
			this->Closing += gcnew System::ComponentModel::CancelEventHandler(this, &MessageWindow::OnClosing);
			this->Load += gcnew System::EventHandler(this, &MessageWindow::TimeoutWindow_Load);
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
	private: System::Void MessageWindow::TimeoutWindow_Load(System::Object^, System::EventArgs^);
	private: System::Void metroButtonOK_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void metroButtonCancel_Click(System::Object^  sender, System::EventArgs^  e);
			 void OnClosing(System::Object ^sender, System::ComponentModel::CancelEventArgs ^e);
	};
}
