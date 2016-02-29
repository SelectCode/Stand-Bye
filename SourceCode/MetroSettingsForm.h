#pragma once
#include "stdafx.h"
#include "SystemMetricWatcher.h"
#include "SettingsProvider.h"
#include "InputMonitor.h"
#include "ProcessItem.h"
#include "ProcessSelectionForm.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class mainApplication;

namespace StandBye {
	/// <summary>
	/// Provides a Form to set up the Settings for the Application
	/// </summary>
	public ref class MetroSettingsForm : public MetroFramework::Forms::MetroForm
	{
	private:
		SystemAccess^ system_access;
		SettingsProvider* settings_provider;
		SystemMetricWatcher^ system_watcher;
		InputMonitor^ input_monitor;
		Drawing::Color lightGreen, darkGreen, lightRed, darkRed;
	private: MetroFramework::Controls::MetroLabel^  metroLabel16;
	private: MetroFramework::Controls::MetroToggle^  metroToggleUPDATES;
	private: MetroFramework::Controls::MetroLabel^  metroLabel22;
	private: MetroFramework::Controls::MetroToggle^  metroToggleMessages;

			 mainApplication^ parent;

	public:
		MetroSettingsForm(mainApplication^ parent, SystemMetricWatcher^ smw, SettingsProvider* pro, SystemAccess^ system_access, InputMonitor^ inputMon)
		{
			//Sets global variables
			this->parent = parent;
			settings_provider = pro;
			this->system_access = system_access;
			system_watcher = smw;
			input_monitor = inputMon;

			//temporary solution
			this->CheckForIllegalCrossThreadCalls = false;

			//Initialze Components()
			InitializeComponent();

			//Sets form options
			this->MinimizeBox = false;
			this->MaximizeBox = false;

			//Defines colors
			lightGreen = ColorTranslator::FromHtml("#a5d6a7");
			darkGreen = ColorTranslator::FromHtml("#33691e");
			lightRed = ColorTranslator::FromHtml("#ef9a9a");
			darkRed = ColorTranslator::FromHtml(" #f44336");
		}

	protected:
		~MetroSettingsForm()
		{
			delete system_access;
			if (components)
			{
				delete components;
			}
		}

#pragma region Windows Form Designer generated code
	private: MetroFramework::Components::MetroStyleExtender^  metroStyleExtender1;
	private: MetroFramework::Components::MetroStyleManager^  metroStyleManager1;
	private: MetroFramework::Components::MetroToolTip^  metroToolTip1;
	private: MetroFramework::Controls::MetroButton^  metroButtonAddFromFile;
	private: MetroFramework::Controls::MetroButton^  metroButtonAddFromList;
	private: MetroFramework::Controls::MetroButton^  metroButtonCancel;
	private: MetroFramework::Controls::MetroButton^  metroButtonOK;
	private: MetroFramework::Controls::MetroButton^  metroButtonRemove;
	private: MetroFramework::Controls::MetroLabel^  metroLabel10;
	private: MetroFramework::Controls::MetroLabel^  metroLabel11;
	private: MetroFramework::Controls::MetroLabel^  metroLabel12;
	private: MetroFramework::Controls::MetroLabel^  metroLabel13;
	private: MetroFramework::Controls::MetroLabel^  metroLabel14;
	private: MetroFramework::Controls::MetroLabel^  metroLabel15;
	private: MetroFramework::Controls::MetroLabel^  metroLabel17;
	private: MetroFramework::Controls::MetroLabel^  metroLabel18;
	private: MetroFramework::Controls::MetroLabel^  metroLabel19;
	private: MetroFramework::Controls::MetroLabel^  metroLabel1;
	private: MetroFramework::Controls::MetroLabel^  metroLabel20;
	private: MetroFramework::Controls::MetroLabel^  metroLabel21;
	private: MetroFramework::Controls::MetroLabel^  metroLabel2;
	private: MetroFramework::Controls::MetroLabel^  metroLabel3;
	private: MetroFramework::Controls::MetroLabel^  metroLabel4;
	private: MetroFramework::Controls::MetroLabel^  metroLabel5;
	private: MetroFramework::Controls::MetroLabel^  metroLabel6;
	private: MetroFramework::Controls::MetroLabel^  metroLabel7;
	private: MetroFramework::Controls::MetroLabel^  metroLabel8;
	private: MetroFramework::Controls::MetroLabel^  metroLabel9;
	private: MetroFramework::Controls::MetroLabel^  metroLabelCPUPer;
	private: MetroFramework::Controls::MetroLabel^  metroLabelCurCPU;
	private: MetroFramework::Controls::MetroLabel^  metroLabelCurHDD;
	private: MetroFramework::Controls::MetroLabel^  metroLabelCurNET;
	private: MetroFramework::Controls::MetroLabel^  metroLabelCurRAM;
	private: MetroFramework::Controls::MetroLabel^  metroLabelRAMPer;
	private: MetroFramework::Controls::MetroLabel^  metroLabelView;
	private: MetroFramework::Controls::MetroLink^  metroLinkHomepage;
	private: MetroFramework::Controls::MetroTabControl^  metroTabControl1;
	private: MetroFramework::Controls::MetroTabPage^  metroTabPage1;
	private: MetroFramework::Controls::MetroTabPage^  metroTabPage2;
	private: MetroFramework::Controls::MetroTabPage^  metroTabPage3;
	private: MetroFramework::Controls::MetroTabPage^  metroTabPage4;
	private: MetroFramework::Controls::MetroTextBox^  metroTextBoxHDD;
	private: MetroFramework::Controls::MetroTextBox^  metroTextBoxNET;
	private: MetroFramework::Controls::MetroTextBox^  metroTextBoxTimeMIN;
	private: MetroFramework::Controls::MetroTextBox^  metroTextBoxTimeSEC;
	private: MetroFramework::Controls::MetroTile^  metroTileGithub;
	private: MetroFramework::Controls::MetroTile^  metroTileHomepage;
	private: MetroFramework::Controls::MetroToggle^  metroToggleAutoStart;
	private: MetroFramework::Controls::MetroToggle^  metroToggleCPU;
	private: MetroFramework::Controls::MetroToggle^  metroToggleHDD;
	private: MetroFramework::Controls::MetroToggle^  metroToggleNET;
	private: MetroFramework::Controls::MetroToggle^  metroToggleOnTop;
	private: MetroFramework::Controls::MetroToggle^  metroTogglePresMode;
	private: MetroFramework::Controls::MetroToggle^  metroToggleRAM;
	private: MetroFramework::Controls::MetroToggle^  metroToggleSOUND;
	private: MetroFramework::Controls::MetroToggle^  metroToggleTutorial;
	private: MetroFramework::Controls::MetroToggle^  metroToggleView;
	private: MetroFramework::Controls::MetroTrackBar^  metroTrackBarCPU;
	private: MetroFramework::Controls::MetroTrackBar^  metroTrackBarRAM;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;

	private: System::Windows::Forms::ListView^  listViewProc;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel10;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel11;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel12;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel3;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel4;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel5;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel6;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel7;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel8;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel9;
	private: System::Windows::Forms::Timer^  timerRefresh;

			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MetroSettingsForm::typeid));
				 this->metroTabControl1 = (gcnew MetroFramework::Controls::MetroTabControl());
				 this->metroTabPage1 = (gcnew MetroFramework::Controls::MetroTabPage());
				 this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->metroLabelCurNET = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroToggleNET = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroToggleHDD = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroLabelCurHDD = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabel13 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabelCurRAM = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroToggleRAM = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroLabelCurCPU = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroToggleCPU = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroTextBoxNET = (gcnew MetroFramework::Controls::MetroTextBox());
				 this->metroLabel14 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabel5 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabel6 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabel7 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabel8 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabelRAMPer = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroTrackBarCPU = (gcnew MetroFramework::Controls::MetroTrackBar());
				 this->metroLabelCPUPer = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroTextBoxHDD = (gcnew MetroFramework::Controls::MetroTextBox());
				 this->metroTrackBarRAM = (gcnew MetroFramework::Controls::MetroTrackBar());
				 this->metroLabel3 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->tableLayoutPanel10 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->metroLabel21 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabel4 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabel9 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->tableLayoutPanel12 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->metroTextBoxTimeMIN = (gcnew MetroFramework::Controls::MetroTextBox());
				 this->metroLabel10 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroTextBoxTimeSEC = (gcnew MetroFramework::Controls::MetroTextBox());
				 this->metroLabel19 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroTogglePresMode = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroToggleSOUND = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroLabel2 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabel1 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroTabPage2 = (gcnew MetroFramework::Controls::MetroTabPage());
				 this->tableLayoutPanel5 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->listViewProc = (gcnew System::Windows::Forms::ListView());
				 this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
				 this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
				 this->tableLayoutPanel6 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->tableLayoutPanel7 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->metroButtonRemove = (gcnew MetroFramework::Controls::MetroButton());
				 this->metroButtonAddFromList = (gcnew MetroFramework::Controls::MetroButton());
				 this->metroButtonAddFromFile = (gcnew MetroFramework::Controls::MetroButton());
				 this->tableLayoutPanel8 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->metroToggleView = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroLabelView = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabel17 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroTabPage4 = (gcnew MetroFramework::Controls::MetroTabPage());
				 this->tableLayoutPanel11 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->metroLabel16 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroToggleUPDATES = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroLabel11 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroToggleAutoStart = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroLabel20 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabel18 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroToggleOnTop = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroToggleTutorial = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroLabel22 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroToggleMessages = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroTabPage3 = (gcnew MetroFramework::Controls::MetroTabPage());
				 this->tableLayoutPanel9 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->metroTileHomepage = (gcnew MetroFramework::Controls::MetroTile());
				 this->metroTileGithub = (gcnew MetroFramework::Controls::MetroTile());
				 this->metroLabel15 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->metroButtonOK = (gcnew MetroFramework::Controls::MetroButton());
				 this->metroButtonCancel = (gcnew MetroFramework::Controls::MetroButton());
				 this->metroLabel12 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLinkHomepage = (gcnew MetroFramework::Controls::MetroLink());
				 this->timerRefresh = (gcnew System::Windows::Forms::Timer(this->components));
				 this->metroStyleManager1 = (gcnew MetroFramework::Components::MetroStyleManager(this->components));
				 this->metroStyleExtender1 = (gcnew MetroFramework::Components::MetroStyleExtender(this->components));
				 this->metroToolTip1 = (gcnew MetroFramework::Components::MetroToolTip());
				 this->metroTabControl1->SuspendLayout();
				 this->metroTabPage1->SuspendLayout();
				 this->tableLayoutPanel3->SuspendLayout();
				 this->tableLayoutPanel10->SuspendLayout();
				 this->tableLayoutPanel12->SuspendLayout();
				 this->metroTabPage2->SuspendLayout();
				 this->tableLayoutPanel5->SuspendLayout();
				 this->tableLayoutPanel6->SuspendLayout();
				 this->tableLayoutPanel7->SuspendLayout();
				 this->tableLayoutPanel8->SuspendLayout();
				 this->metroTabPage4->SuspendLayout();
				 this->tableLayoutPanel11->SuspendLayout();
				 this->metroTabPage3->SuspendLayout();
				 this->tableLayoutPanel9->SuspendLayout();
				 this->tableLayoutPanel1->SuspendLayout();
				 this->tableLayoutPanel4->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->metroStyleManager1))->BeginInit();
				 this->SuspendLayout();
				 //
				 // metroTabControl1
				 //
				 this->metroTabControl1->Controls->Add(this->metroTabPage1);
				 this->metroTabControl1->Controls->Add(this->metroTabPage2);
				 this->metroTabControl1->Controls->Add(this->metroTabPage4);
				 this->metroTabControl1->Controls->Add(this->metroTabPage3);
				 this->metroTabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroTabControl1->Location = System::Drawing::Point(13, 12);
				 this->metroTabControl1->Margin = System::Windows::Forms::Padding(13, 12, 13, 12);
				 this->metroTabControl1->Name = L"metroTabControl1";
				 this->metroTabControl1->SelectedIndex = 0;
				 this->metroTabControl1->Size = System::Drawing::Size(957, 393);
				 this->metroTabControl1->TabIndex = 0;
				 this->metroTabControl1->UseSelectable = true;
				 //
				 // metroTabPage1
				 //
				 this->metroTabPage1->BackColor = System::Drawing::SystemColors::Control;
				 this->metroTabPage1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->metroTabPage1->Controls->Add(this->tableLayoutPanel3);
				 this->metroTabPage1->Controls->Add(this->metroLabel3);
				 this->metroTabPage1->Controls->Add(this->tableLayoutPanel10);
				 this->metroTabPage1->Controls->Add(this->metroLabel2);
				 this->metroTabPage1->Controls->Add(this->metroLabel1);
				 this->metroTabPage1->HorizontalScrollbarBarColor = false;
				 this->metroTabPage1->HorizontalScrollbarHighlightOnWheel = false;
				 this->metroTabPage1->HorizontalScrollbarSize = 0;
				 this->metroTabPage1->Location = System::Drawing::Point(4, 38);
				 this->metroTabPage1->Margin = System::Windows::Forms::Padding(4);
				 this->metroTabPage1->Name = L"metroTabPage1";
				 this->metroTabPage1->Size = System::Drawing::Size(949, 351);
				 this->metroTabPage1->Style = MetroFramework::MetroColorStyle::Green;
				 this->metroTabPage1->TabIndex = 0;
				 this->metroTabPage1->Text = L"Settings";
				 this->metroTabPage1->VerticalScrollbarBarColor = false;
				 this->metroTabPage1->VerticalScrollbarHighlightOnWheel = false;
				 this->metroTabPage1->VerticalScrollbarSize = 0;
				 //
				 // tableLayoutPanel3
				 //
				 this->tableLayoutPanel3->BackColor = System::Drawing::Color::White;
				 this->tableLayoutPanel3->ColumnCount = 5;
				 this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanel3->Controls->Add(this->metroLabelCurNET, 4, 3);
				 this->tableLayoutPanel3->Controls->Add(this->metroToggleNET, 0, 3);
				 this->tableLayoutPanel3->Controls->Add(this->metroToggleHDD, 0, 2);
				 this->tableLayoutPanel3->Controls->Add(this->metroLabelCurHDD, 4, 2);
				 this->tableLayoutPanel3->Controls->Add(this->metroLabel13, 3, 3);
				 this->tableLayoutPanel3->Controls->Add(this->metroLabelCurRAM, 4, 1);
				 this->tableLayoutPanel3->Controls->Add(this->metroToggleRAM, 0, 1);
				 this->tableLayoutPanel3->Controls->Add(this->metroLabelCurCPU, 4, 0);
				 this->tableLayoutPanel3->Controls->Add(this->metroToggleCPU, 0, 0);
				 this->tableLayoutPanel3->Controls->Add(this->metroTextBoxNET, 2, 3);
				 this->tableLayoutPanel3->Controls->Add(this->metroLabel14, 3, 2);
				 this->tableLayoutPanel3->Controls->Add(this->metroLabel5, 1, 0);
				 this->tableLayoutPanel3->Controls->Add(this->metroLabel6, 1, 1);
				 this->tableLayoutPanel3->Controls->Add(this->metroLabel7, 1, 2);
				 this->tableLayoutPanel3->Controls->Add(this->metroLabel8, 1, 3);
				 this->tableLayoutPanel3->Controls->Add(this->metroLabelRAMPer, 3, 1);
				 this->tableLayoutPanel3->Controls->Add(this->metroTrackBarCPU, 2, 0);
				 this->tableLayoutPanel3->Controls->Add(this->metroLabelCPUPer, 3, 0);
				 this->tableLayoutPanel3->Controls->Add(this->metroTextBoxHDD, 2, 2);
				 this->tableLayoutPanel3->Controls->Add(this->metroTrackBarRAM, 2, 1);
				 this->tableLayoutPanel3->Location = System::Drawing::Point(91, 201);
				 this->tableLayoutPanel3->Margin = System::Windows::Forms::Padding(4);
				 this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
				 this->tableLayoutPanel3->RowCount = 4;
				 this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
				 this->tableLayoutPanel3->Size = System::Drawing::Size(757, 142);
				 this->tableLayoutPanel3->TabIndex = 3;
				 //
				 // metroLabelCurNET
				 //
				 this->metroLabelCurNET->AutoSize = true;
				 this->metroLabelCurNET->BackColor = System::Drawing::SystemColors::Control;
				 this->metroLabelCurNET->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelCurNET->Location = System::Drawing::Point(545, 105);
				 this->metroLabelCurNET->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabelCurNET->Name = L"metroLabelCurNET";
				 this->metroLabelCurNET->Size = System::Drawing::Size(208, 37);
				 this->metroLabelCurNET->TabIndex = 41;
				 this->metroLabelCurNET->Text = L"-";
				 this->metroLabelCurNET->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroLabelCurNET->UseCustomBackColor = true;
				 this->metroLabelCurNET->UseCustomForeColor = true;
				 //
				 // metroToggleNET
				 //
				 this->metroToggleNET->AutoSize = true;
				 this->metroToggleNET->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroToggleNET->Location = System::Drawing::Point(4, 111);
				 this->metroToggleNET->Margin = System::Windows::Forms::Padding(4, 6, 4, 4);
				 this->metroToggleNET->Name = L"metroToggleNET";
				 this->metroToggleNET->Size = System::Drawing::Size(80, 27);
				 this->metroToggleNET->TabIndex = 49;
				 this->metroToggleNET->Text = L"Aus";
				 this->metroToggleNET->UseSelectable = true;
				 //
				 // metroToggleHDD
				 //
				 this->metroToggleHDD->AutoSize = true;
				 this->metroToggleHDD->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroToggleHDD->Location = System::Drawing::Point(4, 74);
				 this->metroToggleHDD->Margin = System::Windows::Forms::Padding(4);
				 this->metroToggleHDD->Name = L"metroToggleHDD";
				 this->metroToggleHDD->Size = System::Drawing::Size(80, 27);
				 this->metroToggleHDD->TabIndex = 48;
				 this->metroToggleHDD->Text = L"Aus";
				 this->metroToggleHDD->UseSelectable = true;
				 //
				 // metroLabelCurHDD
				 //
				 this->metroLabelCurHDD->AutoSize = true;
				 this->metroLabelCurHDD->BackColor = System::Drawing::SystemColors::Control;
				 this->metroLabelCurHDD->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelCurHDD->Location = System::Drawing::Point(545, 70);
				 this->metroLabelCurHDD->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabelCurHDD->Name = L"metroLabelCurHDD";
				 this->metroLabelCurHDD->Size = System::Drawing::Size(208, 35);
				 this->metroLabelCurHDD->TabIndex = 40;
				 this->metroLabelCurHDD->Text = L"-";
				 this->metroLabelCurHDD->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroLabelCurHDD->UseCustomBackColor = true;
				 this->metroLabelCurHDD->UseCustomForeColor = true;
				 //
				 // metroLabel13
				 //
				 this->metroLabel13->AutoSize = true;
				 this->metroLabel13->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel13->Location = System::Drawing::Point(490, 105);
				 this->metroLabel13->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel13->Name = L"metroLabel13";
				 this->metroLabel13->Size = System::Drawing::Size(47, 37);
				 this->metroLabel13->TabIndex = 36;
				 this->metroLabel13->Text = L"MBit/s";
				 this->metroLabel13->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 //
				 // metroLabelCurRAM
				 //
				 this->metroLabelCurRAM->AutoSize = true;
				 this->metroLabelCurRAM->BackColor = System::Drawing::SystemColors::Control;
				 this->metroLabelCurRAM->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelCurRAM->Location = System::Drawing::Point(545, 35);
				 this->metroLabelCurRAM->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabelCurRAM->Name = L"metroLabelCurRAM";
				 this->metroLabelCurRAM->Size = System::Drawing::Size(208, 35);
				 this->metroLabelCurRAM->TabIndex = 39;
				 this->metroLabelCurRAM->Text = L"-";
				 this->metroLabelCurRAM->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroLabelCurRAM->UseCustomBackColor = true;
				 this->metroLabelCurRAM->UseCustomForeColor = true;
				 //
				 // metroToggleRAM
				 //
				 this->metroToggleRAM->AutoSize = true;
				 this->metroToggleRAM->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroToggleRAM->Location = System::Drawing::Point(4, 39);
				 this->metroToggleRAM->Margin = System::Windows::Forms::Padding(4);
				 this->metroToggleRAM->Name = L"metroToggleRAM";
				 this->metroToggleRAM->Size = System::Drawing::Size(80, 27);
				 this->metroToggleRAM->TabIndex = 47;
				 this->metroToggleRAM->Text = L"Aus";
				 this->metroToggleRAM->UseSelectable = true;
				 //
				 // metroLabelCurCPU
				 //
				 this->metroLabelCurCPU->AutoSize = true;
				 this->metroLabelCurCPU->BackColor = System::Drawing::SystemColors::Control;
				 this->metroLabelCurCPU->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelCurCPU->ForeColor = System::Drawing::SystemColors::ControlText;
				 this->metroLabelCurCPU->Location = System::Drawing::Point(545, 0);
				 this->metroLabelCurCPU->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabelCurCPU->Name = L"metroLabelCurCPU";
				 this->metroLabelCurCPU->Size = System::Drawing::Size(208, 35);
				 this->metroLabelCurCPU->TabIndex = 38;
				 this->metroLabelCurCPU->Text = L"-";
				 this->metroLabelCurCPU->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroLabelCurCPU->UseCustomBackColor = true;
				 this->metroLabelCurCPU->UseCustomForeColor = true;
				 //
				 // metroToggleCPU
				 //
				 this->metroToggleCPU->AutoSize = true;
				 this->metroToggleCPU->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroToggleCPU->Location = System::Drawing::Point(4, 4);
				 this->metroToggleCPU->Margin = System::Windows::Forms::Padding(4);
				 this->metroToggleCPU->Name = L"metroToggleCPU";
				 this->metroToggleCPU->Size = System::Drawing::Size(80, 27);
				 this->metroToggleCPU->TabIndex = 46;
				 this->metroToggleCPU->Text = L"Aus";
				 this->metroToggleCPU->UseSelectable = true;
				 //
				 // metroTextBoxNET
				 //
				 this->metroTextBoxNET->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroTextBoxNET->Lines = gcnew cli::array< System::String^  >(1) { L" " };
				 this->metroTextBoxNET->Location = System::Drawing::Point(227, 107);
				 this->metroTextBoxNET->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
				 this->metroTextBoxNET->MaxLength = 3;
				 this->metroTextBoxNET->Name = L"metroTextBoxNET";
				 this->metroTextBoxNET->PasswordChar = '\0';
				 this->metroTextBoxNET->ScrollBars = System::Windows::Forms::ScrollBars::None;
				 this->metroTextBoxNET->SelectedText = L"";
				 this->metroTextBoxNET->Size = System::Drawing::Size(256, 33);
				 this->metroTextBoxNET->TabIndex = 45;
				 this->metroTextBoxNET->Text = L" ";
				 this->metroTextBoxNET->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
				 this->metroTextBoxNET->UseSelectable = true;
				 this->metroTextBoxNET->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MetroSettingsForm::ReformatTextBoxValueOnReturn);
				 //
				 // metroLabel14
				 //
				 this->metroLabel14->AutoSize = true;
				 this->metroLabel14->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel14->Location = System::Drawing::Point(490, 70);
				 this->metroLabel14->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel14->Name = L"metroLabel14";
				 this->metroLabel14->Size = System::Drawing::Size(47, 35);
				 this->metroLabel14->TabIndex = 37;
				 this->metroLabel14->Text = L"MBit/s";
				 this->metroLabel14->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 //
				 // metroLabel5
				 //
				 this->metroLabel5->AutoSize = true;
				 this->metroLabel5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel5->Location = System::Drawing::Point(92, 0);
				 this->metroLabel5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel5->Name = L"metroLabel5";
				 this->metroLabel5->Size = System::Drawing::Size(128, 35);
				 this->metroLabel5->TabIndex = 30;
				 this->metroLabel5->Text = L"CPU Threshold";
				 this->metroLabel5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroToolTip1->SetToolTip(this->metroLabel5, L"  If Usage > Setting --> No Standby  ");
				 //
				 // metroLabel6
				 //
				 this->metroLabel6->AutoSize = true;
				 this->metroLabel6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel6->Location = System::Drawing::Point(92, 35);
				 this->metroLabel6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel6->Name = L"metroLabel6";
				 this->metroLabel6->Size = System::Drawing::Size(128, 35);
				 this->metroLabel6->TabIndex = 31;
				 this->metroLabel6->Text = L"RAM Threshold";
				 this->metroLabel6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroToolTip1->SetToolTip(this->metroLabel6, L"  If Usage > Setting --> No Standby  ");
				 //
				 // metroLabel7
				 //
				 this->metroLabel7->AutoSize = true;
				 this->metroLabel7->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel7->Location = System::Drawing::Point(92, 70);
				 this->metroLabel7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel7->Name = L"metroLabel7";
				 this->metroLabel7->Size = System::Drawing::Size(128, 35);
				 this->metroLabel7->TabIndex = 32;
				 this->metroLabel7->Text = L"HDD Threshold";
				 this->metroLabel7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroToolTip1->SetToolTip(this->metroLabel7, L"  If Usage > Setting --> No Standby  ");
				 //
				 // metroLabel8
				 //
				 this->metroLabel8->AutoSize = true;
				 this->metroLabel8->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel8->Location = System::Drawing::Point(92, 105);
				 this->metroLabel8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel8->Name = L"metroLabel8";
				 this->metroLabel8->Size = System::Drawing::Size(128, 37);
				 this->metroLabel8->TabIndex = 33;
				 this->metroLabel8->Text = L"Network Threshold";
				 this->metroLabel8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroToolTip1->SetToolTip(this->metroLabel8, L"  If Usage > Setting --> No Standby  ");
				 //
				 // metroLabelRAMPer
				 //
				 this->metroLabelRAMPer->AutoSize = true;
				 this->metroLabelRAMPer->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelRAMPer->Location = System::Drawing::Point(490, 35);
				 this->metroLabelRAMPer->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabelRAMPer->Name = L"metroLabelRAMPer";
				 this->metroLabelRAMPer->Size = System::Drawing::Size(47, 35);
				 this->metroLabelRAMPer->TabIndex = 35;
				 this->metroLabelRAMPer->Text = L"%";
				 this->metroLabelRAMPer->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 //
				 // metroTrackBarCPU
				 //
				 this->metroTrackBarCPU->BackColor = System::Drawing::Color::Transparent;
				 this->metroTrackBarCPU->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroTrackBarCPU->Location = System::Drawing::Point(228, 4);
				 this->metroTrackBarCPU->Margin = System::Windows::Forms::Padding(4);
				 this->metroTrackBarCPU->Name = L"metroTrackBarCPU";
				 this->metroTrackBarCPU->Size = System::Drawing::Size(254, 27);
				 this->metroTrackBarCPU->TabIndex = 42;
				 this->metroTrackBarCPU->Text = L"metroTrackBar1";
				 this->metroTrackBarCPU->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MetroSettingsForm::metroTrackBarCPU_Scroll);
				 //
				 // metroLabelCPUPer
				 //
				 this->metroLabelCPUPer->AutoSize = true;
				 this->metroLabelCPUPer->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelCPUPer->Location = System::Drawing::Point(490, 0);
				 this->metroLabelCPUPer->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabelCPUPer->Name = L"metroLabelCPUPer";
				 this->metroLabelCPUPer->Size = System::Drawing::Size(47, 35);
				 this->metroLabelCPUPer->TabIndex = 34;
				 this->metroLabelCPUPer->Text = L"%";
				 this->metroLabelCPUPer->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 //
				 // metroTextBoxHDD
				 //
				 this->metroTextBoxHDD->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroTextBoxHDD->Lines = gcnew cli::array< System::String^  >(1) { L" " };
				 this->metroTextBoxHDD->Location = System::Drawing::Point(227, 72);
				 this->metroTextBoxHDD->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
				 this->metroTextBoxHDD->MaxLength = 3;
				 this->metroTextBoxHDD->Name = L"metroTextBoxHDD";
				 this->metroTextBoxHDD->PasswordChar = '\0';
				 this->metroTextBoxHDD->ScrollBars = System::Windows::Forms::ScrollBars::None;
				 this->metroTextBoxHDD->SelectedText = L"";
				 this->metroTextBoxHDD->Size = System::Drawing::Size(256, 31);
				 this->metroTextBoxHDD->TabIndex = 44;
				 this->metroTextBoxHDD->Text = L" ";
				 this->metroTextBoxHDD->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
				 this->metroTextBoxHDD->UseSelectable = true;
				 this->metroTextBoxHDD->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MetroSettingsForm::ReformatTextBoxValueOnReturn);
				 //
				 // metroTrackBarRAM
				 //
				 this->metroTrackBarRAM->BackColor = System::Drawing::Color::Transparent;
				 this->metroTrackBarRAM->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroTrackBarRAM->Location = System::Drawing::Point(228, 39);
				 this->metroTrackBarRAM->Margin = System::Windows::Forms::Padding(4);
				 this->metroTrackBarRAM->Name = L"metroTrackBarRAM";
				 this->metroTrackBarRAM->Size = System::Drawing::Size(254, 27);
				 this->metroTrackBarRAM->TabIndex = 43;
				 this->metroTrackBarRAM->Text = L"metroTrackBar2";
				 this->metroTrackBarRAM->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MetroSettingsForm::metroTrackBarRAM_Scroll);
				 //
				 // metroLabel3
				 //
				 this->metroLabel3->AutoSize = true;
				 this->metroLabel3->FontWeight = MetroFramework::MetroLabelWeight::Regular;
				 this->metroLabel3->Location = System::Drawing::Point(707, 161);
				 this->metroLabel3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel3->Name = L"metroLabel3";
				 this->metroLabel3->Size = System::Drawing::Size(112, 20);
				 this->metroLabel3->TabIndex = 50;
				 this->metroLabel3->Text = L"Average Usage:";
				 this->metroLabel3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->metroToolTip1->SetToolTip(this->metroLabel3, L"   Stand-Bye uses the average usage over 15 sec. (measurement 2 times / sec)");
				 //
				 // tableLayoutPanel10
				 //
				 this->tableLayoutPanel10->BackColor = System::Drawing::Color::White;
				 this->tableLayoutPanel10->ColumnCount = 2;
				 this->tableLayoutPanel10->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanel10->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanel10->Controls->Add(this->metroLabel21, 0, 2);
				 this->tableLayoutPanel10->Controls->Add(this->metroLabel4, 0, 0);
				 this->tableLayoutPanel10->Controls->Add(this->metroLabel9, 0, 1);
				 this->tableLayoutPanel10->Controls->Add(this->tableLayoutPanel12, 1, 0);
				 this->tableLayoutPanel10->Controls->Add(this->metroTogglePresMode, 1, 2);
				 this->tableLayoutPanel10->Controls->Add(this->metroToggleSOUND, 1, 1);
				 this->tableLayoutPanel10->Location = System::Drawing::Point(89, 41);
				 this->tableLayoutPanel10->Margin = System::Windows::Forms::Padding(4);
				 this->tableLayoutPanel10->Name = L"tableLayoutPanel10";
				 this->tableLayoutPanel10->RowCount = 3;
				 this->tableLayoutPanel10->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
				 this->tableLayoutPanel10->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
				 this->tableLayoutPanel10->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
				 this->tableLayoutPanel10->Size = System::Drawing::Size(540, 117);
				 this->tableLayoutPanel10->TabIndex = 53;
				 //
				 // metroLabel21
				 //
				 this->metroLabel21->AutoSize = true;
				 this->metroLabel21->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel21->Location = System::Drawing::Point(4, 78);
				 this->metroLabel21->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel21->Name = L"metroLabel21";
				 this->metroLabel21->Size = System::Drawing::Size(244, 39);
				 this->metroLabel21->TabIndex = 53;
				 this->metroLabel21->Text = L"Activate Presentation-Mode";
				 this->metroLabel21->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->metroToolTip1->SetToolTip(this->metroLabel21, L"  If enabled --> no standby and no display timeout.  ");
				 //
				 // metroLabel4
				 //
				 this->metroLabel4->AutoSize = true;
				 this->metroLabel4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel4->Location = System::Drawing::Point(0, 0);
				 this->metroLabel4->Margin = System::Windows::Forms::Padding(0);
				 this->metroLabel4->Name = L"metroLabel4";
				 this->metroLabel4->Size = System::Drawing::Size(252, 39);
				 this->metroLabel4->TabIndex = 3;
				 this->metroLabel4->Text = L"Activate Standby After";
				 this->metroLabel4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->metroToolTip1->SetToolTip(this->metroLabel4, L"  The waiting time till standby starts.  ");
				 //
				 // metroLabel9
				 //
				 this->metroLabel9->AutoSize = true;
				 this->metroLabel9->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel9->Location = System::Drawing::Point(4, 39);
				 this->metroLabel9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel9->Name = L"metroLabel9";
				 this->metroLabel9->Size = System::Drawing::Size(244, 39);
				 this->metroLabel9->TabIndex = 52;
				 this->metroLabel9->Text = L"Cancel Standby while Sound is playing";
				 this->metroLabel9->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->metroToolTip1->SetToolTip(this->metroLabel9, L"  If you like enjoying music or movies, thats a good choice.  ");
				 //
				 // tableLayoutPanel12
				 //
				 this->tableLayoutPanel12->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
				 this->tableLayoutPanel12->ColumnCount = 4;
				 this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 25)));
				 this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 25)));
				 this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 25)));
				 this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 25)));
				 this->tableLayoutPanel12->Controls->Add(this->metroTextBoxTimeMIN, 0, 0);
				 this->tableLayoutPanel12->Controls->Add(this->metroLabel10, 1, 0);
				 this->tableLayoutPanel12->Controls->Add(this->metroTextBoxTimeSEC, 2, 0);
				 this->tableLayoutPanel12->Controls->Add(this->metroLabel19, 3, 0);
				 this->tableLayoutPanel12->Location = System::Drawing::Point(252, 9);
				 this->tableLayoutPanel12->Margin = System::Windows::Forms::Padding(0);
				 this->tableLayoutPanel12->Name = L"tableLayoutPanel12";
				 this->tableLayoutPanel12->RowCount = 1;
				 this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
				 this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
					 30)));
				 this->tableLayoutPanel12->Size = System::Drawing::Size(204, 30);
				 this->tableLayoutPanel12->TabIndex = 55;
				 //
				 // metroTextBoxTimeMIN
				 //
				 this->metroTextBoxTimeMIN->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroTextBoxTimeMIN->Lines = gcnew cli::array< System::String^  >(1) { L" " };
				 this->metroTextBoxTimeMIN->Location = System::Drawing::Point(0, 0);
				 this->metroTextBoxTimeMIN->Margin = System::Windows::Forms::Padding(0);
				 this->metroTextBoxTimeMIN->MaxLength = 3;
				 this->metroTextBoxTimeMIN->Name = L"metroTextBoxTimeMIN";
				 this->metroTextBoxTimeMIN->PasswordChar = '\0';
				 this->metroTextBoxTimeMIN->ScrollBars = System::Windows::Forms::ScrollBars::None;
				 this->metroTextBoxTimeMIN->SelectedText = L"";
				 this->metroTextBoxTimeMIN->Size = System::Drawing::Size(51, 30);
				 this->metroTextBoxTimeMIN->TabIndex = 46;
				 this->metroTextBoxTimeMIN->Text = L" ";
				 this->metroTextBoxTimeMIN->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
				 this->metroTextBoxTimeMIN->UseSelectable = true;
				 this->metroTextBoxTimeMIN->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MetroSettingsForm::ReformatTextBoxValueOnReturn);
				 //
				 // metroLabel10
				 //
				 this->metroLabel10->AutoSize = true;
				 this->metroLabel10->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel10->Location = System::Drawing::Point(55, 0);
				 this->metroLabel10->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel10->Name = L"metroLabel10";
				 this->metroLabel10->Size = System::Drawing::Size(43, 30);
				 this->metroLabel10->TabIndex = 48;
				 this->metroLabel10->Text = L"min";
				 this->metroLabel10->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 //
				 // metroTextBoxTimeSEC
				 //
				 this->metroTextBoxTimeSEC->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroTextBoxTimeSEC->Lines = gcnew cli::array< System::String^  >(1) { L" " };
				 this->metroTextBoxTimeSEC->Location = System::Drawing::Point(102, 0);
				 this->metroTextBoxTimeSEC->Margin = System::Windows::Forms::Padding(0);
				 this->metroTextBoxTimeSEC->MaxLength = 2;
				 this->metroTextBoxTimeSEC->Name = L"metroTextBoxTimeSEC";
				 this->metroTextBoxTimeSEC->PasswordChar = '\0';
				 this->metroTextBoxTimeSEC->ScrollBars = System::Windows::Forms::ScrollBars::None;
				 this->metroTextBoxTimeSEC->SelectedText = L"";
				 this->metroTextBoxTimeSEC->Size = System::Drawing::Size(51, 30);
				 this->metroTextBoxTimeSEC->TabIndex = 47;
				 this->metroTextBoxTimeSEC->Text = L" ";
				 this->metroTextBoxTimeSEC->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
				 this->metroTextBoxTimeSEC->UseSelectable = true;
				 this->metroTextBoxTimeSEC->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MetroSettingsForm::ReformatTextBoxValueOnReturn);
				 //
				 // metroLabel19
				 //
				 this->metroLabel19->AutoSize = true;
				 this->metroLabel19->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel19->Location = System::Drawing::Point(157, 0);
				 this->metroLabel19->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel19->Name = L"metroLabel19";
				 this->metroLabel19->Size = System::Drawing::Size(43, 30);
				 this->metroLabel19->TabIndex = 49;
				 this->metroLabel19->Text = L"s";
				 this->metroLabel19->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 //
				 // metroTogglePresMode
				 //
				 this->metroTogglePresMode->Anchor = System::Windows::Forms::AnchorStyles::Left;
				 this->metroTogglePresMode->AutoSize = true;
				 this->metroTogglePresMode->Location = System::Drawing::Point(256, 87);
				 this->metroTogglePresMode->Margin = System::Windows::Forms::Padding(4);
				 this->metroTogglePresMode->Name = L"metroTogglePresMode";
				 this->metroTogglePresMode->Size = System::Drawing::Size(80, 21);
				 this->metroTogglePresMode->TabIndex = 54;
				 this->metroTogglePresMode->Text = L"Aus";
				 this->metroTogglePresMode->UseSelectable = true;
				 this->metroTogglePresMode->CheckedChanged += gcnew System::EventHandler(this, &MetroSettingsForm::metroTogglePresMode_CheckedChanged);
				 //
				 // metroToggleSOUND
				 //
				 this->metroToggleSOUND->Anchor = System::Windows::Forms::AnchorStyles::Left;
				 this->metroToggleSOUND->AutoSize = true;
				 this->metroToggleSOUND->Location = System::Drawing::Point(256, 48);
				 this->metroToggleSOUND->Margin = System::Windows::Forms::Padding(4);
				 this->metroToggleSOUND->Name = L"metroToggleSOUND";
				 this->metroToggleSOUND->Size = System::Drawing::Size(80, 21);
				 this->metroToggleSOUND->TabIndex = 51;
				 this->metroToggleSOUND->Text = L"Aus";
				 this->metroToggleSOUND->UseSelectable = true;
				 //
				 // metroLabel2
				 //
				 this->metroLabel2->AutoSize = true;
				 this->metroLabel2->FontWeight = MetroFramework::MetroLabelWeight::Bold;
				 this->metroLabel2->Location = System::Drawing::Point(4, 161);
				 this->metroLabel2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel2->Name = L"metroLabel2";
				 this->metroLabel2->Size = System::Drawing::Size(188, 20);
				 this->metroLabel2->TabIndex = 29;
				 this->metroLabel2->Text = L"System Usage Thresholds";
				 this->metroLabel2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 //
				 // metroLabel1
				 //
				 this->metroLabel1->AutoSize = true;
				 this->metroLabel1->FontWeight = MetroFramework::MetroLabelWeight::Bold;
				 this->metroLabel1->Location = System::Drawing::Point(4, 14);
				 this->metroLabel1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel1->Name = L"metroLabel1";
				 this->metroLabel1->Size = System::Drawing::Size(131, 20);
				 this->metroLabel1->TabIndex = 0;
				 this->metroLabel1->Text = L"Program Settings";
				 this->metroLabel1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 //
				 // metroTabPage2
				 //
				 this->metroTabPage2->Controls->Add(this->tableLayoutPanel5);
				 this->metroTabPage2->HorizontalScrollbarBarColor = true;
				 this->metroTabPage2->HorizontalScrollbarHighlightOnWheel = false;
				 this->metroTabPage2->HorizontalScrollbarSize = 0;
				 this->metroTabPage2->Location = System::Drawing::Point(4, 38);
				 this->metroTabPage2->Margin = System::Windows::Forms::Padding(4);
				 this->metroTabPage2->Name = L"metroTabPage2";
				 this->metroTabPage2->Size = System::Drawing::Size(949, 351);
				 this->metroTabPage2->TabIndex = 1;
				 this->metroTabPage2->Text = L"Exception Processes";
				 this->metroTabPage2->VerticalScrollbarBarColor = true;
				 this->metroTabPage2->VerticalScrollbarHighlightOnWheel = false;
				 this->metroTabPage2->VerticalScrollbarSize = 0;
				 //
				 // tableLayoutPanel5
				 //
				 this->tableLayoutPanel5->ColumnCount = 2;
				 this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 70)));
				 this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 30)));
				 this->tableLayoutPanel5->Controls->Add(this->listViewProc, 0, 0);
				 this->tableLayoutPanel5->Controls->Add(this->tableLayoutPanel6, 1, 0);
				 this->tableLayoutPanel5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel5->Location = System::Drawing::Point(0, 0);
				 this->tableLayoutPanel5->Margin = System::Windows::Forms::Padding(4);
				 this->tableLayoutPanel5->Name = L"tableLayoutPanel5";
				 this->tableLayoutPanel5->RowCount = 1;
				 this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
				 this->tableLayoutPanel5->Size = System::Drawing::Size(949, 351);
				 this->tableLayoutPanel5->TabIndex = 2;
				 //
				 // listViewProc
				 //
				 this->metroStyleExtender1->SetApplyMetroTheme(this->listViewProc, true);
				 this->listViewProc->BorderStyle = System::Windows::Forms::BorderStyle::None;
				 this->listViewProc->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {
					 this->columnHeader1,
						 this->columnHeader2
				 });
				 this->listViewProc->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->listViewProc->FullRowSelect = true;
				 this->listViewProc->GridLines = true;
				 this->listViewProc->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
				 this->listViewProc->Location = System::Drawing::Point(13, 12);
				 this->listViewProc->Margin = System::Windows::Forms::Padding(13, 12, 13, 12);
				 this->listViewProc->MultiSelect = false;
				 this->listViewProc->Name = L"listViewProc";
				 this->listViewProc->Size = System::Drawing::Size(638, 327);
				 this->listViewProc->Sorting = System::Windows::Forms::SortOrder::Ascending;
				 this->listViewProc->TabIndex = 0;
				 this->listViewProc->UseCompatibleStateImageBehavior = false;
				 this->listViewProc->View = System::Windows::Forms::View::Tile;
				 this->listViewProc->SelectedIndexChanged += gcnew System::EventHandler(this, &MetroSettingsForm::listViewProc_SelectedIndexChanged);
				 //
				 // columnHeader1
				 //
				 this->columnHeader1->Text = L"Name";
				 this->columnHeader1->Width = 97;
				 //
				 // columnHeader2
				 //
				 this->columnHeader2->Text = L"Path";
				 this->columnHeader2->Width = 382;
				 //
				 // tableLayoutPanel6
				 //
				 this->tableLayoutPanel6->BackColor = System::Drawing::Color::White;
				 this->tableLayoutPanel6->ColumnCount = 1;
				 this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 100)));
				 this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
					 27)));
				 this->tableLayoutPanel6->Controls->Add(this->tableLayoutPanel7, 0, 1);
				 this->tableLayoutPanel6->Controls->Add(this->metroLabel17, 0, 0);
				 this->tableLayoutPanel6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel6->Location = System::Drawing::Point(668, 4);
				 this->tableLayoutPanel6->Margin = System::Windows::Forms::Padding(4);
				 this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
				 this->tableLayoutPanel6->RowCount = 2;
				 this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel6->Size = System::Drawing::Size(277, 343);
				 this->tableLayoutPanel6->TabIndex = 1;
				 //
				 // tableLayoutPanel7
				 //
				 this->tableLayoutPanel7->ColumnCount = 1;
				 this->tableLayoutPanel7->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 100)));
				 this->tableLayoutPanel7->Controls->Add(this->metroButtonRemove, 0, 2);
				 this->tableLayoutPanel7->Controls->Add(this->metroButtonAddFromList, 0, 1);
				 this->tableLayoutPanel7->Controls->Add(this->metroButtonAddFromFile, 0, 0);
				 this->tableLayoutPanel7->Controls->Add(this->tableLayoutPanel8, 0, 3);
				 this->tableLayoutPanel7->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel7->Location = System::Drawing::Point(4, 175);
				 this->tableLayoutPanel7->Margin = System::Windows::Forms::Padding(4);
				 this->tableLayoutPanel7->Name = L"tableLayoutPanel7";
				 this->tableLayoutPanel7->RowCount = 4;
				 this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel7->Size = System::Drawing::Size(269, 164);
				 this->tableLayoutPanel7->TabIndex = 0;
				 //
				 // metroButtonRemove
				 //
				 this->metroButtonRemove->BackColor = System::Drawing::Color::DarkCyan;
				 this->metroButtonRemove->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroButtonRemove->Location = System::Drawing::Point(7, 88);
				 this->metroButtonRemove->Margin = System::Windows::Forms::Padding(7, 6, 7, 6);
				 this->metroButtonRemove->Name = L"metroButtonRemove";
				 this->metroButtonRemove->Size = System::Drawing::Size(255, 29);
				 this->metroButtonRemove->TabIndex = 2;
				 this->metroButtonRemove->Text = L"Remove Process";
				 this->metroButtonRemove->UseCustomBackColor = true;
				 this->metroButtonRemove->UseSelectable = true;
				 this->metroButtonRemove->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroButtonRemove_Click);
				 //
				 // metroButtonAddFromList
				 //
				 this->metroButtonAddFromList->BackColor = System::Drawing::Color::DarkCyan;
				 this->metroButtonAddFromList->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroButtonAddFromList->Location = System::Drawing::Point(7, 47);
				 this->metroButtonAddFromList->Margin = System::Windows::Forms::Padding(7, 6, 7, 6);
				 this->metroButtonAddFromList->Name = L"metroButtonAddFromList";
				 this->metroButtonAddFromList->Size = System::Drawing::Size(255, 29);
				 this->metroButtonAddFromList->TabIndex = 1;
				 this->metroButtonAddFromList->Text = L"Add current running Process";
				 this->metroButtonAddFromList->UseCustomBackColor = true;
				 this->metroButtonAddFromList->UseSelectable = true;
				 this->metroButtonAddFromList->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroButtonAddFromList_Click);
				 //
				 // metroButtonAddFromFile
				 //
				 this->metroButtonAddFromFile->BackColor = System::Drawing::Color::DarkCyan;
				 this->metroButtonAddFromFile->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroButtonAddFromFile->Location = System::Drawing::Point(7, 6);
				 this->metroButtonAddFromFile->Margin = System::Windows::Forms::Padding(7, 6, 7, 6);
				 this->metroButtonAddFromFile->Name = L"metroButtonAddFromFile";
				 this->metroButtonAddFromFile->Size = System::Drawing::Size(255, 29);
				 this->metroButtonAddFromFile->TabIndex = 0;
				 this->metroButtonAddFromFile->Text = L"Add Process From File";
				 this->metroButtonAddFromFile->UseCustomBackColor = true;
				 this->metroButtonAddFromFile->UseSelectable = true;
				 this->metroButtonAddFromFile->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroButtonAddFromFile_Click);
				 //
				 // tableLayoutPanel8
				 //
				 this->tableLayoutPanel8->ColumnCount = 2;
				 this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 50)));
				 this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 50)));
				 this->tableLayoutPanel8->Controls->Add(this->metroToggleView, 1, 0);
				 this->tableLayoutPanel8->Controls->Add(this->metroLabelView, 0, 0);
				 this->tableLayoutPanel8->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel8->Location = System::Drawing::Point(4, 127);
				 this->tableLayoutPanel8->Margin = System::Windows::Forms::Padding(4);
				 this->tableLayoutPanel8->Name = L"tableLayoutPanel8";
				 this->tableLayoutPanel8->RowCount = 1;
				 this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
				 this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 33)));
				 this->tableLayoutPanel8->Size = System::Drawing::Size(261, 33);
				 this->tableLayoutPanel8->TabIndex = 3;
				 //
				 // metroToggleView
				 //
				 this->metroToggleView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
				 this->metroToggleView->AutoSize = true;
				 this->metroToggleView->Location = System::Drawing::Point(155, 9);
				 this->metroToggleView->Margin = System::Windows::Forms::Padding(9);
				 this->metroToggleView->Name = L"metroToggleView";
				 this->metroToggleView->Size = System::Drawing::Size(80, 15);
				 this->metroToggleView->TabIndex = 3;
				 this->metroToggleView->Text = L"Aus";
				 this->metroToggleView->UseSelectable = true;
				 this->metroToggleView->CheckedChanged += gcnew System::EventHandler(this, &MetroSettingsForm::metroToggleView_CheckedChanged);
				 //
				 // metroLabelView
				 //
				 this->metroLabelView->AutoSize = true;
				 this->metroLabelView->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelView->Location = System::Drawing::Point(4, 0);
				 this->metroLabelView->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabelView->Name = L"metroLabelView";
				 this->metroLabelView->Size = System::Drawing::Size(122, 33);
				 this->metroLabelView->TabIndex = 4;
				 this->metroLabelView->Text = L"Show Details";
				 this->metroLabelView->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 //
				 // metroLabel17
				 //
				 this->metroLabel17->AutoSize = true;
				 this->metroLabel17->BackColor = System::Drawing::SystemColors::Control;
				 this->metroLabel17->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel17->FontWeight = MetroFramework::MetroLabelWeight::Regular;
				 this->metroLabel17->Location = System::Drawing::Point(4, 0);
				 this->metroLabel17->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel17->Name = L"metroLabel17";
				 this->metroLabel17->Size = System::Drawing::Size(269, 171);
				 this->metroLabel17->TabIndex = 1;
				 this->metroLabel17->Text = L"If at least one of the set up processes is running, the program will prevent the "
					 L"system from changing over to standby mode.";
				 this->metroLabel17->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroLabel17->UseCustomBackColor = true;
				 this->metroLabel17->WrapToLine = true;
				 //
				 // metroTabPage4
				 //
				 this->metroTabPage4->Controls->Add(this->tableLayoutPanel11);
				 this->metroTabPage4->HorizontalScrollbarBarColor = true;
				 this->metroTabPage4->HorizontalScrollbarHighlightOnWheel = false;
				 this->metroTabPage4->HorizontalScrollbarSize = 0;
				 this->metroTabPage4->Location = System::Drawing::Point(4, 38);
				 this->metroTabPage4->Margin = System::Windows::Forms::Padding(4);
				 this->metroTabPage4->Name = L"metroTabPage4";
				 this->metroTabPage4->Size = System::Drawing::Size(949, 351);
				 this->metroTabPage4->TabIndex = 3;
				 this->metroTabPage4->Text = L"Advanced Settings";
				 this->metroTabPage4->VerticalScrollbarBarColor = true;
				 this->metroTabPage4->VerticalScrollbarHighlightOnWheel = false;
				 this->metroTabPage4->VerticalScrollbarSize = 0;
				 //
				 // tableLayoutPanel11
				 //
				 this->tableLayoutPanel11->BackColor = System::Drawing::Color::White;
				 this->tableLayoutPanel11->ColumnCount = 2;
				 this->tableLayoutPanel11->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 50)));
				 this->tableLayoutPanel11->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 50)));
				 this->tableLayoutPanel11->Controls->Add(this->metroLabel16, 0, 1);
				 this->tableLayoutPanel11->Controls->Add(this->metroToggleUPDATES, 1, 1);
				 this->tableLayoutPanel11->Controls->Add(this->metroLabel11, 0, 0);
				 this->tableLayoutPanel11->Controls->Add(this->metroToggleAutoStart, 1, 0);
				 this->tableLayoutPanel11->Controls->Add(this->metroLabel20, 0, 3);
				 this->tableLayoutPanel11->Controls->Add(this->metroLabel18, 0, 4);
				 this->tableLayoutPanel11->Controls->Add(this->metroToggleOnTop, 1, 3);
				 this->tableLayoutPanel11->Controls->Add(this->metroToggleTutorial, 1, 4);
				 this->tableLayoutPanel11->Controls->Add(this->metroLabel22, 0, 2);
				 this->tableLayoutPanel11->Controls->Add(this->metroToggleMessages, 1, 2);
				 this->tableLayoutPanel11->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel11->Location = System::Drawing::Point(0, 0);
				 this->tableLayoutPanel11->Margin = System::Windows::Forms::Padding(4);
				 this->tableLayoutPanel11->Name = L"tableLayoutPanel11";
				 this->tableLayoutPanel11->RowCount = 6;
				 this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
				 this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
				 this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
				 this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
				 this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
				 this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
					 20)));
				 this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
					 20)));
				 this->tableLayoutPanel11->Size = System::Drawing::Size(949, 351);
				 this->tableLayoutPanel11->TabIndex = 2;
				 //
				 // metroLabel16
				 //
				 this->metroLabel16->AutoSize = true;
				 this->metroLabel16->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel16->Location = System::Drawing::Point(4, 66);
				 this->metroLabel16->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel16->Name = L"metroLabel16";
				 this->metroLabel16->Size = System::Drawing::Size(466, 66);
				 this->metroLabel16->TabIndex = 6;
				 this->metroLabel16->Text = L"Search for Updates:";
				 this->metroLabel16->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->metroToolTip1->SetToolTip(this->metroLabel16, L"  Determine if Stand-Bye! should search for updates.");
				 //
				 // metroToggleUPDATES
				 //
				 this->metroToggleUPDATES->AutoSize = true;
				 this->metroToggleUPDATES->Location = System::Drawing::Point(474, 86);
				 this->metroToggleUPDATES->Margin = System::Windows::Forms::Padding(0, 20, 0, 20);
				 this->metroToggleUPDATES->Name = L"metroToggleUPDATES";
				 this->metroToggleUPDATES->Size = System::Drawing::Size(80, 21);
				 this->metroToggleUPDATES->TabIndex = 7;
				 this->metroToggleUPDATES->Text = L"Aus";
				 this->metroToggleUPDATES->UseSelectable = true;
				 //
				 // metroLabel11
				 //
				 this->metroLabel11->AutoSize = true;
				 this->metroLabel11->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel11->Location = System::Drawing::Point(4, 0);
				 this->metroLabel11->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel11->Name = L"metroLabel11";
				 this->metroLabel11->Size = System::Drawing::Size(466, 66);
				 this->metroLabel11->TabIndex = 0;
				 this->metroLabel11->Text = L"Start with Windows:";
				 this->metroLabel11->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->metroToolTip1->SetToolTip(this->metroLabel11, L"Starts Stand-Bye! with windows.");
				 //
				 // metroToggleAutoStart
				 //
				 this->metroToggleAutoStart->AutoSize = true;
				 this->metroToggleAutoStart->Location = System::Drawing::Point(474, 20);
				 this->metroToggleAutoStart->Margin = System::Windows::Forms::Padding(0, 20, 0, 20);
				 this->metroToggleAutoStart->Name = L"metroToggleAutoStart";
				 this->metroToggleAutoStart->Size = System::Drawing::Size(80, 21);
				 this->metroToggleAutoStart->TabIndex = 1;
				 this->metroToggleAutoStart->Text = L"Aus";
				 this->metroToggleAutoStart->UseSelectable = true;
				 this->metroToggleAutoStart->CheckedChanged += gcnew System::EventHandler(this, &MetroSettingsForm::metroToggleAutoStart_CheckedChanged);
				 //
				 // metroLabel20
				 //
				 this->metroLabel20->AutoSize = true;
				 this->metroLabel20->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel20->Location = System::Drawing::Point(4, 198);
				 this->metroLabel20->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel20->Name = L"metroLabel20";
				 this->metroLabel20->Size = System::Drawing::Size(466, 66);
				 this->metroLabel20->TabIndex = 4;
				 this->metroLabel20->Text = L"Always on top:";
				 this->metroLabel20->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->metroToolTip1->SetToolTip(this->metroLabel20, L"Shows form always on top of the others.");
				 //
				 // metroLabel18
				 //
				 this->metroLabel18->AutoSize = true;
				 this->metroLabel18->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel18->Enabled = false;
				 this->metroLabel18->Location = System::Drawing::Point(4, 264);
				 this->metroLabel18->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel18->Name = L"metroLabel18";
				 this->metroLabel18->Size = System::Drawing::Size(466, 66);
				 this->metroLabel18->TabIndex = 2;
				 this->metroLabel18->Text = L"Show Tutorial:";
				 this->metroLabel18->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 //
				 // metroToggleOnTop
				 //
				 this->metroToggleOnTop->AutoSize = true;
				 this->metroToggleOnTop->Location = System::Drawing::Point(474, 218);
				 this->metroToggleOnTop->Margin = System::Windows::Forms::Padding(0, 20, 0, 20);
				 this->metroToggleOnTop->Name = L"metroToggleOnTop";
				 this->metroToggleOnTop->Size = System::Drawing::Size(80, 21);
				 this->metroToggleOnTop->TabIndex = 5;
				 this->metroToggleOnTop->Text = L"Aus";
				 this->metroToggleOnTop->UseSelectable = true;
				 this->metroToggleOnTop->CheckedChanged += gcnew System::EventHandler(this, &MetroSettingsForm::metroToggleOnTop_CheckedChanged);
				 //
				 // metroToggleTutorial
				 //
				 this->metroToggleTutorial->AutoSize = true;
				 this->metroToggleTutorial->Enabled = false;
				 this->metroToggleTutorial->Location = System::Drawing::Point(474, 284);
				 this->metroToggleTutorial->Margin = System::Windows::Forms::Padding(0, 20, 0, 20);
				 this->metroToggleTutorial->Name = L"metroToggleTutorial";
				 this->metroToggleTutorial->Size = System::Drawing::Size(80, 21);
				 this->metroToggleTutorial->TabIndex = 3;
				 this->metroToggleTutorial->Text = L"Aus";
				 this->metroToggleTutorial->UseSelectable = true;
				 //
				 // metroLabel22
				 //
				 this->metroLabel22->AutoSize = true;
				 this->metroLabel22->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel22->Location = System::Drawing::Point(4, 132);
				 this->metroLabel22->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel22->Name = L"metroLabel22";
				 this->metroLabel22->Size = System::Drawing::Size(466, 66);
				 this->metroLabel22->TabIndex = 8;
				 this->metroLabel22->Text = L"Show Messages";
				 this->metroLabel22->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->metroToolTip1->SetToolTip(this->metroLabel22, L"    Determine if Stand-Bye! should show messages from the icon (for ex. presentat"
					 L"ion mode enabled)");
				 //
				 // metroToggleMessages
				 //
				 this->metroToggleMessages->AutoSize = true;
				 this->metroToggleMessages->Location = System::Drawing::Point(474, 152);
				 this->metroToggleMessages->Margin = System::Windows::Forms::Padding(0, 20, 0, 20);
				 this->metroToggleMessages->Name = L"metroToggleMessages";
				 this->metroToggleMessages->Size = System::Drawing::Size(80, 21);
				 this->metroToggleMessages->TabIndex = 9;
				 this->metroToggleMessages->Text = L"Aus";
				 this->metroToggleMessages->UseSelectable = true;
				 //
				 // metroTabPage3
				 //
				 this->metroTabPage3->AutoScroll = true;
				 this->metroTabPage3->Controls->Add(this->tableLayoutPanel9);
				 this->metroTabPage3->Controls->Add(this->metroLabel15);
				 this->metroTabPage3->HorizontalScrollbar = true;
				 this->metroTabPage3->HorizontalScrollbarBarColor = true;
				 this->metroTabPage3->HorizontalScrollbarHighlightOnWheel = false;
				 this->metroTabPage3->HorizontalScrollbarSize = 6;
				 this->metroTabPage3->Location = System::Drawing::Point(4, 38);
				 this->metroTabPage3->Margin = System::Windows::Forms::Padding(4);
				 this->metroTabPage3->Name = L"metroTabPage3";
				 this->metroTabPage3->Size = System::Drawing::Size(949, 351);
				 this->metroTabPage3->TabIndex = 2;
				 this->metroTabPage3->Text = L"About";
				 this->metroTabPage3->VerticalScrollbar = true;
				 this->metroTabPage3->VerticalScrollbarBarColor = true;
				 this->metroTabPage3->VerticalScrollbarHighlightOnWheel = false;
				 this->metroTabPage3->VerticalScrollbarSize = 7;
				 //
				 // tableLayoutPanel9
				 //
				 this->tableLayoutPanel9->ColumnCount = 2;
				 this->tableLayoutPanel9->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 50)));
				 this->tableLayoutPanel9->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 50)));
				 this->tableLayoutPanel9->Controls->Add(this->metroTileHomepage, 0, 0);
				 this->tableLayoutPanel9->Controls->Add(this->metroTileGithub, 1, 0);
				 this->tableLayoutPanel9->Location = System::Drawing::Point(4, 4);
				 this->tableLayoutPanel9->Margin = System::Windows::Forms::Padding(4);
				 this->tableLayoutPanel9->Name = L"tableLayoutPanel9";
				 this->tableLayoutPanel9->RowCount = 1;
				 this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
				 this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 85)));
				 this->tableLayoutPanel9->Size = System::Drawing::Size(947, 85);
				 this->tableLayoutPanel9->TabIndex = 2;
				 //
				 // metroTileHomepage
				 //
				 this->metroTileHomepage->ActiveControl = nullptr;
				 this->metroTileHomepage->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroTileHomepage->Location = System::Drawing::Point(4, 4);
				 this->metroTileHomepage->Margin = System::Windows::Forms::Padding(4);
				 this->metroTileHomepage->Name = L"metroTileHomepage";
				 this->metroTileHomepage->Size = System::Drawing::Size(465, 77);
				 this->metroTileHomepage->Style = MetroFramework::MetroColorStyle::Orange;
				 this->metroTileHomepage->TabIndex = 0;
				 this->metroTileHomepage->Text = L"Visit our Homepage!";
				 this->metroTileHomepage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroTileHomepage->UseSelectable = true;
				 this->metroTileHomepage->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroTileHomepage_Click);
				 //
				 // metroTileGithub
				 //
				 this->metroTileGithub->ActiveControl = nullptr;
				 this->metroTileGithub->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroTileGithub->Location = System::Drawing::Point(477, 4);
				 this->metroTileGithub->Margin = System::Windows::Forms::Padding(4);
				 this->metroTileGithub->Name = L"metroTileGithub";
				 this->metroTileGithub->Size = System::Drawing::Size(466, 77);
				 this->metroTileGithub->TabIndex = 1;
				 this->metroTileGithub->Text = L"Visit us on Github!";
				 this->metroTileGithub->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroTileGithub->UseSelectable = true;
				 this->metroTileGithub->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroTileGithub_Click);
				 //
				 // metroLabel15
				 //
				 this->metroLabel15->Location = System::Drawing::Point(8, 92);
				 this->metroLabel15->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel15->Name = L"metroLabel15";
				 this->metroLabel15->Size = System::Drawing::Size(921, 1274);
				 this->metroLabel15->TabIndex = 1;
				 this->metroLabel15->Text = resources->GetString(L"metroLabel15.Text");
				 this->metroLabel15->WrapToLine = true;
				 //
				 // tableLayoutPanel1
				 //
				 this->tableLayoutPanel1->AutoSize = true;
				 this->tableLayoutPanel1->ColumnCount = 1;
				 this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 100)));
				 this->tableLayoutPanel1->Controls->Add(this->metroTabControl1, 0, 0);
				 this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel4, 0, 1);
				 this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel1->Location = System::Drawing::Point(0, 74);
				 this->tableLayoutPanel1->Margin = System::Windows::Forms::Padding(13, 12, 13, 12);
				 this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
				 this->tableLayoutPanel1->RowCount = 2;
				 this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
				 this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 74)));
				 this->tableLayoutPanel1->Size = System::Drawing::Size(983, 491);
				 this->tableLayoutPanel1->TabIndex = 1;
				 //
				 // tableLayoutPanel4
				 //
				 this->tableLayoutPanel4->ColumnCount = 5;
				 this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 20)));
				 this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 20)));
				 this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 20)));
				 this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 20)));
				 this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 20)));
				 this->tableLayoutPanel4->Controls->Add(this->metroButtonOK, 4, 0);
				 this->tableLayoutPanel4->Controls->Add(this->metroButtonCancel, 3, 0);
				 this->tableLayoutPanel4->Controls->Add(this->metroLabel12, 0, 0);
				 this->tableLayoutPanel4->Controls->Add(this->metroLinkHomepage, 1, 0);
				 this->tableLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel4->Location = System::Drawing::Point(4, 421);
				 this->tableLayoutPanel4->Margin = System::Windows::Forms::Padding(4);
				 this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
				 this->tableLayoutPanel4->RowCount = 1;
				 this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
				 this->tableLayoutPanel4->Size = System::Drawing::Size(975, 66);
				 this->tableLayoutPanel4->TabIndex = 1;
				 //
				 // metroButtonOK
				 //
				 this->metroButtonOK->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroButtonOK->FontSize = MetroFramework::MetroButtonSize::Medium;
				 this->metroButtonOK->Location = System::Drawing::Point(793, 12);
				 this->metroButtonOK->Margin = System::Windows::Forms::Padding(13, 12, 13, 12);
				 this->metroButtonOK->Name = L"metroButtonOK";
				 this->metroButtonOK->Size = System::Drawing::Size(169, 42);
				 this->metroButtonOK->TabIndex = 1;
				 this->metroButtonOK->Text = L"OK";
				 this->metroButtonOK->UseSelectable = true;
				 this->metroButtonOK->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroButtonOK_Click);
				 //
				 // metroButtonCancel
				 //
				 this->metroButtonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				 this->metroButtonCancel->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroButtonCancel->Location = System::Drawing::Point(598, 12);
				 this->metroButtonCancel->Margin = System::Windows::Forms::Padding(13, 12, 13, 12);
				 this->metroButtonCancel->Name = L"metroButtonCancel";
				 this->metroButtonCancel->Size = System::Drawing::Size(169, 42);
				 this->metroButtonCancel->TabIndex = 0;
				 this->metroButtonCancel->Text = L"Cancel";
				 this->metroButtonCancel->UseSelectable = true;
				 this->metroButtonCancel->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroButtonCancel_Click);
				 //
				 // metroLabel12
				 //
				 this->metroLabel12->AutoSize = true;
				 this->metroLabel12->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel12->FontSize = MetroFramework::MetroLabelSize::Small;
				 this->metroLabel12->Location = System::Drawing::Point(4, 0);
				 this->metroLabel12->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->metroLabel12->Name = L"metroLabel12";
				 this->metroLabel12->Size = System::Drawing::Size(187, 66);
				 this->metroLabel12->TabIndex = 2;
				 this->metroLabel12->Text = L"v0.5.2.0\n© Florian Baader, Stephan Le, Matthias Weirich";
				 this->metroLabel12->TextAlign = System::Drawing::ContentAlignment::BottomLeft;
				 this->metroLabel12->WrapToLine = true;
				 //
				 // metroLinkHomepage
				 //
				 this->metroLinkHomepage->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLinkHomepage->Location = System::Drawing::Point(199, 4);
				 this->metroLinkHomepage->Margin = System::Windows::Forms::Padding(4);
				 this->metroLinkHomepage->Name = L"metroLinkHomepage";
				 this->metroLinkHomepage->Size = System::Drawing::Size(187, 58);
				 this->metroLinkHomepage->TabIndex = 3;
				 this->metroLinkHomepage->Text = L"www.stand-bye.de";
				 this->metroLinkHomepage->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
				 this->metroToolTip1->SetToolTip(this->metroLinkHomepage, L"Visit our homepage!");
				 this->metroLinkHomepage->UseSelectable = true;
				 this->metroLinkHomepage->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroLinkHomepage_Click);
				 //
				 // timerRefresh
				 //
				 this->timerRefresh->Interval = 1000;
				 this->timerRefresh->Tick += gcnew System::EventHandler(this, &MetroSettingsForm::timerUIRefresh_Tick);
				 //
				 // metroStyleManager1
				 //
				 this->metroStyleManager1->Owner = this;
				 this->metroStyleManager1->Style = MetroFramework::MetroColorStyle::Teal;
				 //
				 // metroToolTip1
				 //
				 this->metroToolTip1->AutoPopDelay = 5000;
				 this->metroToolTip1->InitialDelay = 100;
				 this->metroToolTip1->ReshowDelay = 100;
				 this->metroToolTip1->Style = MetroFramework::MetroColorStyle::Blue;
				 this->metroToolTip1->StyleManager = nullptr;
				 this->metroToolTip1->Theme = MetroFramework::MetroThemeStyle::Light;
				 //
				 // MetroSettingsForm
				 //
				 this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->BackImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackImage")));
				 this->BackImagePadding = System::Windows::Forms::Padding(0, 5, 0, 0);
				 this->BackMaxSize = 760;
				 this->BorderStyle = MetroFramework::Forms::MetroFormBorderStyle::FixedSingle;
				 this->CancelButton = this->metroButtonCancel;
				 this->ClientSize = System::Drawing::Size(983, 565);
				 this->Controls->Add(this->tableLayoutPanel1);
				 this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
				 this->Margin = System::Windows::Forms::Padding(4);
				 this->MaximizeBox = false;
				 this->MinimizeBox = false;
				 this->Name = L"MetroSettingsForm";
				 this->Padding = System::Windows::Forms::Padding(0, 74, 0, 0);
				 this->Resizable = false;
				 this->ShadowType = MetroFramework::Forms::MetroFormShadowType::DropShadow;
				 this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
				 this->Style = MetroFramework::MetroColorStyle::Green;
				 this->Closing += gcnew System::ComponentModel::CancelEventHandler(this, &MetroSettingsForm::OnClosing);
				 this->Load += gcnew System::EventHandler(this, &MetroSettingsForm::MetroSettingsForm_Load);
				 this->VisibleChanged += gcnew System::EventHandler(this, &MetroSettingsForm::OnVisibleChanged);
				 this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MetroSettingsForm::OnKeyDown);
				 this->metroTabControl1->ResumeLayout(false);
				 this->metroTabPage1->ResumeLayout(false);
				 this->metroTabPage1->PerformLayout();
				 this->tableLayoutPanel3->ResumeLayout(false);
				 this->tableLayoutPanel3->PerformLayout();
				 this->tableLayoutPanel10->ResumeLayout(false);
				 this->tableLayoutPanel10->PerformLayout();
				 this->tableLayoutPanel12->ResumeLayout(false);
				 this->tableLayoutPanel12->PerformLayout();
				 this->metroTabPage2->ResumeLayout(false);
				 this->tableLayoutPanel5->ResumeLayout(false);
				 this->tableLayoutPanel6->ResumeLayout(false);
				 this->tableLayoutPanel6->PerformLayout();
				 this->tableLayoutPanel7->ResumeLayout(false);
				 this->tableLayoutPanel8->ResumeLayout(false);
				 this->tableLayoutPanel8->PerformLayout();
				 this->metroTabPage4->ResumeLayout(false);
				 this->tableLayoutPanel11->ResumeLayout(false);
				 this->tableLayoutPanel11->PerformLayout();
				 this->metroTabPage3->ResumeLayout(false);
				 this->tableLayoutPanel9->ResumeLayout(false);
				 this->tableLayoutPanel1->ResumeLayout(false);
				 this->tableLayoutPanel4->ResumeLayout(false);
				 this->tableLayoutPanel4->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->metroStyleManager1))->EndInit();
				 this->ResumeLayout(false);
				 this->PerformLayout();
			 }
