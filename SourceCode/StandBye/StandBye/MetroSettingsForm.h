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
using namespace System::Globalization;
using namespace System::Resources;

ref class mainApplication;

namespace StandBye {
	/// <summary>
	/// Provides a Form to set up the Settings for the Application
	/// </summary>
	public ref class MetroSettingsForm : public MetroFramework::Forms::MetroForm
	{
	private:
		mainApplication^ parent;
		SystemAccess^ system_access;
		SettingsProvider* settings_provider;
		SystemMetricWatcher^ system_watcher;
		InputMonitor^ input_monitor;
		ResourceManager^ res_man;
		List<CultureInfo^>^ supportedLanguages;
		Drawing::Color lightGreen, darkGreen, lightRed, darkRed;

	private: MetroFramework::Controls::MetroTabPage^  metroTabPageThresholds;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanelUsageThresholds;
	private: MetroFramework::Controls::MetroLabel^  metroLabelCurNET;
	private: MetroFramework::Controls::MetroToggle^  metroToggleNET;
	private: MetroFramework::Controls::MetroToggle^  metroToggleHDD;
	private: MetroFramework::Controls::MetroLabel^  metroLabelCurHDD;
	private: MetroFramework::Controls::MetroLabel^  metroLabel13;
	private: MetroFramework::Controls::MetroLabel^  metroLabelCurRAM;
	private: MetroFramework::Controls::MetroToggle^  metroToggleRAM;
	private: MetroFramework::Controls::MetroLabel^  metroLabelCurCPU;
	private: MetroFramework::Controls::MetroToggle^  metroToggleCPU;
	private: MetroFramework::Controls::MetroTextBox^  metroTextBoxNET;
	private: MetroFramework::Controls::MetroLabel^  metroLabel14;
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextCPU;
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextRAM;
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextHDD;
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextNET;
	private: MetroFramework::Controls::MetroLabel^  metroLabelRAMPer;
	private: MetroFramework::Controls::MetroTrackBar^  metroTrackBarCPU;
	private: MetroFramework::Controls::MetroLabel^  metroLabelCPUPer;
	private: MetroFramework::Controls::MetroTextBox^  metroTextBoxHDD;
	private: MetroFramework::Controls::MetroTrackBar^  metroTrackBarRAM;
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextAverageUsage;

	private: MetroFramework::Controls::MetroTextBox^  infoThresholds;
	private: MetroFramework::Controls::MetroTextBox^  infoGeneral;
	private: MetroFramework::Controls::MetroTextBox^  infoExcpProcesses;

	private: MetroFramework::Controls::MetroLabel^  metroLabelTextUsageThresholds;

	public:
		MetroSettingsForm(mainApplication^ parent, SystemMetricWatcher^ smw, SettingsProvider* pro, SystemAccess^ system_access, InputMonitor^ inputMon, List<CultureInfo^>^ supportLanguages)
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

			//Loads Languages
			supportedLanguages = supportLanguages;

			for each(CultureInfo^ cul in supportedLanguages) {
				metroComboBoxLanguage->Items->Add(cul->NativeName);
			}

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
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextUpdates;
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextLanguage;
	private: MetroFramework::Controls::MetroComboBox^  metroComboBoxLanguage;
	protected:

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
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextAutoStart;
	private: MetroFramework::Controls::MetroLabel^  metroLabelVersion;

	private: MetroFramework::Controls::MetroLabel^  metroLabelTextAbout;

	private: MetroFramework::Controls::MetroLabel^  metroLabel19;

	private: MetroFramework::Controls::MetroLabel^  metroLabelTextMessages;

	private: MetroFramework::Controls::MetroLabel^  metroLabelTextPresMode;
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextProgramSettings;

	private: MetroFramework::Controls::MetroLabel^  metroLabelTextSound;
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextWaitTime;
	private: MetroFramework::Controls::MetroLabel^  metroLabelView;
	private: MetroFramework::Controls::MetroLink^  metroLinkHomepage;
	private: MetroFramework::Controls::MetroTabControl^  metroTabControl1;
	private: MetroFramework::Controls::MetroTabPage^  metroTabPageSettings;
	private: MetroFramework::Controls::MetroTabPage^  metroTabPageExcpProcess;
	private: MetroFramework::Controls::MetroTabPage^  metroTabPageAbout;
	private: MetroFramework::Controls::MetroTabPage^  metroTabPageAdvSettings;

	private: MetroFramework::Controls::MetroTextBox^  metroTextBoxTimeMIN;
	private: MetroFramework::Controls::MetroTextBox^  metroTextBoxTimeSEC;
	private: MetroFramework::Controls::MetroTile^  metroTileGithub;
	private: MetroFramework::Controls::MetroTile^  metroTileHomepage;
	private: MetroFramework::Controls::MetroToggle^  metroToggleAutoStart;

	private: MetroFramework::Controls::MetroToggle^  metroToggleMessages;

	private: MetroFramework::Controls::MetroToggle^  metroTogglePresMode;

	private: MetroFramework::Controls::MetroToggle^  metroToggleSOUND;

	private: MetroFramework::Controls::MetroToggle^  metroToggleUPDATES;
	private: MetroFramework::Controls::MetroToggle^  metroToggleView;

	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;
	private: System::Windows::Forms::ListView^  listViewProc;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanelProgrammSettings;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel11;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel12;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;

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
				 this->metroTabPageSettings = (gcnew MetroFramework::Controls::MetroTabPage());
				 this->infoGeneral = (gcnew MetroFramework::Controls::MetroTextBox());
				 this->tableLayoutPanelProgrammSettings = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->metroLabelTextWaitTime = (gcnew MetroFramework::Controls::MetroLabel());
				 this->tableLayoutPanel12 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->metroTextBoxTimeMIN = (gcnew MetroFramework::Controls::MetroTextBox());
				 this->metroLabel10 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroTextBoxTimeSEC = (gcnew MetroFramework::Controls::MetroTextBox());
				 this->metroLabel19 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabelTextPresMode = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroTogglePresMode = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroLabelTextSound = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroToggleSOUND = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroLabelTextProgramSettings = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroTabPageThresholds = (gcnew MetroFramework::Controls::MetroTabPage());
				 this->infoThresholds = (gcnew MetroFramework::Controls::MetroTextBox());
				 this->tableLayoutPanelUsageThresholds = (gcnew System::Windows::Forms::TableLayoutPanel());
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
				 this->metroLabelTextCPU = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabelTextRAM = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabelTextHDD = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabelTextNET = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabelRAMPer = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroTrackBarCPU = (gcnew MetroFramework::Controls::MetroTrackBar());
				 this->metroLabelCPUPer = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroTextBoxHDD = (gcnew MetroFramework::Controls::MetroTextBox());
				 this->metroTrackBarRAM = (gcnew MetroFramework::Controls::MetroTrackBar());
				 this->metroLabelTextAverageUsage = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabelTextUsageThresholds = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroTabPageExcpProcess = (gcnew MetroFramework::Controls::MetroTabPage());
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
				 this->infoExcpProcesses = (gcnew MetroFramework::Controls::MetroTextBox());
				 this->metroTabPageAdvSettings = (gcnew MetroFramework::Controls::MetroTabPage());
				 this->tableLayoutPanel11 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->metroLabelTextUpdates = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroToggleUPDATES = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroLabelTextAutoStart = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroToggleAutoStart = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroLabelTextMessages = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroToggleMessages = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroLabelTextLanguage = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroComboBoxLanguage = (gcnew MetroFramework::Controls::MetroComboBox());
				 this->metroTabPageAbout = (gcnew MetroFramework::Controls::MetroTabPage());
				 this->tableLayoutPanel9 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->metroTileHomepage = (gcnew MetroFramework::Controls::MetroTile());
				 this->metroTileGithub = (gcnew MetroFramework::Controls::MetroTile());
				 this->metroLabelTextAbout = (gcnew MetroFramework::Controls::MetroLabel());
				 this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->metroButtonOK = (gcnew MetroFramework::Controls::MetroButton());
				 this->metroButtonCancel = (gcnew MetroFramework::Controls::MetroButton());
				 this->metroLabelVersion = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLinkHomepage = (gcnew MetroFramework::Controls::MetroLink());
				 this->timerRefresh = (gcnew System::Windows::Forms::Timer(this->components));
				 this->metroStyleManager1 = (gcnew MetroFramework::Components::MetroStyleManager(this->components));
				 this->metroStyleExtender1 = (gcnew MetroFramework::Components::MetroStyleExtender(this->components));
				 this->metroToolTip1 = (gcnew MetroFramework::Components::MetroToolTip());
				 this->metroTabControl1->SuspendLayout();
				 this->metroTabPageSettings->SuspendLayout();
				 this->tableLayoutPanelProgrammSettings->SuspendLayout();
				 this->tableLayoutPanel12->SuspendLayout();
				 this->metroTabPageThresholds->SuspendLayout();
				 this->tableLayoutPanelUsageThresholds->SuspendLayout();
				 this->metroTabPageExcpProcess->SuspendLayout();
				 this->tableLayoutPanel5->SuspendLayout();
				 this->tableLayoutPanel6->SuspendLayout();
				 this->tableLayoutPanel7->SuspendLayout();
				 this->tableLayoutPanel8->SuspendLayout();
				 this->metroTabPageAdvSettings->SuspendLayout();
				 this->tableLayoutPanel11->SuspendLayout();
				 this->metroTabPageAbout->SuspendLayout();
				 this->tableLayoutPanel9->SuspendLayout();
				 this->tableLayoutPanel1->SuspendLayout();
				 this->tableLayoutPanel4->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->metroStyleManager1))->BeginInit();
				 this->SuspendLayout();
				 //
				 // metroTabControl1
				 //
				 this->metroTabControl1->Controls->Add(this->metroTabPageSettings);
				 this->metroTabControl1->Controls->Add(this->metroTabPageThresholds);
				 this->metroTabControl1->Controls->Add(this->metroTabPageExcpProcess);
				 this->metroTabControl1->Controls->Add(this->metroTabPageAdvSettings);
				 this->metroTabControl1->Controls->Add(this->metroTabPageAbout);
				 this->metroTabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroTabControl1->Location = System::Drawing::Point(10, 10);
				 this->metroTabControl1->Margin = System::Windows::Forms::Padding(10);
				 this->metroTabControl1->Name = L"metroTabControl1";
				 this->metroTabControl1->SelectedIndex = 3;
				 this->metroTabControl1->Size = System::Drawing::Size(739, 266);
				 this->metroTabControl1->TabIndex = 0;
				 this->metroTabControl1->UseSelectable = true;
				 //
				 // metroTabPageSettings
				 //
				 this->metroTabPageSettings->BackColor = System::Drawing::SystemColors::Control;
				 this->metroTabPageSettings->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->metroTabPageSettings->Controls->Add(this->infoGeneral);
				 this->metroTabPageSettings->Controls->Add(this->tableLayoutPanelProgrammSettings);
				 this->metroTabPageSettings->Controls->Add(this->metroLabelTextProgramSettings);
				 this->metroTabPageSettings->HorizontalScrollbarBarColor = false;
				 this->metroTabPageSettings->HorizontalScrollbarHighlightOnWheel = false;
				 this->metroTabPageSettings->HorizontalScrollbarSize = 0;
				 this->metroTabPageSettings->Location = System::Drawing::Point(4, 38);
				 this->metroTabPageSettings->Name = L"metroTabPageSettings";
				 this->metroTabPageSettings->Size = System::Drawing::Size(731, 224);
				 this->metroTabPageSettings->Style = MetroFramework::MetroColorStyle::Green;
				 this->metroTabPageSettings->TabIndex = 0;
				 this->metroTabPageSettings->Text = L"Settings";
				 this->metroTabPageSettings->VerticalScrollbarBarColor = false;
				 this->metroTabPageSettings->VerticalScrollbarHighlightOnWheel = false;
				 this->metroTabPageSettings->VerticalScrollbarSize = 0;
				 //
				 // infoGeneral
				 //
				 this->infoGeneral->Enabled = false;
				 this->infoGeneral->Lines = gcnew cli::array< System::String^  >(1) { resources->GetString(L"infoGeneral.Lines") };
				 this->infoGeneral->Location = System::Drawing::Point(63, 33);
				 this->infoGeneral->MaxLength = 32767;
				 this->infoGeneral->Multiline = true;
				 this->infoGeneral->Name = L"infoGeneral";
				 this->infoGeneral->PasswordChar = '\0';
				 this->infoGeneral->ReadOnly = true;
				 this->infoGeneral->ScrollBars = System::Windows::Forms::ScrollBars::None;
				 this->infoGeneral->SelectedText = L"";
				 this->infoGeneral->Size = System::Drawing::Size(658, 53);
				 this->infoGeneral->TabIndex = 56;
				 this->infoGeneral->Text = resources->GetString(L"infoGeneral.Text");
				 this->infoGeneral->UseSelectable = true;
				 //
				 // tableLayoutPanelProgrammSettings
				 //
				 this->tableLayoutPanelProgrammSettings->BackColor = System::Drawing::Color::White;
				 this->tableLayoutPanelProgrammSettings->ColumnCount = 2;
				 this->tableLayoutPanelProgrammSettings->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanelProgrammSettings->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanelProgrammSettings->Controls->Add(this->metroLabelTextWaitTime, 0, 0);
				 this->tableLayoutPanelProgrammSettings->Controls->Add(this->tableLayoutPanel12, 1, 0);
				 this->tableLayoutPanelProgrammSettings->Controls->Add(this->metroLabelTextPresMode, 0, 1);
				 this->tableLayoutPanelProgrammSettings->Controls->Add(this->metroTogglePresMode, 1, 1);
				 this->tableLayoutPanelProgrammSettings->Controls->Add(this->metroLabelTextSound, 0, 2);
				 this->tableLayoutPanelProgrammSettings->Controls->Add(this->metroToggleSOUND, 1, 2);
				 this->tableLayoutPanelProgrammSettings->Location = System::Drawing::Point(63, 103);
				 this->tableLayoutPanelProgrammSettings->Name = L"tableLayoutPanelProgrammSettings";
				 this->tableLayoutPanelProgrammSettings->RowCount = 3;
				 this->tableLayoutPanelProgrammSettings->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
					 25)));
				 this->tableLayoutPanelProgrammSettings->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
					 25)));
				 this->tableLayoutPanelProgrammSettings->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
					 25)));
				 this->tableLayoutPanelProgrammSettings->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
					 20)));
				 this->tableLayoutPanelProgrammSettings->Size = System::Drawing::Size(405, 95);
				 this->tableLayoutPanelProgrammSettings->TabIndex = 53;
				 //
				 // metroLabelTextWaitTime
				 //
				 this->metroLabelTextWaitTime->AutoSize = true;
				 this->metroLabelTextWaitTime->Location = System::Drawing::Point(0, 0);
				 this->metroLabelTextWaitTime->Margin = System::Windows::Forms::Padding(0);
				 this->metroLabelTextWaitTime->Name = L"metroLabelTextWaitTime";
				 this->metroLabelTextWaitTime->Size = System::Drawing::Size(139, 19);
				 this->metroLabelTextWaitTime->TabIndex = 3;
				 this->metroLabelTextWaitTime->Text = L"Activate Standby After";
				 this->metroLabelTextWaitTime->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->metroToolTip1->SetToolTip(this->metroLabelTextWaitTime, L"  The waiting time till standby starts.  ");
				 //
				 // tableLayoutPanel12
				 //
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
				 this->tableLayoutPanel12->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel12->Location = System::Drawing::Point(237, 0);
				 this->tableLayoutPanel12->Margin = System::Windows::Forms::Padding(0);
				 this->tableLayoutPanel12->Name = L"tableLayoutPanel12";
				 this->tableLayoutPanel12->RowCount = 1;
				 this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
				 this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
					 31)));
				 this->tableLayoutPanel12->Size = System::Drawing::Size(168, 31);
				 this->tableLayoutPanel12->TabIndex = 55;
				 //
				 // metroTextBoxTimeMIN
				 //
				 this->metroTextBoxTimeMIN->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroTextBoxTimeMIN->Lines = gcnew cli::array< System::String^  >(1) { L" " };
				 this->metroTextBoxTimeMIN->Location = System::Drawing::Point(3, 3);
				 this->metroTextBoxTimeMIN->MaxLength = 3;
				 this->metroTextBoxTimeMIN->Name = L"metroTextBoxTimeMIN";
				 this->metroTextBoxTimeMIN->PasswordChar = '\0';
				 this->metroTextBoxTimeMIN->ScrollBars = System::Windows::Forms::ScrollBars::None;
				 this->metroTextBoxTimeMIN->SelectedText = L"";
				 this->metroTextBoxTimeMIN->Size = System::Drawing::Size(36, 25);
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
				 this->metroLabel10->Location = System::Drawing::Point(45, 0);
				 this->metroLabel10->Name = L"metroLabel10";
				 this->metroLabel10->Size = System::Drawing::Size(36, 31);
				 this->metroLabel10->TabIndex = 48;
				 this->metroLabel10->Text = L"min";
				 this->metroLabel10->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 //
				 // metroTextBoxTimeSEC
				 //
				 this->metroTextBoxTimeSEC->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroTextBoxTimeSEC->Lines = gcnew cli::array< System::String^  >(1) { L" " };
				 this->metroTextBoxTimeSEC->Location = System::Drawing::Point(87, 3);
				 this->metroTextBoxTimeSEC->MaxLength = 2;
				 this->metroTextBoxTimeSEC->Name = L"metroTextBoxTimeSEC";
				 this->metroTextBoxTimeSEC->PasswordChar = '\0';
				 this->metroTextBoxTimeSEC->ScrollBars = System::Windows::Forms::ScrollBars::None;
				 this->metroTextBoxTimeSEC->SelectedText = L"";
				 this->metroTextBoxTimeSEC->Size = System::Drawing::Size(36, 25);
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
				 this->metroLabel19->Location = System::Drawing::Point(129, 0);
				 this->metroLabel19->Name = L"metroLabel19";
				 this->metroLabel19->Size = System::Drawing::Size(36, 31);
				 this->metroLabel19->TabIndex = 49;
				 this->metroLabel19->Text = L"s";
				 this->metroLabel19->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 //
				 // metroLabelTextPresMode
				 //
				 this->metroLabelTextPresMode->AutoSize = true;
				 this->metroLabelTextPresMode->Location = System::Drawing::Point(3, 31);
				 this->metroLabelTextPresMode->Name = L"metroLabelTextPresMode";
				 this->metroLabelTextPresMode->Size = System::Drawing::Size(172, 19);
				 this->metroLabelTextPresMode->TabIndex = 53;
				 this->metroLabelTextPresMode->Text = L"Activate Presentation-Mode";
				 this->metroLabelTextPresMode->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->metroToolTip1->SetToolTip(this->metroLabelTextPresMode, L"  If enabled --> no standby and no display timeout.  ");
				 //
				 // metroTogglePresMode
				 //
				 this->metroTogglePresMode->Anchor = System::Windows::Forms::AnchorStyles::Left;
				 this->metroTogglePresMode->AutoSize = true;
				 this->metroTogglePresMode->Location = System::Drawing::Point(240, 38);
				 this->metroTogglePresMode->Name = L"metroTogglePresMode";
				 this->metroTogglePresMode->Size = System::Drawing::Size(80, 17);
				 this->metroTogglePresMode->TabIndex = 54;
				 this->metroTogglePresMode->Text = L"Aus";
				 this->metroTogglePresMode->UseSelectable = true;
				 this->metroTogglePresMode->CheckedChanged += gcnew System::EventHandler(this, &MetroSettingsForm::metroTogglePresMode_CheckedChanged);
				 //
				 // metroLabelTextSound
				 //
				 this->metroLabelTextSound->AutoSize = true;
				 this->metroLabelTextSound->Location = System::Drawing::Point(3, 62);
				 this->metroLabelTextSound->Name = L"metroLabelTextSound";
				 this->metroLabelTextSound->Size = System::Drawing::Size(231, 19);
				 this->metroLabelTextSound->TabIndex = 52;
				 this->metroLabelTextSound->Text = L"Cancel Standby while Sound is playing";
				 this->metroLabelTextSound->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->metroToolTip1->SetToolTip(this->metroLabelTextSound, L"  If you like enjoying music or movies, thats a good choice.  ");
				 //
				 // metroToggleSOUND
				 //
				 this->metroToggleSOUND->Anchor = System::Windows::Forms::AnchorStyles::Left;
				 this->metroToggleSOUND->AutoSize = true;
				 this->metroToggleSOUND->Location = System::Drawing::Point(240, 70);
				 this->metroToggleSOUND->Name = L"metroToggleSOUND";
				 this->metroToggleSOUND->Size = System::Drawing::Size(80, 17);
				 this->metroToggleSOUND->TabIndex = 51;
				 this->metroToggleSOUND->Text = L"Aus";
				 this->metroToggleSOUND->UseSelectable = true;
				 //
				 // metroLabelTextProgramSettings
				 //
				 this->metroLabelTextProgramSettings->AutoSize = true;
				 this->metroLabelTextProgramSettings->FontWeight = MetroFramework::MetroLabelWeight::Bold;
				 this->metroLabelTextProgramSettings->Location = System::Drawing::Point(3, 11);
				 this->metroLabelTextProgramSettings->Name = L"metroLabelTextProgramSettings";
				 this->metroLabelTextProgramSettings->Size = System::Drawing::Size(118, 19);
				 this->metroLabelTextProgramSettings->TabIndex = 0;
				 this->metroLabelTextProgramSettings->Text = L"General Settings";
				 this->metroLabelTextProgramSettings->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 //
				 // metroTabPageThresholds
				 //
				 this->metroTabPageThresholds->Controls->Add(this->infoThresholds);
				 this->metroTabPageThresholds->Controls->Add(this->tableLayoutPanelUsageThresholds);
				 this->metroTabPageThresholds->Controls->Add(this->metroLabelTextUsageThresholds);
				 this->metroTabPageThresholds->HorizontalScrollbarBarColor = true;
				 this->metroTabPageThresholds->HorizontalScrollbarHighlightOnWheel = false;
				 this->metroTabPageThresholds->HorizontalScrollbarSize = 10;
				 this->metroTabPageThresholds->Location = System::Drawing::Point(4, 38);
				 this->metroTabPageThresholds->Name = L"metroTabPageThresholds";
				 this->metroTabPageThresholds->Size = System::Drawing::Size(731, 224);
				 this->metroTabPageThresholds->TabIndex = 4;
				 this->metroTabPageThresholds->Text = L"Thresholds";
				 this->metroTabPageThresholds->VerticalScrollbarBarColor = true;
				 this->metroTabPageThresholds->VerticalScrollbarHighlightOnWheel = false;
				 this->metroTabPageThresholds->VerticalScrollbarSize = 10;
				 //
				 // infoThresholds
				 //
				 this->infoThresholds->Enabled = false;
				 this->infoThresholds->Lines = gcnew cli::array< System::String^  >(1) {
					 L"Stand-Bye checks if the current usage is greater than the selected one. If it is,"
						 L" there will be no change to standby-mode. This prevents resource needing process"
						 L"es to be interrupted."
				 };
				 this->infoThresholds->Location = System::Drawing::Point(59, 37);
				 this->infoThresholds->MaxLength = 32767;
				 this->infoThresholds->Multiline = true;
				 this->infoThresholds->Name = L"infoThresholds";
				 this->infoThresholds->PasswordChar = '\0';
				 this->infoThresholds->ReadOnly = true;
				 this->infoThresholds->ScrollBars = System::Windows::Forms::ScrollBars::None;
				 this->infoThresholds->SelectedText = L"";
				 this->infoThresholds->Size = System::Drawing::Size(565, 42);
				 this->infoThresholds->TabIndex = 55;
				 this->infoThresholds->Text = L"Stand-Bye checks if the current usage is greater than the selected one. If it is,"
					 L" there will be no change to standby-mode. This prevents resource needing process"
					 L"es to be interrupted.";
				 this->infoThresholds->UseSelectable = true;
				 //
				 // tableLayoutPanelUsageThresholds
				 //
				 this->tableLayoutPanelUsageThresholds->BackColor = System::Drawing::Color::White;
				 this->tableLayoutPanelUsageThresholds->ColumnCount = 5;
				 this->tableLayoutPanelUsageThresholds->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanelUsageThresholds->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanelUsageThresholds->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanelUsageThresholds->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanelUsageThresholds->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelCurNET, 4, 4);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroToggleNET, 0, 4);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroToggleHDD, 0, 3);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelCurHDD, 4, 3);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabel13, 3, 4);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelCurRAM, 4, 2);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroToggleRAM, 0, 2);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelCurCPU, 4, 1);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroToggleCPU, 0, 1);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroTextBoxNET, 2, 4);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabel14, 3, 3);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelTextCPU, 1, 1);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelTextRAM, 1, 2);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelTextHDD, 1, 3);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelTextNET, 1, 4);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelRAMPer, 3, 2);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroTrackBarCPU, 2, 1);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelCPUPer, 3, 1);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroTextBoxHDD, 2, 3);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroTrackBarRAM, 2, 2);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelTextAverageUsage, 2, 0);
				 this->tableLayoutPanelUsageThresholds->Location = System::Drawing::Point(59, 85);
				 this->tableLayoutPanelUsageThresholds->Name = L"tableLayoutPanelUsageThresholds";
				 this->tableLayoutPanelUsageThresholds->RowCount = 5;
				 this->tableLayoutPanelUsageThresholds->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
					 20)));
				 this->tableLayoutPanelUsageThresholds->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
					 20)));
				 this->tableLayoutPanelUsageThresholds->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
					 20)));
				 this->tableLayoutPanelUsageThresholds->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
					 20)));
				 this->tableLayoutPanelUsageThresholds->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
					 20)));
				 this->tableLayoutPanelUsageThresholds->Size = System::Drawing::Size(568, 136);
				 this->tableLayoutPanelUsageThresholds->TabIndex = 57;
				 //
				 // metroLabelCurNET
				 //
				 this->metroLabelCurNET->AutoSize = true;
				 this->metroLabelCurNET->BackColor = System::Drawing::SystemColors::Control;
				 this->metroLabelCurNET->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelCurNET->Location = System::Drawing::Point(462, 108);
				 this->metroLabelCurNET->Name = L"metroLabelCurNET";
				 this->metroLabelCurNET->Size = System::Drawing::Size(103, 28);
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
				 this->metroToggleNET->Location = System::Drawing::Point(3, 113);
				 this->metroToggleNET->Margin = System::Windows::Forms::Padding(3, 5, 3, 3);
				 this->metroToggleNET->Name = L"metroToggleNET";
				 this->metroToggleNET->Size = System::Drawing::Size(80, 20);
				 this->metroToggleNET->TabIndex = 49;
				 this->metroToggleNET->Text = L"Aus";
				 this->metroToggleNET->UseSelectable = true;
				 //
				 // metroToggleHDD
				 //
				 this->metroToggleHDD->AutoSize = true;
				 this->metroToggleHDD->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroToggleHDD->Location = System::Drawing::Point(3, 84);
				 this->metroToggleHDD->Name = L"metroToggleHDD";
				 this->metroToggleHDD->Size = System::Drawing::Size(80, 21);
				 this->metroToggleHDD->TabIndex = 48;
				 this->metroToggleHDD->Text = L"Aus";
				 this->metroToggleHDD->UseSelectable = true;
				 //
				 // metroLabelCurHDD
				 //
				 this->metroLabelCurHDD->AutoSize = true;
				 this->metroLabelCurHDD->BackColor = System::Drawing::SystemColors::Control;
				 this->metroLabelCurHDD->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelCurHDD->Location = System::Drawing::Point(462, 81);
				 this->metroLabelCurHDD->Name = L"metroLabelCurHDD";
				 this->metroLabelCurHDD->Size = System::Drawing::Size(103, 27);
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
				 this->metroLabel13->Location = System::Drawing::Point(410, 108);
				 this->metroLabel13->Name = L"metroLabel13";
				 this->metroLabel13->Size = System::Drawing::Size(46, 28);
				 this->metroLabel13->TabIndex = 36;
				 this->metroLabel13->Text = L"MBit/s";
				 this->metroLabel13->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 //
				 // metroLabelCurRAM
				 //
				 this->metroLabelCurRAM->AutoSize = true;
				 this->metroLabelCurRAM->BackColor = System::Drawing::SystemColors::Control;
				 this->metroLabelCurRAM->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelCurRAM->Location = System::Drawing::Point(462, 54);
				 this->metroLabelCurRAM->Name = L"metroLabelCurRAM";
				 this->metroLabelCurRAM->Size = System::Drawing::Size(103, 27);
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
				 this->metroToggleRAM->Location = System::Drawing::Point(3, 57);
				 this->metroToggleRAM->Name = L"metroToggleRAM";
				 this->metroToggleRAM->Size = System::Drawing::Size(80, 21);
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
				 this->metroLabelCurCPU->Location = System::Drawing::Point(462, 27);
				 this->metroLabelCurCPU->Name = L"metroLabelCurCPU";
				 this->metroLabelCurCPU->Size = System::Drawing::Size(103, 27);
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
				 this->metroToggleCPU->Location = System::Drawing::Point(3, 30);
				 this->metroToggleCPU->Name = L"metroToggleCPU";
				 this->metroToggleCPU->Size = System::Drawing::Size(80, 21);
				 this->metroToggleCPU->TabIndex = 46;
				 this->metroToggleCPU->Text = L"Aus";
				 this->metroToggleCPU->UseSelectable = true;
				 //
				 // metroTextBoxNET
				 //
				 this->metroTextBoxNET->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroTextBoxNET->Lines = gcnew cli::array< System::String^  >(1) { L" " };
				 this->metroTextBoxNET->Location = System::Drawing::Point(213, 110);
				 this->metroTextBoxNET->Margin = System::Windows::Forms::Padding(2);
				 this->metroTextBoxNET->MaxLength = 3;
				 this->metroTextBoxNET->Name = L"metroTextBoxNET";
				 this->metroTextBoxNET->PasswordChar = '\0';
				 this->metroTextBoxNET->ScrollBars = System::Windows::Forms::ScrollBars::None;
				 this->metroTextBoxNET->SelectedText = L"";
				 this->metroTextBoxNET->Size = System::Drawing::Size(192, 24);
				 this->metroTextBoxNET->TabIndex = 45;
				 this->metroTextBoxNET->Text = L" ";
				 this->metroTextBoxNET->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
				 this->metroTextBoxNET->UseSelectable = true;
				 //
				 // metroLabel14
				 //
				 this->metroLabel14->AutoSize = true;
				 this->metroLabel14->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel14->Location = System::Drawing::Point(410, 81);
				 this->metroLabel14->Name = L"metroLabel14";
				 this->metroLabel14->Size = System::Drawing::Size(46, 27);
				 this->metroLabel14->TabIndex = 37;
				 this->metroLabel14->Text = L"MBit/s";
				 this->metroLabel14->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 //
				 // metroLabelTextCPU
				 //
				 this->metroLabelTextCPU->AutoSize = true;
				 this->metroLabelTextCPU->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelTextCPU->Location = System::Drawing::Point(89, 27);
				 this->metroLabelTextCPU->Name = L"metroLabelTextCPU";
				 this->metroLabelTextCPU->Size = System::Drawing::Size(119, 27);
				 this->metroLabelTextCPU->TabIndex = 30;
				 this->metroLabelTextCPU->Text = L"CPU Threshold";
				 this->metroLabelTextCPU->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 //
				 // metroLabelTextRAM
				 //
				 this->metroLabelTextRAM->AutoSize = true;
				 this->metroLabelTextRAM->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelTextRAM->Location = System::Drawing::Point(89, 54);
				 this->metroLabelTextRAM->Name = L"metroLabelTextRAM";
				 this->metroLabelTextRAM->Size = System::Drawing::Size(119, 27);
				 this->metroLabelTextRAM->TabIndex = 31;
				 this->metroLabelTextRAM->Text = L"RAM Threshold";
				 this->metroLabelTextRAM->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 //
				 // metroLabelTextHDD
				 //
				 this->metroLabelTextHDD->AutoSize = true;
				 this->metroLabelTextHDD->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelTextHDD->Location = System::Drawing::Point(89, 81);
				 this->metroLabelTextHDD->Name = L"metroLabelTextHDD";
				 this->metroLabelTextHDD->Size = System::Drawing::Size(119, 27);
				 this->metroLabelTextHDD->TabIndex = 32;
				 this->metroLabelTextHDD->Text = L"HDD Threshold";
				 this->metroLabelTextHDD->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 //
				 // metroLabelTextNET
				 //
				 this->metroLabelTextNET->AutoSize = true;
				 this->metroLabelTextNET->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelTextNET->Location = System::Drawing::Point(89, 108);
				 this->metroLabelTextNET->Name = L"metroLabelTextNET";
				 this->metroLabelTextNET->Size = System::Drawing::Size(119, 28);
				 this->metroLabelTextNET->TabIndex = 33;
				 this->metroLabelTextNET->Text = L"Network Threshold";
				 this->metroLabelTextNET->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 //
				 // metroLabelRAMPer
				 //
				 this->metroLabelRAMPer->AutoSize = true;
				 this->metroLabelRAMPer->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelRAMPer->Location = System::Drawing::Point(410, 54);
				 this->metroLabelRAMPer->Name = L"metroLabelRAMPer";
				 this->metroLabelRAMPer->Size = System::Drawing::Size(46, 27);
				 this->metroLabelRAMPer->TabIndex = 35;
				 this->metroLabelRAMPer->Text = L"%";
				 this->metroLabelRAMPer->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 //
				 // metroTrackBarCPU
				 //
				 this->metroTrackBarCPU->BackColor = System::Drawing::Color::Transparent;
				 this->metroTrackBarCPU->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroTrackBarCPU->Location = System::Drawing::Point(214, 30);
				 this->metroTrackBarCPU->Name = L"metroTrackBarCPU";
				 this->metroTrackBarCPU->Size = System::Drawing::Size(190, 21);
				 this->metroTrackBarCPU->TabIndex = 42;
				 this->metroTrackBarCPU->Text = L"metroTrackBar1";
				 //
				 // metroLabelCPUPer
				 //
				 this->metroLabelCPUPer->AutoSize = true;
				 this->metroLabelCPUPer->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelCPUPer->Location = System::Drawing::Point(410, 27);
				 this->metroLabelCPUPer->Name = L"metroLabelCPUPer";
				 this->metroLabelCPUPer->Size = System::Drawing::Size(46, 27);
				 this->metroLabelCPUPer->TabIndex = 34;
				 this->metroLabelCPUPer->Text = L"%";
				 this->metroLabelCPUPer->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 //
				 // metroTextBoxHDD
				 //
				 this->metroTextBoxHDD->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroTextBoxHDD->Lines = gcnew cli::array< System::String^  >(1) { L" " };
				 this->metroTextBoxHDD->Location = System::Drawing::Point(213, 83);
				 this->metroTextBoxHDD->Margin = System::Windows::Forms::Padding(2);
				 this->metroTextBoxHDD->MaxLength = 3;
				 this->metroTextBoxHDD->Name = L"metroTextBoxHDD";
				 this->metroTextBoxHDD->PasswordChar = '\0';
				 this->metroTextBoxHDD->ScrollBars = System::Windows::Forms::ScrollBars::None;
				 this->metroTextBoxHDD->SelectedText = L"";
				 this->metroTextBoxHDD->Size = System::Drawing::Size(192, 23);
				 this->metroTextBoxHDD->TabIndex = 44;
				 this->metroTextBoxHDD->Text = L" ";
				 this->metroTextBoxHDD->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
				 this->metroTextBoxHDD->UseSelectable = true;
				 //
				 // metroTrackBarRAM
				 //
				 this->metroTrackBarRAM->BackColor = System::Drawing::Color::Transparent;
				 this->metroTrackBarRAM->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroTrackBarRAM->Location = System::Drawing::Point(214, 57);
				 this->metroTrackBarRAM->Name = L"metroTrackBarRAM";
				 this->metroTrackBarRAM->Size = System::Drawing::Size(190, 21);
				 this->metroTrackBarRAM->TabIndex = 43;
				 this->metroTrackBarRAM->Text = L"metroTrackBar2";
				 //
				 // metroLabelTextAverageUsage
				 //
				 this->metroLabelTextAverageUsage->AutoSize = true;
				 this->tableLayoutPanelUsageThresholds->SetColumnSpan(this->metroLabelTextAverageUsage, 3);
				 this->metroLabelTextAverageUsage->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelTextAverageUsage->FontWeight = MetroFramework::MetroLabelWeight::Regular;
				 this->metroLabelTextAverageUsage->Location = System::Drawing::Point(214, 0);
				 this->metroLabelTextAverageUsage->Name = L"metroLabelTextAverageUsage";
				 this->metroLabelTextAverageUsage->Size = System::Drawing::Size(351, 27);
				 this->metroLabelTextAverageUsage->TabIndex = 50;
				 this->metroLabelTextAverageUsage->Text = L"Average Usage:";
				 this->metroLabelTextAverageUsage->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->metroToolTip1->SetToolTip(this->metroLabelTextAverageUsage, L"   Stand-Bye uses the average usage over 15 sec. (measurement 2 times / sec)");
				 //
				 // metroLabelTextUsageThresholds
				 //
				 this->metroLabelTextUsageThresholds->AutoSize = true;
				 this->metroLabelTextUsageThresholds->FontWeight = MetroFramework::MetroLabelWeight::Bold;
				 this->metroLabelTextUsageThresholds->Location = System::Drawing::Point(3, 15);
				 this->metroLabelTextUsageThresholds->Name = L"metroLabelTextUsageThresholds";
				 this->metroLabelTextUsageThresholds->Size = System::Drawing::Size(178, 19);
				 this->metroLabelTextUsageThresholds->TabIndex = 30;
				 this->metroLabelTextUsageThresholds->Text = L"System Usage Thresholds";
				 this->metroLabelTextUsageThresholds->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 //
				 // metroTabPageExcpProcess
				 //
				 this->metroTabPageExcpProcess->Controls->Add(this->tableLayoutPanel5);
				 this->metroTabPageExcpProcess->HorizontalScrollbarBarColor = true;
				 this->metroTabPageExcpProcess->HorizontalScrollbarHighlightOnWheel = false;
				 this->metroTabPageExcpProcess->HorizontalScrollbarSize = 0;
				 this->metroTabPageExcpProcess->Location = System::Drawing::Point(4, 38);
				 this->metroTabPageExcpProcess->Name = L"metroTabPageExcpProcess";
				 this->metroTabPageExcpProcess->Size = System::Drawing::Size(731, 224);
				 this->metroTabPageExcpProcess->TabIndex = 1;
				 this->metroTabPageExcpProcess->Text = L"Exception Processes";
				 this->metroTabPageExcpProcess->VerticalScrollbarBarColor = true;
				 this->metroTabPageExcpProcess->VerticalScrollbarHighlightOnWheel = false;
				 this->metroTabPageExcpProcess->VerticalScrollbarSize = 0;
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
				 this->tableLayoutPanel5->Size = System::Drawing::Size(731, 224);
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
				 this->listViewProc->Size = System::Drawing::Size(491, 204);
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
				 this->tableLayoutPanel6->Controls->Add(this->infoExcpProcesses, 0, 0);
				 this->tableLayoutPanel6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel6->Location = System::Drawing::Point(514, 3);
				 this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
				 this->tableLayoutPanel6->RowCount = 2;
				 this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel6->Size = System::Drawing::Size(214, 218);
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
				 this->tableLayoutPanel7->Location = System::Drawing::Point(3, 112);
				 this->tableLayoutPanel7->Name = L"tableLayoutPanel7";
				 this->tableLayoutPanel7->RowCount = 4;
				 this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel7->Size = System::Drawing::Size(208, 103);
				 this->tableLayoutPanel7->TabIndex = 0;
				 //
				 // metroButtonRemove
				 //
				 this->metroButtonRemove->BackColor = System::Drawing::Color::DarkCyan;
				 this->metroButtonRemove->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroButtonRemove->Location = System::Drawing::Point(5, 55);
				 this->metroButtonRemove->Margin = System::Windows::Forms::Padding(5);
				 this->metroButtonRemove->Name = L"metroButtonRemove";
				 this->metroButtonRemove->Size = System::Drawing::Size(198, 15);
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
				 this->metroButtonAddFromList->Location = System::Drawing::Point(5, 30);
				 this->metroButtonAddFromList->Margin = System::Windows::Forms::Padding(5);
				 this->metroButtonAddFromList->Name = L"metroButtonAddFromList";
				 this->metroButtonAddFromList->Size = System::Drawing::Size(198, 15);
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
				 this->metroButtonAddFromFile->Size = System::Drawing::Size(198, 15);
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
				 this->tableLayoutPanel8->Location = System::Drawing::Point(3, 78);
				 this->tableLayoutPanel8->Name = L"tableLayoutPanel8";
				 this->tableLayoutPanel8->RowCount = 1;
				 this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
				 this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 22)));
				 this->tableLayoutPanel8->Size = System::Drawing::Size(202, 22);
				 this->tableLayoutPanel8->TabIndex = 3;
				 //
				 // metroToggleView
				 //
				 this->metroToggleView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
				 this->metroToggleView->AutoSize = true;
				 this->metroToggleView->Location = System::Drawing::Point(111, 7);
				 this->metroToggleView->Margin = System::Windows::Forms::Padding(7);
				 this->metroToggleView->Name = L"metroToggleView";
				 this->metroToggleView->Size = System::Drawing::Size(80, 8);
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
				 this->metroLabelView->Size = System::Drawing::Size(95, 22);
				 this->metroLabelView->TabIndex = 4;
				 this->metroLabelView->Text = L"Show Details";
				 this->metroLabelView->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 //
				 // infoExcpProcesses
				 //
				 this->infoExcpProcesses->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->infoExcpProcesses->Enabled = false;
				 this->infoExcpProcesses->Lines = gcnew cli::array< System::String^  >(1) {
					 L"If at least one of the set up processes is running, the program will prevent the "
						 L"system from changing over to standby mode."
				 };
				 this->infoExcpProcesses->Location = System::Drawing::Point(3, 3);
				 this->infoExcpProcesses->MaxLength = 32767;
				 this->infoExcpProcesses->Multiline = true;
				 this->infoExcpProcesses->Name = L"infoExcpProcesses";
				 this->infoExcpProcesses->PasswordChar = '\0';
				 this->infoExcpProcesses->ScrollBars = System::Windows::Forms::ScrollBars::None;
				 this->infoExcpProcesses->SelectedText = L"";
				 this->infoExcpProcesses->Size = System::Drawing::Size(208, 103);
				 this->infoExcpProcesses->TabIndex = 1;
				 this->infoExcpProcesses->Text = L"If at least one of the set up processes is running, the program will prevent the "
					 L"system from changing over to standby mode.";
				 this->infoExcpProcesses->UseSelectable = true;
				 //
				 // metroTabPageAdvSettings
				 //
				 this->metroTabPageAdvSettings->Controls->Add(this->tableLayoutPanel11);
				 this->metroTabPageAdvSettings->HorizontalScrollbarBarColor = true;
				 this->metroTabPageAdvSettings->HorizontalScrollbarHighlightOnWheel = false;
				 this->metroTabPageAdvSettings->HorizontalScrollbarSize = 0;
				 this->metroTabPageAdvSettings->Location = System::Drawing::Point(4, 38);
				 this->metroTabPageAdvSettings->Name = L"metroTabPageAdvSettings";
				 this->metroTabPageAdvSettings->Size = System::Drawing::Size(731, 224);
				 this->metroTabPageAdvSettings->TabIndex = 3;
				 this->metroTabPageAdvSettings->Text = L"Advanced Settings";
				 this->metroTabPageAdvSettings->VerticalScrollbarBarColor = true;
				 this->metroTabPageAdvSettings->VerticalScrollbarHighlightOnWheel = false;
				 this->metroTabPageAdvSettings->VerticalScrollbarSize = 0;
				 //
				 // tableLayoutPanel11
				 //
				 this->tableLayoutPanel11->BackColor = System::Drawing::Color::White;
				 this->tableLayoutPanel11->ColumnCount = 2;
				 this->tableLayoutPanel11->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 50)));
				 this->tableLayoutPanel11->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 50)));
				 this->tableLayoutPanel11->Controls->Add(this->metroLabelTextUpdates, 0, 2);
				 this->tableLayoutPanel11->Controls->Add(this->metroToggleUPDATES, 1, 2);
				 this->tableLayoutPanel11->Controls->Add(this->metroLabelTextAutoStart, 0, 0);
				 this->tableLayoutPanel11->Controls->Add(this->metroToggleAutoStart, 1, 0);
				 this->tableLayoutPanel11->Controls->Add(this->metroLabelTextMessages, 0, 3);
				 this->tableLayoutPanel11->Controls->Add(this->metroToggleMessages, 1, 3);
				 this->tableLayoutPanel11->Controls->Add(this->metroLabelTextLanguage, 0, 1);
				 this->tableLayoutPanel11->Controls->Add(this->metroComboBoxLanguage, 1, 1);
				 this->tableLayoutPanel11->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel11->Location = System::Drawing::Point(0, 0);
				 this->tableLayoutPanel11->Name = L"tableLayoutPanel11";
				 this->tableLayoutPanel11->RowCount = 6;
				 this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
				 this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
				 this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
				 this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
				 this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
				 this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 16.66667F)));
				 this->tableLayoutPanel11->Size = System::Drawing::Size(731, 224);
				 this->tableLayoutPanel11->TabIndex = 2;
				 //
				 // metroLabelTextUpdates
				 //
				 this->metroLabelTextUpdates->AutoSize = true;
				 this->metroLabelTextUpdates->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelTextUpdates->Location = System::Drawing::Point(3, 74);
				 this->metroLabelTextUpdates->Name = L"metroLabelTextUpdates";
				 this->metroLabelTextUpdates->Size = System::Drawing::Size(359, 37);
				 this->metroLabelTextUpdates->TabIndex = 6;
				 this->metroLabelTextUpdates->Text = L"Search for Updates:";
				 this->metroLabelTextUpdates->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->metroToolTip1->SetToolTip(this->metroLabelTextUpdates, L"  Determine if Stand-Bye! should search for updates.");
				 //
				 // metroToggleUPDATES
				 //
				 this->metroToggleUPDATES->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
					 | System::Windows::Forms::AnchorStyles::Left));
				 this->metroToggleUPDATES->AutoSize = true;
				 this->metroToggleUPDATES->Location = System::Drawing::Point(370, 86);
				 this->metroToggleUPDATES->Margin = System::Windows::Forms::Padding(5, 12, 0, 12);
				 this->metroToggleUPDATES->Name = L"metroToggleUPDATES";
				 this->metroToggleUPDATES->Size = System::Drawing::Size(80, 13);
				 this->metroToggleUPDATES->TabIndex = 7;
				 this->metroToggleUPDATES->Text = L"Aus";
				 this->metroToggleUPDATES->UseSelectable = true;
				 //
				 // metroLabelTextAutoStart
				 //
				 this->metroLabelTextAutoStart->AutoSize = true;
				 this->metroLabelTextAutoStart->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelTextAutoStart->Location = System::Drawing::Point(3, 0);
				 this->metroLabelTextAutoStart->Name = L"metroLabelTextAutoStart";
				 this->metroLabelTextAutoStart->Size = System::Drawing::Size(359, 37);
				 this->metroLabelTextAutoStart->TabIndex = 0;
				 this->metroLabelTextAutoStart->Text = L"Start with Windows:";
				 this->metroLabelTextAutoStart->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->metroToolTip1->SetToolTip(this->metroLabelTextAutoStart, L"Starts Stand-Bye! with windows.");
				 //
				 // metroToggleAutoStart
				 //
				 this->metroToggleAutoStart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
					 | System::Windows::Forms::AnchorStyles::Left));
				 this->metroToggleAutoStart->AutoSize = true;
				 this->metroToggleAutoStart->Location = System::Drawing::Point(370, 12);
				 this->metroToggleAutoStart->Margin = System::Windows::Forms::Padding(5, 12, 0, 12);
				 this->metroToggleAutoStart->Name = L"metroToggleAutoStart";
				 this->metroToggleAutoStart->Size = System::Drawing::Size(80, 13);
				 this->metroToggleAutoStart->TabIndex = 1;
				 this->metroToggleAutoStart->Text = L"Aus";
				 this->metroToggleAutoStart->UseSelectable = true;
				 this->metroToggleAutoStart->CheckedChanged += gcnew System::EventHandler(this, &MetroSettingsForm::metroToggleAutoStart_CheckedChanged);
				 //
				 // metroLabelTextMessages
				 //
				 this->metroLabelTextMessages->AutoSize = true;
				 this->metroLabelTextMessages->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelTextMessages->Location = System::Drawing::Point(3, 111);
				 this->metroLabelTextMessages->Name = L"metroLabelTextMessages";
				 this->metroLabelTextMessages->Size = System::Drawing::Size(359, 37);
				 this->metroLabelTextMessages->TabIndex = 8;
				 this->metroLabelTextMessages->Text = L"Show Messages";
				 this->metroLabelTextMessages->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->metroToolTip1->SetToolTip(this->metroLabelTextMessages, L"    Determine if Stand-Bye! should show messages from the icon (for ex. presentat"
					 L"ion mode enabled)");
				 //
				 // metroToggleMessages
				 //
				 this->metroToggleMessages->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
					 | System::Windows::Forms::AnchorStyles::Left));
				 this->metroToggleMessages->AutoSize = true;
				 this->metroToggleMessages->Location = System::Drawing::Point(370, 123);
				 this->metroToggleMessages->Margin = System::Windows::Forms::Padding(5, 12, 0, 12);
				 this->metroToggleMessages->Name = L"metroToggleMessages";
				 this->metroToggleMessages->Size = System::Drawing::Size(80, 13);
				 this->metroToggleMessages->TabIndex = 9;
				 this->metroToggleMessages->Text = L"Aus";
				 this->metroToggleMessages->UseSelectable = true;
				 //
				 // metroLabelTextLanguage
				 //
				 this->metroLabelTextLanguage->AutoSize = true;
				 this->metroLabelTextLanguage->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelTextLanguage->Location = System::Drawing::Point(3, 37);
				 this->metroLabelTextLanguage->Name = L"metroLabelTextLanguage";
				 this->metroLabelTextLanguage->Size = System::Drawing::Size(359, 37);
				 this->metroLabelTextLanguage->TabIndex = 10;
				 this->metroLabelTextLanguage->Text = L"Language:";
				 this->metroLabelTextLanguage->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 //
				 // metroComboBoxLanguage
				 //
				 this->metroComboBoxLanguage->DisplayMember = L"0";
				 this->metroComboBoxLanguage->FormattingEnabled = true;
				 this->metroComboBoxLanguage->ItemHeight = 23;
				 this->metroComboBoxLanguage->Location = System::Drawing::Point(368, 47);
				 this->metroComboBoxLanguage->Margin = System::Windows::Forms::Padding(3, 10, 3, 3);
				 this->metroComboBoxLanguage->Name = L"metroComboBoxLanguage";
				 this->metroComboBoxLanguage->Size = System::Drawing::Size(168, 29);
				 this->metroComboBoxLanguage->TabIndex = 11;
				 this->metroComboBoxLanguage->UseSelectable = true;
				 this->metroComboBoxLanguage->ValueMember = L"0";
				 this->metroComboBoxLanguage->SelectedIndexChanged += gcnew System::EventHandler(this, &MetroSettingsForm::LanguageIndexChanged);
				 //
				 // metroTabPageAbout
				 //
				 this->metroTabPageAbout->AutoScroll = true;
				 this->metroTabPageAbout->Controls->Add(this->tableLayoutPanel9);
				 this->metroTabPageAbout->Controls->Add(this->metroLabelTextAbout);
				 this->metroTabPageAbout->HorizontalScrollbar = true;
				 this->metroTabPageAbout->HorizontalScrollbarBarColor = true;
				 this->metroTabPageAbout->HorizontalScrollbarHighlightOnWheel = false;
				 this->metroTabPageAbout->HorizontalScrollbarSize = 5;
				 this->metroTabPageAbout->Location = System::Drawing::Point(4, 38);
				 this->metroTabPageAbout->Name = L"metroTabPageAbout";
				 this->metroTabPageAbout->Size = System::Drawing::Size(731, 224);
				 this->metroTabPageAbout->TabIndex = 2;
				 this->metroTabPageAbout->Text = L"About";
				 this->metroTabPageAbout->VerticalScrollbar = true;
				 this->metroTabPageAbout->VerticalScrollbarBarColor = true;
				 this->metroTabPageAbout->VerticalScrollbarHighlightOnWheel = false;
				 this->metroTabPageAbout->VerticalScrollbarSize = 5;
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
				 // metroLabelTextAbout
				 //
				 this->metroLabelTextAbout->Location = System::Drawing::Point(6, 75);
				 this->metroLabelTextAbout->Name = L"metroLabelTextAbout";
				 this->metroLabelTextAbout->Size = System::Drawing::Size(691, 1035);
				 this->metroLabelTextAbout->TabIndex = 1;
				 this->metroLabelTextAbout->Text = L"About:";
				 this->metroLabelTextAbout->WrapToLine = true;
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
				 this->tableLayoutPanel1->Size = System::Drawing::Size(759, 346);
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
				 this->tableLayoutPanel4->Controls->Add(this->metroLabelVersion, 0, 0);
				 this->tableLayoutPanel4->Controls->Add(this->metroLinkHomepage, 1, 0);
				 this->tableLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel4->Location = System::Drawing::Point(3, 289);
				 this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
				 this->tableLayoutPanel4->RowCount = 1;
				 this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
				 this->tableLayoutPanel4->Size = System::Drawing::Size(753, 54);
				 this->tableLayoutPanel4->TabIndex = 1;
				 //
				 // metroButtonOK
				 //
				 this->metroButtonOK->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroButtonOK->FontSize = MetroFramework::MetroButtonSize::Medium;
				 this->metroButtonOK->Location = System::Drawing::Point(610, 10);
				 this->metroButtonOK->Margin = System::Windows::Forms::Padding(10);
				 this->metroButtonOK->Name = L"metroButtonOK";
				 this->metroButtonOK->Size = System::Drawing::Size(133, 34);
				 this->metroButtonOK->TabIndex = 1;
				 this->metroButtonOK->Text = L"OK";
				 this->metroButtonOK->UseSelectable = true;
				 this->metroButtonOK->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroButtonOK_Click);
				 //
				 // metroButtonCancel
				 //
				 this->metroButtonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				 this->metroButtonCancel->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroButtonCancel->Location = System::Drawing::Point(460, 10);
				 this->metroButtonCancel->Margin = System::Windows::Forms::Padding(10);
				 this->metroButtonCancel->Name = L"metroButtonCancel";
				 this->metroButtonCancel->Size = System::Drawing::Size(130, 34);
				 this->metroButtonCancel->TabIndex = 0;
				 this->metroButtonCancel->Text = L"Cancel";
				 this->metroButtonCancel->UseSelectable = true;
				 this->metroButtonCancel->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroButtonCancel_Click);
				 //
				 // metroLabelVersion
				 //
				 this->metroLabelVersion->AutoSize = true;
				 this->metroLabelVersion->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelVersion->FontSize = MetroFramework::MetroLabelSize::Small;
				 this->metroLabelVersion->Location = System::Drawing::Point(3, 0);
				 this->metroLabelVersion->Name = L"metroLabelVersion";
				 this->metroLabelVersion->Size = System::Drawing::Size(144, 54);
				 this->metroLabelVersion->TabIndex = 2;
				 this->metroLabelVersion->Text = L"v0.5.2.0\n© Florian Baader, Stephan Le, Matthias Weirich";
				 this->metroLabelVersion->TextAlign = System::Drawing::ContentAlignment::BottomLeft;
				 this->metroLabelVersion->WrapToLine = true;
				 //
				 // metroLinkHomepage
				 //
				 this->metroLinkHomepage->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLinkHomepage->Location = System::Drawing::Point(153, 3);
				 this->metroLinkHomepage->Name = L"metroLinkHomepage";
				 this->metroLinkHomepage->Size = System::Drawing::Size(144, 48);
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
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->BackImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackImage")));
				 this->BackImagePadding = System::Windows::Forms::Padding(0, 5, 0, 0);
				 this->BackMaxSize = 760;
				 this->BorderStyle = MetroFramework::Forms::MetroFormBorderStyle::FixedSingle;
				 this->CancelButton = this->metroButtonCancel;
				 this->ClientSize = System::Drawing::Size(759, 406);
				 this->Controls->Add(this->tableLayoutPanel1);
				 this->MaximizeBox = false;
				 this->MinimizeBox = false;
				 this->Name = L"MetroSettingsForm";
				 this->Padding = System::Windows::Forms::Padding(0, 60, 0, 0);
				 this->Resizable = false;
				 this->ShadowType = MetroFramework::Forms::MetroFormShadowType::DropShadow;
				 this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
				 this->Style = MetroFramework::MetroColorStyle::Green;
				 this->Closing += gcnew System::ComponentModel::CancelEventHandler(this, &MetroSettingsForm::OnClosing);
				 this->Load += gcnew System::EventHandler(this, &MetroSettingsForm::MetroSettingsForm_Load);
				 this->VisibleChanged += gcnew System::EventHandler(this, &MetroSettingsForm::OnVisibleChanged);
				 this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MetroSettingsForm::OnKeyDown);
				 this->metroTabControl1->ResumeLayout(false);
				 this->metroTabPageSettings->ResumeLayout(false);
				 this->metroTabPageSettings->PerformLayout();
				 this->tableLayoutPanelProgrammSettings->ResumeLayout(false);
				 this->tableLayoutPanelProgrammSettings->PerformLayout();
				 this->tableLayoutPanel12->ResumeLayout(false);
				 this->tableLayoutPanel12->PerformLayout();
				 this->metroTabPageThresholds->ResumeLayout(false);
				 this->metroTabPageThresholds->PerformLayout();
				 this->tableLayoutPanelUsageThresholds->ResumeLayout(false);
				 this->tableLayoutPanelUsageThresholds->PerformLayout();
				 this->metroTabPageExcpProcess->ResumeLayout(false);
				 this->tableLayoutPanel5->ResumeLayout(false);
				 this->tableLayoutPanel6->ResumeLayout(false);
				 this->tableLayoutPanel7->ResumeLayout(false);
				 this->tableLayoutPanel8->ResumeLayout(false);
				 this->tableLayoutPanel8->PerformLayout();
				 this->metroTabPageAdvSettings->ResumeLayout(false);
				 this->tableLayoutPanel11->ResumeLayout(false);
				 this->tableLayoutPanel11->PerformLayout();
				 this->metroTabPageAbout->ResumeLayout(false);
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

		//Events
		void OnVisibleChanged(System::Object ^sender, System::EventArgs ^e);
		void OnClosing(System::Object ^sender, System::ComponentModel::CancelEventArgs ^e);
		void OnKeyDown(System::Object ^sender, System::Windows::Forms::KeyEventArgs ^e);

		//Switching Language
		void switchLanguage();
		void LanguageIndexChanged(System::Object ^sender, System::EventArgs ^e);
	};
}
