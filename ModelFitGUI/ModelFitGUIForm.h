/////////////////////////////////////////////////////////////////////
//
// Defines and Implements the ModelFitGUIForm class
//
// Author: Jason Jenkins
//
// This class implements the form based GUI used by the application.
//
/////////////////////////////////////////////////////////////////////

#pragma once

/////////////////////////////////////////////////////////////////////

#include "NeuralNet.h"
#include "NNetTrainer.h"
#include "NNetUnit.h"
#include "DbaseTable.h"

/////////////////////////////////////////////////////////////////////

#include <cmath>
#include <limits>
#include <algorithm>

/////////////////////////////////////////////////////////////////////

#include <msclr\marshal_cppstd.h>

/////////////////////////////////////////////////////////////////////

namespace ModelFitGUI 
{
	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Microsoft::Office::Interop::Excel;

	/// <summary>
	/// This class implements the form based GUI used by the ModelFitGUI 
	/// application.
	/// 
	/// The form allows the user to explore the various settings that 
	/// can be applied to a simple single hidden layer neural network 
	/// that can be used to model the potential relationship between 
	/// a single predictor variable (X) and a single corresponding 
	/// response variable (Y) chosen from a selected .CSV data file.
	///
	/// The results of the model fit can be saved in both .CSV and .XLS
	/// format and they can also be viewed directly in Excel if desired. 
	/// </summary>
	public ref class ModelFitGUIForm : public System::Windows::Forms::Form
	{
	private:

		/////////////////////////////////////////////////////////////////////
		// Private Data Members
		/////////////////////////////////////////////////////////////////////

		/// <summary>
		/// the data table column index of the selected predictor variable (X)
		/// </summary>
		int mPredictorIdx = -1;

		/// <summary>
		/// the data table column index of the selected response variable (Y)
		/// </summary>
		int mResponseIdx = -1;
		
		/// <summary>
		/// the name of data file (including the full path)
		/// </summary>
		String^ mDataFile;
		
		/// <summary>
		/// the neural network used to fit models to the data
		/// </summary>
		NeuralNet *mNet = new NeuralNet();

		/// <summary>
		/// used to store the data file as a table
		/// </summary>
		DbaseTable *mDataTable = new DbaseTable();
		
		/// <summary>
		/// the training set input vectors
		/// </summary>
		vector<vector<double> > *mInputVecs = new vector<vector<double> >;

		/// <summary>
		/// the training set target vectors
		/// </summary>
		vector<vector<double> > *mTargetVecs = new vector<vector<double> >;

	public:
		
		/////////////////////////////////////////////////////////////////////
		// Constructor
		/////////////////////////////////////////////////////////////////////

		ModelFitGUIForm(void)
		{
			InitializeComponent();
			
			// populates the form's Activation List boxes
			PopulateActivationListBoxes();
		}

	protected:

		/////////////////////////////////////////////////////////////////////
		// Destructor
		/////////////////////////////////////////////////////////////////////

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ModelFitGUIForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::RadioButton^  ExcelRadioBtn;
	private: System::Windows::Forms::ToolTip^  ModelFitToolTip;
	private: System::Windows::Forms::RadioButton^  CSVRadioBtn;
	private: System::Windows::Forms::Button^  SaveToBtn;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::NumericUpDown^  UnitsNumUpDwn;
	private: System::Windows::Forms::NumericUpDown^  ScaleNumUpDwn;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::NumericUpDown^  InitRangeNumUpDwn;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::NumericUpDown^  NumIterNumUpDwn;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::NumericUpDown^  MinNetErrNumUpDwn;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::NumericUpDown^  MomentNumUpDwn;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::NumericUpDown^  LearnConstNumUpDwn;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::NumericUpDown^  HidAmpNumUpDwn;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::NumericUpDown^  HidSlopeNumUpDwn;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::ListBox^  HidFuncListBox;
	private: System::Windows::Forms::ToolStripStatusLabel^  PanelStatus;
	private: System::Windows::Forms::ToolStripStatusLabel^  PanelIterations;
	private: System::Windows::Forms::ToolStripStatusLabel^  PanelNetError;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::Label^  InfoLabel;
	private: System::Windows::Forms::Button^  SaveNetworkBtn;
	private: System::Windows::Forms::CheckBox^  ExcelOutputCkBox;
	private: System::Windows::Forms::DataGridView^  tableDataGridView;
	private: System::Windows::Forms::NumericUpDown^  OutAmpNumUpDwn;
	private: System::Windows::Forms::NumericUpDown^  OutSlopeNumUpDwn;
	private: System::Windows::Forms::ListBox^  OutFuncListBox;
	private: System::Windows::Forms::CheckBox^  HeaderCkBox;
	private: System::Windows::Forms::ListBox^  YlistBox;
	private: System::Windows::Forms::ListBox^  XlistBox;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  FitModelBtn;
	private: System::Windows::Forms::Button^  FileBrowseBtn;
	private: System::Windows::Forms::Button^  ExitBtn;
	private: System::Windows::Forms::TextBox^  DataFileTBox;
	private: System::Windows::Forms::GroupBox^  groupBox6;
	private: System::Windows::Forms::StatusStrip^  AppStatusBar;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label1;
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
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->ExcelRadioBtn = (gcnew System::Windows::Forms::RadioButton());
			this->CSVRadioBtn = (gcnew System::Windows::Forms::RadioButton());
			this->SaveToBtn = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->UnitsNumUpDwn = (gcnew System::Windows::Forms::NumericUpDown());
			this->ScaleNumUpDwn = (gcnew System::Windows::Forms::NumericUpDown());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->InitRangeNumUpDwn = (gcnew System::Windows::Forms::NumericUpDown());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->NumIterNumUpDwn = (gcnew System::Windows::Forms::NumericUpDown());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->MinNetErrNumUpDwn = (gcnew System::Windows::Forms::NumericUpDown());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->MomentNumUpDwn = (gcnew System::Windows::Forms::NumericUpDown());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->LearnConstNumUpDwn = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->HidAmpNumUpDwn = (gcnew System::Windows::Forms::NumericUpDown());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->HidSlopeNumUpDwn = (gcnew System::Windows::Forms::NumericUpDown());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->HidFuncListBox = (gcnew System::Windows::Forms::ListBox());
			this->PanelStatus = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->PanelIterations = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->PanelNetError = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->InfoLabel = (gcnew System::Windows::Forms::Label());
			this->ModelFitToolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->SaveNetworkBtn = (gcnew System::Windows::Forms::Button());
			this->ExcelOutputCkBox = (gcnew System::Windows::Forms::CheckBox());
			this->tableDataGridView = (gcnew System::Windows::Forms::DataGridView());
			this->OutAmpNumUpDwn = (gcnew System::Windows::Forms::NumericUpDown());
			this->OutSlopeNumUpDwn = (gcnew System::Windows::Forms::NumericUpDown());
			this->OutFuncListBox = (gcnew System::Windows::Forms::ListBox());
			this->HeaderCkBox = (gcnew System::Windows::Forms::CheckBox());
			this->YlistBox = (gcnew System::Windows::Forms::ListBox());
			this->XlistBox = (gcnew System::Windows::Forms::ListBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->FitModelBtn = (gcnew System::Windows::Forms::Button());
			this->FileBrowseBtn = (gcnew System::Windows::Forms::Button());
			this->ExitBtn = (gcnew System::Windows::Forms::Button());
			this->DataFileTBox = (gcnew System::Windows::Forms::TextBox());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->AppStatusBar = (gcnew System::Windows::Forms::StatusStrip());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox5->SuspendLayout();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UnitsNumUpDwn))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ScaleNumUpDwn))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->InitRangeNumUpDwn))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumIterNumUpDwn))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MinNetErrNumUpDwn))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MomentNumUpDwn))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->LearnConstNumUpDwn))->BeginInit();
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HidAmpNumUpDwn))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HidSlopeNumUpDwn))->BeginInit();
			this->groupBox4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tableDataGridView))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OutAmpNumUpDwn))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OutSlopeNumUpDwn))->BeginInit();
			this->groupBox6->SuspendLayout();
			this->AppStatusBar->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox5
			// 
			this->groupBox5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->groupBox5->Controls->Add(this->ExcelRadioBtn);
			this->groupBox5->Controls->Add(this->CSVRadioBtn);
			this->groupBox5->Controls->Add(this->SaveToBtn);
			this->groupBox5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox5->Location = System::Drawing::Point(796, 198);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(174, 113);
			this->groupBox5->TabIndex = 63;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Output";
			// 
			// ExcelRadioBtn
			// 
			this->ExcelRadioBtn->AutoSize = true;
			this->ExcelRadioBtn->Location = System::Drawing::Point(10, 51);
			this->ExcelRadioBtn->Name = L"ExcelRadioBtn";
			this->ExcelRadioBtn->Size = System::Drawing::Size(98, 17);
			this->ExcelRadioBtn->TabIndex = 41;
			this->ExcelRadioBtn->Text = L"Save as XLS";
			this->ModelFitToolTip->SetToolTip(this->ExcelRadioBtn, L"if set the model output is produced in XLS (Excel) format");
			this->ExcelRadioBtn->UseVisualStyleBackColor = true;
			// 
			// CSVRadioBtn
			// 
			this->CSVRadioBtn->AutoSize = true;
			this->CSVRadioBtn->Checked = true;
			this->CSVRadioBtn->Location = System::Drawing::Point(10, 21);
			this->CSVRadioBtn->Name = L"CSVRadioBtn";
			this->CSVRadioBtn->Size = System::Drawing::Size(99, 17);
			this->CSVRadioBtn->TabIndex = 40;
			this->CSVRadioBtn->TabStop = true;
			this->CSVRadioBtn->Text = L"Save as CSV";
			this->ModelFitToolTip->SetToolTip(this->CSVRadioBtn, L"if set the model output is produced in CSV format");
			this->CSVRadioBtn->UseVisualStyleBackColor = true;
			// 
			// SaveToBtn
			// 
			this->SaveToBtn->Enabled = false;
			this->SaveToBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SaveToBtn->Location = System::Drawing::Point(83, 82);
			this->SaveToBtn->Name = L"SaveToBtn";
			this->SaveToBtn->Size = System::Drawing::Size(85, 20);
			this->SaveToBtn->TabIndex = 42;
			this->SaveToBtn->Text = L"Save";
			this->ModelFitToolTip->SetToolTip(this->SaveToBtn, L"click to save the latest model output in the selected format");
			this->SaveToBtn->UseVisualStyleBackColor = true;
			this->SaveToBtn->Click += gcnew System::EventHandler(this, &ModelFitGUIForm::SaveToBtn_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->groupBox2->Controls->Add(this->label17);
			this->groupBox2->Controls->Add(this->UnitsNumUpDwn);
			this->groupBox2->Controls->Add(this->ScaleNumUpDwn);
			this->groupBox2->Controls->Add(this->label16);
			this->groupBox2->Controls->Add(this->InitRangeNumUpDwn);
			this->groupBox2->Controls->Add(this->label9);
			this->groupBox2->Controls->Add(this->NumIterNumUpDwn);
			this->groupBox2->Controls->Add(this->label8);
			this->groupBox2->Controls->Add(this->MinNetErrNumUpDwn);
			this->groupBox2->Controls->Add(this->label7);
			this->groupBox2->Controls->Add(this->MomentNumUpDwn);
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->LearnConstNumUpDwn);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox2->Location = System::Drawing::Point(395, 198);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(220, 228);
			this->groupBox2->TabIndex = 59;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Main Settings";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label17->Location = System::Drawing::Point(14, 201);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(123, 13);
			this->label17->TabIndex = 23;
			this->label17->Text = L"No. of Hidden Units:";
			// 
			// UnitsNumUpDwn
			// 
			this->UnitsNumUpDwn->Location = System::Drawing::Point(139, 198);
			this->UnitsNumUpDwn->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->UnitsNumUpDwn->Name = L"UnitsNumUpDwn";
			this->UnitsNumUpDwn->Size = System::Drawing::Size(65, 20);
			this->UnitsNumUpDwn->TabIndex = 24;
			this->UnitsNumUpDwn->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->ModelFitToolTip->SetToolTip(this->UnitsNumUpDwn, L"sets the number of units in the hidden layer");
			this->UnitsNumUpDwn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
			this->UnitsNumUpDwn->ValueChanged += gcnew System::EventHandler(this, &ModelFitGUIForm::ListBox_SelectedIndexChanged);
			// 
			// ScaleNumUpDwn
			// 
			this->ScaleNumUpDwn->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			this->ScaleNumUpDwn->Location = System::Drawing::Point(139, 138);
			this->ScaleNumUpDwn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
			this->ScaleNumUpDwn->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->ScaleNumUpDwn->Name = L"ScaleNumUpDwn";
			this->ScaleNumUpDwn->Size = System::Drawing::Size(65, 20);
			this->ScaleNumUpDwn->TabIndex = 20;
			this->ScaleNumUpDwn->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->ModelFitToolTip->SetToolTip(this->ScaleNumUpDwn, L"used to divide the data values to reduce their magnitude - this may improve the f"
				L"it");
			this->ScaleNumUpDwn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->ScaleNumUpDwn->ValueChanged += gcnew System::EventHandler(this, &ModelFitGUIForm::ListBox_SelectedIndexChanged);
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label16->Location = System::Drawing::Point(53, 141);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(83, 13);
			this->label16->TabIndex = 19;
			this->label16->Text = L"Scale Factor:";
			// 
			// InitRangeNumUpDwn
			// 
			this->InitRangeNumUpDwn->Location = System::Drawing::Point(139, 168);
			this->InitRangeNumUpDwn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 50, 0, 0, 0 });
			this->InitRangeNumUpDwn->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->InitRangeNumUpDwn->Name = L"InitRangeNumUpDwn";
			this->InitRangeNumUpDwn->Size = System::Drawing::Size(65, 20);
			this->InitRangeNumUpDwn->TabIndex = 22;
			this->InitRangeNumUpDwn->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->ModelFitToolTip->SetToolTip(this->InitRangeNumUpDwn, L"sets the range of the random values initially connecting the layers of the networ"
				L"k, 2 represents -1 to +1");
			this->InitRangeNumUpDwn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->InitRangeNumUpDwn->ValueChanged += gcnew System::EventHandler(this, &ModelFitGUIForm::ListBox_SelectedIndexChanged);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(54, 171);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(83, 13);
			this->label9->TabIndex = 21;
			this->label9->Text = L"Initial Range:";
			// 
			// NumIterNumUpDwn
			// 
			this->NumIterNumUpDwn->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			this->NumIterNumUpDwn->Location = System::Drawing::Point(139, 108);
			this->NumIterNumUpDwn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 500000, 0, 0, 0 });
			this->NumIterNumUpDwn->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			this->NumIterNumUpDwn->Name = L"NumIterNumUpDwn";
			this->NumIterNumUpDwn->Size = System::Drawing::Size(65, 20);
			this->NumIterNumUpDwn->TabIndex = 18;
			this->NumIterNumUpDwn->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->ModelFitToolTip->SetToolTip(this->NumIterNumUpDwn, L"sets the maximum number of iterations for the training process");
			this->NumIterNumUpDwn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->NumIterNumUpDwn->ValueChanged += gcnew System::EventHandler(this, &ModelFitGUIForm::ListBox_SelectedIndexChanged);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(12, 111);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(126, 13);
			this->label8->TabIndex = 17;
			this->label8->Text = L"Number of Iterations:";
			// 
			// MinNetErrNumUpDwn
			// 
			this->MinNetErrNumUpDwn->DecimalPlaces = 3;
			this->MinNetErrNumUpDwn->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 65536 });
			this->MinNetErrNumUpDwn->Location = System::Drawing::Point(139, 78);
			this->MinNetErrNumUpDwn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			this->MinNetErrNumUpDwn->Name = L"MinNetErrNumUpDwn";
			this->MinNetErrNumUpDwn->Size = System::Drawing::Size(65, 20);
			this->MinNetErrNumUpDwn->TabIndex = 16;
			this->MinNetErrNumUpDwn->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->ModelFitToolTip->SetToolTip(this->MinNetErrNumUpDwn, L"training will stop when the total network error is less than this value");
			this->MinNetErrNumUpDwn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->MinNetErrNumUpDwn->ValueChanged += gcnew System::EventHandler(this, &ModelFitGUIForm::ListBox_SelectedIndexChanged);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(20, 81);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(117, 13);
			this->label7->TabIndex = 15;
			this->label7->Text = L"Min. Network Error:";
			// 
			// MomentNumUpDwn
			// 
			this->MomentNumUpDwn->DecimalPlaces = 3;
			this->MomentNumUpDwn->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 196608 });
			this->MomentNumUpDwn->Location = System::Drawing::Point(139, 48);
			this->MomentNumUpDwn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->MomentNumUpDwn->Name = L"MomentNumUpDwn";
			this->MomentNumUpDwn->Size = System::Drawing::Size(65, 20);
			this->MomentNumUpDwn->TabIndex = 14;
			this->MomentNumUpDwn->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->ModelFitToolTip->SetToolTip(this->MomentNumUpDwn, L"used to weight the search of the error surface to continue along the same \'direct"
				L"ion\' as the previous step");
			this->MomentNumUpDwn->ValueChanged += gcnew System::EventHandler(this, &ModelFitGUIForm::ListBox_SelectedIndexChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(66, 51);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(71, 13);
			this->label6->TabIndex = 13;
			this->label6->Text = L"Momentum:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(24, 21);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(114, 13);
			this->label5->TabIndex = 11;
			this->label5->Text = L"Learning Constant:";
			// 
			// LearnConstNumUpDwn
			// 
			this->LearnConstNumUpDwn->DecimalPlaces = 3;
			this->LearnConstNumUpDwn->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 196608 });
			this->LearnConstNumUpDwn->Location = System::Drawing::Point(139, 18);
			this->LearnConstNumUpDwn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->LearnConstNumUpDwn->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 196608 });
			this->LearnConstNumUpDwn->Name = L"LearnConstNumUpDwn";
			this->LearnConstNumUpDwn->Size = System::Drawing::Size(65, 20);
			this->LearnConstNumUpDwn->TabIndex = 12;
			this->LearnConstNumUpDwn->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->ModelFitToolTip->SetToolTip(this->LearnConstNumUpDwn, L"governs the \'size\' of the steps taken down the error surface");
			this->LearnConstNumUpDwn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
			this->LearnConstNumUpDwn->ValueChanged += gcnew System::EventHandler(this, &ModelFitGUIForm::ListBox_SelectedIndexChanged);
			// 
			// groupBox3
			// 
			this->groupBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->groupBox3->Controls->Add(this->label14);
			this->groupBox3->Controls->Add(this->HidAmpNumUpDwn);
			this->groupBox3->Controls->Add(this->label15);
			this->groupBox3->Controls->Add(this->HidSlopeNumUpDwn);
			this->groupBox3->Controls->Add(this->label11);
			this->groupBox3->Controls->Add(this->HidFuncListBox);
			this->groupBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox3->Location = System::Drawing::Point(210, 306);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(162, 150);
			this->groupBox3->TabIndex = 62;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Hidden Layer";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(30, 126);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(51, 13);
			this->label14->TabIndex = 37;
			this->label14->Text = L"Amplify:";
			// 
			// HidAmpNumUpDwn
			// 
			this->HidAmpNumUpDwn->DecimalPlaces = 2;
			this->HidAmpNumUpDwn->Location = System::Drawing::Point(84, 124);
			this->HidAmpNumUpDwn->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
			this->HidAmpNumUpDwn->Name = L"HidAmpNumUpDwn";
			this->HidAmpNumUpDwn->Size = System::Drawing::Size(65, 20);
			this->HidAmpNumUpDwn->TabIndex = 38;
			this->HidAmpNumUpDwn->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->ModelFitToolTip->SetToolTip(this->HidAmpNumUpDwn, L"used to boost or reduce the hidden layer units signal value");
			this->HidAmpNumUpDwn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->HidAmpNumUpDwn->ValueChanged += gcnew System::EventHandler(this, &ModelFitGUIForm::ListBox_SelectedIndexChanged);
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(38, 104);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(43, 13);
			this->label15->TabIndex = 35;
			this->label15->Text = L"Slope:";
			// 
			// HidSlopeNumUpDwn
			// 
			this->HidSlopeNumUpDwn->DecimalPlaces = 2;
			this->HidSlopeNumUpDwn->Location = System::Drawing::Point(84, 99);
			this->HidSlopeNumUpDwn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->HidSlopeNumUpDwn->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
			this->HidSlopeNumUpDwn->Name = L"HidSlopeNumUpDwn";
			this->HidSlopeNumUpDwn->Size = System::Drawing::Size(65, 20);
			this->HidSlopeNumUpDwn->TabIndex = 36;
			this->HidSlopeNumUpDwn->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->ModelFitToolTip->SetToolTip(this->HidSlopeNumUpDwn, L"used to adjust the sensitivity of the hidden layer units activation function");
			this->HidSlopeNumUpDwn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->HidSlopeNumUpDwn->ValueChanged += gcnew System::EventHandler(this, &ModelFitGUIForm::ListBox_SelectedIndexChanged);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(30, 20);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(117, 13);
			this->label11->TabIndex = 33;
			this->label11->Text = L"Activation Function";
			// 
			// HidFuncListBox
			// 
			this->HidFuncListBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->HidFuncListBox->FormattingEnabled = true;
			this->HidFuncListBox->Location = System::Drawing::Point(29, 37);
			this->HidFuncListBox->Name = L"HidFuncListBox";
			this->HidFuncListBox->Size = System::Drawing::Size(119, 56);
			this->HidFuncListBox->TabIndex = 34;
			this->ModelFitToolTip->SetToolTip(this->HidFuncListBox, L"select the hidden layer units activation function");
			this->HidFuncListBox->SelectedValueChanged += gcnew System::EventHandler(this, &ModelFitGUIForm::ListBox_SelectedIndexChanged);
			// 
			// PanelStatus
			// 
			this->PanelStatus->BorderSides = System::Windows::Forms::ToolStripStatusLabelBorderSides::Right;
			this->PanelStatus->Name = L"PanelStatus";
			this->PanelStatus->Size = System::Drawing::Size(80, 23);
			this->PanelStatus->Text = L"Status: Idle";
			// 
			// PanelIterations
			// 
			this->PanelIterations->BorderSides = System::Windows::Forms::ToolStripStatusLabelBorderSides::Right;
			this->PanelIterations->Name = L"PanelIterations";
			this->PanelIterations->Size = System::Drawing::Size(4, 23);
			// 
			// PanelNetError
			// 
			this->PanelNetError->BorderSides = System::Windows::Forms::ToolStripStatusLabelBorderSides::Right;
			this->PanelNetError->Name = L"PanelNetError";
			this->PanelNetError->Size = System::Drawing::Size(4, 23);
			// 
			// groupBox4
			// 
			this->groupBox4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->groupBox4->Controls->Add(this->InfoLabel);
			this->groupBox4->Location = System::Drawing::Point(589, 425);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(286, 35);
			this->groupBox4->TabIndex = 65;
			this->groupBox4->TabStop = false;
			// 
			// InfoLabel
			// 
			this->InfoLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->InfoLabel->AutoSize = true;
			this->InfoLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.818182F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->InfoLabel->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->InfoLabel->Location = System::Drawing::Point(8, 10);
			this->InfoLabel->Name = L"InfoLabel";
			this->InfoLabel->Size = System::Drawing::Size(201, 20);
			this->InfoLabel->TabIndex = 46;
			this->InfoLabel->Text = L"Please select a data file";
			// 
			// SaveNetworkBtn
			// 
			this->SaveNetworkBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->SaveNetworkBtn->Enabled = false;
			this->SaveNetworkBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SaveNetworkBtn->Location = System::Drawing::Point(83, 39);
			this->SaveNetworkBtn->Name = L"SaveNetworkBtn";
			this->SaveNetworkBtn->Size = System::Drawing::Size(85, 20);
			this->SaveNetworkBtn->TabIndex = 44;
			this->SaveNetworkBtn->Text = L"Save Network";
			this->ModelFitToolTip->SetToolTip(this->SaveNetworkBtn, L"click to serialise the current trained neural network to a file");
			this->SaveNetworkBtn->UseVisualStyleBackColor = true;
			this->SaveNetworkBtn->Click += gcnew System::EventHandler(this, &ModelFitGUIForm::SaveNetworkBtn_Click);
			// 
			// ExcelOutputCkBox
			// 
			this->ExcelOutputCkBox->AutoSize = true;
			this->ExcelOutputCkBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ExcelOutputCkBox->Location = System::Drawing::Point(12, 16);
			this->ExcelOutputCkBox->Name = L"ExcelOutputCkBox";
			this->ExcelOutputCkBox->Size = System::Drawing::Size(146, 17);
			this->ExcelOutputCkBox->TabIndex = 43;
			this->ExcelOutputCkBox->Text = L"Show output in Excel";
			this->ModelFitToolTip->SetToolTip(this->ExcelOutputCkBox, L"check to show the fitted model output in Excel at the end of the training process"
				L"");
			this->ExcelOutputCkBox->UseVisualStyleBackColor = true;
			// 
			// tableDataGridView
			// 
			this->tableDataGridView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableDataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->tableDataGridView->Location = System::Drawing::Point(23, 78);
			this->tableDataGridView->Name = L"tableDataGridView";
			this->tableDataGridView->ReadOnly = true;
			this->tableDataGridView->Size = System::Drawing::Size(947, 102);
			this->tableDataGridView->TabIndex = 69;
			this->tableDataGridView->TabStop = false;
			this->ModelFitToolTip->SetToolTip(this->tableDataGridView, L"displays the first 100 lines of the data file - the last two rows contain the min"
				L" and max values");
			// 
			// OutAmpNumUpDwn
			// 
			this->OutAmpNumUpDwn->DecimalPlaces = 2;
			this->OutAmpNumUpDwn->Location = System::Drawing::Point(84, 124);
			this->OutAmpNumUpDwn->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
			this->OutAmpNumUpDwn->Name = L"OutAmpNumUpDwn";
			this->OutAmpNumUpDwn->Size = System::Drawing::Size(65, 20);
			this->OutAmpNumUpDwn->TabIndex = 31;
			this->OutAmpNumUpDwn->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->ModelFitToolTip->SetToolTip(this->OutAmpNumUpDwn, L"used to boost or reduce the output layer units signal value");
			this->OutAmpNumUpDwn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->OutAmpNumUpDwn->ValueChanged += gcnew System::EventHandler(this, &ModelFitGUIForm::ListBox_SelectedIndexChanged);
			// 
			// OutSlopeNumUpDwn
			// 
			this->OutSlopeNumUpDwn->DecimalPlaces = 2;
			this->OutSlopeNumUpDwn->Location = System::Drawing::Point(84, 99);
			this->OutSlopeNumUpDwn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->OutSlopeNumUpDwn->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 393216 });
			this->OutSlopeNumUpDwn->Name = L"OutSlopeNumUpDwn";
			this->OutSlopeNumUpDwn->Size = System::Drawing::Size(65, 20);
			this->OutSlopeNumUpDwn->TabIndex = 29;
			this->OutSlopeNumUpDwn->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->ModelFitToolTip->SetToolTip(this->OutSlopeNumUpDwn, L"used to adjust the sensitivity of the output layer units activation function");
			this->OutSlopeNumUpDwn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->OutSlopeNumUpDwn->ValueChanged += gcnew System::EventHandler(this, &ModelFitGUIForm::ListBox_SelectedIndexChanged);
			// 
			// OutFuncListBox
			// 
			this->OutFuncListBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->OutFuncListBox->FormattingEnabled = true;
			this->OutFuncListBox->Location = System::Drawing::Point(31, 37);
			this->OutFuncListBox->Name = L"OutFuncListBox";
			this->OutFuncListBox->Size = System::Drawing::Size(119, 56);
			this->OutFuncListBox->TabIndex = 27;
			this->ModelFitToolTip->SetToolTip(this->OutFuncListBox, L"select the output layer units activation function");
			this->OutFuncListBox->SelectedValueChanged += gcnew System::EventHandler(this, &ModelFitGUIForm::ListBox_SelectedIndexChanged);
			// 
			// HeaderCkBox
			// 
			this->HeaderCkBox->AutoSize = true;
			this->HeaderCkBox->Checked = true;
			this->HeaderCkBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->HeaderCkBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->HeaderCkBox->Location = System::Drawing::Point(570, 28);
			this->HeaderCkBox->Name = L"HeaderCkBox";
			this->HeaderCkBox->Size = System::Drawing::Size(137, 17);
			this->HeaderCkBox->TabIndex = 53;
			this->HeaderCkBox->Text = L"File has header row";
			this->ModelFitToolTip->SetToolTip(this->HeaderCkBox, L"check if the data file has a header row");
			this->HeaderCkBox->UseVisualStyleBackColor = true;
			this->HeaderCkBox->CheckedChanged += gcnew System::EventHandler(this, &ModelFitGUIForm::HeaderCkBox_CheckedChanged);
			// 
			// YlistBox
			// 
			this->YlistBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->YlistBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->YlistBox->FormattingEnabled = true;
			this->YlistBox->Location = System::Drawing::Point(210, 217);
			this->YlistBox->Name = L"YlistBox";
			this->YlistBox->Size = System::Drawing::Size(162, 69);
			this->YlistBox->TabIndex = 58;
			this->ModelFitToolTip->SetToolTip(this->YlistBox, L"select the data column containing the response variable (Y)");
			this->YlistBox->SelectedValueChanged += gcnew System::EventHandler(this, &ModelFitGUIForm::ListBox_SelectedIndexChanged);
			// 
			// XlistBox
			// 
			this->XlistBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->XlistBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->XlistBox->FormattingEnabled = true;
			this->XlistBox->Location = System::Drawing::Point(20, 217);
			this->XlistBox->Name = L"XlistBox";
			this->XlistBox->Size = System::Drawing::Size(162, 69);
			this->XlistBox->TabIndex = 56;
			this->ModelFitToolTip->SetToolTip(this->XlistBox, L"select the data column containing the predictor variable (X)");
			this->XlistBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ModelFitGUIForm::ListBox_SelectedIndexChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(20, 58);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(83, 13);
			this->label2->TabIndex = 54;
			this->label2->Text = L"Data Preview";
			this->ModelFitToolTip->SetToolTip(this->label2, L"displays the first 100 lines of the data file - the last two rows contain the min"
				L" and max values");
			// 
			// FitModelBtn
			// 
			this->FitModelBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->FitModelBtn->Enabled = false;
			this->FitModelBtn->Location = System::Drawing::Point(885, 435);
			this->FitModelBtn->Name = L"FitModelBtn";
			this->FitModelBtn->Size = System::Drawing::Size(85, 20);
			this->FitModelBtn->TabIndex = 66;
			this->FitModelBtn->Text = L"Fit Model";
			this->ModelFitToolTip->SetToolTip(this->FitModelBtn, L"click to start the training process and fit a model to the data");
			this->FitModelBtn->UseVisualStyleBackColor = true;
			this->FitModelBtn->Click += gcnew System::EventHandler(this, &ModelFitGUIForm::FitModelBtn_Click);
			// 
			// FileBrowseBtn
			// 
			this->FileBrowseBtn->Location = System::Drawing::Point(465, 25);
			this->FileBrowseBtn->Name = L"FileBrowseBtn";
			this->FileBrowseBtn->Size = System::Drawing::Size(85, 20);
			this->FileBrowseBtn->TabIndex = 52;
			this->FileBrowseBtn->Text = L"Browse";
			this->ModelFitToolTip->SetToolTip(this->FileBrowseBtn, L"click to browse for a CSV data file");
			this->FileBrowseBtn->UseVisualStyleBackColor = true;
			this->FileBrowseBtn->Click += gcnew System::EventHandler(this, &ModelFitGUIForm::FileBrowseBtn_Click);
			// 
			// ExitBtn
			// 
			this->ExitBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ExitBtn->Location = System::Drawing::Point(885, 25);
			this->ExitBtn->Name = L"ExitBtn";
			this->ExitBtn->Size = System::Drawing::Size(85, 20);
			this->ExitBtn->TabIndex = 67;
			this->ExitBtn->Text = L"Exit";
			this->ModelFitToolTip->SetToolTip(this->ExitBtn, L"click to exit the application");
			this->ExitBtn->UseVisualStyleBackColor = true;
			this->ExitBtn->Click += gcnew System::EventHandler(this, &ModelFitGUIForm::ExitBtn_Click);
			// 
			// DataFileTBox
			// 
			this->DataFileTBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DataFileTBox->Location = System::Drawing::Point(20, 25);
			this->DataFileTBox->Name = L"DataFileTBox";
			this->DataFileTBox->ReadOnly = true;
			this->DataFileTBox->Size = System::Drawing::Size(429, 20);
			this->DataFileTBox->TabIndex = 68;
			this->DataFileTBox->TabStop = false;
			this->ModelFitToolTip->SetToolTip(this->DataFileTBox, L"displays the full name and path of the data file");
			// 
			// groupBox6
			// 
			this->groupBox6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->groupBox6->Controls->Add(this->SaveNetworkBtn);
			this->groupBox6->Controls->Add(this->ExcelOutputCkBox);
			this->groupBox6->Location = System::Drawing::Point(796, 317);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(174, 67);
			this->groupBox6->TabIndex = 64;
			this->groupBox6->TabStop = false;
			// 
			// AppStatusBar
			// 
			this->AppStatusBar->ImageScalingSize = System::Drawing::Size(18, 18);
			this->AppStatusBar->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->PanelStatus, this->PanelIterations,
					this->PanelNetError
			});
			this->AppStatusBar->Location = System::Drawing::Point(0, 468);
			this->AppStatusBar->Name = L"AppStatusBar";
			this->AppStatusBar->Size = System::Drawing::Size(992, 28);
			this->AppStatusBar->TabIndex = 61;
			this->AppStatusBar->Text = L"statusStrip1";
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->groupBox1->Controls->Add(this->label13);
			this->groupBox1->Controls->Add(this->label12);
			this->groupBox1->Controls->Add(this->OutAmpNumUpDwn);
			this->groupBox1->Controls->Add(this->OutSlopeNumUpDwn);
			this->groupBox1->Controls->Add(this->label10);
			this->groupBox1->Controls->Add(this->OutFuncListBox);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox1->Location = System::Drawing::Point(20, 306);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(162, 150);
			this->groupBox1->TabIndex = 60;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Output Layer";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(30, 126);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(51, 13);
			this->label13->TabIndex = 30;
			this->label13->Text = L"Amplify:";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(38, 104);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(43, 13);
			this->label12->TabIndex = 28;
			this->label12->Text = L"Slope:";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(32, 19);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(117, 13);
			this->label10->TabIndex = 26;
			this->label10->Text = L"Activation Function";
			// 
			// label4
			// 
			this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(210, 198);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(133, 13);
			this->label4->TabIndex = 57;
			this->label4->Text = L"Response Variable (Y)";
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(20, 198);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(128, 13);
			this->label3->TabIndex = 55;
			this->label3->Text = L"Predictor Variable (X)";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(20, 6);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(58, 13);
			this->label1->TabIndex = 51;
			this->label1->Text = L"Data File";
			// 
			// ModelFitGUIForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(992, 496);
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->tableDataGridView);
			this->Controls->Add(this->groupBox6);
			this->Controls->Add(this->AppStatusBar);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->HeaderCkBox);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->YlistBox);
			this->Controls->Add(this->XlistBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->FitModelBtn);
			this->Controls->Add(this->FileBrowseBtn);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ExitBtn);
			this->Controls->Add(this->DataFileTBox);
			this->MinimumSize = System::Drawing::Size(850, 490);
			this->Name = L"ModelFitGUIForm";
			this->Text = L"ModelFit";
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->UnitsNumUpDwn))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ScaleNumUpDwn))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->InitRangeNumUpDwn))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumIterNumUpDwn))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MinNetErrNumUpDwn))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MomentNumUpDwn))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->LearnConstNumUpDwn))->EndInit();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HidAmpNumUpDwn))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HidSlopeNumUpDwn))->EndInit();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tableDataGridView))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OutAmpNumUpDwn))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OutSlopeNumUpDwn))->EndInit();
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			this->AppStatusBar->ResumeLayout(false);
			this->AppStatusBar->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		/////////////////////////////////////////////////////////////////////
		// Message Handlers
		/////////////////////////////////////////////////////////////////////

		private: System::Void FileBrowseBtn_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			OpenFileDialog openFileDialog;			

			openFileDialog.InitialDirectory = Directory::GetCurrentDirectory();
			openFileDialog.Filter = "csv files (*.csv)|*.csv|All files (*.*)|*.*";
			openFileDialog.FilterIndex = 1;
			openFileDialog.RestoreDirectory = true;

			if (openFileDialog.ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				// display the wait cursor
				Cursor->Current = Cursors::WaitCursor;

				// the full file name of specified data file
				String^ fullFileName = openFileDialog.FileName;

				// load the CSV file containing the training data
				try
				{
					// when new data is aquired the model parameters must be set before we can fit a model
					this->FitModelBtn->Enabled = false;
					this->SaveToBtn->Enabled = false;
					this->SaveNetworkBtn->Enabled = false;

					LoadData(fullFileName);
				}
				catch (IOException^ ioEx)
				{
					MessageBox::Show(ioEx->Message, "ModelFit", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				}

				// reset the cursor
				Cursor->Current = Cursors::Default;
			}
		}

		/////////////////////////////////////////////////////////////////////

		private: System::Void FitModelBtn_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if (mPredictorIdx != -1 && mResponseIdx != -1)
			{
				// display the wait cursor
				Cursor->Current = Cursors::WaitCursor;

				// disable the GUI buttons
				this->ExitBtn->Enabled = false;
				this->FitModelBtn->Enabled = false;
				this->FileBrowseBtn->Enabled = false;
				this->SaveToBtn->Enabled = false;
				this->SaveNetworkBtn->Enabled = false;

				// update the information text label and status bar
				this->InfoLabel->Text = "Training Started - Please wait...";
				this->PanelStatus->Text = "Status: Running...";
				this->PanelIterations->Text = "Iterations: 0";
				this->PanelNetError->Text = "Minimum Error:";
				Update();

				// fit the model
				int result = FitModel();

				// reset the cursor
				Cursor->Current = Cursors::Default;

				// update the information text label
				this->PanelStatus->Text = "Status: Idle";

				// always re-enable the exit and browse buttons
				this->ExitBtn->Enabled = true;
				this->FileBrowseBtn->Enabled = true;

				// only re-enable the rest of the controls if there is a valid result
				if (result == 0)
				{
					this->InfoLabel->Text = "Training Complete!";

					// enable the GUI buttons
					this->FitModelBtn->Enabled = true;
					this->SaveToBtn->Enabled = true;
					this->SaveNetworkBtn->Enabled = true;
				}
				else
				{
					this->InfoLabel->Text = "Training Terminated!";
					this->PanelIterations->Text = "";
					this->PanelNetError->Text = "";
				}
			}
			else
			{
				// the GUI should prevent these situations - but just in case - handle them anyway
				if (mPredictorIdx == -1 && mResponseIdx == -1)
				{
					MessageBox::Show("You must select a predictor (X) and a response variable (Y).",
						             "ModelFit", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				}
				else if (mPredictorIdx == -1)
				{
					MessageBox::Show("You have not selected a predictor variable (X).",
									 "ModelFit", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				}
				else
				{
					MessageBox::Show("You have not selected a response variable (Y).",
									 "ModelFit", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				}
			}
		}

		/////////////////////////////////////////////////////////////////////

		private: System::Void SaveToBtn_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			SaveFileDialog saveFileDialog;

			saveFileDialog.InitialDirectory = Directory::GetCurrentDirectory();
			saveFileDialog.FilterIndex = 1;
			saveFileDialog.RestoreDirectory = true;

			// the default output file name
			String^ fname = mDataFile->Substring(mDataFile->LastIndexOf('\\') + 1);

			// determine the output type
			if (this->CSVRadioBtn->Checked)
			{
				saveFileDialog.Filter = "csv files (*.csv)|*.csv";
				fname = fname->Substring(0, fname->IndexOf('.')) + "_TrainedOutput.csv";
			}
			else if (this->ExcelRadioBtn->Checked)
			{
				saveFileDialog.Filter = "xls files (*.xls)|*.xls";
				fname = fname->Substring(0, fname->IndexOf('.')) + "_TrainedOutput.xls";
			}

			saveFileDialog.FileName = fname;

			if (saveFileDialog.ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				// the full name of the file to save the data to
				String^ fullFileName = saveFileDialog.FileName;

				// generate output of the appropriate type
				try
				{
					if (this->CSVRadioBtn->Checked)
					{
						GenerateCSVOutput(*mNet, fullFileName);
					}
					else if (this->ExcelRadioBtn->Checked)
					{
						GenerateExcelOutput(*mNet, fullFileName);
					}
				}
				catch (IOException^ ioEx)
				{
					MessageBox::Show(ioEx->Message, "ModelFit", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				}
			}
		}

		/////////////////////////////////////////////////////////////////////

		private: System::Void SaveNetworkBtn_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			SaveFileDialog saveFileDialog;

			saveFileDialog.InitialDirectory = Directory::GetCurrentDirectory();
			saveFileDialog.FilterIndex = 1;
			saveFileDialog.RestoreDirectory = true;
			saveFileDialog.Filter = "net files (*.net)|*.net";

			// the default network file name
			String^ fname = mDataFile->Substring(mDataFile->LastIndexOf('\\') + 1);
			fname = fname->Substring(0, fname->IndexOf('.')) + "_TrainedNetwork.net";

			saveFileDialog.FileName = fname;

			if (saveFileDialog.ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				// the full name of the file to save the network to
				String^ fullFileName = saveFileDialog.FileName;

				// write the network to the file
				try
				{
					msclr::interop::marshal_context context;					
					mNet->writeToFile(context.marshal_as<std::string>(fullFileName));
				}
				catch (IOException^ ioEx)
				{
					MessageBox::Show(ioEx->Message, "ModelFit", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				}
			}
		}

		/////////////////////////////////////////////////////////////////////

		private: System::Void HeaderCkBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		{
			mDataTable->setHeader(this->HeaderCkBox->Checked);

			// re-load the CSV file (if selected) to reflect the change in header status
			if (mDataFile->Length > 0)
			{
				// display the wait cursor
				Cursor->Current = Cursors::WaitCursor;

				LoadData(mDataFile);
				PopulateVariableListBoxes();

				// reset the cursor
				Cursor->Current = Cursors::Default;
			}
		}

		/////////////////////////////////////////////////////////////////////

		private: System::Void ListBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
		{
			mPredictorIdx = this->XlistBox->SelectedIndex;
			mResponseIdx = this->YlistBox->SelectedIndex;
			
			if (mPredictorIdx != -1 && mResponseIdx != -1)
			{
				// update the information text label
				this->InfoLabel->Text = "You can now fit the model";

				// enable the fit model button
				if (this->FitModelBtn->Enabled == false)
				{
					this->FitModelBtn->Enabled = true;
				}

				this->PanelIterations->Text = "";
				this->PanelNetError->Text = "";
			}

			this->SaveToBtn->Enabled = false;
			this->SaveNetworkBtn->Enabled = false;
		}

		/////////////////////////////////////////////////////////////////////

		private: System::Void ExitBtn_Click(System::Object^  sender, System::EventArgs^  e)
		{
			Close();
		}

		/////////////////////////////////////////////////////////////////////
		// Private Helper Methods
		/////////////////////////////////////////////////////////////////////

		/// <summary>
		/// Constructs and trains a neural network, using the user selected
		/// settings, to fit a model to the selected dataset.
		/// 
		/// Training continues until the maximum number of iterations has 
		/// been exceeded or the total network error is less than the set
		/// minimum network error value.  In the former case the trained 
		/// neural network is the network that achieved the minimum network
		/// error during the training process.
		/// </summary>
		/// <returns>0 if successful otherwise -1</returns>        
		/// 
		private: int FitModel()
		{
			int result = 0;
			bool converged = false;
			bool invalidResult = false;
			double netError = -1;
			double minErr = DBL_MAX;

			NeuralNet minNet;		// keeps track of the network with the minimum network error
			NNetTrainer trainer;	// this object trains the neural net

			// get the user selected parameters
			int numIterations = (int)this->NumIterNumUpDwn->Value;
			int numHiddenUnits = (int)this->UnitsNumUpDwn->Value;
			double learnConst = (double)this->LearnConstNumUpDwn->Value;
			double momentum = (double)this->MomentNumUpDwn->Value;
			double scaleFactor = (double)this->ScaleNumUpDwn->Value;
			double minNetError = (double)this->MinNetErrNumUpDwn->Value;
			double initRange = (double)this->InitRangeNumUpDwn->Value;
			double outSlope = (double)this->OutSlopeNumUpDwn->Value;
			double hidSlope = (double)this->HidSlopeNumUpDwn->Value;
			double outAmplify = (double)this->OutAmpNumUpDwn->Value;
			double hidAmplify = (double)this->HidAmpNumUpDwn->Value;			
			ActiveT outFunction = (ActiveT)this->OutFuncListBox->SelectedIndex;
			ActiveT hidFunction = (ActiveT)this->HidFuncListBox->SelectedIndex;

			// use a fixed seed (for now) so the results can be repeated
			srand(1);

			// populate the training set data
			PopulateTrainingSet();

			// initialize the trainer
			trainer.addNewTrainingSet(*mInputVecs, *mTargetVecs);
			trainer.setLearningConstant(learnConst);
			trainer.setMomentum(momentum);

			// clear the neural network ready to fit the model data
			mNet->clearNeuralNetwork();

			// initialize the network
			mNet->setNumInputs(1);                          // a single input value (the 'x-value')
			mNet->setNumOutputs(1);                         // a single output value (the 'y-value')
			mNet->setOutputUnitType(outFunction);
			mNet->setOutputUnitSlope(outSlope);
			mNet->setOutputUnitAmplify(outAmplify);

			// use a fixed architecture of one hidden layer
			mNet->addLayer(numHiddenUnits, hidFunction, initRange, hidSlope, hidAmplify);

			// carry out the training
			for (int i = 1; i <= numIterations; i++)
			{
				trainer.trainNeuralNet(*mNet);
				netError = trainer.getNetError() * scaleFactor;

				// check for an invalid result from the network trainer
				if (std::isnan(netError) || fabs(netError) == std::numeric_limits<double>::infinity())
				{
					MessageBox::Show("The network trainer has produced an invalid result:\nNetwork Error = " + netError.ToString() +
									 "\nThe training process has been stopped.\nPlease adjust the model settings and try again.",
									 "ModelFit", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);

					invalidResult = true;
					result = -1;
					break;
				}

				if (netError < minNetError)
				{
					// the solution has converged
					MessageBox::Show("The solution has converged after " + i.ToString() + " iterations.",
									 "ModelFit", MessageBoxButtons::OK, MessageBoxIcon::Information);

					// update the status bar
					this->PanelIterations->Text = "Iterations: " + i.ToString();
					this->PanelNetError->Text = "Minimum Error: " + netError.ToString("G5");

					converged = true;
					break;
				}

				// keep track of the minimum error value
				if (netError < minErr)
				{
					// copy the state of the neural net at the minimum error value
					minNet = *mNet;
					minErr = netError;
				}

				// show the current progress
				if (i % 100 == 0)
				{
					this->PanelIterations->Text = "Iterations: " + i.ToString();
					this->PanelNetError->Text = "Network Error: " + netError.ToString("G5");
					Update();
				}

				trainer.resetNetError();
			}

			if (!converged && !invalidResult)
			{
				// the solution has not converged within the given number of iterations
				MessageBox::Show("The solution has not converged.\n" +
								 "The minimum error value was: " + minErr.ToString("G5") + "\n" +
								 "The neural network that achieved this minimum will be used to fit the model.",
								 "ModelFit", MessageBoxButtons::OK, MessageBoxIcon::Information);

				// copy the net with settings at the minimum error value
				*mNet = minNet;

				// update the status bar
				this->PanelIterations->Text = "Iterations: " + numIterations.ToString();
				this->PanelNetError->Text = "Minimum Error: " + minErr.ToString("G5");
			}

			// show the output in excel - if requested
			if (this->ExcelOutputCkBox->Checked && !invalidResult)
			{
				ShowOutputInExcel(*mNet);
			}

			return result;
		}

		/// <summary>
		/// Populates the training set input and target vectors.
		/// 
		/// The input and target vectors are extracted from the database
		/// table and stored within a list so that they can be used by the 
		/// neural network training routine. The values are also scaled -
		/// scaling the magnitude of the data values to fall within the
		/// range 0-1 can improve the model fit.
		/// </summary>
		/// 
		private: void PopulateTrainingSet()
		{
			double scaleFactor = (double)this->ScaleNumUpDwn->Value;

			if (mPredictorIdx != -1 && mResponseIdx != -1)
			{
				// we are only using single input and target values in this application but 
				// the neural net allows for multiple input and target values using a list
				// so the single x- and y-values are stored in a list with only one element
				vector<double> dX;
				vector<double> dY;

				// clear the training set data
				mInputVecs->clear();
				mTargetVecs->clear();

				// read the x-predictor and y-response values from the data table
				mDataTable->getNumericCol(mPredictorIdx, dX);
				mDataTable->getNumericCol(mResponseIdx, dY);

				// populate the training set input and target vectors
				for (int i = 0; i < (int)dX.size(); i++)
				{
					vector<double> iVec;
					vector<double> tVec;

					// scale the training set input and output values
					iVec.push_back(dX[i] / scaleFactor);      // training set input vector
					tVec.push_back(dY[i] / scaleFactor);      // training set target vector

					// the input and target vectors are also stored within a list
					mInputVecs->push_back(iVec);
					mTargetVecs->push_back(tVec);
				}
			}
		}

		/// <summary>
		/// Loads the selected data file into an internal DataTable object.
		///
		/// The first 100 lines of the data file are also written to a table and
		/// displayed in the form's data preview data grid control. The predictor
		/// and response variables list boxes are also populated with the data 
		/// file column headings.
		/// </summary>
		/// <param name="filename">the full name, including path, of the data file</param>
		/// 
		private: void LoadData(String^ const filename)
		{
			// create a data table from the database file containing the training data
			msclr::interop::marshal_context context;
			mDataTable->readFromFile(context.marshal_as<std::string>(filename), this->HeaderCkBox->Checked);

			// check that the data has been read from the file without any errors
			if (mDataTable->getNumRows() <= 0 || mDataTable->getNumCols() <= 0)
			{
				MessageBox::Show("The selected file does not appear to be in the correct format.",
								 "ModelFit", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);

				// clear the filename textbox, the data preview control and the variables list boxes
				this->DataFileTBox->Clear();
				this->tableDataGridView->DataSource = nullptr;
				this->XlistBox->Items->Clear();
				this->YlistBox->Items->Clear();
				this->PanelIterations->Text = "";
				this->PanelNetError->Text = "";

				// update the information text label
				this->InfoLabel->Text = "Please select a data file";
			}
			else
			{
				// set the data file name (after the data has successfully loaded)
				mDataFile = filename;
				this->DataFileTBox->Text = filename;

				// populate the data preview
				PopulateTableGridView();

				// populate the x and y variable list boxes
				PopulateVariableListBoxes();

				// update the information text label
				this->InfoLabel->Text = "Please select the variables";
				this->PanelIterations->Text = "";
				this->PanelNetError->Text = "";
			}
		}

		/// <summary>
		/// Populates the preview data grid view with the first 100 lines of the 
		/// selected data file.
		/// </summary>
		/// 
		private: void PopulateTableGridView()
		{
			// create a new data source for the grid view
			System::Data::DataTable^ dt = gcnew System::Data::DataTable();

			// add the data file column names to the new data source
			vector<string> colNames;
			mDataTable->getColumnNames(colNames);

			if (colNames.size() > 0)
			{
				// use the data file column names
				for (int j = 0; j < mDataTable->getNumCols(); j++)
				{
					String^ columnName = gcnew String(colNames[j].c_str());
					dt->Columns->Add(columnName->Trim());
				}
			}
			else
			{
				// use generic column names
				for (int i = 0; i < mDataTable->getNumCols(); i++)
				{
					String^ columnName = "Column " + (i + 1).ToString();
					dt->Columns->Add(columnName->Trim());
				}
			}

			// populate the new data source with up to the first 100 rows of the data file
			int numRows = 100;

			if (mDataTable->getNumRows() < 100)
			{
				// the table has less than 100 rows
				numRows = mDataTable->getNumRows();
			}

			// add the data file rows to the new data source
			for (int i = 0; i < numRows; i++)
			{
				// get the row data
				vector<double> row;
				mDataTable->getNumericRow(i, row);
				cli::array<DOUBLE^>^ line = gcnew cli::array<DOUBLE^>(mDataTable->getNumCols());

				for (int j = 0; j < mDataTable->getNumCols(); j++)
				{
					// populate the row cells
					double colVal = row[j];
					line[j] = colVal;
				}

				// add the row
				dt->Rows->Add(line);
			}

			// add two rows to the new data source containing the minimum and maximum column values
			vector<double> column;

			for (int i = 0; i < 2; i++)
			{
				cli::array<DOUBLE^>^ line = gcnew cli::array<DOUBLE^>(mDataTable->getNumCols());

				for (int j = 0; j < mDataTable->getNumCols(); j++)
				{
					// get the column data
					column.clear();
					mDataTable->getNumericCol(j, column);

					double minMaxvalue = 0;

					if (i == 0 && column.size() > 0)
					{
						// get the minimum value
						minMaxvalue = *min_element(column.begin(), column.end());
					}
					else if (i == 1 && column.size() > 0)
					{
						// get the maximum value
						minMaxvalue = *max_element(column.begin(), column.end());
					}

					// populate the row cells
					line[j] = minMaxvalue;
				}

				// add the row
				dt->Rows->Add(line);
			}

			// attach the new data source to the grid view
			tableDataGridView->DataSource = dt;
		}

		/// <summary>
		/// Applies the trained neural network model to the selected predictor
		/// input data and outputs the results to a .csv file.
		/// 
		/// The output consists of 3 columns - the first contains the selected
		/// training set input (or predictor) values, the second the selected 
		/// training set target values and the third contains the trained model 
		/// output responses to the given input values.
		/// </summary>
		/// <param name="net">the trained neural network</param>
		/// <param name="fname">the name of the file to write the results to</param>
		/// 
		private: void GenerateCSVOutput(NeuralNet net, String^ const fname)
		{
			vector<double> dX;
			vector<double> dM;
			double scaleFactor = (double)this->ScaleNumUpDwn->Value;

			try
			{
				StreamWriter^ ofstream = gcnew StreamWriter(fname);

				// output the column titles
				vector<string> colNames;
				mDataTable->getColumnNames(colNames);
				String^ sPredictor = gcnew String(colNames[mPredictorIdx].c_str());
				String^ sResponse = gcnew String(colNames[mResponseIdx].c_str());

				ofstream->WriteLine(sPredictor->Trim() + "," + sResponse->Trim() + ",model");

				for (int i = 0; i < (int)mInputVecs->size(); i++)
				{
					// calculate the model response value given the predictor value from the training set
					dX = (*mInputVecs)[i];
					net.getResponse(dX, dM);

					// the required values are stored in vectors and need re-scaling
					double xValue = dX[0] * scaleFactor;
					double yValue = (*mTargetVecs)[i][0] * scaleFactor;
					double mValue = dM[0] * scaleFactor;

					// write the results to the output file
					ofstream->Write(xValue.ToString("G16"));
					ofstream->Write(",");
					ofstream->Write(yValue.ToString("G16"));
					ofstream->Write(",");
					ofstream->WriteLine(mValue.ToString("G16"));
				}

				ofstream->Close();
			}
			catch (IOException^ ioEx)
			{
				MessageBox::Show(ioEx->Message, "ModelFit", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			}
		}

		/// <summary>
		/// Applies the trained neural network model to the selected predictor
		/// input data and outputs the results to an Excel .xls file.
		/// 
		/// The output consists of 3 columns - the first contains the selected
		/// training set input (or predictor) values, the second the selected 
		/// training set target values and the third contains the trained model 
		/// output responses to the given input values. An XY-Scatter graph of 
		/// the data is also produced.
		/// </summary>
		/// <param name="net">the trained neural network</param>
		/// <param name="fname">the name of the file to write the results to</param>
		///
		private: void GenerateExcelOutput(NeuralNet net, String^ const fname)
		{
			vector<double> dX;
			vector<double> dM;
			double scaleFactor = (double)this->ScaleNumUpDwn->Value;

			// open Excel, add a workbook and obtain a worksheet
			Microsoft::Office::Interop::Excel::Application^ xlApp = 
									gcnew Microsoft::Office::Interop::Excel::ApplicationClass();
			Workbook^ xlWorkBook = xlApp->Workbooks->Add(Type::Missing);
			Worksheet^ xlWorkSheet = safe_cast<Worksheet^>(xlWorkBook->Worksheets->Item[1]);			

			// stops Excel asking the user if they want to replace an existing file
			// the save file dialog will have already asked this question
			xlApp->DisplayAlerts = false;

			// add a header line
			xlWorkSheet->Cells[1, 1] = "";
			xlWorkSheet->Cells[1, 2] = "target";
			xlWorkSheet->Cells[1, 3] = "model";

			// add the model and training data 
			for (int i = 0; i < (int)mInputVecs->size(); i++)
			{
				// calculate the model response value given the predictor value from the training set
				dX = (*mInputVecs)[i];
				net.getResponse(dX, dM);

				// the required values are stored in vectors and need re-scaling
				double xValue = dX[0] * scaleFactor;
				double yValue = (*mTargetVecs)[i][0] * scaleFactor;
				double mValue = dM[0] * scaleFactor;

				// write out the results
				xlWorkSheet->Cells[i + 2, 1] = xValue.ToString("G16");
				xlWorkSheet->Cells[i + 2, 2] = yValue.ToString("G16");
				xlWorkSheet->Cells[i + 2, 3] = mValue.ToString("G16");
			}

			// plot the data as an xy-scatter graph
			ChartObjects^ xlCharts = safe_cast<ChartObjects^>(xlWorkSheet->ChartObjects(Type::Missing));
			ChartObject^ modelChart = safe_cast<ChartObject^>(xlCharts->Add(200, 10, 450, 300));
			Chart^ chartPage = modelChart->Chart;

			Range^ chartRange = safe_cast<Range^>(xlWorkSheet->Range["A1", "C" + (mInputVecs->size() + 1).ToString()]);
			chartPage->SetSourceData(chartRange, XlRowCol::xlColumns);
			chartPage->ChartType = XlChartType::xlXYScatter;

			// set the axis labels
			vector<string> colNames;
			mDataTable->getColumnNames(colNames);

			Axis^ xAxis = safe_cast<Axis^>(chartPage->Axes(XlAxisType::xlCategory, XlAxisGroup::xlPrimary));
			xAxis->HasTitle = true;
			xAxis->AxisTitle->Text = gcnew String(colNames[mPredictorIdx].c_str());

			Axis^ yAxis = safe_cast<Axis^>(chartPage->Axes(XlAxisType::xlValue, XlAxisGroup::xlPrimary));
			yAxis->HasTitle = true;
			yAxis->AxisTitle->Text = gcnew String(colNames[mResponseIdx].c_str());

			// set the graph title
			chartPage->HasTitle = true;
			chartPage->ChartTitle->Font->Size = 12;
			chartPage->ChartTitle->Text = GraphTitle();

			// save the workbook and close Excel
			xlWorkBook->SaveAs(fname, XlFileFormat::xlWorkbookNormal, 
							   Type::Missing, Type::Missing, Type::Missing, Type::Missing, 
							   XlSaveAsAccessMode::xlExclusive, Type::Missing, Type::Missing, 
							   Type::Missing, Type::Missing, Type::Missing);

			xlWorkBook->Close(true, Type::Missing, Type::Missing);
			xlApp->DisplayAlerts = true;
			xlApp->Quit();

			// release resources
			ReleaseObject(xlWorkSheet);
			ReleaseObject(xlWorkBook);
			ReleaseObject(xlApp);
		}

		/// <summary>
		/// Applies the trained neural network model to the selected predictor
		/// input data and displays the results in Excel.
		/// 
		/// The results consists of 3 columns - the first contains the selected
		/// training set input (or predictor) values, the second the selected 
		/// training set target values and the third contains the trained model 
		/// output responses to the given input values. An XY-Scatter graph of 
		/// the data is also produced.
		/// </summary>
		/// <param name="net">the trained neural network</param>
		/// 
		private: void ShowOutputInExcel(NeuralNet net)
		{
			vector<double> dX;
			vector<double> dM;
			double scaleFactor = (double)this->ScaleNumUpDwn->Value;

			// open Excel, add a workbook and obtain a worksheet
			Microsoft::Office::Interop::Excel::Application^ xlApp =
				gcnew Microsoft::Office::Interop::Excel::ApplicationClass();
			Workbook^ xlWorkBook = xlApp->Workbooks->Add(Type::Missing);
			Worksheet^ xlWorkSheet = safe_cast<Worksheet^>(xlWorkBook->Worksheets->Item[1]);

			// add a header line
			xlWorkSheet->Cells[1, 1] = "";
			xlWorkSheet->Cells[1, 2] = "target";
			xlWorkSheet->Cells[1, 3] = "model";

			// add the model and training data 
			for (int i = 0; i < (int)mInputVecs->size(); i++)
			{
				// calculate the model response value given the predictor value from the training set
				dX = (*mInputVecs)[i];
				net.getResponse(dX, dM);

				// the required values are stored in vectors and need re-scaling
				double xValue = dX[0] * scaleFactor;
				double yValue = (*mTargetVecs)[i][0] * scaleFactor;
				double mValue = dM[0] * scaleFactor;

				// write out the results
				xlWorkSheet->Cells[i + 2, 1] = xValue.ToString("G16");
				xlWorkSheet->Cells[i + 2, 2] = yValue.ToString("G16");
				xlWorkSheet->Cells[i + 2, 3] = mValue.ToString("G16");
			}

			// plot the data as an xy-scatter graph
			ChartObjects^ xlCharts = safe_cast<ChartObjects^>(xlWorkSheet->ChartObjects(Type::Missing));
			ChartObject^ modelChart = safe_cast<ChartObject^>(xlCharts->Add(200, 10, 450, 300));
			Chart^ chartPage = modelChart->Chart;

			Range^ chartRange = safe_cast<Range^>(xlWorkSheet->Range["A1", "C" + (mInputVecs->size() + 1).ToString()]);
			chartPage->SetSourceData(chartRange, XlRowCol::xlColumns);
			chartPage->ChartType = XlChartType::xlXYScatter;

			// set the axis labels
			vector<string> colNames;
			mDataTable->getColumnNames(colNames);

			Axis^ xAxis = safe_cast<Axis^>(chartPage->Axes(XlAxisType::xlCategory, XlAxisGroup::xlPrimary));
			xAxis->HasTitle = true;
			xAxis->AxisTitle->Text = gcnew String(colNames[mPredictorIdx].c_str());

			Axis^ yAxis = safe_cast<Axis^>(chartPage->Axes(XlAxisType::xlValue, XlAxisGroup::xlPrimary));
			yAxis->HasTitle = true;
			yAxis->AxisTitle->Text = gcnew String(colNames[mResponseIdx].c_str());

			// set the graph title
			chartPage->HasTitle = true;
			chartPage->ChartTitle->Font->Size = 12;
			chartPage->ChartTitle->Text = GraphTitle();

			// make Excel visible to the user
			xlApp->Visible = true;

			// release resources
			ReleaseObject(xlWorkSheet);
			ReleaseObject(xlWorkBook);
			ReleaseObject(xlApp);
		}

		/// <summary>
		/// Formats the graph title for the Excel plot.
		/// </summary>
		/// <returns>the formatted graph title</returns>
		/// 
		private: String^ GraphTitle()
		{
			// extract the variable names and make them lowercase
			vector<string> colNames;
			mDataTable->getColumnNames(colNames);
			String^ predictor = gcnew String(colNames[mPredictorIdx].c_str());
			String^ response = gcnew String(colNames[mResponseIdx].c_str());

			predictor = predictor->ToLower();
			response = response->ToLower();

			// make the first letter of each name uppercase
			String^ firstLetter = predictor->Substring(0, 1);
			firstLetter = firstLetter->ToUpper();
			predictor = predictor->Remove(0, 1);
			predictor = predictor->Insert(0, firstLetter);

			firstLetter = response->Substring(0, 1);
			firstLetter = firstLetter->ToUpper();
			response = response->Remove(0, 1);
			response = response->Insert(0, firstLetter);

			// create and format the finished title
			String^ title = predictor + " (Predictor) vs " + response + " (Response)";

			return title;
		}


		/// <summary>
		/// Releases a specified COM object.
		/// </summary>
		/// <param name="obj">the object to be released</param>
		/// 
		private: void ReleaseObject(System::Object^ obj)
		{
			try
			{
				System::Runtime::InteropServices::Marshal::ReleaseComObject(obj);
				obj = nullptr;
			}
			catch (Exception^ ex)
			{
				obj = nullptr;
				MessageBox::Show("Exception Occured while releasing object " + ex->ToString());
			}
			finally
			{
				GC::Collect();
			}
		}

		/// <summary>
		/// Populates the form's Activation function list boxes with the available 
		/// values of the ActiveT enumerated type.
		/// </summary>
		/// 
		private: void PopulateActivationListBoxes()
		{
			int id = 0;
			bool done = false;

			while (!done)
			{
				ActiveT func = (ActiveT)id;
				string funcID = NNetUnit::ActiveTtoString(func);

				if (funcID == "Unknown")
				{
					// we have processed all the valid ActiveT enum values
					done = true;
				}
				else
				{					
					this->OutFuncListBox->Items->Add(gcnew String(funcID.c_str()));
					this->HidFuncListBox->Items->Add(gcnew String(funcID.c_str()));

					id++;
				}
			}

			// select the first entries in the list boxes
			this->OutFuncListBox->SelectedIndex = 0;
			this->HidFuncListBox->SelectedIndex = 0;
		}

		/// <summary>
		/// Populates the forms Predictor and Response variables 
		/// list boxes with the data file column headings.
		/// </summary>
		/// 
		private: void PopulateVariableListBoxes()
		{
			// clear the list boxes
			this->XlistBox->Items->Clear();
			this->YlistBox->Items->Clear();

			if (mDataTable->getHeader())
			{
				// populate the list boxes with the data header row
				vector<string> colNames;
				mDataTable->getColumnNames(colNames);

				for (int i = 0; i < (int)colNames.size(); i++)
				{
					this->XlistBox->Items->Add(gcnew String(colNames[i].c_str()));
					this->YlistBox->Items->Add(gcnew String(colNames[i].c_str()));
				}
			}
			else
			{
				// populate the list boxes with column ids
				for (int i = 0; i < mDataTable->getNumCols(); i++)
				{
					String^ name = "Column " + (i + 1).ToString();

					this->XlistBox->Items->Add(name);
					this->YlistBox->Items->Add(name);
				}
			}
		}
	};
}
