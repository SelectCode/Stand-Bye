#pragma once
#include "stdafx.h"
#include "SystemAccess.h"

namespace StandBye {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für StartBanner
	/// </summary>
	public ref class StartBanner : public System::Windows::Forms::Form
	{
	public:
		StartBanner(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~StartBanner()
		{
			if (components)
			{
				delete components;
			}
		}
	private: MetroFramework::Controls::MetroLabel^  metroLabelVersion;
	protected:
	private: MetroFramework::Controls::MetroLabel^  metroLabel1;
	private: MetroFramework::Controls::MetroLabel^  metroLabel2;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(StartBanner::typeid));
			this->metroLabelVersion = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroLabel1 = (gcnew MetroFramework::Controls::MetroLabel());
			this->metroLabel2 = (gcnew MetroFramework::Controls::MetroLabel());
			this->SuspendLayout();
			// 
			// metroLabelVersion
			// 
			this->metroLabelVersion->AutoSize = true;
			this->metroLabelVersion->BackColor = System::Drawing::Color::Transparent;
			this->metroLabelVersion->FontWeight = MetroFramework::MetroLabelWeight::Regular;
			this->metroLabelVersion->ForeColor = System::Drawing::Color::White;
			this->metroLabelVersion->Location = System::Drawing::Point(12, 202);
			this->metroLabelVersion->Name = L"metroLabelVersion";
			this->metroLabelVersion->Size = System::Drawing::Size(65, 19);
			this->metroLabelVersion->TabIndex = 0;
			this->metroLabelVersion->Text = L"VERSION";
			this->metroLabelVersion->UseCustomBackColor = true;
			this->metroLabelVersion->UseCustomForeColor = true;
			// 
			// metroLabel1
			// 
			this->metroLabel1->AutoSize = true;
			this->metroLabel1->BackColor = System::Drawing::Color::Transparent;
			this->metroLabel1->FontWeight = MetroFramework::MetroLabelWeight::Regular;
			this->metroLabel1->ForeColor = System::Drawing::Color::White;
			this->metroLabel1->Location = System::Drawing::Point(202, 202);
			this->metroLabel1->Name = L"metroLabel1";
			this->metroLabel1->Size = System::Drawing::Size(334, 19);
			this->metroLabel1->TabIndex = 1;
			this->metroLabel1->Text = L"(c) 2015 Florian Baader, Stephan Le, Matthias Weirich";
			this->metroLabel1->UseCustomBackColor = true;
			this->metroLabel1->UseCustomForeColor = true;
			// 
			// metroLabel2
			// 
			this->metroLabel2->AutoSize = true;
			this->metroLabel2->BackColor = System::Drawing::Color::Transparent;
			this->metroLabel2->FontWeight = MetroFramework::MetroLabelWeight::Regular;
			this->metroLabel2->ForeColor = System::Drawing::Color::White;
			this->metroLabel2->Location = System::Drawing::Point(408, 9);
			this->metroLabel2->Name = L"metroLabel2";
			this->metroLabel2->Size = System::Drawing::Size(128, 19);
			this->metroLabel2->TabIndex = 2;
			this->metroLabel2->Text = L"Feel free to donate!";
			this->metroLabel2->UseCustomBackColor = true;
			this->metroLabel2->UseCustomForeColor = true;
			// 
			// StartBanner
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(548, 230);
			this->ControlBox = false;
			this->Controls->Add(this->metroLabel2);
			this->Controls->Add(this->metroLabel1);
			this->Controls->Add(this->metroLabelVersion);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"StartBanner";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"StartBanner";
			this->Load += gcnew System::EventHandler(this, &StartBanner::OnLoad);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		void OnLoad(System::Object ^sender, System::EventArgs ^e);
	};
}
