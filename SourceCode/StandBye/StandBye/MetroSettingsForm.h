#pragma once
#include "stdafx.h"
#include "SystemMetricWatcher.h"
#include "SettingsProvider.h"
#include "InputMonitor.h"
#include "ProcessItem.h"
#include "ProcessSelectionForm.h"
#include "InfoBox.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
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
		ResourceManager^ res_manIMG;
		List<CultureInfo^>^ supportedLanguages;
		Drawing::Color lightGreen, darkGreen, lightRed, darkRed;
		Drawing::Size defined_size;

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
			this->MaximumSize = this->Size;

			//Defines colors
			lightGreen = ColorTranslator::FromHtml("#a5d6a7");
			darkGreen = ColorTranslator::FromHtml("#33691e");
			lightRed = ColorTranslator::FromHtml("#ef9a9a");
			darkRed = ColorTranslator::FromHtml(" #f44336");
		}

	protected:
		~MetroSettingsForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

#pragma region Windows Form Designer generated code
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextUpdates;
	private: MetroFramework::Components::MetroStyleExtender^  metroStyleExtender1;
	private: MetroFramework::Components::MetroStyleManager^  metroStyleManager1;
	private: MetroFramework::Components::MetroToolTip^  metroToolTip1;
	private: MetroFramework::Controls::MetroButton^  metroButtonAddFromFile;
	private: MetroFramework::Controls::MetroButton^  metroButtonAddFromList;
	private: MetroFramework::Controls::MetroButton^  metroButtonCancel;
	private: MetroFramework::Controls::MetroButton^  metroButtonOK;
	private: MetroFramework::Controls::MetroButton^  metroButtonRemove;
	private: MetroFramework::Controls::MetroComboBox^  metroComboBox1;
	private: MetroFramework::Controls::MetroComboBox^  metroComboBoxLanguage;
	private: MetroFramework::Controls::MetroLabel^  explCPU;
	private: MetroFramework::Controls::MetroLabel^  explHDD;
	private: MetroFramework::Controls::MetroLabel^  explNET;
	private: MetroFramework::Controls::MetroLabel^  explRAM;
	private: MetroFramework::Controls::MetroLabel^  metroLabel10;
	private: MetroFramework::Controls::MetroLabel^  metroLabelNETStatus;
	private: MetroFramework::Controls::MetroTrackBar^  metroTrackBarHDD;
	private: MetroFramework::Controls::MetroTrackBar^  metroTrackBarNET;
	private: MetroFramework::Controls::MetroLabel^  metroLabelHDDStatus;
	private: MetroFramework::Controls::MetroLabel^  metroLabel1;
	private: MetroFramework::Controls::MetroLabel^  metroLabel2;
	private: MetroFramework::Controls::MetroLabel^  metroLabel3;
	private: MetroFramework::Controls::MetroLabel^  metroLabel4;
	private: MetroFramework::Controls::MetroLabel^  metroLabel5;
	private: MetroFramework::Controls::MetroLabel^  metroLabel6;
	private: MetroFramework::Controls::MetroLabel^  metroLabelCPUPer;
	private: MetroFramework::Controls::MetroLabel^  metroLabelCurCPU;
	private: MetroFramework::Controls::MetroLabel^  metroLabelCurHDD;
	private: MetroFramework::Controls::MetroLabel^  metroLabelCurNET;
	private: MetroFramework::Controls::MetroLabel^  metroLabelCurRAM;
	private: MetroFramework::Controls::MetroLabel^  metroLabelRAMPer;
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextAbout;
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextAutoStart;
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextAverageUsage;
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextCPU;
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextHDD;
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextLanguage;
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextMessages;
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextNET;
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextRAM;
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextSound;
	private: MetroFramework::Controls::MetroLabel^  metroLabelTextWaitTime;
	private: MetroFramework::Controls::MetroLabel^  metroLabelVersion;
	private: MetroFramework::Controls::MetroLabel^  metroLabelView;
	private: MetroFramework::Controls::MetroLink^  metroLinkHomepage;
	private: MetroFramework::Controls::MetroTabControl^  metroTabControl1;
	private: MetroFramework::Controls::MetroTabPage^  metroTabPageAbout;
	private: MetroFramework::Controls::MetroTabPage^  metroTabPageAdvSettings;
	private: MetroFramework::Controls::MetroTabPage^  metroTabPageExcpProcess;
	private: MetroFramework::Controls::MetroTabPage^  metroTabPageSettings;
	private: MetroFramework::Controls::MetroTabPage^  metroTabPageThresholds;
	private: MetroFramework::Controls::MetroTextBox^  infoExcpProcesses;
	private: MetroFramework::Controls::MetroTextBox^  infoGeneral;
	private: MetroFramework::Controls::MetroTextBox^  infoThresholds;

	private: MetroFramework::Controls::MetroTile^  metroTileAbout;
	private: MetroFramework::Controls::MetroTile^  metroTileVisit;
	private: MetroFramework::Controls::MetroTile^  metroTileProcesses;
	private: MetroFramework::Controls::MetroTile^  metroTileSettings;

	private: MetroFramework::Controls::MetroTile^  metroTileCanceledStatus;

	private: MetroFramework::Controls::MetroTile^  metroTileGithub;
	private: MetroFramework::Controls::MetroTile^  metroTileHomepage;
	private: MetroFramework::Controls::MetroTile^  metroTilePresMode;
	private: MetroFramework::Controls::MetroToggle^  metroToggle2;
	private: MetroFramework::Controls::MetroToggle^  metroToggleAutoStart;
	private: MetroFramework::Controls::MetroToggle^  metroToggleCPU;
	private: MetroFramework::Controls::MetroToggle^  metroToggleHDD;
	private: MetroFramework::Controls::MetroToggle^  metroToggleMessages;
	private: MetroFramework::Controls::MetroToggle^  metroToggleNET;
	private: MetroFramework::Controls::MetroToggle^  metroToggleRAM;
	private: MetroFramework::Controls::MetroToggle^  metroToggleSOUND;
	private: MetroFramework::Controls::MetroToggle^  metroToggleUPDATES;
	private: MetroFramework::Controls::MetroToggle^  metroToggleView;
	private: MetroFramework::Controls::MetroTrackBar^  metroTrackBarCPU;
	private: MetroFramework::Controls::MetroTrackBar^  metroTrackBarRAM;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::ListView^  listViewProc;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPaneWaitTime;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel10;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel11;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel12;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel13;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel14;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel3;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel4;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel5;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel6;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel7;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel8;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel9;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanelUsageThresholds;
	private: System::Windows::Forms::TextBox^  textBoxTimeMIN;
	private: System::Windows::Forms::TextBox^  textBoxTimeSEC;
	private: System::Windows::Forms::Timer^  timerRefresh;

			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MetroSettingsForm::typeid));
				 this->metroTabControl1 = (gcnew MetroFramework::Controls::MetroTabControl());
				 this->metroTabPageSettings = (gcnew MetroFramework::Controls::MetroTabPage());
				 this->tableLayoutPanel10 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->infoGeneral = (gcnew MetroFramework::Controls::MetroTextBox());
				 this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				 this->tableLayoutPanel12 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->tableLayoutPaneWaitTime = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->metroLabel5 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->textBoxTimeSEC = (gcnew System::Windows::Forms::TextBox());
				 this->metroLabel10 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabelTextWaitTime = (gcnew MetroFramework::Controls::MetroLabel());
				 this->textBoxTimeMIN = (gcnew System::Windows::Forms::TextBox());
				 this->metroTileCanceledStatus = (gcnew MetroFramework::Controls::MetroTile());
				 this->metroTileSettings = (gcnew MetroFramework::Controls::MetroTile());
				 this->metroTileProcesses = (gcnew MetroFramework::Controls::MetroTile());
				 this->metroTileVisit = (gcnew MetroFramework::Controls::MetroTile());
				 this->metroTileAbout = (gcnew MetroFramework::Controls::MetroTile());
				 this->metroTilePresMode = (gcnew MetroFramework::Controls::MetroTile());
				 this->metroTabPageThresholds = (gcnew MetroFramework::Controls::MetroTabPage());
				 this->tableLayoutPanel13 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
				 this->tableLayoutPanel14 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->metroToggleSOUND = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroLabelTextSound = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabel3 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->infoThresholds = (gcnew MetroFramework::Controls::MetroTextBox());
				 this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
				 this->tableLayoutPanelUsageThresholds = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->metroLabelCurNET = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroToggleNET = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroToggleHDD = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroLabelCurHDD = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabelNETStatus = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabelCurRAM = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroToggleRAM = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroLabelCurCPU = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroToggleCPU = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroLabelHDDStatus = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabelTextCPU = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabelTextRAM = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabelTextHDD = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabelTextNET = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabelRAMPer = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroTrackBarCPU = (gcnew MetroFramework::Controls::MetroTrackBar());
				 this->metroLabelCPUPer = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroTrackBarRAM = (gcnew MetroFramework::Controls::MetroTrackBar());
				 this->explCPU = (gcnew MetroFramework::Controls::MetroLabel());
				 this->explRAM = (gcnew MetroFramework::Controls::MetroLabel());
				 this->explHDD = (gcnew MetroFramework::Controls::MetroLabel());
				 this->explNET = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabelTextAverageUsage = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroTrackBarHDD = (gcnew MetroFramework::Controls::MetroTrackBar());
				 this->metroTrackBarNET = (gcnew MetroFramework::Controls::MetroTrackBar());
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
				 this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->metroLabel4 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroToggle2 = (gcnew MetroFramework::Controls::MetroToggle());
				 this->metroLabel6 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroComboBox1 = (gcnew MetroFramework::Controls::MetroComboBox());
				 this->metroLabel2 = (gcnew MetroFramework::Controls::MetroLabel());
				 this->metroLabel1 = (gcnew MetroFramework::Controls::MetroLabel());
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
				 this->tableLayoutPanel10->SuspendLayout();
				 this->groupBox1->SuspendLayout();
				 this->tableLayoutPanel12->SuspendLayout();
				 this->tableLayoutPaneWaitTime->SuspendLayout();
				 this->metroTabPageThresholds->SuspendLayout();
				 this->tableLayoutPanel13->SuspendLayout();
				 this->groupBox3->SuspendLayout();
				 this->tableLayoutPanel14->SuspendLayout();
				 this->groupBox2->SuspendLayout();
				 this->tableLayoutPanelUsageThresholds->SuspendLayout();
				 this->metroTabPageExcpProcess->SuspendLayout();
				 this->tableLayoutPanel5->SuspendLayout();
				 this->tableLayoutPanel6->SuspendLayout();
				 this->tableLayoutPanel7->SuspendLayout();
				 this->tableLayoutPanel8->SuspendLayout();
				 this->metroTabPageAdvSettings->SuspendLayout();
				 this->tableLayoutPanel2->SuspendLayout();
				 this->tableLayoutPanel3->SuspendLayout();
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
				 this->metroTabControl1->SelectedIndex = 0;
				 this->metroTabControl1->Size = System::Drawing::Size(740, 350);
				 this->metroTabControl1->TabIndex = 0;
				 this->metroTabControl1->UseSelectable = true;
				 //
				 // metroTabPageSettings
				 //
				 this->metroTabPageSettings->BackColor = System::Drawing::SystemColors::Control;
				 this->metroTabPageSettings->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->metroTabPageSettings->Controls->Add(this->tableLayoutPanel10);
				 this->metroTabPageSettings->HorizontalScrollbarBarColor = false;
				 this->metroTabPageSettings->HorizontalScrollbarHighlightOnWheel = false;
				 this->metroTabPageSettings->HorizontalScrollbarSize = 0;
				 this->metroTabPageSettings->Location = System::Drawing::Point(4, 38);
				 this->metroTabPageSettings->Name = L"metroTabPageSettings";
				 this->metroTabPageSettings->Size = System::Drawing::Size(732, 308);
				 this->metroTabPageSettings->Style = MetroFramework::MetroColorStyle::Green;
				 this->metroTabPageSettings->TabIndex = 0;
				 this->metroTabPageSettings->Text = L"General";
				 this->metroTabPageSettings->VerticalScrollbarBarColor = false;
				 this->metroTabPageSettings->VerticalScrollbarHighlightOnWheel = false;
				 this->metroTabPageSettings->VerticalScrollbarSize = 0;
				 this->metroTabPageSettings->Visible = false;
				 //
				 // tableLayoutPanel10
				 //
				 this->tableLayoutPanel10->AutoSize = true;
				 this->tableLayoutPanel10->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				 this->tableLayoutPanel10->BackColor = System::Drawing::Color::White;
				 this->tableLayoutPanel10->ColumnCount = 1;
				 this->tableLayoutPanel10->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 100)));
				 this->tableLayoutPanel10->Controls->Add(this->infoGeneral, 0, 0);
				 this->tableLayoutPanel10->Controls->Add(this->groupBox1, 0, 1);
				 this->tableLayoutPanel10->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel10->Location = System::Drawing::Point(0, 0);
				 this->tableLayoutPanel10->Name = L"tableLayoutPanel10";
				 this->tableLayoutPanel10->RowCount = 2;
				 this->tableLayoutPanel10->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
				 this->tableLayoutPanel10->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
				 this->tableLayoutPanel10->Size = System::Drawing::Size(730, 306);
				 this->tableLayoutPanel10->TabIndex = 57;
				 //
				 // infoGeneral
				 //
				 this->infoGeneral->BackColor = System::Drawing::Color::LightBlue;
				 this->infoGeneral->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->infoGeneral->Lines = gcnew cli::array< System::String^  >(1) { resources->GetString(L"infoGeneral.Lines") };
				 this->infoGeneral->Location = System::Drawing::Point(3, 3);
				 this->infoGeneral->MaxLength = 32767;
				 this->infoGeneral->Multiline = true;
				 this->infoGeneral->Name = L"infoGeneral";
				 this->infoGeneral->PasswordChar = '\0';
				 this->infoGeneral->ReadOnly = true;
				 this->infoGeneral->ScrollBars = System::Windows::Forms::ScrollBars::None;
				 this->infoGeneral->SelectedText = L"";
				 this->infoGeneral->Size = System::Drawing::Size(724, 55);
				 this->infoGeneral->TabIndex = 56;
				 this->infoGeneral->Text = resources->GetString(L"infoGeneral.Text");
				 this->infoGeneral->UseCustomBackColor = true;
				 this->infoGeneral->UseSelectable = true;
				 //
				 // groupBox1
				 //
				 this->groupBox1->Controls->Add(this->tableLayoutPanel12);
				 this->groupBox1->Location = System::Drawing::Point(3, 64);
				 this->groupBox1->Name = L"groupBox1";
				 this->groupBox1->Size = System::Drawing::Size(724, 239);
				 this->groupBox1->TabIndex = 57;
				 this->groupBox1->TabStop = false;
				 //
				 // tableLayoutPanel12
				 //
				 this->tableLayoutPanel12->ColumnCount = 8;
				 this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
					 20)));
				 this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
					 20)));
				 this->tableLayoutPanel12->Controls->Add(this->tableLayoutPaneWaitTime, 0, 0);
				 this->tableLayoutPanel12->Controls->Add(this->metroTileCanceledStatus, 6, 0);
				 this->tableLayoutPanel12->Controls->Add(this->metroTileSettings, 1, 1);
				 this->tableLayoutPanel12->Controls->Add(this->metroTileProcesses, 2, 1);
				 this->tableLayoutPanel12->Controls->Add(this->metroTileVisit, 3, 1);
				 this->tableLayoutPanel12->Controls->Add(this->metroTileAbout, 4, 1);
				 this->tableLayoutPanel12->Controls->Add(this->metroTilePresMode, 7, 0);
				 this->tableLayoutPanel12->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel12->Location = System::Drawing::Point(3, 16);
				 this->tableLayoutPanel12->Name = L"tableLayoutPanel12";
				 this->tableLayoutPanel12->RowCount = 2;
				 this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
				 this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
				 this->tableLayoutPanel12->Size = System::Drawing::Size(718, 220);
				 this->tableLayoutPanel12->TabIndex = 62;
				 //
				 // tableLayoutPaneWaitTime
				 //
				 this->tableLayoutPaneWaitTime->AutoSize = true;
				 this->tableLayoutPaneWaitTime->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				 this->tableLayoutPaneWaitTime->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(76)),
					 static_cast<System::Int32>(static_cast<System::Byte>(175)), static_cast<System::Int32>(static_cast<System::Byte>(80)));
				 this->tableLayoutPaneWaitTime->ColumnCount = 3;
				 this->tableLayoutPanel12->SetColumnSpan(this->tableLayoutPaneWaitTime, 5);
				 this->tableLayoutPaneWaitTime->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPaneWaitTime->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPaneWaitTime->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPaneWaitTime->Controls->Add(this->metroLabel5, 2, 1);
				 this->tableLayoutPaneWaitTime->Controls->Add(this->textBoxTimeSEC, 1, 1);
				 this->tableLayoutPaneWaitTime->Controls->Add(this->metroLabel10, 2, 0);
				 this->tableLayoutPaneWaitTime->Controls->Add(this->metroLabelTextWaitTime, 0, 0);
				 this->tableLayoutPaneWaitTime->Controls->Add(this->textBoxTimeMIN, 1, 0);
				 this->tableLayoutPaneWaitTime->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPaneWaitTime->Location = System::Drawing::Point(3, 3);
				 this->tableLayoutPaneWaitTime->Name = L"tableLayoutPaneWaitTime";
				 this->tableLayoutPaneWaitTime->RowCount = 2;
				 this->tableLayoutPaneWaitTime->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
				 this->tableLayoutPaneWaitTime->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
				 this->tableLayoutPaneWaitTime->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
					 20)));
				 this->tableLayoutPaneWaitTime->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
					 20)));
				 this->tableLayoutPaneWaitTime->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
					 20)));
				 this->tableLayoutPaneWaitTime->Size = System::Drawing::Size(378, 118);
				 this->tableLayoutPaneWaitTime->TabIndex = 61;
				 //
				 // metroLabel5
				 //
				 this->metroLabel5->AutoSize = true;
				 this->metroLabel5->BackColor = System::Drawing::Color::Transparent;
				 this->metroLabel5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel5->FontSize = MetroFramework::MetroLabelSize::Tall;
				 this->metroLabel5->FontWeight = MetroFramework::MetroLabelWeight::Regular;
				 this->metroLabel5->ForeColor = System::Drawing::Color::White;
				 this->metroLabel5->Location = System::Drawing::Point(303, 59);
				 this->metroLabel5->Name = L"metroLabel5";
				 this->metroLabel5->Size = System::Drawing::Size(72, 59);
				 this->metroLabel5->TabIndex = 63;
				 this->metroLabel5->Text = L"s";
				 this->metroLabel5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->metroLabel5->UseCustomBackColor = true;
				 this->metroLabel5->UseCustomForeColor = true;
				 //
				 // textBoxTimeSEC
				 //
				 this->textBoxTimeSEC->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(76)), static_cast<System::Int32>(static_cast<System::Byte>(175)),
					 static_cast<System::Int32>(static_cast<System::Byte>(80)));
				 this->textBoxTimeSEC->BorderStyle = System::Windows::Forms::BorderStyle::None;
				 this->textBoxTimeSEC->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 35, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->textBoxTimeSEC->Location = System::Drawing::Point(210, 62);
				 this->textBoxTimeSEC->Name = L"textBoxTimeSEC";
				 this->textBoxTimeSEC->Size = System::Drawing::Size(87, 53);
				 this->textBoxTimeSEC->TabIndex = 62;
				 this->textBoxTimeSEC->Text = L"1";
				 this->textBoxTimeSEC->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
				 this->textBoxTimeSEC->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MetroSettingsForm::ReformatTextBoxValueOnReturn);
				 this->textBoxTimeSEC->MouseEnter += gcnew System::EventHandler(this, &MetroSettingsForm::OnTextBoxMouseEnter);
				 this->textBoxTimeSEC->MouseLeave += gcnew System::EventHandler(this, &MetroSettingsForm::OnTextBoxMouseLeave);
				 //
				 // metroLabel10
				 //
				 this->metroLabel10->AutoSize = true;
				 this->metroLabel10->BackColor = System::Drawing::Color::Transparent;
				 this->metroLabel10->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel10->FontSize = MetroFramework::MetroLabelSize::Tall;
				 this->metroLabel10->FontWeight = MetroFramework::MetroLabelWeight::Regular;
				 this->metroLabel10->ForeColor = System::Drawing::Color::White;
				 this->metroLabel10->Location = System::Drawing::Point(303, 0);
				 this->metroLabel10->Name = L"metroLabel10";
				 this->metroLabel10->Size = System::Drawing::Size(72, 59);
				 this->metroLabel10->TabIndex = 61;
				 this->metroLabel10->Text = L"min";
				 this->metroLabel10->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->metroLabel10->UseCustomBackColor = true;
				 this->metroLabel10->UseCustomForeColor = true;
				 //
				 // metroLabelTextWaitTime
				 //
				 this->metroLabelTextWaitTime->AutoSize = true;
				 this->metroLabelTextWaitTime->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelTextWaitTime->FontSize = MetroFramework::MetroLabelSize::Tall;
				 this->metroLabelTextWaitTime->FontWeight = MetroFramework::MetroLabelWeight::Bold;
				 this->metroLabelTextWaitTime->ForeColor = System::Drawing::Color::White;
				 this->metroLabelTextWaitTime->Location = System::Drawing::Point(0, 0);
				 this->metroLabelTextWaitTime->Margin = System::Windows::Forms::Padding(0);
				 this->metroLabelTextWaitTime->Name = L"metroLabelTextWaitTime";
				 this->tableLayoutPaneWaitTime->SetRowSpan(this->metroLabelTextWaitTime, 2);
				 this->metroLabelTextWaitTime->Size = System::Drawing::Size(207, 118);
				 this->metroLabelTextWaitTime->TabIndex = 57;
				 this->metroLabelTextWaitTime->Text = L"Activate Standby After";
				 this->metroLabelTextWaitTime->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->metroLabelTextWaitTime->Theme = MetroFramework::MetroThemeStyle::Light;
				 this->metroToolTip1->SetToolTip(this->metroLabelTextWaitTime, L"  The waiting time till standby starts.  ");
				 this->metroLabelTextWaitTime->UseCustomBackColor = true;
				 this->metroLabelTextWaitTime->UseCustomForeColor = true;
				 //
				 // textBoxTimeMIN
				 //
				 this->textBoxTimeMIN->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(76)), static_cast<System::Int32>(static_cast<System::Byte>(175)),
					 static_cast<System::Int32>(static_cast<System::Byte>(80)));
				 this->textBoxTimeMIN->BorderStyle = System::Windows::Forms::BorderStyle::None;
				 this->textBoxTimeMIN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 35, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->textBoxTimeMIN->Location = System::Drawing::Point(210, 3);
				 this->textBoxTimeMIN->Name = L"textBoxTimeMIN";
				 this->textBoxTimeMIN->Size = System::Drawing::Size(87, 53);
				 this->textBoxTimeMIN->TabIndex = 60;
				 this->textBoxTimeMIN->Text = L"1";
				 this->textBoxTimeMIN->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
				 this->textBoxTimeMIN->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MetroSettingsForm::ReformatTextBoxValueOnReturn);
				 this->textBoxTimeMIN->MouseEnter += gcnew System::EventHandler(this, &MetroSettingsForm::OnTextBoxMouseEnter);
				 this->textBoxTimeMIN->MouseLeave += gcnew System::EventHandler(this, &MetroSettingsForm::OnTextBoxMouseLeave);
				 //
				 // metroTileCanceledStatus
				 //
				 this->metroTileCanceledStatus->ActiveControl = nullptr;
				 this->metroTileCanceledStatus->Location = System::Drawing::Point(387, 3);
				 this->metroTileCanceledStatus->Name = L"metroTileCanceledStatus";
				 this->metroTileCanceledStatus->Size = System::Drawing::Size(127, 118);
				 this->metroTileCanceledStatus->Style = MetroFramework::MetroColorStyle::Teal;
				 this->metroTileCanceledStatus->TabIndex = 66;
				 this->metroTileCanceledStatus->Text = L"Stand-By Canceled";
				 this->metroTileCanceledStatus->TileImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"metroTileCanceledStatus.TileImage")));
				 this->metroTileCanceledStatus->TileImageAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroTileCanceledStatus->UseSelectable = true;
				 this->metroTileCanceledStatus->UseTileImage = true;
				 //
				 // metroTileSettings
				 //
				 this->metroTileSettings->ActiveControl = nullptr;
				 this->metroTileSettings->Location = System::Drawing::Point(3, 127);
				 this->metroTileSettings->Name = L"metroTileSettings";
				 this->metroTileSettings->Size = System::Drawing::Size(90, 90);
				 this->metroTileSettings->Style = MetroFramework::MetroColorStyle::Silver;
				 this->metroTileSettings->TabIndex = 65;
				 this->metroTileSettings->Text = L"Settings";
				 this->metroTileSettings->TileImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"metroTileSettings.TileImage")));
				 this->metroTileSettings->TileImageAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroTileSettings->UseSelectable = true;
				 this->metroTileSettings->UseTileImage = true;
				 this->metroTileSettings->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroTileSettings_Click);
				 this->metroTileSettings->MouseEnter += gcnew System::EventHandler(this, &MetroSettingsForm::OnMetroTileMouseEnter);
				 this->metroTileSettings->MouseLeave += gcnew System::EventHandler(this, &MetroSettingsForm::OnMetroTileMouseLeave);
				 //
				 // metroTileProcesses
				 //
				 this->metroTileProcesses->ActiveControl = nullptr;
				 this->metroTileProcesses->Location = System::Drawing::Point(99, 127);
				 this->metroTileProcesses->Name = L"metroTileProcesses";
				 this->metroTileProcesses->Size = System::Drawing::Size(90, 90);
				 this->metroTileProcesses->Style = MetroFramework::MetroColorStyle::Teal;
				 this->metroTileProcesses->TabIndex = 64;
				 this->metroTileProcesses->Text = L"Processes";
				 this->metroTileProcesses->TileImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"metroTileProcesses.TileImage")));
				 this->metroTileProcesses->TileImageAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroTileProcesses->UseSelectable = true;
				 this->metroTileProcesses->UseTileImage = true;
				 this->metroTileProcesses->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroTileProcesses_Click);
				 this->metroTileProcesses->MouseEnter += gcnew System::EventHandler(this, &MetroSettingsForm::OnMetroTileMouseEnter);
				 this->metroTileProcesses->MouseLeave += gcnew System::EventHandler(this, &MetroSettingsForm::OnMetroTileMouseLeave);
				 //
				 // metroTileVisit
				 //
				 this->metroTileVisit->ActiveControl = nullptr;
				 this->metroTileVisit->Location = System::Drawing::Point(195, 127);
				 this->metroTileVisit->Name = L"metroTileVisit";
				 this->metroTileVisit->Size = System::Drawing::Size(90, 90);
				 this->metroTileVisit->Style = MetroFramework::MetroColorStyle::Blue;
				 this->metroTileVisit->TabIndex = 63;
				 this->metroTileVisit->Text = L"Visit us!";
				 this->metroTileVisit->TileImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"metroTileVisit.TileImage")));
				 this->metroTileVisit->TileImageAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroTileVisit->UseSelectable = true;
				 this->metroTileVisit->UseTileImage = true;
				 this->metroTileVisit->Click += gcnew System::EventHandler(this, &MetroSettingsForm::OpenHomepageOnClick);
				 this->metroTileVisit->MouseEnter += gcnew System::EventHandler(this, &MetroSettingsForm::OnMetroTileMouseEnter);
				 this->metroTileVisit->MouseLeave += gcnew System::EventHandler(this, &MetroSettingsForm::OnMetroTileMouseLeave);
				 //
				 // metroTileAbout
				 //
				 this->metroTileAbout->ActiveControl = nullptr;
				 this->metroTileAbout->Location = System::Drawing::Point(291, 127);
				 this->metroTileAbout->Name = L"metroTileAbout";
				 this->metroTileAbout->Size = System::Drawing::Size(90, 90);
				 this->metroTileAbout->Style = MetroFramework::MetroColorStyle::Lime;
				 this->metroTileAbout->TabIndex = 62;
				 this->metroTileAbout->Text = L"About";
				 this->metroTileAbout->TileImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"metroTileAbout.TileImage")));
				 this->metroTileAbout->TileImageAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroTileAbout->UseSelectable = true;
				 this->metroTileAbout->UseTileImage = true;
				 this->metroTileAbout->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroTileAbout_Click);
				 this->metroTileAbout->MouseEnter += gcnew System::EventHandler(this, &MetroSettingsForm::OnMetroTileMouseEnter);
				 this->metroTileAbout->MouseLeave += gcnew System::EventHandler(this, &MetroSettingsForm::OnMetroTileMouseLeave);
				 //
				 // metroTilePresMode
				 //
				 this->metroTilePresMode->ActiveControl = nullptr;
				 this->metroTilePresMode->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->metroTilePresMode->Location = System::Drawing::Point(520, 3);
				 this->metroTilePresMode->Name = L"metroTilePresMode";
				 this->tableLayoutPanel12->SetRowSpan(this->metroTilePresMode, 2);
				 this->metroTilePresMode->Size = System::Drawing::Size(195, 214);
				 this->metroTilePresMode->Style = MetroFramework::MetroColorStyle::Blue;
				 this->metroTilePresMode->TabIndex = 54;
				 this->metroTilePresMode->Text = L"Presentation Mode";
				 this->metroTilePresMode->TileImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"metroTilePresMode.TileImage")));
				 this->metroTilePresMode->TileImageAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroTilePresMode->TileTextFontWeight = MetroFramework::MetroTileTextWeight::Bold;
				 this->metroTilePresMode->UseSelectable = true;
				 this->metroTilePresMode->UseTileImage = true;
				 this->metroTilePresMode->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroTilePresMode_Click);
				 this->metroTilePresMode->MouseEnter += gcnew System::EventHandler(this, &MetroSettingsForm::OnMetroTileMouseEnter);
				 this->metroTilePresMode->MouseLeave += gcnew System::EventHandler(this, &MetroSettingsForm::OnMetroTileMouseLeave);
				 //
				 // metroTabPageThresholds
				 //
				 this->metroTabPageThresholds->Controls->Add(this->tableLayoutPanel13);
				 this->metroTabPageThresholds->HorizontalScrollbarBarColor = true;
				 this->metroTabPageThresholds->HorizontalScrollbarHighlightOnWheel = false;
				 this->metroTabPageThresholds->HorizontalScrollbarSize = 0;
				 this->metroTabPageThresholds->Location = System::Drawing::Point(4, 38);
				 this->metroTabPageThresholds->Name = L"metroTabPageThresholds";
				 this->metroTabPageThresholds->Size = System::Drawing::Size(732, 308);
				 this->metroTabPageThresholds->TabIndex = 4;
				 this->metroTabPageThresholds->Text = L"Thresholds";
				 this->metroTabPageThresholds->VerticalScrollbarBarColor = true;
				 this->metroTabPageThresholds->VerticalScrollbarHighlightOnWheel = false;
				 this->metroTabPageThresholds->VerticalScrollbarSize = 0;
				 //
				 // tableLayoutPanel13
				 //
				 this->tableLayoutPanel13->AutoSize = true;
				 this->tableLayoutPanel13->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				 this->tableLayoutPanel13->BackColor = System::Drawing::Color::White;
				 this->tableLayoutPanel13->ColumnCount = 1;
				 this->tableLayoutPanel13->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 100)));
				 this->tableLayoutPanel13->Controls->Add(this->groupBox3, 0, 2);
				 this->tableLayoutPanel13->Controls->Add(this->infoThresholds, 0, 0);
				 this->tableLayoutPanel13->Controls->Add(this->groupBox2, 0, 1);
				 this->tableLayoutPanel13->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel13->Location = System::Drawing::Point(0, 0);
				 this->tableLayoutPanel13->Margin = System::Windows::Forms::Padding(10);
				 this->tableLayoutPanel13->Name = L"tableLayoutPanel13";
				 this->tableLayoutPanel13->RowCount = 3;
				 this->tableLayoutPanel13->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
				 this->tableLayoutPanel13->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
				 this->tableLayoutPanel13->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
				 this->tableLayoutPanel13->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
					 20)));
				 this->tableLayoutPanel13->Size = System::Drawing::Size(732, 308);
				 this->tableLayoutPanel13->TabIndex = 58;
				 //
				 // groupBox3
				 //
				 this->groupBox3->Controls->Add(this->tableLayoutPanel14);
				 this->groupBox3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->groupBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->groupBox3->Location = System::Drawing::Point(3, 214);
				 this->groupBox3->Name = L"groupBox3";
				 this->groupBox3->Size = System::Drawing::Size(726, 91);
				 this->groupBox3->TabIndex = 61;
				 this->groupBox3->TabStop = false;
				 this->groupBox3->Text = L"Extra Features";
				 //
				 // tableLayoutPanel14
				 //
				 this->tableLayoutPanel14->ColumnCount = 3;
				 this->tableLayoutPanel14->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanel14->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanel14->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
					 520)));
				 this->tableLayoutPanel14->Controls->Add(this->metroToggleSOUND, 0, 0);
				 this->tableLayoutPanel14->Controls->Add(this->metroLabelTextSound, 1, 0);
				 this->tableLayoutPanel14->Controls->Add(this->metroLabel3, 2, 0);
				 this->tableLayoutPanel14->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel14->Location = System::Drawing::Point(3, 17);
				 this->tableLayoutPanel14->Name = L"tableLayoutPanel14";
				 this->tableLayoutPanel14->RowCount = 1;
				 this->tableLayoutPanel14->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
				 this->tableLayoutPanel14->Size = System::Drawing::Size(720, 71);
				 this->tableLayoutPanel14->TabIndex = 0;
				 //
				 // metroToggleSOUND
				 //
				 this->metroToggleSOUND->Anchor = System::Windows::Forms::AnchorStyles::Left;
				 this->metroToggleSOUND->AutoSize = true;
				 this->metroToggleSOUND->Location = System::Drawing::Point(3, 26);
				 this->metroToggleSOUND->Name = L"metroToggleSOUND";
				 this->metroToggleSOUND->Size = System::Drawing::Size(80, 19);
				 this->metroToggleSOUND->TabIndex = 55;
				 this->metroToggleSOUND->Text = L"Aus";
				 this->metroToggleSOUND->UseSelectable = true;
				 //
				 // metroLabelTextSound
				 //
				 this->metroLabelTextSound->AutoSize = true;
				 this->metroLabelTextSound->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelTextSound->Location = System::Drawing::Point(89, 0);
				 this->metroLabelTextSound->Name = L"metroLabelTextSound";
				 this->metroLabelTextSound->Size = System::Drawing::Size(108, 71);
				 this->metroLabelTextSound->TabIndex = 56;
				 this->metroLabelTextSound->Text = L"Cancel on Sound";
				 this->metroLabelTextSound->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->metroToolTip1->SetToolTip(this->metroLabelTextSound, L"  If you like enjoying music or movies, thats a good choice.  ");
				 //
				 // metroLabel3
				 //
				 this->metroLabel3->AutoSize = true;
				 this->metroLabel3->BackColor = System::Drawing::Color::White;
				 this->metroLabel3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel3->Location = System::Drawing::Point(202, 2);
				 this->metroLabel3->Margin = System::Windows::Forms::Padding(2);
				 this->metroLabel3->Name = L"metroLabel3";
				 this->metroLabel3->Size = System::Drawing::Size(516, 67);
				 this->metroLabel3->TabIndex = 57;
				 this->metroLabel3->Text = L"Prevents Standby when playing music / movies";
				 this->metroLabel3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroLabel3->UseCustomBackColor = true;
				 //
				 // infoThresholds
				 //
				 this->infoThresholds->BackColor = System::Drawing::Color::LightBlue;
				 this->infoThresholds->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->infoThresholds->Lines = gcnew cli::array< System::String^  >(1) {
					 L"Stand-Bye checks if the current usage is greater than the selected one. If it is,"
						 L" there will be no change to standby-mode. This prevents resource needing process"
						 L"es to be interrupted."
				 };
				 this->infoThresholds->Location = System::Drawing::Point(3, 3);
				 this->infoThresholds->MaxLength = 32767;
				 this->infoThresholds->Multiline = true;
				 this->infoThresholds->Name = L"infoThresholds";
				 this->infoThresholds->PasswordChar = '\0';
				 this->infoThresholds->ReadOnly = true;
				 this->infoThresholds->ScrollBars = System::Windows::Forms::ScrollBars::None;
				 this->infoThresholds->SelectedText = L"";
				 this->infoThresholds->Size = System::Drawing::Size(726, 42);
				 this->infoThresholds->TabIndex = 55;
				 this->infoThresholds->Text = L"Stand-Bye checks if the current usage is greater than the selected one. If it is,"
					 L" there will be no change to standby-mode. This prevents resource needing process"
					 L"es to be interrupted.";
				 this->infoThresholds->UseCustomBackColor = true;
				 this->infoThresholds->UseSelectable = true;
				 //
				 // groupBox2
				 //
				 this->groupBox2->Controls->Add(this->tableLayoutPanelUsageThresholds);
				 this->groupBox2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->groupBox2->Location = System::Drawing::Point(3, 51);
				 this->groupBox2->Name = L"groupBox2";
				 this->groupBox2->Size = System::Drawing::Size(726, 157);
				 this->groupBox2->TabIndex = 59;
				 this->groupBox2->TabStop = false;
				 this->groupBox2->Text = L"General Thresholds";
				 //
				 // tableLayoutPanelUsageThresholds
				 //
				 this->tableLayoutPanelUsageThresholds->AutoSize = true;
				 this->tableLayoutPanelUsageThresholds->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				 this->tableLayoutPanelUsageThresholds->BackColor = System::Drawing::Color::White;
				 this->tableLayoutPanelUsageThresholds->ColumnCount = 6;
				 this->tableLayoutPanelUsageThresholds->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanelUsageThresholds->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanelUsageThresholds->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanelUsageThresholds->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanelUsageThresholds->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanelUsageThresholds->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelCurNET, 4, 4);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroToggleNET, 0, 4);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroToggleHDD, 0, 3);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelCurHDD, 4, 3);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelNETStatus, 3, 4);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelCurRAM, 4, 2);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroToggleRAM, 0, 2);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelCurCPU, 4, 1);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroToggleCPU, 0, 1);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelHDDStatus, 3, 3);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelTextCPU, 1, 1);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelTextRAM, 1, 2);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelTextHDD, 1, 3);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelTextNET, 1, 4);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelRAMPer, 3, 2);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroTrackBarCPU, 2, 1);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelCPUPer, 3, 1);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroTrackBarRAM, 2, 2);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->explCPU, 5, 1);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->explRAM, 5, 2);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->explHDD, 5, 3);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->explNET, 5, 4);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroLabelTextAverageUsage, 3, 0);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroTrackBarHDD, 2, 3);
				 this->tableLayoutPanelUsageThresholds->Controls->Add(this->metroTrackBarNET, 2, 4);
				 this->tableLayoutPanelUsageThresholds->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanelUsageThresholds->Location = System::Drawing::Point(3, 17);
				 this->tableLayoutPanelUsageThresholds->Margin = System::Windows::Forms::Padding(0);
				 this->tableLayoutPanelUsageThresholds->MaximumSize = System::Drawing::Size(999, 999);
				 this->tableLayoutPanelUsageThresholds->Name = L"tableLayoutPanelUsageThresholds";
				 this->tableLayoutPanelUsageThresholds->RowCount = 5;
				 this->tableLayoutPanelUsageThresholds->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
				 this->tableLayoutPanelUsageThresholds->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
					 25)));
				 this->tableLayoutPanelUsageThresholds->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
					 25)));
				 this->tableLayoutPanelUsageThresholds->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
					 25)));
				 this->tableLayoutPanelUsageThresholds->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
					 25)));
				 this->tableLayoutPanelUsageThresholds->Size = System::Drawing::Size(720, 137);
				 this->tableLayoutPanelUsageThresholds->TabIndex = 57;
				 //
				 // metroLabelCurNET
				 //
				 this->metroLabelCurNET->AutoSize = true;
				 this->metroLabelCurNET->BackColor = System::Drawing::SystemColors::Control;
				 this->metroLabelCurNET->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelCurNET->Location = System::Drawing::Point(414, 106);
				 this->metroLabelCurNET->Name = L"metroLabelCurNET";
				 this->metroLabelCurNET->Size = System::Drawing::Size(52, 31);
				 this->metroLabelCurNET->TabIndex = 41;
				 this->metroLabelCurNET->Text = L"-";
				 this->metroLabelCurNET->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroLabelCurNET->UseCustomBackColor = true;
				 this->metroLabelCurNET->UseCustomForeColor = true;
				 //
				 // metroToggleNET
				 //
				 this->metroToggleNET->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->metroToggleNET->AutoSize = true;
				 this->metroToggleNET->Location = System::Drawing::Point(3, 113);
				 this->metroToggleNET->Margin = System::Windows::Forms::Padding(3, 5, 3, 3);
				 this->metroToggleNET->Name = L"metroToggleNET";
				 this->metroToggleNET->Size = System::Drawing::Size(80, 19);
				 this->metroToggleNET->TabIndex = 49;
				 this->metroToggleNET->Text = L"Aus";
				 this->metroToggleNET->UseSelectable = true;
				 //
				 // metroToggleHDD
				 //
				 this->metroToggleHDD->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->metroToggleHDD->AutoSize = true;
				 this->metroToggleHDD->Location = System::Drawing::Point(3, 82);
				 this->metroToggleHDD->Name = L"metroToggleHDD";
				 this->metroToggleHDD->Size = System::Drawing::Size(80, 19);
				 this->metroToggleHDD->TabIndex = 48;
				 this->metroToggleHDD->Text = L"Aus";
				 this->metroToggleHDD->UseSelectable = true;
				 //
				 // metroLabelCurHDD
				 //
				 this->metroLabelCurHDD->AutoSize = true;
				 this->metroLabelCurHDD->BackColor = System::Drawing::SystemColors::Control;
				 this->metroLabelCurHDD->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelCurHDD->Location = System::Drawing::Point(414, 77);
				 this->metroLabelCurHDD->Name = L"metroLabelCurHDD";
				 this->metroLabelCurHDD->Size = System::Drawing::Size(52, 29);
				 this->metroLabelCurHDD->TabIndex = 40;
				 this->metroLabelCurHDD->Text = L"-";
				 this->metroLabelCurHDD->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroLabelCurHDD->UseCustomBackColor = true;
				 this->metroLabelCurHDD->UseCustomForeColor = true;
				 //
				 // metroLabelNETStatus
				 //
				 this->metroLabelNETStatus->AutoSize = true;
				 this->metroLabelNETStatus->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelNETStatus->Location = System::Drawing::Point(362, 106);
				 this->metroLabelNETStatus->Name = L"metroLabelNETStatus";
				 this->metroLabelNETStatus->Size = System::Drawing::Size(46, 31);
				 this->metroLabelNETStatus->TabIndex = 36;
				 this->metroLabelNETStatus->Text = L"MBit/s";
				 this->metroLabelNETStatus->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 //
				 // metroLabelCurRAM
				 //
				 this->metroLabelCurRAM->AutoSize = true;
				 this->metroLabelCurRAM->BackColor = System::Drawing::SystemColors::Control;
				 this->metroLabelCurRAM->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelCurRAM->Location = System::Drawing::Point(414, 48);
				 this->metroLabelCurRAM->Name = L"metroLabelCurRAM";
				 this->metroLabelCurRAM->Size = System::Drawing::Size(52, 29);
				 this->metroLabelCurRAM->TabIndex = 39;
				 this->metroLabelCurRAM->Text = L"-";
				 this->metroLabelCurRAM->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroLabelCurRAM->UseCustomBackColor = true;
				 this->metroLabelCurRAM->UseCustomForeColor = true;
				 //
				 // metroToggleRAM
				 //
				 this->metroToggleRAM->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->metroToggleRAM->AutoSize = true;
				 this->metroToggleRAM->Location = System::Drawing::Point(3, 53);
				 this->metroToggleRAM->Name = L"metroToggleRAM";
				 this->metroToggleRAM->Size = System::Drawing::Size(80, 19);
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
				 this->metroLabelCurCPU->Location = System::Drawing::Point(414, 19);
				 this->metroLabelCurCPU->Name = L"metroLabelCurCPU";
				 this->metroLabelCurCPU->Size = System::Drawing::Size(52, 29);
				 this->metroLabelCurCPU->TabIndex = 38;
				 this->metroLabelCurCPU->Text = L"-";
				 this->metroLabelCurCPU->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->metroLabelCurCPU->UseCustomBackColor = true;
				 this->metroLabelCurCPU->UseCustomForeColor = true;
				 //
				 // metroToggleCPU
				 //
				 this->metroToggleCPU->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->metroToggleCPU->AutoSize = true;
				 this->metroToggleCPU->Location = System::Drawing::Point(3, 24);
				 this->metroToggleCPU->Name = L"metroToggleCPU";
				 this->metroToggleCPU->Size = System::Drawing::Size(80, 19);
				 this->metroToggleCPU->TabIndex = 46;
				 this->metroToggleCPU->Text = L"Aus";
				 this->metroToggleCPU->UseSelectable = true;
				 //
				 // metroLabelHDDStatus
				 //
				 this->metroLabelHDDStatus->AutoSize = true;
				 this->metroLabelHDDStatus->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelHDDStatus->Location = System::Drawing::Point(362, 77);
				 this->metroLabelHDDStatus->Name = L"metroLabelHDDStatus";
				 this->metroLabelHDDStatus->Size = System::Drawing::Size(46, 29);
				 this->metroLabelHDDStatus->TabIndex = 37;
				 this->metroLabelHDDStatus->Text = L"MBit/s";
				 this->metroLabelHDDStatus->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 //
				 // metroLabelTextCPU
				 //
				 this->metroLabelTextCPU->AutoSize = true;
				 this->metroLabelTextCPU->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelTextCPU->Location = System::Drawing::Point(89, 19);
				 this->metroLabelTextCPU->Name = L"metroLabelTextCPU";
				 this->metroLabelTextCPU->Size = System::Drawing::Size(119, 29);
				 this->metroLabelTextCPU->TabIndex = 30;
				 this->metroLabelTextCPU->Text = L"CPU Threshold";
				 this->metroLabelTextCPU->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 //
				 // metroLabelTextRAM
				 //
				 this->metroLabelTextRAM->AutoSize = true;
				 this->metroLabelTextRAM->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelTextRAM->Location = System::Drawing::Point(89, 48);
				 this->metroLabelTextRAM->Name = L"metroLabelTextRAM";
				 this->metroLabelTextRAM->Size = System::Drawing::Size(119, 29);
				 this->metroLabelTextRAM->TabIndex = 31;
				 this->metroLabelTextRAM->Text = L"RAM Threshold";
				 this->metroLabelTextRAM->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 //
				 // metroLabelTextHDD
				 //
				 this->metroLabelTextHDD->AutoSize = true;
				 this->metroLabelTextHDD->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelTextHDD->Location = System::Drawing::Point(89, 77);
				 this->metroLabelTextHDD->Name = L"metroLabelTextHDD";
				 this->metroLabelTextHDD->Size = System::Drawing::Size(119, 29);
				 this->metroLabelTextHDD->TabIndex = 32;
				 this->metroLabelTextHDD->Text = L"HDD Threshold";
				 this->metroLabelTextHDD->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 //
				 // metroLabelTextNET
				 //
				 this->metroLabelTextNET->AutoSize = true;
				 this->metroLabelTextNET->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelTextNET->Location = System::Drawing::Point(89, 106);
				 this->metroLabelTextNET->Name = L"metroLabelTextNET";
				 this->metroLabelTextNET->Size = System::Drawing::Size(119, 31);
				 this->metroLabelTextNET->TabIndex = 33;
				 this->metroLabelTextNET->Text = L"Network Threshold";
				 this->metroLabelTextNET->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 //
				 // metroLabelRAMPer
				 //
				 this->metroLabelRAMPer->AutoSize = true;
				 this->metroLabelRAMPer->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelRAMPer->Location = System::Drawing::Point(362, 48);
				 this->metroLabelRAMPer->Name = L"metroLabelRAMPer";
				 this->metroLabelRAMPer->Size = System::Drawing::Size(46, 29);
				 this->metroLabelRAMPer->TabIndex = 35;
				 this->metroLabelRAMPer->Text = L"%";
				 this->metroLabelRAMPer->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 //
				 // metroTrackBarCPU
				 //
				 this->metroTrackBarCPU->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->metroTrackBarCPU->BackColor = System::Drawing::Color::Transparent;
				 this->metroTrackBarCPU->Location = System::Drawing::Point(214, 24);
				 this->metroTrackBarCPU->Name = L"metroTrackBarCPU";
				 this->metroTrackBarCPU->Size = System::Drawing::Size(141, 18);
				 this->metroTrackBarCPU->TabIndex = 42;
				 this->metroTrackBarCPU->Text = L"metroTrackBar1";
				 this->metroTrackBarCPU->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MetroSettingsForm::metroTrackBarCPU_Scroll);
				 //
				 // metroLabelCPUPer
				 //
				 this->metroLabelCPUPer->AutoSize = true;
				 this->metroLabelCPUPer->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelCPUPer->Location = System::Drawing::Point(362, 19);
				 this->metroLabelCPUPer->Name = L"metroLabelCPUPer";
				 this->metroLabelCPUPer->Size = System::Drawing::Size(46, 29);
				 this->metroLabelCPUPer->TabIndex = 34;
				 this->metroLabelCPUPer->Text = L"%";
				 this->metroLabelCPUPer->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 //
				 // metroTrackBarRAM
				 //
				 this->metroTrackBarRAM->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->metroTrackBarRAM->BackColor = System::Drawing::Color::Transparent;
				 this->metroTrackBarRAM->Location = System::Drawing::Point(214, 53);
				 this->metroTrackBarRAM->Name = L"metroTrackBarRAM";
				 this->metroTrackBarRAM->Size = System::Drawing::Size(142, 18);
				 this->metroTrackBarRAM->TabIndex = 43;
				 this->metroTrackBarRAM->Text = L"metroTrackBar2";
				 this->metroTrackBarRAM->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MetroSettingsForm::metroTrackBarRAM_Scroll);
				 //
				 // explCPU
				 //
				 this->explCPU->AutoSize = true;
				 this->explCPU->BackColor = System::Drawing::Color::White;
				 this->explCPU->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->explCPU->Location = System::Drawing::Point(471, 21);
				 this->explCPU->Margin = System::Windows::Forms::Padding(2);
				 this->explCPU->Name = L"explCPU";
				 this->explCPU->Size = System::Drawing::Size(247, 25);
				 this->explCPU->TabIndex = 51;
				 this->explCPU->Text = L"example";
				 this->explCPU->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->explCPU->UseCustomBackColor = true;
				 //
				 // explRAM
				 //
				 this->explRAM->AutoSize = true;
				 this->explRAM->BackColor = System::Drawing::Color::White;
				 this->explRAM->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->explRAM->Location = System::Drawing::Point(471, 50);
				 this->explRAM->Margin = System::Windows::Forms::Padding(2);
				 this->explRAM->Name = L"explRAM";
				 this->explRAM->Size = System::Drawing::Size(247, 25);
				 this->explRAM->TabIndex = 52;
				 this->explRAM->Text = L"example";
				 this->explRAM->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->explRAM->UseCustomBackColor = true;
				 //
				 // explHDD
				 //
				 this->explHDD->AutoSize = true;
				 this->explHDD->BackColor = System::Drawing::Color::White;
				 this->explHDD->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->explHDD->Location = System::Drawing::Point(471, 79);
				 this->explHDD->Margin = System::Windows::Forms::Padding(2);
				 this->explHDD->Name = L"explHDD";
				 this->explHDD->Size = System::Drawing::Size(247, 25);
				 this->explHDD->TabIndex = 53;
				 this->explHDD->Text = L"example";
				 this->explHDD->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->explHDD->UseCustomBackColor = true;
				 //
				 // explNET
				 //
				 this->explNET->AutoSize = true;
				 this->explNET->BackColor = System::Drawing::Color::White;
				 this->explNET->Location = System::Drawing::Point(471, 108);
				 this->explNET->Margin = System::Windows::Forms::Padding(2);
				 this->explNET->Name = L"explNET";
				 this->explNET->Size = System::Drawing::Size(59, 19);
				 this->explNET->TabIndex = 54;
				 this->explNET->Text = L"example";
				 this->explNET->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->explNET->UseCustomBackColor = true;
				 //
				 // metroLabelTextAverageUsage
				 //
				 this->metroLabelTextAverageUsage->AutoSize = true;
				 this->tableLayoutPanelUsageThresholds->SetColumnSpan(this->metroLabelTextAverageUsage, 2);
				 this->metroLabelTextAverageUsage->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelTextAverageUsage->FontWeight = MetroFramework::MetroLabelWeight::Regular;
				 this->metroLabelTextAverageUsage->Location = System::Drawing::Point(362, 0);
				 this->metroLabelTextAverageUsage->Name = L"metroLabelTextAverageUsage";
				 this->metroLabelTextAverageUsage->Size = System::Drawing::Size(104, 19);
				 this->metroLabelTextAverageUsage->TabIndex = 50;
				 this->metroLabelTextAverageUsage->Text = L"Average Usage:";
				 this->metroLabelTextAverageUsage->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->metroToolTip1->SetToolTip(this->metroLabelTextAverageUsage, L"   Stand-Bye uses the average usage over 15 sec. (measurement 2 times / sec)");
				 //
				 // metroTrackBarHDD
				 //
				 this->metroTrackBarHDD->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->metroTrackBarHDD->BackColor = System::Drawing::Color::Transparent;
				 this->metroTrackBarHDD->Location = System::Drawing::Point(214, 82);
				 this->metroTrackBarHDD->Name = L"metroTrackBarHDD";
				 this->metroTrackBarHDD->Size = System::Drawing::Size(142, 18);
				 this->metroTrackBarHDD->TabIndex = 55;
				 this->metroTrackBarHDD->Text = L"metroTrackBar2";
				 this->metroTrackBarHDD->Value = 10;
				 this->metroTrackBarHDD->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MetroSettingsForm::metroTrackBarHDD_Scroll);
				 //
				 // metroTrackBarNET
				 //
				 this->metroTrackBarNET->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->metroTrackBarNET->BackColor = System::Drawing::Color::Transparent;
				 this->metroTrackBarNET->Location = System::Drawing::Point(214, 112);
				 this->metroTrackBarNET->Name = L"metroTrackBarNET";
				 this->metroTrackBarNET->Size = System::Drawing::Size(142, 18);
				 this->metroTrackBarNET->TabIndex = 56;
				 this->metroTrackBarNET->Text = L"metroTrackBar2";
				 this->metroTrackBarNET->Value = 10;
				 this->metroTrackBarNET->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MetroSettingsForm::metroTrackBarNET_Scroll);
				 //
				 // metroTabPageExcpProcess
				 //
				 this->metroTabPageExcpProcess->Controls->Add(this->tableLayoutPanel5);
				 this->metroTabPageExcpProcess->HorizontalScrollbarBarColor = true;
				 this->metroTabPageExcpProcess->HorizontalScrollbarHighlightOnWheel = false;
				 this->metroTabPageExcpProcess->HorizontalScrollbarSize = 0;
				 this->metroTabPageExcpProcess->Location = System::Drawing::Point(4, 38);
				 this->metroTabPageExcpProcess->Name = L"metroTabPageExcpProcess";
				 this->metroTabPageExcpProcess->Size = System::Drawing::Size(732, 308);
				 this->metroTabPageExcpProcess->TabIndex = 1;
				 this->metroTabPageExcpProcess->Text = L"Exception Processes";
				 this->metroTabPageExcpProcess->VerticalScrollbarBarColor = true;
				 this->metroTabPageExcpProcess->VerticalScrollbarHighlightOnWheel = false;
				 this->metroTabPageExcpProcess->VerticalScrollbarSize = 0;
				 this->metroTabPageExcpProcess->Visible = false;
				 //
				 // tableLayoutPanel5
				 //
				 this->tableLayoutPanel5->AutoSize = true;
				 this->tableLayoutPanel5->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
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
				 this->tableLayoutPanel5->Size = System::Drawing::Size(732, 308);
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
				 this->listViewProc->Size = System::Drawing::Size(492, 288);
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
				 this->tableLayoutPanel6->AutoSize = true;
				 this->tableLayoutPanel6->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				 this->tableLayoutPanel6->BackColor = System::Drawing::Color::White;
				 this->tableLayoutPanel6->ColumnCount = 1;
				 this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 100)));
				 this->tableLayoutPanel6->Controls->Add(this->tableLayoutPanel7, 0, 1);
				 this->tableLayoutPanel6->Controls->Add(this->infoExcpProcesses, 0, 0);
				 this->tableLayoutPanel6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel6->Location = System::Drawing::Point(515, 3);
				 this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
				 this->tableLayoutPanel6->RowCount = 2;
				 this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 49.99999F)));
				 this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
				 this->tableLayoutPanel6->Size = System::Drawing::Size(214, 302);
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
				 this->tableLayoutPanel7->Location = System::Drawing::Point(3, 153);
				 this->tableLayoutPanel7->Name = L"tableLayoutPanel7";
				 this->tableLayoutPanel7->RowCount = 4;
				 this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel7->Size = System::Drawing::Size(208, 146);
				 this->tableLayoutPanel7->TabIndex = 0;
				 //
				 // metroButtonRemove
				 //
				 this->metroButtonRemove->BackColor = System::Drawing::Color::DarkCyan;
				 this->metroButtonRemove->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroButtonRemove->Location = System::Drawing::Point(5, 77);
				 this->metroButtonRemove->Margin = System::Windows::Forms::Padding(5);
				 this->metroButtonRemove->Name = L"metroButtonRemove";
				 this->metroButtonRemove->Size = System::Drawing::Size(198, 26);
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
				 this->metroButtonAddFromList->Location = System::Drawing::Point(5, 41);
				 this->metroButtonAddFromList->Margin = System::Windows::Forms::Padding(5);
				 this->metroButtonAddFromList->Name = L"metroButtonAddFromList";
				 this->metroButtonAddFromList->Size = System::Drawing::Size(198, 26);
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
				 this->metroButtonAddFromFile->Highlight = true;
				 this->metroButtonAddFromFile->Location = System::Drawing::Point(5, 5);
				 this->metroButtonAddFromFile->Margin = System::Windows::Forms::Padding(5);
				 this->metroButtonAddFromFile->Name = L"metroButtonAddFromFile";
				 this->metroButtonAddFromFile->Size = System::Drawing::Size(198, 26);
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
				 this->tableLayoutPanel8->Location = System::Drawing::Point(3, 111);
				 this->tableLayoutPanel8->Name = L"tableLayoutPanel8";
				 this->tableLayoutPanel8->RowCount = 1;
				 this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
				 this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 32)));
				 this->tableLayoutPanel8->Size = System::Drawing::Size(202, 32);
				 this->tableLayoutPanel8->TabIndex = 3;
				 //
				 // metroToggleView
				 //
				 this->metroToggleView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
				 this->metroToggleView->AutoSize = true;
				 this->metroToggleView->Location = System::Drawing::Point(111, 7);
				 this->metroToggleView->Margin = System::Windows::Forms::Padding(7);
				 this->metroToggleView->Name = L"metroToggleView";
				 this->metroToggleView->Size = System::Drawing::Size(80, 18);
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
				 this->metroLabelView->Size = System::Drawing::Size(95, 32);
				 this->metroLabelView->TabIndex = 4;
				 this->metroLabelView->Text = L"Show Details";
				 this->metroLabelView->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 //
				 // infoExcpProcesses
				 //
				 this->infoExcpProcesses->BackColor = System::Drawing::Color::LightBlue;
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
				 this->infoExcpProcesses->Size = System::Drawing::Size(208, 74);
				 this->infoExcpProcesses->TabIndex = 1;
				 this->infoExcpProcesses->Text = L"If at least one of the set up processes is running, the program will prevent the "
					 L"system from changing over to standby mode.";
				 this->infoExcpProcesses->UseCustomBackColor = true;
				 this->infoExcpProcesses->UseSelectable = true;
				 //
				 // metroTabPageAdvSettings
				 //
				 this->metroTabPageAdvSettings->Controls->Add(this->tableLayoutPanel2);
				 this->metroTabPageAdvSettings->HorizontalScrollbarBarColor = true;
				 this->metroTabPageAdvSettings->HorizontalScrollbarHighlightOnWheel = false;
				 this->metroTabPageAdvSettings->HorizontalScrollbarSize = 0;
				 this->metroTabPageAdvSettings->Location = System::Drawing::Point(4, 38);
				 this->metroTabPageAdvSettings->Name = L"metroTabPageAdvSettings";
				 this->metroTabPageAdvSettings->Size = System::Drawing::Size(732, 308);
				 this->metroTabPageAdvSettings->TabIndex = 3;
				 this->metroTabPageAdvSettings->Text = L"Advanced Settings";
				 this->metroTabPageAdvSettings->VerticalScrollbarBarColor = true;
				 this->metroTabPageAdvSettings->VerticalScrollbarHighlightOnWheel = false;
				 this->metroTabPageAdvSettings->VerticalScrollbarSize = 0;
				 this->metroTabPageAdvSettings->Visible = false;
				 //
				 // tableLayoutPanel2
				 //
				 this->tableLayoutPanel2->ColumnCount = 2;
				 this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 50)));
				 this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 50)));
				 this->tableLayoutPanel2->Controls->Add(this->tableLayoutPanel3, 0, 1);
				 this->tableLayoutPanel2->Controls->Add(this->metroLabel2, 1, 0);
				 this->tableLayoutPanel2->Controls->Add(this->metroLabel1, 0, 0);
				 this->tableLayoutPanel2->Controls->Add(this->tableLayoutPanel11, 0, 1);
				 this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel2->Location = System::Drawing::Point(0, 0);
				 this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
				 this->tableLayoutPanel2->RowCount = 2;
				 this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10)));
				 this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 90)));
				 this->tableLayoutPanel2->Size = System::Drawing::Size(732, 308);
				 this->tableLayoutPanel2->TabIndex = 4;
				 //
				 // tableLayoutPanel3
				 //
				 this->tableLayoutPanel3->BackColor = System::Drawing::Color::White;
				 this->tableLayoutPanel3->ColumnCount = 2;
				 this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 50)));
				 this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 50)));
				 this->tableLayoutPanel3->Controls->Add(this->metroLabel4, 0, 0);
				 this->tableLayoutPanel3->Controls->Add(this->metroToggle2, 1, 0);
				 this->tableLayoutPanel3->Controls->Add(this->metroLabel6, 0, 1);
				 this->tableLayoutPanel3->Controls->Add(this->metroComboBox1, 1, 1);
				 this->tableLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel3->Location = System::Drawing::Point(369, 33);
				 this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
				 this->tableLayoutPanel3->RowCount = 4;
				 this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
				 this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
				 this->tableLayoutPanel3->Size = System::Drawing::Size(360, 272);
				 this->tableLayoutPanel3->TabIndex = 5;
				 //
				 // metroLabel4
				 //
				 this->metroLabel4->AutoSize = true;
				 this->metroLabel4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel4->Location = System::Drawing::Point(3, 0);
				 this->metroLabel4->Name = L"metroLabel4";
				 this->metroLabel4->Size = System::Drawing::Size(174, 68);
				 this->metroLabel4->TabIndex = 0;
				 this->metroLabel4->Text = L"Enable Logging:";
				 this->metroLabel4->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->metroToolTip1->SetToolTip(this->metroLabel4, L"Starts Stand-Bye! with windows.");
				 //
				 // metroToggle2
				 //
				 this->metroToggle2->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->metroToggle2->AutoSize = true;
				 this->metroToggle2->Location = System::Drawing::Point(230, 25);
				 this->metroToggle2->Margin = System::Windows::Forms::Padding(0);
				 this->metroToggle2->Name = L"metroToggle2";
				 this->metroToggle2->Size = System::Drawing::Size(80, 17);
				 this->metroToggle2->TabIndex = 1;
				 this->metroToggle2->Text = L"Aus";
				 this->metroToggle2->UseSelectable = true;
				 //
				 // metroLabel6
				 //
				 this->metroLabel6->AutoSize = true;
				 this->metroLabel6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel6->Location = System::Drawing::Point(3, 68);
				 this->metroLabel6->Name = L"metroLabel6";
				 this->metroLabel6->Size = System::Drawing::Size(174, 68);
				 this->metroLabel6->TabIndex = 10;
				 this->metroLabel6->Text = L"Select Standby-Mode:";
				 this->metroLabel6->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 //
				 // metroComboBox1
				 //
				 this->metroComboBox1->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->metroComboBox1->DisplayMember = L"0";
				 this->metroComboBox1->FormattingEnabled = true;
				 this->metroComboBox1->ItemHeight = 23;
				 this->metroComboBox1->Location = System::Drawing::Point(193, 91);
				 this->metroComboBox1->Margin = System::Windows::Forms::Padding(3, 10, 3, 3);
				 this->metroComboBox1->Name = L"metroComboBox1";
				 this->metroComboBox1->Size = System::Drawing::Size(154, 29);
				 this->metroComboBox1->TabIndex = 11;
				 this->metroComboBox1->UseSelectable = true;
				 this->metroComboBox1->ValueMember = L"0";
				 //
				 // metroLabel2
				 //
				 this->metroLabel2->AutoSize = true;
				 this->metroLabel2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel2->FontWeight = MetroFramework::MetroLabelWeight::Bold;
				 this->metroLabel2->Location = System::Drawing::Point(369, 0);
				 this->metroLabel2->Name = L"metroLabel2";
				 this->metroLabel2->Size = System::Drawing::Size(360, 30);
				 this->metroLabel2->TabIndex = 4;
				 this->metroLabel2->Text = L"Stand-Bye Settings";
				 this->metroLabel2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 //
				 // metroLabel1
				 //
				 this->metroLabel1->AutoSize = true;
				 this->metroLabel1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabel1->FontWeight = MetroFramework::MetroLabelWeight::Bold;
				 this->metroLabel1->Location = System::Drawing::Point(3, 0);
				 this->metroLabel1->Name = L"metroLabel1";
				 this->metroLabel1->Size = System::Drawing::Size(360, 30);
				 this->metroLabel1->TabIndex = 3;
				 this->metroLabel1->Text = L"General Settings";
				 this->metroLabel1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
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
				 this->tableLayoutPanel11->Location = System::Drawing::Point(3, 33);
				 this->tableLayoutPanel11->Name = L"tableLayoutPanel11";
				 this->tableLayoutPanel11->RowCount = 4;
				 this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
				 this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
					 20)));
				 this->tableLayoutPanel11->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
					 20)));
				 this->tableLayoutPanel11->Size = System::Drawing::Size(360, 272);
				 this->tableLayoutPanel11->TabIndex = 2;
				 //
				 // metroLabelTextUpdates
				 //
				 this->metroLabelTextUpdates->AutoSize = true;
				 this->metroLabelTextUpdates->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelTextUpdates->Location = System::Drawing::Point(3, 136);
				 this->metroLabelTextUpdates->Name = L"metroLabelTextUpdates";
				 this->metroLabelTextUpdates->Size = System::Drawing::Size(174, 68);
				 this->metroLabelTextUpdates->TabIndex = 6;
				 this->metroLabelTextUpdates->Text = L"Search for Updates:";
				 this->metroLabelTextUpdates->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->metroToolTip1->SetToolTip(this->metroLabelTextUpdates, L"  Determine if Stand-Bye! should search for updates.");
				 //
				 // metroToggleUPDATES
				 //
				 this->metroToggleUPDATES->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->metroToggleUPDATES->AutoSize = true;
				 this->metroToggleUPDATES->Location = System::Drawing::Point(230, 161);
				 this->metroToggleUPDATES->Margin = System::Windows::Forms::Padding(0);
				 this->metroToggleUPDATES->Name = L"metroToggleUPDATES";
				 this->metroToggleUPDATES->Size = System::Drawing::Size(80, 17);
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
				 this->metroLabelTextAutoStart->Size = System::Drawing::Size(174, 68);
				 this->metroLabelTextAutoStart->TabIndex = 0;
				 this->metroLabelTextAutoStart->Text = L"Start with Windows:";
				 this->metroLabelTextAutoStart->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->metroToolTip1->SetToolTip(this->metroLabelTextAutoStart, L"Starts Stand-Bye! with windows.");
				 //
				 // metroToggleAutoStart
				 //
				 this->metroToggleAutoStart->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->metroToggleAutoStart->AutoSize = true;
				 this->metroToggleAutoStart->Location = System::Drawing::Point(230, 25);
				 this->metroToggleAutoStart->Margin = System::Windows::Forms::Padding(0);
				 this->metroToggleAutoStart->Name = L"metroToggleAutoStart";
				 this->metroToggleAutoStart->Size = System::Drawing::Size(80, 17);
				 this->metroToggleAutoStart->TabIndex = 1;
				 this->metroToggleAutoStart->Text = L"Aus";
				 this->metroToggleAutoStart->UseSelectable = true;
				 this->metroToggleAutoStart->CheckedChanged += gcnew System::EventHandler(this, &MetroSettingsForm::metroToggleAutoStart_CheckedChanged);
				 //
				 // metroLabelTextMessages
				 //
				 this->metroLabelTextMessages->AutoSize = true;
				 this->metroLabelTextMessages->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelTextMessages->Location = System::Drawing::Point(3, 204);
				 this->metroLabelTextMessages->Name = L"metroLabelTextMessages";
				 this->metroLabelTextMessages->Size = System::Drawing::Size(174, 68);
				 this->metroLabelTextMessages->TabIndex = 8;
				 this->metroLabelTextMessages->Text = L"Show Messages";
				 this->metroLabelTextMessages->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->metroToolTip1->SetToolTip(this->metroLabelTextMessages, L"    Determine if Stand-Bye! should show messages from the icon (for ex. presentat"
					 L"ion mode enabled)");
				 //
				 // metroToggleMessages
				 //
				 this->metroToggleMessages->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->metroToggleMessages->AutoSize = true;
				 this->metroToggleMessages->Location = System::Drawing::Point(230, 229);
				 this->metroToggleMessages->Margin = System::Windows::Forms::Padding(0);
				 this->metroToggleMessages->Name = L"metroToggleMessages";
				 this->metroToggleMessages->Size = System::Drawing::Size(80, 17);
				 this->metroToggleMessages->TabIndex = 9;
				 this->metroToggleMessages->Text = L"Aus";
				 this->metroToggleMessages->UseSelectable = true;
				 //
				 // metroLabelTextLanguage
				 //
				 this->metroLabelTextLanguage->AutoSize = true;
				 this->metroLabelTextLanguage->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroLabelTextLanguage->Location = System::Drawing::Point(3, 68);
				 this->metroLabelTextLanguage->Name = L"metroLabelTextLanguage";
				 this->metroLabelTextLanguage->Size = System::Drawing::Size(174, 68);
				 this->metroLabelTextLanguage->TabIndex = 10;
				 this->metroLabelTextLanguage->Text = L"Language:";
				 this->metroLabelTextLanguage->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 //
				 // metroComboBoxLanguage
				 //
				 this->metroComboBoxLanguage->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->metroComboBoxLanguage->DisplayMember = L"0";
				 this->metroComboBoxLanguage->FormattingEnabled = true;
				 this->metroComboBoxLanguage->ItemHeight = 23;
				 this->metroComboBoxLanguage->Location = System::Drawing::Point(193, 91);
				 this->metroComboBoxLanguage->Margin = System::Windows::Forms::Padding(3, 10, 3, 3);
				 this->metroComboBoxLanguage->Name = L"metroComboBoxLanguage";
				 this->metroComboBoxLanguage->Size = System::Drawing::Size(154, 29);
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
				 this->metroTabPageAbout->Size = System::Drawing::Size(732, 308);
				 this->metroTabPageAbout->TabIndex = 2;
				 this->metroTabPageAbout->Text = L"About";
				 this->metroTabPageAbout->VerticalScrollbar = true;
				 this->metroTabPageAbout->VerticalScrollbarBarColor = true;
				 this->metroTabPageAbout->VerticalScrollbarHighlightOnWheel = false;
				 this->metroTabPageAbout->VerticalScrollbarSize = 5;
				 this->metroTabPageAbout->Visible = false;
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
				 this->metroTileHomepage->Click += gcnew System::EventHandler(this, &MetroSettingsForm::OpenHomepageOnClick);
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
				 this->metroTileGithub->Click += gcnew System::EventHandler(this, &MetroSettingsForm::openGithubOnClick);
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
				 this->tableLayoutPanel1->Size = System::Drawing::Size(760, 430);
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
				 this->tableLayoutPanel4->Location = System::Drawing::Point(3, 373);
				 this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
				 this->tableLayoutPanel4->RowCount = 1;
				 this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
				 this->tableLayoutPanel4->Size = System::Drawing::Size(754, 54);
				 this->tableLayoutPanel4->TabIndex = 1;
				 //
				 // metroButtonOK
				 //
				 this->metroButtonOK->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->metroButtonOK->FontSize = MetroFramework::MetroButtonSize::Medium;
				 this->metroButtonOK->Location = System::Drawing::Point(610, 10);
				 this->metroButtonOK->Margin = System::Windows::Forms::Padding(10);
				 this->metroButtonOK->Name = L"metroButtonOK";
				 this->metroButtonOK->Size = System::Drawing::Size(134, 34);
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
				 this->metroLinkHomepage->Click += gcnew System::EventHandler(this, &MetroSettingsForm::OpenHomepageOnClick);
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
				 this->BackMaxSize = 774;
				 this->BorderStyle = MetroFramework::Forms::MetroFormBorderStyle::FixedSingle;
				 this->CancelButton = this->metroButtonCancel;
				 this->ClientSize = System::Drawing::Size(760, 490);
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
				 this->metroTabControl1->ResumeLayout(false);
				 this->metroTabPageSettings->ResumeLayout(false);
				 this->metroTabPageSettings->PerformLayout();
				 this->tableLayoutPanel10->ResumeLayout(false);
				 this->groupBox1->ResumeLayout(false);
				 this->tableLayoutPanel12->ResumeLayout(false);
				 this->tableLayoutPanel12->PerformLayout();
				 this->tableLayoutPaneWaitTime->ResumeLayout(false);
				 this->tableLayoutPaneWaitTime->PerformLayout();
				 this->metroTabPageThresholds->ResumeLayout(false);
				 this->metroTabPageThresholds->PerformLayout();
				 this->tableLayoutPanel13->ResumeLayout(false);
				 this->groupBox3->ResumeLayout(false);
				 this->tableLayoutPanel14->ResumeLayout(false);
				 this->tableLayoutPanel14->PerformLayout();
				 this->groupBox2->ResumeLayout(false);
				 this->groupBox2->PerformLayout();
				 this->tableLayoutPanelUsageThresholds->ResumeLayout(false);
				 this->tableLayoutPanelUsageThresholds->PerformLayout();
				 this->metroTabPageExcpProcess->ResumeLayout(false);
				 this->metroTabPageExcpProcess->PerformLayout();
				 this->tableLayoutPanel5->ResumeLayout(false);
				 this->tableLayoutPanel5->PerformLayout();
				 this->tableLayoutPanel6->ResumeLayout(false);
				 this->tableLayoutPanel7->ResumeLayout(false);
				 this->tableLayoutPanel8->ResumeLayout(false);
				 this->tableLayoutPanel8->PerformLayout();
				 this->metroTabPageAdvSettings->ResumeLayout(false);
				 this->tableLayoutPanel2->ResumeLayout(false);
				 this->tableLayoutPanel2->PerformLayout();
				 this->tableLayoutPanel3->ResumeLayout(false);
				 this->tableLayoutPanel3->PerformLayout();
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
		//Form Events
		System::Void MetroSettingsForm_Load(System::Object^  sender, System::EventArgs^  e);
		void OnVisibleChanged(System::Object ^sender, System::EventArgs ^e);
		void OnClosing(System::Object ^sender, System::ComponentModel::CancelEventArgs ^e);

		//Main Page
		System::Void metroTilePresMode_Click(System::Object^  sender, System::EventArgs^  e);
		void OnMetroTileMouseEnter(System::Object ^sender, System::EventArgs ^e);
		void OnMetroTileMouseLeave(System::Object ^sender, System::EventArgs ^e);
		void OnTextBoxMouseEnter(System::Object ^sender, System::EventArgs ^e);
		void OnTextBoxMouseLeave(System::Object ^sender, System::EventArgs ^e);
		System::Void metroTileAbout_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void metroTileProcesses_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void metroTileSettings_Click(System::Object^  sender, System::EventArgs^  e);

		//Thresholds
		System::Void metroTrackBarRAM_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e);
		System::Void metroTrackBarCPU_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e);
		System::Void metroTrackBarHDD_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e);
		System::Void metroTrackBarNET_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e);

		//Processes
		System::Void metroButtonAddFromFile_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void metroButtonAddFromList_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void metroButtonRemove_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void listViewProc_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void metroToggleView_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void refreshIcons();

		System::Void metroButtonOK_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void metroButtonCancel_Click(System::Object^  sender, System::EventArgs^  e);

		//Advanced Settings
		System::Void metroToggleAutoStart_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void LanguageIndexChanged(System::Object ^sender, System::EventArgs ^e);
		void switchLanguage();

		//About
		System::Void openGithubOnClick(System::Object^  sender, System::EventArgs^  e);
		System::Void OpenHomepageOnClick(System::Object^  sender, System::EventArgs^  e);

		//Background
		void changeLabelBackgroundColor(MetroFramework::Controls::MetroLabel^ label, double SettingsValue, double readValue);
		void ShowPresModeStatus();
		System::Void timerUIRefresh_Tick(System::Object^  sender, System::EventArgs^  e);
		void forceRefreshUI();

		//Formatters
		double getTextAsDouble(String^ text);
		String^ FormatDigits(double value);
		System::Void ReformatTextBoxValueOnReturn(System::Object ^, System::Windows::Forms::KeyEventArgs ^);

		//Data
		void writeSettings();
		void loadSettings();
	};
}
