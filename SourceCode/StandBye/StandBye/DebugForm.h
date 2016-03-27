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
#include "mainApplication.h"

namespace StandBye {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace Resources;

	/// <summary>
	/// Form to present debug information
	/// </summary>
	public ref class DebugForm : public System::Windows::Forms::Form
	{
		//attributes
		SystemMetricWatcher^ system_watcher;
		InputMonitor^ input_monitor;
		SettingsProvider* settings_prov;
		mainApplication^ parent;
		SystemAccess^ system_access;

	public:
		DebugForm(mainApplication^ sender, SettingsProvider* set_prov,InputMonitor^ mon)
		{
			parent = sender;
			settings_prov = set_prov;
			input_monitor = mon;
			this->system_access = gcnew SystemAccess(settings_prov);
			this->system_watcher = gcnew SystemMetricWatcher(system_access, 10, 3);

			//Initialize Components
			InitializeComponent();

			//Resource
			ResourceManager^ res_man = gcnew ResourceManager("StandBye.ImageResources.Data", GetType()->Assembly);
			this->Icon = (System::Drawing::Icon^) res_man->GetObject("icon1");

			//Starts Timer
			timerRefresh->Tick += gcnew System::EventHandler(this, &StandBye::DebugForm::OnTick);
			timerRefresh->Interval = 100;
			timerRefresh->Start();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DebugForm()
		{
			if (components)
			{
				delete components;
			}
			delete system_watcher;
			delete system_access;
		}
	private: System::Windows::Forms::RichTextBox^  textBoxLog;
	private: System::Windows::Forms::GroupBox^  groupBox7;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel6;
	private: System::Windows::Forms::GroupBox^  groupBox8;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel7;
	private: System::Windows::Forms::Label^  labelSoundOverLimit;
	private: System::Windows::Forms::Label^  labelSoundPeak;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Button^  buttonMessageWnd;
	private: System::Windows::Forms::Button^  buttonProcessForm;
	private: System::Windows::Forms::Button^  buttonSettingsForm;
	private: System::Windows::Forms::Button^  buttonTimeWnd;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;
	private: System::Windows::Forms::ColumnHeader^  columnHeader3;
	private: System::Windows::Forms::ColumnHeader^  columnHeader4;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::GroupBox^  groupBox6;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  labelBuffCPU;
	private: System::Windows::Forms::Label^  labelBuffHDD;
	private: System::Windows::Forms::Label^  labelBuffNET;
	private: System::Windows::Forms::Label^  labelBuffRAM;
	private: System::Windows::Forms::Label^  labelInputTime;
	private: System::Windows::Forms::Label^  labelRTCPU;
	private: System::Windows::Forms::Label^  labelRTHDD;
	private: System::Windows::Forms::Label^  labelRTNET;
	private: System::Windows::Forms::Label^  labelRTRAM;
	private: System::Windows::Forms::Label^  labelWAITReached;
	private: System::Windows::Forms::ListView^  listViewProc;
	private: System::Windows::Forms::ListView^  listViewSettings;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel3;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel4;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel5;
	private: System::Windows::Forms::Timer^  timerRefresh;
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
			this->components = (gcnew System::ComponentModel::Container());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->labelRTNET = (gcnew System::Windows::Forms::Label());
			this->labelRTHDD = (gcnew System::Windows::Forms::Label());
			this->labelRTRAM = (gcnew System::Windows::Forms::Label());
			this->labelRTCPU = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->labelBuffNET = (gcnew System::Windows::Forms::Label());
			this->labelBuffHDD = (gcnew System::Windows::Forms::Label());
			this->labelBuffRAM = (gcnew System::Windows::Forms::Label());
			this->labelBuffCPU = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->listViewSettings = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->tableLayoutPanel6 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel7 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->labelSoundOverLimit = (gcnew System::Windows::Forms::Label());
			this->labelSoundPeak = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel5 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->labelWAITReached = (gcnew System::Windows::Forms::Label());
			this->labelInputTime = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->buttonTimeWnd = (gcnew System::Windows::Forms::Button());
			this->buttonMessageWnd = (gcnew System::Windows::Forms::Button());
			this->buttonProcessForm = (gcnew System::Windows::Forms::Button());
			this->buttonSettingsForm = (gcnew System::Windows::Forms::Button());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->listViewProc = (gcnew System::Windows::Forms::ListView());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->textBoxLog = (gcnew System::Windows::Forms::RichTextBox());
			this->timerRefresh = (gcnew System::Windows::Forms::Timer(this->components));
			this->tableLayoutPanel1->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tableLayoutPanel6->SuspendLayout();
			this->groupBox8->SuspendLayout();
			this->tableLayoutPanel7->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->tableLayoutPanel5->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->groupBox7->SuspendLayout();
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 5;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				20)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				20)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				20)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				20)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				20)));
			this->tableLayoutPanel1->Controls->Add(this->groupBox3, 2, 0);
			this->tableLayoutPanel1->Controls->Add(this->groupBox2, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->groupBox1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel6, 3, 0);
			this->tableLayoutPanel1->Controls->Add(this->groupBox6, 4, 0);
			this->tableLayoutPanel1->Controls->Add(this->groupBox5, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->groupBox7, 3, 1);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 37.5F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 62.5F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(998, 432);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->tableLayoutPanel3);
			this->groupBox3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox3->Location = System::Drawing::Point(401, 3);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(193, 156);
			this->groupBox3->TabIndex = 2;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Real-Time Usage";
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel3->ColumnCount = 2;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel3->Controls->Add(this->labelRTNET, 1, 4);
			this->tableLayoutPanel3->Controls->Add(this->labelRTHDD, 1, 3);
			this->tableLayoutPanel3->Controls->Add(this->labelRTRAM, 1, 2);
			this->tableLayoutPanel3->Controls->Add(this->labelRTCPU, 1, 1);
			this->tableLayoutPanel3->Controls->Add(this->label14, 0, 4);
			this->tableLayoutPanel3->Controls->Add(this->label15, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->label16, 0, 1);
			this->tableLayoutPanel3->Controls->Add(this->label17, 0, 2);
			this->tableLayoutPanel3->Controls->Add(this->label18, 0, 3);
			this->tableLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel3->Location = System::Drawing::Point(3, 16);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 5;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(187, 137);
			this->tableLayoutPanel3->TabIndex = 1;
			// 
			// labelRTNET
			// 
			this->labelRTNET->AutoSize = true;
			this->labelRTNET->Dock = System::Windows::Forms::DockStyle::Fill;
			this->labelRTNET->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelRTNET->Location = System::Drawing::Point(97, 109);
			this->labelRTNET->Name = L"labelRTNET";
			this->labelRTNET->Size = System::Drawing::Size(86, 27);
			this->labelRTNET->TabIndex = 8;
			this->labelRTNET->Text = L"0.0";
			this->labelRTNET->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelRTHDD
			// 
			this->labelRTHDD->AutoSize = true;
			this->labelRTHDD->Dock = System::Windows::Forms::DockStyle::Fill;
			this->labelRTHDD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelRTHDD->Location = System::Drawing::Point(97, 82);
			this->labelRTHDD->Name = L"labelRTHDD";
			this->labelRTHDD->Size = System::Drawing::Size(86, 26);
			this->labelRTHDD->TabIndex = 7;
			this->labelRTHDD->Text = L"0.0";
			this->labelRTHDD->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelRTRAM
			// 
			this->labelRTRAM->AutoSize = true;
			this->labelRTRAM->Dock = System::Windows::Forms::DockStyle::Fill;
			this->labelRTRAM->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelRTRAM->Location = System::Drawing::Point(97, 55);
			this->labelRTRAM->Name = L"labelRTRAM";
			this->labelRTRAM->Size = System::Drawing::Size(86, 26);
			this->labelRTRAM->TabIndex = 6;
			this->labelRTRAM->Text = L"0.0";
			this->labelRTRAM->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelRTCPU
			// 
			this->labelRTCPU->AutoSize = true;
			this->labelRTCPU->Dock = System::Windows::Forms::DockStyle::Fill;
			this->labelRTCPU->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelRTCPU->Location = System::Drawing::Point(97, 28);
			this->labelRTCPU->Name = L"labelRTCPU";
			this->labelRTCPU->Size = System::Drawing::Size(86, 26);
			this->labelRTCPU->TabIndex = 5;
			this->labelRTCPU->Text = L"0.0";
			this->labelRTCPU->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label14->Location = System::Drawing::Point(4, 109);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(86, 27);
			this->label14->TabIndex = 4;
			this->label14->Text = L"NET";
			this->label14->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->tableLayoutPanel3->SetColumnSpan(this->label15, 2);
			this->label15->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label15->Location = System::Drawing::Point(4, 1);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(179, 26);
			this->label15->TabIndex = 0;
			this->label15->Text = L"Real Time Usage got by Performance Counters";
			this->label15->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label16->Location = System::Drawing::Point(4, 28);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(86, 26);
			this->label16->TabIndex = 1;
			this->label16->Text = L"CPU";
			this->label16->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label17->Location = System::Drawing::Point(4, 55);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(86, 26);
			this->label17->TabIndex = 2;
			this->label17->Text = L"RAM";
			this->label17->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label18->Location = System::Drawing::Point(4, 82);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(86, 26);
			this->label18->TabIndex = 3;
			this->label18->Text = L"HDD";
			this->label18->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->tableLayoutPanel2);
			this->groupBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox2->Location = System::Drawing::Point(202, 3);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(193, 156);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Buffered Usage";
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->Controls->Add(this->labelBuffNET, 1, 4);
			this->tableLayoutPanel2->Controls->Add(this->labelBuffHDD, 1, 3);
			this->tableLayoutPanel2->Controls->Add(this->labelBuffRAM, 1, 2);
			this->tableLayoutPanel2->Controls->Add(this->labelBuffCPU, 1, 1);
			this->tableLayoutPanel2->Controls->Add(this->label5, 0, 4);
			this->tableLayoutPanel2->Controls->Add(this->label1, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->label2, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->label3, 0, 2);
			this->tableLayoutPanel2->Controls->Add(this->label4, 0, 3);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->Location = System::Drawing::Point(3, 16);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 5;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(187, 137);
			this->tableLayoutPanel2->TabIndex = 0;
			// 
			// labelBuffNET
			// 
			this->labelBuffNET->AutoSize = true;
			this->labelBuffNET->Dock = System::Windows::Forms::DockStyle::Fill;
			this->labelBuffNET->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelBuffNET->Location = System::Drawing::Point(97, 109);
			this->labelBuffNET->Name = L"labelBuffNET";
			this->labelBuffNET->Size = System::Drawing::Size(86, 27);
			this->labelBuffNET->TabIndex = 8;
			this->labelBuffNET->Text = L"0.0";
			this->labelBuffNET->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelBuffHDD
			// 
			this->labelBuffHDD->AutoSize = true;
			this->labelBuffHDD->Dock = System::Windows::Forms::DockStyle::Fill;
			this->labelBuffHDD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelBuffHDD->Location = System::Drawing::Point(97, 82);
			this->labelBuffHDD->Name = L"labelBuffHDD";
			this->labelBuffHDD->Size = System::Drawing::Size(86, 26);
			this->labelBuffHDD->TabIndex = 7;
			this->labelBuffHDD->Text = L"0.0";
			this->labelBuffHDD->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelBuffRAM
			// 
			this->labelBuffRAM->AutoSize = true;
			this->labelBuffRAM->Dock = System::Windows::Forms::DockStyle::Fill;
			this->labelBuffRAM->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelBuffRAM->Location = System::Drawing::Point(97, 55);
			this->labelBuffRAM->Name = L"labelBuffRAM";
			this->labelBuffRAM->Size = System::Drawing::Size(86, 26);
			this->labelBuffRAM->TabIndex = 6;
			this->labelBuffRAM->Text = L"0.0";
			this->labelBuffRAM->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelBuffCPU
			// 
			this->labelBuffCPU->AutoSize = true;
			this->labelBuffCPU->Dock = System::Windows::Forms::DockStyle::Fill;
			this->labelBuffCPU->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelBuffCPU->Location = System::Drawing::Point(97, 28);
			this->labelBuffCPU->Name = L"labelBuffCPU";
			this->labelBuffCPU->Size = System::Drawing::Size(86, 26);
			this->labelBuffCPU->TabIndex = 5;
			this->labelBuffCPU->Text = L"0.0";
			this->labelBuffCPU->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(4, 109);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(86, 27);
			this->label5->TabIndex = 4;
			this->label5->Text = L"NET";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->tableLayoutPanel2->SetColumnSpan(this->label1, 2);
			this->label1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label1->Location = System::Drawing::Point(4, 1);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(179, 26);
			this->label1->TabIndex = 0;
			this->label1->Text = L"The values are sampled 2 / sec and stored over 30 seconds";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(4, 28);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(86, 26);
			this->label2->TabIndex = 1;
			this->label2->Text = L"CPU";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(4, 55);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(86, 26);
			this->label3->TabIndex = 2;
			this->label3->Text = L"RAM";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(4, 82);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(86, 26);
			this->label4->TabIndex = 3;
			this->label4->Text = L"HDD";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->listViewSettings);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox1->Location = System::Drawing::Point(3, 3);
			this->groupBox1->Name = L"groupBox1";
			this->tableLayoutPanel1->SetRowSpan(this->groupBox1, 2);
			this->groupBox1->Size = System::Drawing::Size(193, 426);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Settings";
			// 
			// listViewSettings
			// 
			this->listViewSettings->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {
				this->columnHeader1,
					this->columnHeader2
			});
			this->listViewSettings->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listViewSettings->Location = System::Drawing::Point(3, 16);
			this->listViewSettings->Name = L"listViewSettings";
			this->listViewSettings->Size = System::Drawing::Size(187, 407);
			this->listViewSettings->TabIndex = 0;
			this->listViewSettings->UseCompatibleStateImageBehavior = false;
			this->listViewSettings->View = System::Windows::Forms::View::Details;
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"Name";
			this->columnHeader1->Width = 80;
			// 
			// columnHeader2
			// 
			this->columnHeader2->Text = L"Value";
			this->columnHeader2->Width = 104;
			// 
			// tableLayoutPanel6
			// 
			this->tableLayoutPanel6->ColumnCount = 1;
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel6->Controls->Add(this->groupBox8, 0, 1);
			this->tableLayoutPanel6->Controls->Add(this->groupBox4, 0, 0);
			this->tableLayoutPanel6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel6->Location = System::Drawing::Point(600, 3);
			this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
			this->tableLayoutPanel6->RowCount = 2;
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel6->Size = System::Drawing::Size(193, 156);
			this->tableLayoutPanel6->TabIndex = 7;
			// 
			// groupBox8
			// 
			this->groupBox8->Controls->Add(this->tableLayoutPanel7);
			this->groupBox8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox8->Location = System::Drawing::Point(3, 81);
			this->groupBox8->Name = L"groupBox8";
			this->groupBox8->Size = System::Drawing::Size(187, 72);
			this->groupBox8->TabIndex = 4;
			this->groupBox8->TabStop = false;
			this->groupBox8->Text = L"Sound detection";
			// 
			// tableLayoutPanel7
			// 
			this->tableLayoutPanel7->ColumnCount = 2;
			this->tableLayoutPanel7->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel7->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel7->Controls->Add(this->labelSoundOverLimit, 1, 2);
			this->tableLayoutPanel7->Controls->Add(this->labelSoundPeak, 1, 1);
			this->tableLayoutPanel7->Controls->Add(this->label11, 0, 1);
			this->tableLayoutPanel7->Controls->Add(this->label12, 0, 0);
			this->tableLayoutPanel7->Controls->Add(this->label13, 0, 2);
			this->tableLayoutPanel7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel7->Location = System::Drawing::Point(3, 16);
			this->tableLayoutPanel7->Name = L"tableLayoutPanel7";
			this->tableLayoutPanel7->RowCount = 3;
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel7->Size = System::Drawing::Size(181, 53);
			this->tableLayoutPanel7->TabIndex = 0;
			// 
			// labelSoundOverLimit
			// 
			this->labelSoundOverLimit->AutoSize = true;
			this->labelSoundOverLimit->Dock = System::Windows::Forms::DockStyle::Fill;
			this->labelSoundOverLimit->Location = System::Drawing::Point(62, 33);
			this->labelSoundOverLimit->Name = L"labelSoundOverLimit";
			this->labelSoundOverLimit->Size = System::Drawing::Size(116, 20);
			this->labelSoundOverLimit->TabIndex = 4;
			this->labelSoundOverLimit->Text = L"Yes / No";
			this->labelSoundOverLimit->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// labelSoundPeak
			// 
			this->labelSoundPeak->AutoSize = true;
			this->labelSoundPeak->Dock = System::Windows::Forms::DockStyle::Fill;
			this->labelSoundPeak->Location = System::Drawing::Point(62, 13);
			this->labelSoundPeak->Name = L"labelSoundPeak";
			this->labelSoundPeak->Size = System::Drawing::Size(116, 20);
			this->labelSoundPeak->TabIndex = 3;
			this->labelSoundPeak->Text = L"0.0";
			this->labelSoundPeak->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label11->Location = System::Drawing::Point(3, 13);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(53, 20);
			this->label11->TabIndex = 1;
			this->label11->Text = L"Peak";
			this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->tableLayoutPanel7->SetColumnSpan(this->label12, 2);
			this->label12->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label12->Location = System::Drawing::Point(3, 0);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(175, 13);
			this->label12->TabIndex = 0;
			this->label12->Text = L"Gets sound peak information";
			this->label12->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label13->Location = System::Drawing::Point(3, 33);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(53, 20);
			this->label13->TabIndex = 2;
			this->label13->Text = L"Over limit:";
			this->label13->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->tableLayoutPanel5);
			this->groupBox4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox4->Location = System::Drawing::Point(3, 3);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(187, 72);
			this->groupBox4->TabIndex = 3;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Input Monitor";
			// 
			// tableLayoutPanel5
			// 
			this->tableLayoutPanel5->ColumnCount = 2;
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel5->Controls->Add(this->labelWAITReached, 1, 2);
			this->tableLayoutPanel5->Controls->Add(this->labelInputTime, 1, 1);
			this->tableLayoutPanel5->Controls->Add(this->label7, 0, 1);
			this->tableLayoutPanel5->Controls->Add(this->label6, 0, 0);
			this->tableLayoutPanel5->Controls->Add(this->label8, 0, 2);
			this->tableLayoutPanel5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel5->Location = System::Drawing::Point(3, 16);
			this->tableLayoutPanel5->Name = L"tableLayoutPanel5";
			this->tableLayoutPanel5->RowCount = 3;
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel5->Size = System::Drawing::Size(181, 53);
			this->tableLayoutPanel5->TabIndex = 0;
			// 
			// labelWAITReached
			// 
			this->labelWAITReached->AutoSize = true;
			this->labelWAITReached->Dock = System::Windows::Forms::DockStyle::Fill;
			this->labelWAITReached->Location = System::Drawing::Point(113, 33);
			this->labelWAITReached->Name = L"labelWAITReached";
			this->labelWAITReached->Size = System::Drawing::Size(65, 20);
			this->labelWAITReached->TabIndex = 4;
			this->labelWAITReached->Text = L"Yes / No";
			this->labelWAITReached->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// labelInputTime
			// 
			this->labelInputTime->AutoSize = true;
			this->labelInputTime->Dock = System::Windows::Forms::DockStyle::Fill;
			this->labelInputTime->Location = System::Drawing::Point(113, 13);
			this->labelInputTime->Name = L"labelInputTime";
			this->labelInputTime->Size = System::Drawing::Size(65, 20);
			this->labelInputTime->TabIndex = 3;
			this->labelInputTime->Text = L"0.0";
			this->labelInputTime->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label7->Location = System::Drawing::Point(3, 13);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(104, 20);
			this->label7->TabIndex = 1;
			this->label7->Text = L"Time since last Input";
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->tableLayoutPanel5->SetColumnSpan(this->label6, 2);
			this->label6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label6->Location = System::Drawing::Point(3, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(175, 13);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Gets user input information";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label8->Location = System::Drawing::Point(3, 33);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(104, 20);
			this->label8->TabIndex = 2;
			this->label8->Text = L"Waittime reached";
			this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->tableLayoutPanel4);
			this->groupBox6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox6->Location = System::Drawing::Point(799, 3);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(196, 156);
			this->groupBox6->TabIndex = 5;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Controls";
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->ColumnCount = 1;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel4->Controls->Add(this->buttonTimeWnd, 0, 3);
			this->tableLayoutPanel4->Controls->Add(this->buttonMessageWnd, 0, 2);
			this->tableLayoutPanel4->Controls->Add(this->buttonProcessForm, 0, 1);
			this->tableLayoutPanel4->Controls->Add(this->buttonSettingsForm, 0, 0);
			this->tableLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel4->Location = System::Drawing::Point(3, 16);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 4;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(190, 137);
			this->tableLayoutPanel4->TabIndex = 0;
			// 
			// buttonTimeWnd
			// 
			this->buttonTimeWnd->Dock = System::Windows::Forms::DockStyle::Fill;
			this->buttonTimeWnd->Location = System::Drawing::Point(7, 109);
			this->buttonTimeWnd->Margin = System::Windows::Forms::Padding(7);
			this->buttonTimeWnd->Name = L"buttonTimeWnd";
			this->buttonTimeWnd->Size = System::Drawing::Size(176, 21);
			this->buttonTimeWnd->TabIndex = 3;
			this->buttonTimeWnd->Text = L"Open TimeoutWindow";
			this->buttonTimeWnd->UseVisualStyleBackColor = true;
			this->buttonTimeWnd->Click += gcnew System::EventHandler(this, &DebugForm::buttonTimeWnd_Click);
			// 
			// buttonMessageWnd
			// 
			this->buttonMessageWnd->Dock = System::Windows::Forms::DockStyle::Fill;
			this->buttonMessageWnd->Location = System::Drawing::Point(7, 75);
			this->buttonMessageWnd->Margin = System::Windows::Forms::Padding(7);
			this->buttonMessageWnd->Name = L"buttonMessageWnd";
			this->buttonMessageWnd->Size = System::Drawing::Size(176, 20);
			this->buttonMessageWnd->TabIndex = 2;
			this->buttonMessageWnd->Text = L"Open MessageWindow";
			this->buttonMessageWnd->UseVisualStyleBackColor = true;
			this->buttonMessageWnd->Click += gcnew System::EventHandler(this, &DebugForm::buttonMessageWnd_Click);
			// 
			// buttonProcessForm
			// 
			this->buttonProcessForm->Dock = System::Windows::Forms::DockStyle::Fill;
			this->buttonProcessForm->Location = System::Drawing::Point(7, 41);
			this->buttonProcessForm->Margin = System::Windows::Forms::Padding(7);
			this->buttonProcessForm->Name = L"buttonProcessForm";
			this->buttonProcessForm->Size = System::Drawing::Size(176, 20);
			this->buttonProcessForm->TabIndex = 1;
			this->buttonProcessForm->Text = L"Open ProcessSelectionForm";
			this->buttonProcessForm->UseVisualStyleBackColor = true;
			this->buttonProcessForm->Click += gcnew System::EventHandler(this, &DebugForm::buttonProcessForm_Click);
			// 
			// buttonSettingsForm
			// 
			this->buttonSettingsForm->Dock = System::Windows::Forms::DockStyle::Fill;
			this->buttonSettingsForm->Location = System::Drawing::Point(7, 7);
			this->buttonSettingsForm->Margin = System::Windows::Forms::Padding(7);
			this->buttonSettingsForm->Name = L"buttonSettingsForm";
			this->buttonSettingsForm->Size = System::Drawing::Size(176, 20);
			this->buttonSettingsForm->TabIndex = 0;
			this->buttonSettingsForm->Text = L"Open MetroSettingsForm";
			this->buttonSettingsForm->UseVisualStyleBackColor = true;
			this->buttonSettingsForm->Click += gcnew System::EventHandler(this, &DebugForm::buttonSettingsForm_Click);
			// 
			// groupBox5
			// 
			this->tableLayoutPanel1->SetColumnSpan(this->groupBox5, 2);
			this->groupBox5->Controls->Add(this->listViewProc);
			this->groupBox5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox5->Location = System::Drawing::Point(202, 165);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(392, 264);
			this->groupBox5->TabIndex = 4;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Running Processes";
			// 
			// listViewProc
			// 
			this->listViewProc->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {
				this->columnHeader3,
					this->columnHeader4
			});
			this->listViewProc->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listViewProc->FullRowSelect = true;
			this->listViewProc->GridLines = true;
			this->listViewProc->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->listViewProc->Location = System::Drawing::Point(3, 16);
			this->listViewProc->Name = L"listViewProc";
			this->listViewProc->Size = System::Drawing::Size(386, 245);
			this->listViewProc->Sorting = System::Windows::Forms::SortOrder::Ascending;
			this->listViewProc->TabIndex = 1;
			this->listViewProc->UseCompatibleStateImageBehavior = false;
			this->listViewProc->View = System::Windows::Forms::View::Details;
			// 
			// columnHeader3
			// 
			this->columnHeader3->Text = L"Name";
			// 
			// columnHeader4
			// 
			this->columnHeader4->Text = L"Path";
			this->columnHeader4->Width = 216;
			// 
			// groupBox7
			// 
			this->tableLayoutPanel1->SetColumnSpan(this->groupBox7, 2);
			this->groupBox7->Controls->Add(this->textBoxLog);
			this->groupBox7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox7->Location = System::Drawing::Point(600, 165);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(395, 264);
			this->groupBox7->TabIndex = 9;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = L"Log File";
			// 
			// textBoxLog
			// 
			this->textBoxLog->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBoxLog->Location = System::Drawing::Point(3, 16);
			this->textBoxLog->Name = L"textBoxLog";
			this->textBoxLog->Size = System::Drawing::Size(389, 245);
			this->textBoxLog->TabIndex = 8;
			this->textBoxLog->Text = L"";
			// 
			// timerRefresh
			// 
			this->timerRefresh->Enabled = true;
			// 
			// DebugForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(998, 432);
			this->Controls->Add(this->tableLayoutPanel1);
			this->DoubleBuffered = true;
			this->Name = L"DebugForm";
			this->Text = L"DebugForm - (c) Florian Baader, Stephan Le, Matthias Weirich";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &DebugForm::DebugForm_Load);
			this->Closing += gcnew System::ComponentModel::CancelEventHandler(this, &StandBye::DebugForm::OnClosing);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel3->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->tableLayoutPanel6->ResumeLayout(false);
			this->groupBox8->ResumeLayout(false);
			this->tableLayoutPanel7->ResumeLayout(false);
			this->tableLayoutPanel7->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->tableLayoutPanel5->ResumeLayout(false);
			this->tableLayoutPanel5->PerformLayout();
			this->groupBox6->ResumeLayout(false);
			this->tableLayoutPanel4->ResumeLayout(false);
			this->groupBox5->ResumeLayout(false);
			this->groupBox7->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
		//Load
		System::Void DebugForm_Load(System::Object^  sender, System::EventArgs^  e);

		//Button Actions
		System::Void buttonSettingsForm_Click(System::Object^, System::EventArgs^);
		System::Void buttonProcessForm_Click(System::Object^, System::EventArgs^);
		System::Void buttonMessageWnd_Click(System::Object^, System::EventArgs^);
		System::Void buttonTimeWnd_Click(System::Object^, System::EventArgs^);

		//Logs
		System::String^ getLogText();

		//UI
		void OnTick(System::Object ^sender, System::EventArgs ^e);
		void RefreshUISlow();
		void RefreshUIRealTime();
		void OnClosing(System::Object ^sender, System::ComponentModel::CancelEventArgs ^e);
};
}