#pragma endregion
	private:
		//Main
		System::Void MetroSettingsForm_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void metroTrackBarRAM_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e);
		System::Void metroTrackBarCPU_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e);
		System::Void metroButtonOK_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void metroButtonCancel_Click(System::Object^  sender, System::EventArgs^  e);

		//Processes
		System::Void metroButtonAddFromFile_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void metroButtonAddFromList_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void metroButtonRemove_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void listViewProc_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void metroToggleView_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void metroToggleOnTop_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void metroTogglePresMode_CheckedChanged(System::Object^, System::EventArgs^);
		void refreshIcons();

		//Settings
		System::Void metroToggleAutoStart_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void writeSettings();

		//Timer
		System::Void timerUIRefresh_Tick(System::Object^  sender, System::EventArgs^  e);
		void forceRefreshUI();

		//Others
		System::Void metroTileHomepage_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void metroTileGithub_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void metroLinkHomepage_Click(System::Object^  sender, System::EventArgs^  e);
		void changeLabelBackgroundColor(MetroFramework::Controls::MetroLabel^ label, double SettingsValue, double readValue);

		//Formatters
		double getTextBoxValueAsDouble(MetroFramework::Controls::MetroTextBox^ box);
		void setTextBoxValue(MetroFramework::Controls::MetroTextBox^ box, double value);
		System::Void ReformatTextBoxValueOnReturn(System::Object ^, System::Windows::Forms::KeyEventArgs ^);
		void OnVisibleChanged(System::Object ^sender, System::EventArgs ^e);
		void OnClosing(System::Object ^sender, System::ComponentModel::CancelEventArgs ^e);
		void OnKeyDown(System::Object ^sender, System::Windows::Forms::KeyEventArgs ^e);
	};
}
