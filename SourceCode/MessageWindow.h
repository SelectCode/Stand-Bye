#pragma once
#include "stdafx.h"

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
	public ref class MessageWindow : public MetroFramework::Forms::MetroForm
	{
	private: MetroFramework::Controls::MetroButton^  metroButtonCancel;

	private: MetroFramework::Controls::MetroLabel^  metroLabel1;

	private: MetroFramework::Controls::MetroButton^  metroButtonOK;
	public:
		MessageWindow(String^ text) {
			InitializeComponent();
			metroLabel1->Text = text;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MessageWindow::typeid));
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
			this->metroLabel1->FontSize = MetroFramework::MetroLabelSize::Tall;
			this->metroLabel1->Location = System::Drawing::Point(39, 72);
			this->metroLabel1->Name = L"metroLabel1";
			this->metroLabel1->Size = System::Drawing::Size(103, 25);
			this->metroLabel1->TabIndex = 6;
			this->metroLabel1->Text = L"metroLabel1";
			this->metroLabel1->WrapToLine = true;
			//
			// MessageWindow
			//
			this->AeroWindowSnapActive = false;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->BackImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackImage")));
			this->BackImagePadding = System::Windows::Forms::Padding(0, 10, 0, 0);
			this->BackMaxSize = 50;
			this->ClientSize = System::Drawing::Size(400, 200);
			this->ControlBox = false;
			this->Controls->Add(this->metroLabel1);
			this->Controls->Add(this->metroButtonOK);
			this->Controls->Add(this->metroButtonCancel);
			this->Location = System::Drawing::Point(100, 100);
			this->Name = L"MessageWindow";
			this->Resizable = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Style = MetroFramework::MetroColorStyle::Green;
			this->Text = L"     Stand-Bye!";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &MessageWindow::TimeoutWindow_Load);
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
	private: System::Void MessageWindow::TimeoutWindow_Load(System::Object^, System::EventArgs^);
	private: System::Void metroButtonOK_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void metroButtonCancel_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
