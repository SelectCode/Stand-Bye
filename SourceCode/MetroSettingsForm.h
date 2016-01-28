#pragma once
#include "BasicFunc.h"
#include "SystemMetricWatcher.h"
#include "SettingsProvider.h"
#include "ProcessItem.h"
#include "ProcessSelectionForm.h"
#include <winuser.h>
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace SmartLogout {
	/// <summary>
	/// Provides a Form to set up the Settings for the Application
	/// </summary>
	public ref class MetroSettingsForm : public MetroFramework::Forms::MetroForm
	{
	private:
		SystemAccess^ SysAcs;
		SettingsProvider* STP;
		SystemMetricWatcher^ system_watcher;
		Drawing::Color lightGreen, darkGreen, lightRed, darkRed;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel3;
	private: MetroFramework::Controls::MetroLabel^  metroLabel1;
	private: MetroFramework::Controls::MetroLabel^  metroLabel2;

	private: MetroFramework::Controls::MetroLabel^  metroLabel4;
	private: MetroFramework::Controls::MetroLabel^  metroLabel5;
	private: MetroFramework::Controls::MetroLabel^  metroLabel6;
	private: MetroFramework::Controls::MetroLabel^  metroLabel7;
	private: MetroFramework::Controls::MetroLabel^  metroLabel8;

	private: MetroFramework::Controls::MetroLabel^  metroLabel10;
	private: MetroFramework::Controls::MetroLabel^  metroLabelCPUPer;
	private: MetroFramework::Controls::MetroLabel^  metroLabelRAMPer;
	private: MetroFramework::Controls::MetroLabel^  metroLabel13;
	private: MetroFramework::Controls::MetroLabel^  metroLabel14;
	private: MetroFramework::Controls::MetroLabel^  metroLabelCurCPU;
	private: MetroFramework::Controls::MetroLabel^  metroLabelCurRAM;
	private: MetroFramework::Controls::MetroLabel^  metroLabelCurHDD;
	private: MetroFramework::Controls::MetroLabel^  metroLabelCurNET;

	private: MetroFramework::Controls::MetroTrackBar^  metroTrackBarCPU;
	private: MetroFramework::Controls::MetroTrackBar^  metroTrackBarRAM;
	private: MetroFramework::Controls::MetroTextBox^  metroTextBoxHDD;
	private: MetroFramework::Controls::MetroTextBox^  metroTextBoxNET;
	private: MetroFramework::Controls::MetroToggle^  metroToggleCPU;
	private: MetroFramework::Controls::MetroToggle^  metroToggleRAM;
	private: MetroFramework::Controls::MetroToggle^  metroToggleHDD;
	private: MetroFramework::Controls::MetroToggle^  metroToggleNET;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel5;
	private: System::Windows::Forms::ListView^  listViewProc;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel6;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel7;
	private: MetroFramework::Controls::MetroButton^  metroButtonRemove;
	private: MetroFramework::Controls::MetroButton^  metroButtonAddFromList;
	private: MetroFramework::Controls::MetroButton^  metroButtonAddFromFile;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel8;
	private: MetroFramework::Controls::MetroToggle^  metroToggleView;
	private: MetroFramework::Controls::MetroLabel^  metroLabelView;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;

	private: MetroFramework::Components::MetroStyleManager^  metroStyleManager1;
	private: MetroFramework::Components::MetroStyleExtender^  metroStyleExtender1;
	private: MetroFramework::Controls::MetroTile^  metroTileGithub;

	private: MetroFramework::Controls::MetroTile^  metroTileHomepage;

	private: MetroFramework::Controls::MetroLabel^  metroLabel3;
	private: MetroFramework::Components::MetroToolTip^  metroToolTip1;
	private: MetroFramework::Controls::MetroTabPage^  metroTabPage4;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel11;
	private: MetroFramework::Controls::MetroLabel^  metroLabel11;
	private: MetroFramework::Controls::MetroToggle^  metroToggleAutoStart;
	private: MetroFramework::Controls::MetroLabel^  metroLabel12;
	private: MetroFramework::Controls::MetroLabel^  metroLabel15;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel9;
	private: MetroFramework::Controls::MetroLabel^  metroLabel16;
	private: MetroFramework::Controls::MetroLabel^  metroLabel17;
	private: MetroFramework::Controls::MetroLabel^  metroLabel18;
	private: MetroFramework::Controls::MetroToggle^  metroToggleTutorial;
	private: MetroFramework::Controls::MetroLink^  metroLinkHomepage;

	private: MetroFramework::Controls::MetroTextBox^  metroTextBoxWAITTIME;

	public:
		MetroSettingsForm(SystemMetricWatcher^ smw, SettingsProvider* pro)
		{
			STP = pro;
			SysAcs = gcnew SystemAccess(STP);
			InitializeComponent();
			this->MinimizeBox = false;
			this->MaximizeBox = false;
			system_watcher = smw;
			lightGreen = ColorTranslator::FromHtml("#a5d6a7");
			darkGreen = ColorTranslator::FromHtml("#33691e");
			lightRed = ColorTranslator::FromHtml("#ef9a9a");
			darkRed = ColorTranslator::FromHtml(" #f44336");
		}

	protected:
		~MetroSettingsForm()
		{
			delete SysAcs;
			if (components)
			{
				delete components;
			}
		}
	private: MetroFramework::Controls::MetroTabControl^  metroTabControl1;
	protected:
	private: MetroFramework::Controls::MetroTabPage^  metroTabPage1;
	private: MetroFramework::Controls::MetroTabPage^  metroTabPage2;
	private: MetroFramework::Controls::MetroTabPage^  metroTabPage3;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel4;
	private: MetroFramework::Controls::MetroButton^  metroButtonOK;
	private: MetroFramework::Controls::MetroButton^  metroButtonCancel;
	private: System::Windows::Forms::Timer^  timerRefresh;

	private: System::ComponentModel::IContainer^  components;
	private:

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MetroSettingsForm::typeid));
			this->metroTabControl1 = (gcnew MetroFramework::Controls::MetroTabControl());
			this->metroTabPage1 = (gcnew MetroFramework::Controls::MetroTabPage());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->metroLabel1 = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroLabel2 = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroLabel4 = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroLabel5 = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroLabel6 = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroLabel7 = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroLabel8 = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroLabel10 = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroLabelCPUPer = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroLabelRAMPer = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroLabel13 = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroLabel14 = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroLabelCurCPU = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroLabelCurRAM = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroLabelCurHDD = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroLabelCurNET = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroTrackBarCPU = (gcnew MetroFramework::Controls::MetroTrackBar());
			this->metroTrackBarRAM = (gcnew MetroFramework::Controls::MetroTrackBar());
			this->metroTextBoxHDD = (gcnew MetroFramework::Controls::MetroTextBox());
			this->metroTextBoxNET = (gcnew MetroFramework::Controls::MetroTextBox());
			this->metroToggleCPU = (gcnew MetroFramework::Controls::MetroToggle());
			this->metroToggleRAM = (gcnew MetroFramework::Controls::MetroToggle());
			this->metroToggleHDD = (gcnew MetroFramework::Controls::MetroToggle());
			this->metroToggleNET = (gcnew MetroFramework::Controls::MetroToggle());
			this->metroTextBoxWAITTIME = (gcnew MetroFramework::Controls::MetroTextBox());
			this->metroLabel3 = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroLabel16 = (gcnew MetroFramework::Controls::MetroLabel());
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
			this->metroLabel11 = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroToggleAutoStart = (gcnew MetroFramework::Controls::MetroToggle());
			this->metroLabel18 = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroToggleTutorial = (gcnew MetroFramework::Controls::MetroToggle());
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
			this->tableLayoutPanel2->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
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
			this->metroTabControl1->Location = System::Drawing::Point(10, 10);
			this->metroTabControl1->Margin = System::Windows::Forms::Padding(10);
			this->metroTabControl1->Name = L"metroTabControl1";
			this->metroTabControl1->SelectedIndex = 0;
			this->metroTabControl1->Size = System::Drawing::Size(726, 316);
			this->metroTabControl1->TabIndex = 0;
			this->metroTabControl1->UseSelectable = true;
			//
			// metroTabPage1
			//
			this->metroTabPage1->BackColor = System::Drawing::Color::White;
			this->metroTabPage1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->metroTabPage1->Controls->Add(this->tableLayoutPanel2);
			this->metroTabPage1->HorizontalScrollbarBarColor = false;
			this->metroTabPage1->HorizontalScrollbarHighlightOnWheel = false;
			this->metroTabPage1->HorizontalScrollbarSize = 0;
			this->metroTabPage1->Location = System::Drawing::Point(4, 38);
			this->metroTabPage1->Name = L"metroTabPage1";
			this->metroTabPage1->Size = System::Drawing::Size(718, 274);
			this->metroTabPage1->Style = MetroFramework::MetroColorStyle::Green;
			this->metroTabPage1->TabIndex = 0;
			this->metroTabPage1->Text = L"Settings";
			this->metroTabPage1->VerticalScrollbarBarColor = false;
			this->metroTabPage1->VerticalScrollbarHighlightOnWheel = false;
			this->metroTabPage1->VerticalScrollbarSize = 0;
			//
			// tableLayoutPanel2
			//
			this->tableLayoutPanel2->ColumnCount = 1;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel2->Controls->Add(this->tableLayoutPanel3, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->metroLabel16, 0, 0);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel2->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 15)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 85)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(716, 272);
			this->tableLayoutPanel2->TabIndex = 4;
			//
			// tableLayoutPanel3
			//
			this->tableLayoutPanel3->AutoSize = true;
			this->tableLayoutPanel3->BackColor = System::Drawing::Color::White;
			this->tableLayoutPanel3->ColumnCount = 6;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				80)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				80)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				120)));
			this->tableLayoutPanel3->Controls->Add(this->metroLabel1, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->metroLabel2, 0, 2);
			this->tableLayoutPanel3->Controls->Add(this->metroLabel4, 2, 1);
			this->tableLayoutPanel3->Controls->Add(this->metroLabel5, 2, 3);
			this->tableLayoutPanel3->Controls->Add(this->metroLabel6, 2, 4);
			this->tableLayoutPanel3->Controls->Add(this->metroLabel7, 2, 5);
			this->tableLayoutPanel3->Controls->Add(this->metroLabel8, 2, 6);
			this->tableLayoutPanel3->Controls->Add(this->metroLabel10, 4, 1);
			this->tableLayoutPanel3->Controls->Add(this->metroLabelCPUPer, 4, 3);
			this->tableLayoutPanel3->Controls->Add(this->metroLabelRAMPer, 4, 4);
			this->tableLayoutPanel3->Controls->Add(this->metroLabel13, 4, 5);
			this->tableLayoutPanel3->Controls->Add(this->metroLabel14, 4, 6);
			this->tableLayoutPanel3->Controls->Add(this->metroLabelCurCPU, 5, 3);
			this->tableLayoutPanel3->Controls->Add(this->metroLabelCurRAM, 5, 4);
			this->tableLayoutPanel3->Controls->Add(this->metroLabelCurHDD, 5, 5);
			this->tableLayoutPanel3->Controls->Add(this->metroLabelCurNET, 5, 6);
			this->tableLayoutPanel3->Controls->Add(this->metroTrackBarCPU, 3, 3);
			this->tableLayoutPanel3->Controls->Add(this->metroTrackBarRAM, 3, 4);
			this->tableLayoutPanel3->Controls->Add(this->metroTextBoxHDD, 3, 5);
			this->tableLayoutPanel3->Controls->Add(this->metroTextBoxNET, 3, 6);
			this->tableLayoutPanel3->Controls->Add(this->metroToggleCPU, 1, 3);
			this->tableLayoutPanel3->Controls->Add(this->metroToggleRAM, 1, 4);
			this->tableLayoutPanel3->Controls->Add(this->metroToggleHDD, 1, 5);
			this->tableLayoutPanel3->Controls->Add(this->metroToggleNET, 1, 6);
			this->tableLayoutPanel3->Controls->Add(this->metroTextBoxWAITTIME, 3, 1);
			this->tableLayoutPanel3->Controls->Add(this->metroLabel3, 5, 2);
			this->tableLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel3->Location = System::Drawing::Point(10, 50);
			this->tableLayoutPanel3->Margin = System::Windows::Forms::Padding(10);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 7;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(696, 212);
			this->tableLayoutPanel3->TabIndex = 1;
			//
			// metroLabel1
			//
			this->metroLabel1->AutoSize = true;
			this->tableLayoutPanel3->SetColumnSpan(this->metroLabel1, 3);
			this->metroLabel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLabel1->FontWeight = MetroFramework::MetroLabelWeight::Regular;
			this->metroLabel1->Location = System::Drawing::Point(3, 0);
			this->metroLabel1->Name = L"metroLabel1";
			this->metroLabel1->Size = System::Drawing::Size(299, 30);
			this->metroLabel1->TabIndex = 0;
			this->metroLabel1->Text = L"Program Settings";
			this->metroLabel1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			//
			// metroLabel2
			//
			this->metroLabel2->AutoSize = true;
			this->tableLayoutPanel3->SetColumnSpan(this->metroLabel2, 3);
			this->metroLabel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLabel2->FontWeight = MetroFramework::MetroLabelWeight::Regular;
			this->metroLabel2->Location = System::Drawing::Point(3, 60);
			this->metroLabel2->Name = L"metroLabel2";
			this->metroLabel2->Size = System::Drawing::Size(299, 30);
			this->metroLabel2->TabIndex = 1;
			this->metroLabel2->Text = L"System Usage Thresholds";
			this->metroLabel2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			//
			// metroLabel4
			//
			this->metroLabel4->AutoSize = true;
			this->metroLabel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLabel4->Location = System::Drawing::Point(169, 30);
			this->metroLabel4->Name = L"metroLabel4";
			this->metroLabel4->Size = System::Drawing::Size(133, 30);
			this->metroLabel4->TabIndex = 3;
			this->metroLabel4->Text = L"activate standby after";
			this->metroLabel4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			//
			// metroLabel5
			//
			this->metroLabel5->AutoSize = true;
			this->metroLabel5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLabel5->Location = System::Drawing::Point(169, 90);
			this->metroLabel5->Name = L"metroLabel5";
			this->metroLabel5->Size = System::Drawing::Size(133, 30);
			this->metroLabel5->TabIndex = 4;
			this->metroLabel5->Text = L"CPU Threshold";
			this->metroLabel5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			//
			// metroLabel6
			//
			this->metroLabel6->AutoSize = true;
			this->metroLabel6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLabel6->Location = System::Drawing::Point(169, 120);
			this->metroLabel6->Name = L"metroLabel6";
			this->metroLabel6->Size = System::Drawing::Size(133, 30);
			this->metroLabel6->TabIndex = 5;
			this->metroLabel6->Text = L"RAM Threshold";
			this->metroLabel6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			//
			// metroLabel7
			//
			this->metroLabel7->AutoSize = true;
			this->metroLabel7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLabel7->Location = System::Drawing::Point(169, 150);
			this->metroLabel7->Name = L"metroLabel7";
			this->metroLabel7->Size = System::Drawing::Size(133, 30);
			this->metroLabel7->TabIndex = 6;
			this->metroLabel7->Text = L"HDD Threshold";
			this->metroLabel7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			//
			// metroLabel8
			//
			this->metroLabel8->AutoSize = true;
			this->metroLabel8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLabel8->Location = System::Drawing::Point(169, 180);
			this->metroLabel8->Name = L"metroLabel8";
			this->metroLabel8->Size = System::Drawing::Size(133, 32);
			this->metroLabel8->TabIndex = 7;
			this->metroLabel8->Text = L"Network Threshold";
			this->metroLabel8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			//
			// metroLabel10
			//
			this->metroLabel10->AutoSize = true;
			this->metroLabel10->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLabel10->Location = System::Drawing::Point(499, 30);
			this->metroLabel10->Name = L"metroLabel10";
			this->metroLabel10->Size = System::Drawing::Size(74, 30);
			this->metroLabel10->TabIndex = 9;
			this->metroLabel10->Text = L"min";
			this->metroLabel10->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			//
			// metroLabelCPUPer
			//
			this->metroLabelCPUPer->AutoSize = true;
			this->metroLabelCPUPer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLabelCPUPer->Location = System::Drawing::Point(499, 90);
			this->metroLabelCPUPer->Name = L"metroLabelCPUPer";
			this->metroLabelCPUPer->Size = System::Drawing::Size(74, 30);
			this->metroLabelCPUPer->TabIndex = 10;
			this->metroLabelCPUPer->Text = L"%";
			this->metroLabelCPUPer->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			//
			// metroLabelRAMPer
			//
			this->metroLabelRAMPer->AutoSize = true;
			this->metroLabelRAMPer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLabelRAMPer->Location = System::Drawing::Point(499, 120);
			this->metroLabelRAMPer->Name = L"metroLabelRAMPer";
			this->metroLabelRAMPer->Size = System::Drawing::Size(74, 30);
			this->metroLabelRAMPer->TabIndex = 11;
			this->metroLabelRAMPer->Text = L"%";
			this->metroLabelRAMPer->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			//
			// metroLabel13
			//
			this->metroLabel13->AutoSize = true;
			this->metroLabel13->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLabel13->Location = System::Drawing::Point(499, 150);
			this->metroLabel13->Name = L"metroLabel13";
			this->metroLabel13->Size = System::Drawing::Size(74, 30);
			this->metroLabel13->TabIndex = 12;
			this->metroLabel13->Text = L"MBit/s";
			this->metroLabel13->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			//
			// metroLabel14
			//
			this->metroLabel14->AutoSize = true;
			this->metroLabel14->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLabel14->Location = System::Drawing::Point(499, 180);
			this->metroLabel14->Name = L"metroLabel14";
			this->metroLabel14->Size = System::Drawing::Size(74, 32);
			this->metroLabel14->TabIndex = 13;
			this->metroLabel14->Text = L"MBit/s";
			this->metroLabel14->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			//
			// metroLabelCurCPU
			//
			this->metroLabelCurCPU->AutoSize = true;
			this->metroLabelCurCPU->BackColor = System::Drawing::SystemColors::Control;
			this->metroLabelCurCPU->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLabelCurCPU->ForeColor = System::Drawing::SystemColors::ControlText;
			this->metroLabelCurCPU->Location = System::Drawing::Point(579, 90);
			this->metroLabelCurCPU->Name = L"metroLabelCurCPU";
			this->metroLabelCurCPU->Size = System::Drawing::Size(114, 30);
			this->metroLabelCurCPU->TabIndex = 14;
			this->metroLabelCurCPU->Text = L"-";
			this->metroLabelCurCPU->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->metroLabelCurCPU->UseCustomBackColor = true;
			this->metroLabelCurCPU->UseCustomForeColor = true;
			//
			// metroLabelCurRAM
			//
			this->metroLabelCurRAM->AutoSize = true;
			this->metroLabelCurRAM->BackColor = System::Drawing::SystemColors::Control;
			this->metroLabelCurRAM->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLabelCurRAM->Location = System::Drawing::Point(579, 120);
			this->metroLabelCurRAM->Name = L"metroLabelCurRAM";
			this->metroLabelCurRAM->Size = System::Drawing::Size(114, 30);
			this->metroLabelCurRAM->TabIndex = 15;
			this->metroLabelCurRAM->Text = L"-";
			this->metroLabelCurRAM->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->metroLabelCurRAM->UseCustomBackColor = true;
			this->metroLabelCurRAM->UseCustomForeColor = true;
			//
			// metroLabelCurHDD
			//
			this->metroLabelCurHDD->AutoSize = true;
			this->metroLabelCurHDD->BackColor = System::Drawing::SystemColors::Control;
			this->metroLabelCurHDD->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLabelCurHDD->Location = System::Drawing::Point(579, 150);
			this->metroLabelCurHDD->Name = L"metroLabelCurHDD";
			this->metroLabelCurHDD->Size = System::Drawing::Size(114, 30);
			this->metroLabelCurHDD->TabIndex = 16;
			this->metroLabelCurHDD->Text = L"-";
			this->metroLabelCurHDD->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->metroLabelCurHDD->UseCustomBackColor = true;
			this->metroLabelCurHDD->UseCustomForeColor = true;
			//
			// metroLabelCurNET
			//
			this->metroLabelCurNET->AutoSize = true;
			this->metroLabelCurNET->BackColor = System::Drawing::SystemColors::Control;
			this->metroLabelCurNET->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLabelCurNET->Location = System::Drawing::Point(579, 180);
			this->metroLabelCurNET->Name = L"metroLabelCurNET";
			this->metroLabelCurNET->Size = System::Drawing::Size(114, 32);
			this->metroLabelCurNET->TabIndex = 17;
			this->metroLabelCurNET->Text = L"-";
			this->metroLabelCurNET->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->metroLabelCurNET->UseCustomBackColor = true;
			this->metroLabelCurNET->UseCustomForeColor = true;
			//
			// metroTrackBarCPU
			//
			this->metroTrackBarCPU->BackColor = System::Drawing::Color::Transparent;
			this->metroTrackBarCPU->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroTrackBarCPU->Location = System::Drawing::Point(308, 93);
			this->metroTrackBarCPU->Name = L"metroTrackBarCPU";
			this->metroTrackBarCPU->Size = System::Drawing::Size(185, 24);
			this->metroTrackBarCPU->TabIndex = 19;
			this->metroTrackBarCPU->Text = L"metroTrackBar1";
			this->metroTrackBarCPU->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MetroSettingsForm::metroTrackBarCPU_Scroll);
			//
			// metroTrackBarRAM
			//
			this->metroTrackBarRAM->BackColor = System::Drawing::Color::Transparent;
			this->metroTrackBarRAM->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroTrackBarRAM->Location = System::Drawing::Point(308, 123);
			this->metroTrackBarRAM->Name = L"metroTrackBarRAM";
			this->metroTrackBarRAM->Size = System::Drawing::Size(185, 24);
			this->metroTrackBarRAM->TabIndex = 20;
			this->metroTrackBarRAM->Text = L"metroTrackBar2";
			this->metroTrackBarRAM->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MetroSettingsForm::metroTrackBarRAM_Scroll);
			//
			// metroTextBoxHDD
			//
			this->metroTextBoxHDD->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroTextBoxHDD->Lines = gcnew cli::array< System::String^  >(1) { L" " };
			this->metroTextBoxHDD->Location = System::Drawing::Point(307, 152);
			this->metroTextBoxHDD->Margin = System::Windows::Forms::Padding(2);
			this->metroTextBoxHDD->MaxLength = 32767;
			this->metroTextBoxHDD->Name = L"metroTextBoxHDD";
			this->metroTextBoxHDD->PasswordChar = '\0';
			this->metroTextBoxHDD->ScrollBars = System::Windows::Forms::ScrollBars::None;
			this->metroTextBoxHDD->SelectedText = L"";
			this->metroTextBoxHDD->Size = System::Drawing::Size(187, 26);
			this->metroTextBoxHDD->TabIndex = 21;
			this->metroTextBoxHDD->Text = L" ";
			this->metroTextBoxHDD->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->metroTextBoxHDD->UseSelectable = true;
			this->metroTextBoxHDD->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MetroSettingsForm::OnTextBoxTextChanged);
			//
			// metroTextBoxNET
			//
			this->metroTextBoxNET->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroTextBoxNET->Lines = gcnew cli::array< System::String^  >(1) { L" " };
			this->metroTextBoxNET->Location = System::Drawing::Point(307, 182);
			this->metroTextBoxNET->Margin = System::Windows::Forms::Padding(2);
			this->metroTextBoxNET->MaxLength = 32767;
			this->metroTextBoxNET->Name = L"metroTextBoxNET";
			this->metroTextBoxNET->PasswordChar = '\0';
			this->metroTextBoxNET->ScrollBars = System::Windows::Forms::ScrollBars::None;
			this->metroTextBoxNET->SelectedText = L"";
			this->metroTextBoxNET->Size = System::Drawing::Size(187, 28);
			this->metroTextBoxNET->TabIndex = 22;
			this->metroTextBoxNET->Text = L" ";
			this->metroTextBoxNET->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->metroTextBoxNET->UseSelectable = true;
			this->metroTextBoxNET->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MetroSettingsForm::OnTextBoxTextChanged);
			//
			// metroToggleCPU
			//
			this->metroToggleCPU->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->metroToggleCPU->AutoSize = true;
			this->metroToggleCPU->Location = System::Drawing::Point(83, 93);
			this->metroToggleCPU->Name = L"metroToggleCPU";
			this->metroToggleCPU->Size = System::Drawing::Size(80, 24);
			this->metroToggleCPU->TabIndex = 23;
			this->metroToggleCPU->Text = L"Aus";
			this->metroToggleCPU->UseSelectable = true;
			//
			// metroToggleRAM
			//
			this->metroToggleRAM->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->metroToggleRAM->AutoSize = true;
			this->metroToggleRAM->Location = System::Drawing::Point(83, 123);
			this->metroToggleRAM->Name = L"metroToggleRAM";
			this->metroToggleRAM->Size = System::Drawing::Size(80, 24);
			this->metroToggleRAM->TabIndex = 24;
			this->metroToggleRAM->Text = L"Aus";
			this->metroToggleRAM->UseSelectable = true;
			//
			// metroToggleHDD
			//
			this->metroToggleHDD->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->metroToggleHDD->AutoSize = true;
			this->metroToggleHDD->Location = System::Drawing::Point(83, 153);
			this->metroToggleHDD->Name = L"metroToggleHDD";
			this->metroToggleHDD->Size = System::Drawing::Size(80, 24);
			this->metroToggleHDD->TabIndex = 25;
			this->metroToggleHDD->Text = L"Aus";
			this->metroToggleHDD->UseSelectable = true;
			//
			// metroToggleNET
			//
			this->metroToggleNET->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->metroToggleNET->AutoSize = true;
			this->metroToggleNET->Location = System::Drawing::Point(83, 183);
			this->metroToggleNET->Name = L"metroToggleNET";
			this->metroToggleNET->Size = System::Drawing::Size(80, 26);
			this->metroToggleNET->TabIndex = 26;
			this->metroToggleNET->Text = L"Aus";
			this->metroToggleNET->UseSelectable = true;
			//
			// metroTextBoxWAITTIME
			//
			this->metroTextBoxWAITTIME->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroTextBoxWAITTIME->Lines = gcnew cli::array< System::String^  >(0);
			this->metroTextBoxWAITTIME->Location = System::Drawing::Point(307, 32);
			this->metroTextBoxWAITTIME->Margin = System::Windows::Forms::Padding(2);
			this->metroTextBoxWAITTIME->MaxLength = 32767;
			this->metroTextBoxWAITTIME->Name = L"metroTextBoxWAITTIME";
			this->metroTextBoxWAITTIME->PasswordChar = '\0';
			this->metroTextBoxWAITTIME->ScrollBars = System::Windows::Forms::ScrollBars::None;
			this->metroTextBoxWAITTIME->SelectedText = L"";
			this->metroTextBoxWAITTIME->Size = System::Drawing::Size(187, 26);
			this->metroTextBoxWAITTIME->TabIndex = 27;
			this->metroTextBoxWAITTIME->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->metroTextBoxWAITTIME->UseSelectable = true;
			//
			// metroLabel3
			//
			this->metroLabel3->AutoSize = true;
			this->metroLabel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLabel3->FontWeight = MetroFramework::MetroLabelWeight::Regular;
			this->metroLabel3->Location = System::Drawing::Point(579, 60);
			this->metroLabel3->Name = L"metroLabel3";
			this->metroLabel3->Size = System::Drawing::Size(114, 30);
			this->metroLabel3->TabIndex = 28;
			this->metroLabel3->Text = L"Average Usage:";
			this->metroLabel3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			//
			// metroLabel16
			//
			this->metroLabel16->AutoSize = true;
			this->metroLabel16->BackColor = System::Drawing::SystemColors::Control;
			this->metroLabel16->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLabel16->FontWeight = MetroFramework::MetroLabelWeight::Regular;
			this->metroLabel16->Location = System::Drawing::Point(3, 0);
			this->metroLabel16->Name = L"metroLabel16";
			this->metroLabel16->Size = System::Drawing::Size(710, 40);
			this->metroLabel16->TabIndex = 2;
			this->metroLabel16->Text = L"Please select the thresholds! If the measured usage is greater than the selected "
				L"threshold the system will not go into sleep mode.";
			this->metroLabel16->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->metroLabel16->UseCustomBackColor = true;
			this->metroLabel16->WrapToLine = true;
			//
			// metroTabPage2
			//
			this->metroTabPage2->Controls->Add(this->tableLayoutPanel5);
			this->metroTabPage2->HorizontalScrollbarBarColor = true;
			this->metroTabPage2->HorizontalScrollbarHighlightOnWheel = false;
			this->metroTabPage2->HorizontalScrollbarSize = 0;
			this->metroTabPage2->Location = System::Drawing::Point(4, 38);
			this->metroTabPage2->Name = L"metroTabPage2";
			this->metroTabPage2->Size = System::Drawing::Size(718, 274);
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
			this->tableLayoutPanel5->Name = L"tableLayoutPanel5";
			this->tableLayoutPanel5->RowCount = 1;
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel5->Size = System::Drawing::Size(718, 274);
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
			this->listViewProc->Location = System::Drawing::Point(10, 10);
			this->listViewProc->Margin = System::Windows::Forms::Padding(10);
			this->listViewProc->MultiSelect = false;
			this->listViewProc->Name = L"listViewProc";
			this->listViewProc->Size = System::Drawing::Size(482, 254);
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
				20)));
			this->tableLayoutPanel6->Controls->Add(this->tableLayoutPanel7, 0, 1);
			this->tableLayoutPanel6->Controls->Add(this->metroLabel17, 0, 0);
			this->tableLayoutPanel6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel6->Location = System::Drawing::Point(505, 3);
			this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
			this->tableLayoutPanel6->RowCount = 2;
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel6->Size = System::Drawing::Size(210, 268);
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
			this->tableLayoutPanel7->Location = System::Drawing::Point(3, 137);
			this->tableLayoutPanel7->Name = L"tableLayoutPanel7";
			this->tableLayoutPanel7->RowCount = 4;
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel7->Size = System::Drawing::Size(204, 128);
			this->tableLayoutPanel7->TabIndex = 0;
			//
			// metroButtonRemove
			//
			this->metroButtonRemove->BackColor = System::Drawing::Color::DarkCyan;
			this->metroButtonRemove->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroButtonRemove->Location = System::Drawing::Point(5, 69);
			this->metroButtonRemove->Margin = System::Windows::Forms::Padding(5);
			this->metroButtonRemove->Name = L"metroButtonRemove";
			this->metroButtonRemove->Size = System::Drawing::Size(194, 22);
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
			this->metroButtonAddFromList->Location = System::Drawing::Point(5, 37);
			this->metroButtonAddFromList->Margin = System::Windows::Forms::Padding(5);
			this->metroButtonAddFromList->Name = L"metroButtonAddFromList";
			this->metroButtonAddFromList->Size = System::Drawing::Size(194, 22);
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
			this->metroButtonAddFromFile->Location = System::Drawing::Point(5, 5);
			this->metroButtonAddFromFile->Margin = System::Windows::Forms::Padding(5);
			this->metroButtonAddFromFile->Name = L"metroButtonAddFromFile";
			this->metroButtonAddFromFile->Size = System::Drawing::Size(194, 22);
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
			this->tableLayoutPanel8->Location = System::Drawing::Point(3, 99);
			this->tableLayoutPanel8->Name = L"tableLayoutPanel8";
			this->tableLayoutPanel8->RowCount = 1;
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 26)));
			this->tableLayoutPanel8->Size = System::Drawing::Size(198, 26);
			this->tableLayoutPanel8->TabIndex = 3;
			//
			// metroToggleView
			//
			this->metroToggleView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->metroToggleView->AutoSize = true;
			this->metroToggleView->Location = System::Drawing::Point(108, 7);
			this->metroToggleView->Margin = System::Windows::Forms::Padding(7);
			this->metroToggleView->Name = L"metroToggleView";
			this->metroToggleView->Size = System::Drawing::Size(80, 12);
			this->metroToggleView->TabIndex = 3;
			this->metroToggleView->Text = L"Aus";
			this->metroToggleView->UseSelectable = true;
			this->metroToggleView->CheckedChanged += gcnew System::EventHandler(this, &MetroSettingsForm::metroToggleView_CheckedChanged);
			//
			// metroLabelView
			//
			this->metroLabelView->AutoSize = true;
			this->metroLabelView->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLabelView->Location = System::Drawing::Point(3, 0);
			this->metroLabelView->Name = L"metroLabelView";
			this->metroLabelView->Size = System::Drawing::Size(93, 26);
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
			this->metroLabel17->Location = System::Drawing::Point(3, 0);
			this->metroLabel17->Name = L"metroLabel17";
			this->metroLabel17->Size = System::Drawing::Size(204, 134);
			this->metroLabel17->TabIndex = 1;
			this->metroLabel17->Text = L"If at least one of the set up processes is running, the programm will prevent the"
				L" system from changing over to standby mode.";
			this->metroLabel17->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->metroLabel17->UseCustomBackColor = true;
			this->metroLabel17->WrapToLine = true;
			//
			// metroTabPage4
			//
			this->metroTabPage4->Controls->Add(this->tableLayoutPanel11);
			this->metroTabPage4->HorizontalScrollbarBarColor = true;
			this->metroTabPage4->HorizontalScrollbarHighlightOnWheel = false;
			this->metroTabPage4->HorizontalScrollbarSize = 10;
			this->metroTabPage4->Location = System::Drawing::Point(4, 38);
			this->metroTabPage4->Name = L"metroTabPage4";
			this->metroTabPage4->Size = System::Drawing::Size(718, 274);
			this->metroTabPage4->TabIndex = 3;
			this->metroTabPage4->Text = L"Advanced Settings";
			this->metroTabPage4->VerticalScrollbarBarColor = true;
			this->metroTabPage4->VerticalScrollbarHighlightOnWheel = false;
			this->metroTabPage4->VerticalScrollbarSize = 10;
			//
			// tableLayoutPanel11
			//
			this->tableLayoutPanel11->BackColor = System::Drawing::Color::White;
			this->tableLayoutPanel11->ColumnCount = 2;
			this->tableLayoutPanel11->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel11->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel11->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel11->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel11->Controls->Add(this->metroLabel11, 0, 1);
			this->tableLayoutPanel11->Controls->Add(this->metroToggleAutoStart, 1, 1);
			this->tableLayoutPanel11->Controls->Add(this->metroLabel18, 0, 2);
			this->tableLayoutPanel11->Controls->Add(this->metroToggleTutorial, 1, 2);
			this->tableLayoutPanel11->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel11->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel11->Name = L"tableLayoutPanel11";
			this->tableLayoutPanel11->RowCount = 4;
			this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel11->Size = System::Drawing::Size(718, 274);
			this->tableLayoutPanel11->TabIndex = 2;
			//
			// metroLabel11
			//
			this->metroLabel11->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->metroLabel11->AutoSize = true;
			this->metroLabel11->Location = System::Drawing::Point(232, 68);
			this->metroLabel11->Name = L"metroLabel11";
			this->metroLabel11->Size = System::Drawing::Size(124, 19);
			this->metroLabel11->TabIndex = 0;
			this->metroLabel11->Text = L"Start with Windows:";
			//
			// metroToggleAutoStart
			//
			this->metroToggleAutoStart->AutoSize = true;
			this->metroToggleAutoStart->Location = System::Drawing::Point(362, 71);
			this->metroToggleAutoStart->Name = L"metroToggleAutoStart";
			this->metroToggleAutoStart->Size = System::Drawing::Size(80, 17);
			this->metroToggleAutoStart->TabIndex = 1;
			this->metroToggleAutoStart->Text = L"Aus";
			this->metroToggleAutoStart->UseSelectable = true;
			this->metroToggleAutoStart->CheckedChanged += gcnew System::EventHandler(this, &MetroSettingsForm::metroToggleAutoStart_CheckedChanged);
			//
			// metroLabel18
			//
			this->metroLabel18->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->metroLabel18->AutoSize = true;
			this->metroLabel18->Location = System::Drawing::Point(267, 136);
			this->metroLabel18->Name = L"metroLabel18";
			this->metroLabel18->Size = System::Drawing::Size(89, 19);
			this->metroLabel18->TabIndex = 2;
			this->metroLabel18->Text = L"Show Tutorial:";
			//
			// metroToggleTutorial
			//
			this->metroToggleTutorial->AutoSize = true;
			this->metroToggleTutorial->Location = System::Drawing::Point(362, 139);
			this->metroToggleTutorial->Name = L"metroToggleTutorial";
			this->metroToggleTutorial->Size = System::Drawing::Size(80, 17);
			this->metroToggleTutorial->TabIndex = 3;
			this->metroToggleTutorial->Text = L"Aus";
			this->metroToggleTutorial->UseSelectable = true;
			//
			// metroTabPage3
			//
			this->metroTabPage3->AutoScroll = true;
			this->metroTabPage3->Controls->Add(this->tableLayoutPanel9);
			this->metroTabPage3->Controls->Add(this->metroLabel15);
			this->metroTabPage3->HorizontalScrollbar = true;
			this->metroTabPage3->HorizontalScrollbarBarColor = true;
			this->metroTabPage3->HorizontalScrollbarHighlightOnWheel = false;
			this->metroTabPage3->HorizontalScrollbarSize = 5;
			this->metroTabPage3->Location = System::Drawing::Point(4, 38);
			this->metroTabPage3->Name = L"metroTabPage3";
			this->metroTabPage3->Size = System::Drawing::Size(718, 274);
			this->metroTabPage3->TabIndex = 2;
			this->metroTabPage3->Text = L"About";
			this->metroTabPage3->VerticalScrollbar = true;
			this->metroTabPage3->VerticalScrollbarBarColor = true;
			this->metroTabPage3->VerticalScrollbarHighlightOnWheel = false;
			this->metroTabPage3->VerticalScrollbarSize = 5;
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
			this->tableLayoutPanel9->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel9->Name = L"tableLayoutPanel9";
			this->tableLayoutPanel9->RowCount = 1;
			this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 69)));
			this->tableLayoutPanel9->Size = System::Drawing::Size(710, 69);
			this->tableLayoutPanel9->TabIndex = 2;
			//
			// metroTileHomepage
			//
			this->metroTileHomepage->ActiveControl = nullptr;
			this->metroTileHomepage->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroTileHomepage->Location = System::Drawing::Point(3, 3);
			this->metroTileHomepage->Name = L"metroTileHomepage";
			this->metroTileHomepage->Size = System::Drawing::Size(349, 63);
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
			this->metroTileGithub->Location = System::Drawing::Point(358, 3);
			this->metroTileGithub->Name = L"metroTileGithub";
			this->metroTileGithub->Size = System::Drawing::Size(349, 63);
			this->metroTileGithub->TabIndex = 1;
			this->metroTileGithub->Text = L"Visit us on Github!";
			this->metroTileGithub->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->metroTileGithub->UseSelectable = true;
			this->metroTileGithub->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroTileGithub_Click);
			//
			// metroLabel15
			//
			this->metroLabel15->Location = System::Drawing::Point(6, 75);
			this->metroLabel15->Name = L"metroLabel15";
			this->metroLabel15->Size = System::Drawing::Size(691, 1035);
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
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 60);
			this->tableLayoutPanel1->Margin = System::Windows::Forms::Padding(10);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 60)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(746, 396);
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
			this->tableLayoutPanel4->Location = System::Drawing::Point(3, 339);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 1;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(740, 54);
			this->tableLayoutPanel4->TabIndex = 1;
			//
			// metroButtonOK
			//
			this->metroButtonOK->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroButtonOK->FontSize = MetroFramework::MetroButtonSize::Medium;
			this->metroButtonOK->Location = System::Drawing::Point(602, 10);
			this->metroButtonOK->Margin = System::Windows::Forms::Padding(10);
			this->metroButtonOK->Name = L"metroButtonOK";
			this->metroButtonOK->Size = System::Drawing::Size(128, 34);
			this->metroButtonOK->TabIndex = 1;
			this->metroButtonOK->Text = L"OK";
			this->metroButtonOK->UseSelectable = true;
			this->metroButtonOK->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroButtonOK_Click);
			//
			// metroButtonCancel
			//
			this->metroButtonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->metroButtonCancel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroButtonCancel->Location = System::Drawing::Point(454, 10);
			this->metroButtonCancel->Margin = System::Windows::Forms::Padding(10);
			this->metroButtonCancel->Name = L"metroButtonCancel";
			this->metroButtonCancel->Size = System::Drawing::Size(128, 34);
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
			this->metroLabel12->Location = System::Drawing::Point(3, 0);
			this->metroLabel12->Name = L"metroLabel12";
			this->metroLabel12->Size = System::Drawing::Size(142, 54);
			this->metroLabel12->TabIndex = 2;
			this->metroLabel12->Text = L"© Florian Baader, Stephan Le, Matthias Weirich";
			this->metroLabel12->TextAlign = System::Drawing::ContentAlignment::BottomLeft;
			this->metroLabel12->WrapToLine = true;
			//
			// metroLinkHomepage
			//
			this->metroLinkHomepage->Dock = System::Windows::Forms::DockStyle::Fill;
			this->metroLinkHomepage->Location = System::Drawing::Point(151, 3);
			this->metroLinkHomepage->Name = L"metroLinkHomepage";
			this->metroLinkHomepage->Size = System::Drawing::Size(142, 48);
			this->metroLinkHomepage->TabIndex = 3;
			this->metroLinkHomepage->Text = L"www.stand-bye.de";
			this->metroLinkHomepage->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->metroLinkHomepage->UseSelectable = true;
			this->metroLinkHomepage->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroLinkHomepage_Click);
			//
			// timerRefresh
			//
			this->timerRefresh->Interval = 1000;
			this->timerRefresh->Tick += gcnew System::EventHandler(this, &MetroSettingsForm::timer1_Tick);
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
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackImage")));
			this->BackImagePadding = System::Windows::Forms::Padding(0, 5, 0, 0);
			this->BackMaxSize = 760;
			this->BorderStyle = MetroFramework::Forms::MetroFormBorderStyle::FixedSingle;
			this->ClientSize = System::Drawing::Size(746, 456);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MetroSettingsForm";
			this->Padding = System::Windows::Forms::Padding(0, 60, 0, 0);
			this->Resizable = false;
			this->ShadowType = MetroFramework::Forms::MetroFormShadowType::DropShadow;
			this->Style = MetroFramework::MetroColorStyle::Green;
			this->Load += gcnew System::EventHandler(this, &MetroSettingsForm::MetroSettingsForm_Load);
			this->metroTabControl1->ResumeLayout(false);
			this->metroTabPage1->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel3->PerformLayout();
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
	private: void forceRefresh() {
		timer1_Tick(gcnew System::Object, gcnew System::EventArgs);
	}
	private: System::Void MetroSettingsForm_Load(System::Object^  sender, System::EventArgs^  e) {
		//Focus on first tabPage
		metroTabControl1->SelectedTab = metroTabPage1;

		//Load Settings
		metroTrackBarCPU->Value = STP->getThreshold(SettingName::MAX_CPU);
		metroTrackBarRAM->Value = STP->getThreshold(SettingName::MAX_RAM);
		setTextBoxValue(metroTextBoxNET, (double)STP->getThreshold(SettingName::MAX_NET) / 1000);
		setTextBoxValue(metroTextBoxHDD, (double)STP->getThreshold(SettingName::MAX_HDD) / 1000);
		setTextBoxValue(metroTextBoxWAITTIME, STP->getThreshold(SettingName::WAIT_TIME) / 60);
		metroToggleCPU->Checked = STP->isActive(SettingName::USE_CPU);
		metroToggleHDD->Checked = STP->isActive(SettingName::USE_HDD);
		metroToggleNET->Checked = STP->isActive(SettingName::USE_NET);
		metroToggleRAM->Checked = STP->isActive(SettingName::USE_RAM);

		//Load AutoStart Setting
		metroToggleAutoStart->Checked = SystemAccess::IsInAutoStart();

		//Update UI
		metroLabelCPUPer->Text = String::Format("{0} %", metroTrackBarCPU->Value);
		metroLabelRAMPer->Text = String::Format("{0} %", metroTrackBarRAM->Value);

		//ListView processes
		listViewProc->Font = BasicFunc::getMetroFont(9);

		//Load Processes
		refreshIcons();
		for each(std::string str in  STP->getProcessList()) {
			listViewProc->Items->Add(gcnew ProcessItem(str, listViewProc));
		}
		listViewProc->Update();

		//Start Timer
		timerRefresh->Start();
		forceRefresh();
	}
	private: bool isNumber(std::string line) {
		char* p;
		strtol(line.c_str(), &p, 10);
		return *p == 0;
	}

	private: double getTextBoxValue(MetroFramework::Controls::MetroTextBox^ box) {
		box->Text = box->Text->Replace(",", ".");
		double value = -1;
		value = atof(BasicFunc::StringToString(box->Text).c_str());
		return value;
	}

	private: void setTextBoxValue(MetroFramework::Controls::MetroTextBox^ box, double value) {
		box->Text = String::Format("{0:00.0}", value);
	}

	private: System::Void metroTextBoxWAITTIME_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		if (isNumber(BasicFunc::StringToString(metroTextBoxWAITTIME->Text)) == false) {
			metroTextBoxWAITTIME->Text = "";
		}
		forceRefresh();
	}
	private: void changeColor(MetroFramework::Controls::MetroLabel^ label, double SettingsValue, double readValue) {
		if (SettingsValue > readValue) {
			label->BackColor = lightGreen;
		}
		else {
			label->BackColor = lightRed;
		}
	}

	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		float curCPU, curRAM, curHDD, curNET;
		curCPU = system_watcher->GetSystemMetric(SystemAccess::SystemMetric::CPU);
		curRAM = system_watcher->GetSystemMetric(SystemAccess::SystemMetric::RAM);
		curHDD = system_watcher->GetSystemMetric(SystemAccess::SystemMetric::HDD);
		curNET = system_watcher->GetSystemMetric(SystemAccess::SystemMetric::NETWORK);

		changeColor(metroLabelCurCPU, metroTrackBarCPU->Value, curCPU);
		changeColor(metroLabelCurRAM, metroTrackBarRAM->Value, curRAM);
		changeColor(metroLabelCurHDD, getTextBoxValue(metroTextBoxHDD), curHDD / 1000);
		changeColor(metroLabelCurNET, getTextBoxValue(metroTextBoxNET), curNET / 1000);

		metroLabelCurCPU->Text = String::Format("{0:00.00} %", curCPU);
		metroLabelCurHDD->Text = String::Format("{0:00.00} MBit/s", curHDD / 1000);
		metroLabelCurRAM->Text = String::Format("{0:00.00} % ", curRAM);
		metroLabelCurNET->Text = String::Format("{0:00.00} MBit/s", curNET / 1000);

		metroToolTip1->SetToolTip(metroLabelCurCPU, String::Format("Now: {0:00.00} %", SysAcs->GetMetric(SystemAccess::SystemMetric::CPU)));
		metroToolTip1->SetToolTip(metroLabelCurRAM, String::Format("Now: {0:00.00} % ", SysAcs->GetMetric(SystemAccess::SystemMetric::RAM)));
		metroToolTip1->SetToolTip(metroLabelCurHDD, String::Format("Now: {0:00.00} MBit/s", SysAcs->GetMetric(SystemAccess::SystemMetric::HDD) / 1000));
		metroToolTip1->SetToolTip(metroLabelCurNET, String::Format("Now: {0:00.00} MBit/s", SysAcs->GetMetric(SystemAccess::SystemMetric::NETWORK) / 1000));
	}
	private: System::Void metroButtonOK_Click(System::Object^  sender, System::EventArgs^  e) {
		std::vector<bool> RESULT;
		RESULT.push_back(STP->setSetting(SettingName::MAX_CPU, Decimal::ToInt32(metroTrackBarCPU->Value)));
		RESULT.push_back(STP->setSetting(SettingName::MAX_RAM, Decimal::ToInt32(metroTrackBarRAM->Value)));
		RESULT.push_back(STP->setSetting(SettingName::MAX_HDD, (int)(getTextBoxValue(metroTextBoxHDD) * 1000)));
		RESULT.push_back(STP->setSetting(SettingName::MAX_NET, (int)(getTextBoxValue(metroTextBoxNET) * 1000)));
		RESULT.push_back(STP->setSetting(SettingName::WAIT_TIME, getTextBoxValue(metroTextBoxWAITTIME) * 60));
		RESULT.push_back(STP->setActiveState(SettingName::USE_CPU, metroToggleCPU->Checked));
		RESULT.push_back(STP->setActiveState(SettingName::USE_HDD, metroToggleHDD->Checked));
		RESULT.push_back(STP->setActiveState(SettingName::USE_RAM, metroToggleRAM->Checked));
		RESULT.push_back(STP->setActiveState(SettingName::USE_NET, metroToggleNET->Checked));

		for each(ListViewItem^ l in listViewProc->Items) {
			ProcessItem^ p = (ProcessItem^)l;
			RESULT.push_back(p->Write(STP));
		}

		bool success = true;
		for each (bool b in RESULT) {
			if (b == false) {
				success = false;
				break;
			}
		}
		if (success) {
		}
		else {
			MessageBoxA(NULL, "Writing Settings not successful!", "Writing not successful!", MB_OK);
		}
		this->DialogResult = Windows::Forms::DialogResult::OK;
		this->Hide();
	}
	private: System::Void metroButtonCancel_Click(System::Object^  sender, System::EventArgs^  e) {
		this->DialogResult = Windows::Forms::DialogResult::Cancel;
		this->Hide();
	}
	private: System::Void metroButtonAddFromFile_Click(System::Object^  sender, System::EventArgs^  e) {
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		ofd->InitialDirectory = "C:\\";
		ofd->Filter = "exe files(*.exe)|*.exe";
		ofd->FilterIndex = 1;
		ofd->RestoreDirectory = true;
		if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			if (ofd->CheckFileExists != false) {
				bool res = STP->addProcessToProcessList(BasicFunc::StringToString(ofd->FileName));
				if (res) {
					listViewProc->Items->Add(gcnew ProcessItem(BasicFunc::StringToString(ofd->FileName), listViewProc));
				}
				else {
					MessageBoxA(NULL, "Writing Setting not successful!", "Writing not successful!", MB_OK);
				}
			}
		}
	}
	private: System::Void metroButtonAddFromList_Click(System::Object^  sender, System::EventArgs^  e) {
		using namespace SmartLogout;
		ProcessSelectionForm^ ProcForm = gcnew ProcessSelectionForm;
		if (ProcForm->ShowDialog() == Windows::Forms::DialogResult::OK) {
			if (ProcForm->selectedProcessPath != "") {
				listViewProc->Items->Add(gcnew ProcessItem(BasicFunc::StringToString(ProcForm->selectedProcessPath), listViewProc));
			}
		}
		delete ProcForm;
	}
	private: System::Void metroButtonRemove_Click(System::Object^  sender, System::EventArgs^  e) {
		ProcessItem^ proc = (ProcessItem^)listViewProc->SelectedItems[0];
		bool res = STP->removeProcessFromProcessList(BasicFunc::StringToString(proc->GetPath()));
		if (!res) {
			MessageBoxA(NULL, "Writing Settings not successful!", "Writing not successful!", MB_OK);
		}
		delete proc;
		refreshIcons();
	}
	private: System::Void listViewProc_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		metroButtonRemove->Enabled = (listViewProc->SelectedItems->Count > 0);
	}
	private: System::Void metroToggleView_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (metroToggleView->Checked) {
			ResizeListViewColumns(listViewProc);
			listViewProc->View = Windows::Forms::View::Details;
		}
		else {
			listViewProc->View = Windows::Forms::View::Tile;
		}
	}

	private: void ResizeListViewColumns(ListView^ lv)
	{
		for each(ColumnHeader^ column in lv->Columns)
		{
			column->AutoResize(Windows::Forms::ColumnHeaderAutoResizeStyle::ColumnContent);
		}
	}

	private: void refreshIcons() {
		ImageList^ imglistSmall = gcnew ImageList, ^imglistLarge = gcnew ImageList;

		imglistSmall->ImageSize = Drawing::Size(24, 24);
		imglistLarge->ImageSize = Drawing::Size(50, 50);

		listViewProc->SmallImageList = imglistSmall;
		listViewProc->LargeImageList = imglistLarge;

		for each(ProcessItem^ p in listViewProc->Items) {
			p->addIconToLists(listViewProc);
		}
	}
	private: System::Void metroTrackBarRAM_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
		metroLabelRAMPer->Text = String::Format("{0} %", metroTrackBarRAM->Value);
	}
	private: System::Void metroTrackBarCPU_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
		metroLabelCPUPer->Text = String::Format("{0} %", metroTrackBarCPU->Value);
	}
	private: System::Void metroToggleAutoStart_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		SystemAccess::SetAutoStart(metroToggleAutoStart->Checked);
	}
	private: System::Void metroTileHomepage_Click(System::Object^  sender, System::EventArgs^  e) {
		ShellExecute(0, 0, "http://www.stand-bye.de", 0, 0, SW_SHOW);
	}
	private: System::Void metroTileGithub_Click(System::Object^  sender, System::EventArgs^  e) {
		ShellExecute(0, 0, "https://github.com/flobaader/Stand-Bye", 0, 0, SW_SHOW);
	}
	private: System::Void metroLinkHomepage_Click(System::Object^  sender, System::EventArgs^  e) {
		ShellExecute(0, 0, "http://www.stand-bye.de", 0, 0, SW_SHOW);
	}
	private: System::Void OnTextBoxTextChanged(System::Object ^sender, System::Windows::Forms::KeyEventArgs ^e) {
		using MetroFramework::Controls::MetroTextBox;
		if (e->KeyCode == Windows::Forms::Keys::Return) {
			MetroTextBox^ txt = (MetroTextBox^)sender;
			if (getTextBoxValue(txt) == -1) {
				txt->Text = "";
			}
			else {
				txt->Text = String::Format("{0:00.0}", getTextBoxValue(txt));
			}
			forceRefresh();
		}
	}
	};
}
