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
#pragma once
#include "stdafx.h"
#include "SystemAccess.h"
#include "ProcessItem.h"

namespace StandBye {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für ProcessSelectionForm
	/// </summary>
	public ref class ProcessSelectionForm : public MetroFramework::Forms::MetroForm
	{
	public: String^ selectedProcessPath;
	public:
		ProcessSelectionForm()
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~ProcessSelectionForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: MetroFramework::Controls::MetroProgressSpinner^  metroProgressSpinner1;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::ListView^  listViewProc;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
	private: MetroFramework::Controls::MetroButton^  metroButtonOK;
	private: MetroFramework::Controls::MetroButton^  metroButtonCancel;
	private: MetroFramework::Components::MetroStyleExtender^  metroStyleExtender1;
	private: System::ComponentModel::IContainer^  components;
	protected:

	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->metroProgressSpinner1 = (gcnew MetroFramework::Controls::MetroProgressSpinner());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->listViewProc = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->metroButtonOK = (gcnew MetroFramework::Controls::MetroButton());
			this->metroButtonCancel = (gcnew MetroFramework::Controls::MetroButton());
			this->metroStyleExtender1 = (gcnew MetroFramework::Components::MetroStyleExtender(this->components));
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->SuspendLayout();
			//
			// metroProgressSpinner1
			//
			this->metroProgressSpinner1->Location = System::Drawing::Point(191, 114);
			this->metroProgressSpinner1->Maximum = 100;
			this->metroProgressSpinner1->Name = L"metroProgressSpinner1";
			this->metroProgressSpinner1->Size = System::Drawing::Size(100, 100);
			this->metroProgressSpinner1->Speed = 1.8F;
			this->metroProgressSpinner1->TabIndex = 0;
			//
			// tableLayoutPanel1
			//
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel1->Controls->Add(this->listViewProc, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 0, 1);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 60);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 80)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(511, 262);
			this->tableLayoutPanel1->TabIndex = 2;
			//
			// listViewProc
			//
			this->listViewProc->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {
				this->columnHeader1,
					this->columnHeader2
			});
			this->listViewProc->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listViewProc->FullRowSelect = true;
			this->listViewProc->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->listViewProc->Location = System::Drawing::Point(3, 3);
			this->listViewProc->Name = L"listViewProc";
			this->listViewProc->Size = System::Drawing::Size(505, 203);
			this->listViewProc->Sorting = System::Windows::Forms::SortOrder::Ascending;
			this->listViewProc->TabIndex = 0;
			this->listViewProc->UseCompatibleStateImageBehavior = false;
			this->listViewProc->View = System::Windows::Forms::View::Details;
			//
			// columnHeader1
			//
			this->columnHeader1->Text = L"Name";
			//
			// columnHeader2
			//
			this->columnHeader2->Text = L"Path";
			this->columnHeader2->Width = 216;
			//
			// tableLayoutPanel2
			//
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->Controls->Add(this->metroButtonOK, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->metroButtonCancel, 0, 0);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->Location = System::Drawing::Point(3, 212);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 1;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(505, 47);
			this->tableLayoutPanel2->TabIndex = 1;
			//
			// metroButtonOK
			//
			this->metroButtonOK->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroButtonOK->Location = System::Drawing::Point(260, 8);
			this->metroButtonOK->Margin = System::Windows::Forms::Padding(8);
			this->metroButtonOK->Name = L"metroButtonOK";
			this->metroButtonOK->Size = System::Drawing::Size(237, 31);
			this->metroButtonOK->TabIndex = 1;
			this->metroButtonOK->Text = L"OK";
			this->metroButtonOK->UseSelectable = true;
			this->metroButtonOK->Click += gcnew System::EventHandler(this, &ProcessSelectionForm::metroButtonOK_Click);
			//
			// metroButtonCancel
			//
			this->metroButtonCancel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroButtonCancel->Location = System::Drawing::Point(8, 8);
			this->metroButtonCancel->Margin = System::Windows::Forms::Padding(8);
			this->metroButtonCancel->Name = L"metroButtonCancel";
			this->metroButtonCancel->Size = System::Drawing::Size(236, 31);
			this->metroButtonCancel->TabIndex = 0;
			this->metroButtonCancel->Text = L"Cancel";
			this->metroButtonCancel->UseSelectable = true;
			this->metroButtonCancel->Click += gcnew System::EventHandler(this, &ProcessSelectionForm::metroButtonCancel_Click);
			//
			// ProcessSelectionForm
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(511, 322);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->metroProgressSpinner1);
			this->Name = L"ProcessSelectionForm";
			this->Padding = System::Windows::Forms::Padding(0, 60, 0, 0);
			this->ShowInTaskbar = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Show;
			this->Style = MetroFramework::MetroColorStyle::Green;
			this->Text = L"Select Process";
			this->Load += gcnew System::EventHandler(this, &ProcessSelectionForm::ProcessSelectionForm_Load);
			this->Shown += gcnew System::EventHandler(this, &ProcessSelectionForm::ProcessSelectioNForm_OnShown);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->ResumeLayout(false);
		}
#pragma endregion
	private:
		System::Void ProcessSelectionForm_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void ProcessSelectioNForm_OnShown(System::Object ^sender, System::EventArgs ^e);
		System::Void metroButtonOK_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void metroButtonCancel_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
