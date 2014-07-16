#pragma once
#include "stdafx.h"
#include "VideoManager.h"

namespace Ar_drone_20 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	System::Security::Permissions::FileIOPermission;

	/// <summary>
	/// Summary for MyMainWindowsForm
	/// </summary>
	public ref class MyMainWindowsForm : public System::Windows::Forms::Form
	{
	private: 
		VideoManager* _vm;
	private: System::Windows::Forms::Application^  application;

	private: System::Windows::Forms::TabControl^  tabControl;

	private: System::Windows::Forms::TabPage^  tabPageColor;

	private: System::Windows::Forms::Label^  label2;

	private: System::Windows::Forms::Label^  label_ErrorMargin;

	private: System::Windows::Forms::Label^  label_saturation;

	private: System::Windows::Forms::Label^  label_hue;

	private: System::Windows::Forms::TrackBar^  trackBar_saturation;

	private: System::Windows::Forms::TrackBar^  trackBar_ErrorMargin;

	private: System::Windows::Forms::TrackBar^  trackBar_hue;
	private: System::Windows::Forms::TabPage^  tabPageFace;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::RadioButton^  radioButton_center;
	private: System::Windows::Forms::RadioButton^  radioButton_zoom;



	private: System::Windows::Forms::Label^  label_title_face;
	private: System::Windows::Forms::TabPage^  tabPage_delete;

	private: System::Windows::Forms::ImageList^  imageList_tabControl;
	private: System::Windows::Forms::Label^  labelFPS;
	private: System::Windows::Forms::Label^  labelLatency;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::Label^  labelScale;
	private: System::Windows::Forms::PictureBox^  pictureBox_poweroffPad;
	private: System::Windows::Forms::PictureBox^  pictureBox_powerOffLM;
	private: System::Windows::Forms::CheckBox^  checkBoxVideo;
	private: System::Windows::Forms::Button^  buttonPhoto;
	private: System::Windows::Forms::TextBox^  textBox_saveFile;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
	private: System::Windows::Forms::Label^  labelTxtHue;
	private: System::Windows::Forms::Label^  labelErrorMargin;
	private: System::Windows::Forms::Label^  labelTxtSaturation;
	private: System::Windows::Forms::PictureBox^  pictureBoxTitle;
	private: System::Windows::Forms::CheckBox^  checkBox_automatic_mouvement;
	private: System::Windows::Forms::Label^  label1;








			 Multiple_Input_Devices* _mid;

	public:
		MyMainWindowsForm(VideoManager* vm, Multiple_Input_Devices* mid)
		{
			_vm = vm;
			_mid = mid;
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyMainWindowsForm()
		{
			if (components)
			{
				delete components;
			}
		}

	public: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Timer^  timer1;


	public: System::Windows::Forms::PictureBox^  pictureBox2;

	public: 
	private: 


	private: System::Windows::Forms::PictureBox^  pictureBox_Pad;
	private: System::Windows::Forms::PictureBox^  pictureBox_KeyBoard;
	private: System::Windows::Forms::PictureBox^  pictureBox_LeapMotion;

	public: 
	private: System::ComponentModel::IContainer^  components;

	protected: 

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyMainWindowsForm::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_Pad = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_KeyBoard = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_LeapMotion = (gcnew System::Windows::Forms::PictureBox());
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabPageFace = (gcnew System::Windows::Forms::TabPage());
			this->labelFPS = (gcnew System::Windows::Forms::Label());
			this->labelLatency = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->labelScale = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label_title_face = (gcnew System::Windows::Forms::Label());
			this->radioButton_center = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton_zoom = (gcnew System::Windows::Forms::RadioButton());
			this->tabPageColor = (gcnew System::Windows::Forms::TabPage());
			this->labelErrorMargin = (gcnew System::Windows::Forms::Label());
			this->labelTxtSaturation = (gcnew System::Windows::Forms::Label());
			this->labelTxtHue = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label_ErrorMargin = (gcnew System::Windows::Forms::Label());
			this->label_saturation = (gcnew System::Windows::Forms::Label());
			this->label_hue = (gcnew System::Windows::Forms::Label());
			this->trackBar_saturation = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar_ErrorMargin = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar_hue = (gcnew System::Windows::Forms::TrackBar());
			this->tabPage_delete = (gcnew System::Windows::Forms::TabPage());
			this->imageList_tabControl = (gcnew System::Windows::Forms::ImageList(this->components));
			this->pictureBox_poweroffPad = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_powerOffLM = (gcnew System::Windows::Forms::PictureBox());
			this->checkBoxVideo = (gcnew System::Windows::Forms::CheckBox());
			this->buttonPhoto = (gcnew System::Windows::Forms::Button());
			this->textBox_saveFile = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->pictureBoxTitle = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->checkBox_automatic_mouvement = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox_Pad))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox_KeyBoard))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox_LeapMotion))->BeginInit();
			this->tabControl->SuspendLayout();
			this->tabPageFace->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->BeginInit();
			this->tabPageColor->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_saturation))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_ErrorMargin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_hue))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox_poweroffPad))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox_powerOffLM))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxTitle))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Black;
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pictureBox1->Cursor = System::Windows::Forms::Cursors::Cross;
			this->pictureBox1->Location = System::Drawing::Point(13, 150);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1280, 720);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyMainWindowsForm::pictureBox1_MouseClick);
			// 
			// timer1
			// 
			this->timer1->Interval = 30;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyMainWindowsForm::timer1_Tick);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::Black;
			this->pictureBox2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pictureBox2->Location = System::Drawing::Point(1308, 420);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(582, 450);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->pictureBox2->TabIndex = 15;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox_Pad
			// 
			this->pictureBox_Pad->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->pictureBox_Pad->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox_Pad.Image")));
			this->pictureBox_Pad->Location = System::Drawing::Point(183, 886);
			this->pictureBox_Pad->Name = L"pictureBox_Pad";
			this->pictureBox_Pad->Size = System::Drawing::Size(96, 96);
			this->pictureBox_Pad->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox_Pad->TabIndex = 17;
			this->pictureBox_Pad->TabStop = false;
			this->pictureBox_Pad->UseWaitCursor = true;
			// 
			// pictureBox_KeyBoard
			// 
			this->pictureBox_KeyBoard->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->pictureBox_KeyBoard->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox_KeyBoard.Image")));
			this->pictureBox_KeyBoard->Location = System::Drawing::Point(12, 886);
			this->pictureBox_KeyBoard->Name = L"pictureBox_KeyBoard";
			this->pictureBox_KeyBoard->Size = System::Drawing::Size(96, 96);
			this->pictureBox_KeyBoard->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox_KeyBoard->TabIndex = 18;
			this->pictureBox_KeyBoard->TabStop = false;
			// 
			// pictureBox_LeapMotion
			// 
			this->pictureBox_LeapMotion->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->pictureBox_LeapMotion->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox_LeapMotion.Image")));
			this->pictureBox_LeapMotion->Location = System::Drawing::Point(352, 886);
			this->pictureBox_LeapMotion->Name = L"pictureBox_LeapMotion";
			this->pictureBox_LeapMotion->Size = System::Drawing::Size(96, 96);
			this->pictureBox_LeapMotion->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox_LeapMotion->TabIndex = 19;
			this->pictureBox_LeapMotion->TabStop = false;
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->tabPageFace);
			this->tabControl->Controls->Add(this->tabPageColor);
			this->tabControl->Controls->Add(this->tabPage_delete);
			this->tabControl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->tabControl->ImageList = this->imageList_tabControl;
			this->tabControl->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->tabControl->Location = System::Drawing::Point(1308, 79);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(583, 335);
			this->tabControl->TabIndex = 20;
			this->tabControl->SelectedIndexChanged += gcnew System::EventHandler(this, &MyMainWindowsForm::tabControl1_indexChanged);
			// 
			// tabPageFace
			// 
			this->tabPageFace->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->tabPageFace->Controls->Add(this->checkBox_automatic_mouvement);
			this->tabPageFace->Controls->Add(this->label1);
			this->tabPageFace->Controls->Add(this->labelFPS);
			this->tabPageFace->Controls->Add(this->labelLatency);
			this->tabPageFace->Controls->Add(this->numericUpDown1);
			this->tabPageFace->Controls->Add(this->labelScale);
			this->tabPageFace->Controls->Add(this->label3);
			this->tabPageFace->Controls->Add(this->label_title_face);
			this->tabPageFace->Controls->Add(this->radioButton_center);
			this->tabPageFace->Controls->Add(this->radioButton_zoom);
			this->tabPageFace->ImageIndex = 1;
			this->tabPageFace->Location = System::Drawing::Point(4, 71);
			this->tabPageFace->Name = L"tabPageFace";
			this->tabPageFace->Padding = System::Windows::Forms::Padding(3);
			this->tabPageFace->Size = System::Drawing::Size(575, 260);
			this->tabPageFace->TabIndex = 1;
			// 
			// labelFPS
			// 
			this->labelFPS->AutoSize = true;
			this->labelFPS->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->labelFPS->ForeColor = System::Drawing::Color::Maroon;
			this->labelFPS->Location = System::Drawing::Point(480, 227);
			this->labelFPS->Name = L"labelFPS";
			this->labelFPS->Size = System::Drawing::Size(71, 24);
			this->labelFPS->TabIndex = 7;
			this->labelFPS->Text = L"FPS : 0";
			// 
			// labelLatency
			// 
			this->labelLatency->AutoSize = true;
			this->labelLatency->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->labelLatency->ForeColor = System::Drawing::Color::Maroon;
			this->labelLatency->Location = System::Drawing::Point(449, 195);
			this->labelLatency->Name = L"labelLatency";
			this->labelLatency->Size = System::Drawing::Size(102, 24);
			this->labelLatency->TabIndex = 6;
			this->labelLatency->Text = L"Latence : 0";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->numericUpDown1->Location = System::Drawing::Point(516, 83);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {99, 0, 0, 0});
			this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(45, 30);
			this->numericUpDown1->TabIndex = 5;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {3, 0, 0, 0});
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &MyMainWindowsForm::numericUpDown1_ValueChanged);
			// 
			// labelScale
			// 
			this->labelScale->AutoSize = true;
			this->labelScale->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->labelScale->Location = System::Drawing::Point(244, 85);
			this->labelScale->Name = L"labelScale";
			this->labelScale->Size = System::Drawing::Size(262, 25);
			this->labelScale->TabIndex = 4;
			this->labelScale->Text = L"échelle de l\'image à analyser";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(23, 85);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(161, 25);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Mode d\'affichage";
			// 
			// label_title_face
			// 
			this->label_title_face->AutoSize = true;
			this->label_title_face->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label_title_face->Location = System::Drawing::Point(22, 19);
			this->label_title_face->Name = L"label_title_face";
			this->label_title_face->Size = System::Drawing::Size(186, 32);
			this->label_title_face->TabIndex = 0;
			this->label_title_face->Text = L"Configuration";
			// 
			// radioButton_center
			// 
			this->radioButton_center->AutoSize = true;
			this->radioButton_center->Checked = true;
			this->radioButton_center->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->radioButton_center->Location = System::Drawing::Point(48, 128);
			this->radioButton_center->Name = L"radioButton_center";
			this->radioButton_center->Size = System::Drawing::Size(98, 29);
			this->radioButton_center->TabIndex = 2;
			this->radioButton_center->TabStop = true;
			this->radioButton_center->Text = L"Centrer";
			this->radioButton_center->UseVisualStyleBackColor = true;
			this->radioButton_center->CheckedChanged += gcnew System::EventHandler(this, &MyMainWindowsForm::radioButton_center_CheckedChanged);
			// 
			// radioButton_zoom
			// 
			this->radioButton_zoom->AutoSize = true;
			this->radioButton_zoom->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->radioButton_zoom->Location = System::Drawing::Point(48, 163);
			this->radioButton_zoom->Name = L"radioButton_zoom";
			this->radioButton_zoom->Size = System::Drawing::Size(83, 29);
			this->radioButton_zoom->TabIndex = 1;
			this->radioButton_zoom->Text = L"Zoom";
			this->radioButton_zoom->UseVisualStyleBackColor = true;
			this->radioButton_zoom->CheckedChanged += gcnew System::EventHandler(this, &MyMainWindowsForm::radioButton_zoom_CheckedChanged);
			// 
			// tabPageColor
			// 
			this->tabPageColor->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->tabPageColor->Controls->Add(this->labelErrorMargin);
			this->tabPageColor->Controls->Add(this->labelTxtSaturation);
			this->tabPageColor->Controls->Add(this->labelTxtHue);
			this->tabPageColor->Controls->Add(this->label2);
			this->tabPageColor->Controls->Add(this->label_ErrorMargin);
			this->tabPageColor->Controls->Add(this->label_saturation);
			this->tabPageColor->Controls->Add(this->label_hue);
			this->tabPageColor->Controls->Add(this->trackBar_saturation);
			this->tabPageColor->Controls->Add(this->trackBar_ErrorMargin);
			this->tabPageColor->Controls->Add(this->trackBar_hue);
			this->tabPageColor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->tabPageColor->ImageIndex = 0;
			this->tabPageColor->Location = System::Drawing::Point(4, 71);
			this->tabPageColor->Name = L"tabPageColor";
			this->tabPageColor->Padding = System::Windows::Forms::Padding(3);
			this->tabPageColor->Size = System::Drawing::Size(575, 260);
			this->tabPageColor->TabIndex = 0;
			// 
			// labelErrorMargin
			// 
			this->labelErrorMargin->AutoSize = true;
			this->labelErrorMargin->Location = System::Drawing::Point(33, 210);
			this->labelErrorMargin->Name = L"labelErrorMargin";
			this->labelErrorMargin->Size = System::Drawing::Size(150, 25);
			this->labelErrorMargin->TabIndex = 30;
			this->labelErrorMargin->Text = L"Marge d\'erreur :";
			// 
			// labelTxtSaturation
			// 
			this->labelTxtSaturation->AutoSize = true;
			this->labelTxtSaturation->Location = System::Drawing::Point(71, 142);
			this->labelTxtSaturation->Name = L"labelTxtSaturation";
			this->labelTxtSaturation->Size = System::Drawing::Size(112, 25);
			this->labelTxtSaturation->TabIndex = 29;
			this->labelTxtSaturation->Text = L"Saturation :";
			// 
			// labelTxtHue
			// 
			this->labelTxtHue->AutoSize = true;
			this->labelTxtHue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->labelTxtHue->Location = System::Drawing::Point(53, 77);
			this->labelTxtHue->Name = L"labelTxtHue";
			this->labelTxtHue->Size = System::Drawing::Size(130, 25);
			this->labelTxtHue->TabIndex = 28;
			this->labelTxtHue->Text = L"Teinte / Hue :";
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(250, 12);
			this->label2->Name = L"label2";
			this->label2->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->label2->Size = System::Drawing::Size(148, 35);
			this->label2->TabIndex = 27;
			this->label2->Text = L"TLS / HLS";
			// 
			// label_ErrorMargin
			// 
			this->label_ErrorMargin->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label_ErrorMargin->Location = System::Drawing::Point(189, 210);
			this->label_ErrorMargin->Name = L"label_ErrorMargin";
			this->label_ErrorMargin->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->label_ErrorMargin->Size = System::Drawing::Size(45, 25);
			this->label_ErrorMargin->TabIndex = 25;
			this->label_ErrorMargin->Text = L"10";
			// 
			// label_saturation
			// 
			this->label_saturation->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label_saturation->Location = System::Drawing::Point(189, 142);
			this->label_saturation->Name = L"label_saturation";
			this->label_saturation->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->label_saturation->Size = System::Drawing::Size(45, 25);
			this->label_saturation->TabIndex = 23;
			this->label_saturation->Text = L"0";
			// 
			// label_hue
			// 
			this->label_hue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label_hue->Location = System::Drawing::Point(189, 77);
			this->label_hue->Name = L"label_hue";
			this->label_hue->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->label_hue->Size = System::Drawing::Size(45, 25);
			this->label_hue->TabIndex = 15;
			this->label_hue->Text = L"255";
			// 
			// trackBar_saturation
			// 
			this->trackBar_saturation->BackColor = System::Drawing::Color::SteelBlue;
			this->trackBar_saturation->Location = System::Drawing::Point(240, 128);
			this->trackBar_saturation->Maximum = 255;
			this->trackBar_saturation->Name = L"trackBar_saturation";
			this->trackBar_saturation->Size = System::Drawing::Size(170, 56);
			this->trackBar_saturation->TabIndex = 20;
			this->trackBar_saturation->ValueChanged += gcnew System::EventHandler(this, &MyMainWindowsForm::trackBar_saturation_Scroll);
			// 
			// trackBar_ErrorMargin
			// 
			this->trackBar_ErrorMargin->BackColor = System::Drawing::Color::SeaGreen;
			this->trackBar_ErrorMargin->Location = System::Drawing::Point(240, 198);
			this->trackBar_ErrorMargin->Maximum = 20;
			this->trackBar_ErrorMargin->Name = L"trackBar_ErrorMargin";
			this->trackBar_ErrorMargin->Size = System::Drawing::Size(170, 56);
			this->trackBar_ErrorMargin->TabIndex = 18;
			this->trackBar_ErrorMargin->Value = 10;
			this->trackBar_ErrorMargin->ValueChanged += gcnew System::EventHandler(this, &MyMainWindowsForm::trackBar_ErrorMargin_Scroll);
			// 
			// trackBar_hue
			// 
			this->trackBar_hue->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->trackBar_hue->Location = System::Drawing::Point(240, 66);
			this->trackBar_hue->Maximum = 255;
			this->trackBar_hue->Name = L"trackBar_hue";
			this->trackBar_hue->Size = System::Drawing::Size(170, 56);
			this->trackBar_hue->TabIndex = 16;
			this->trackBar_hue->ValueChanged += gcnew System::EventHandler(this, &MyMainWindowsForm::trackBar_hue_Scroll);
			// 
			// tabPage_delete
			// 
			this->tabPage_delete->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->tabPage_delete->ImageIndex = 2;
			this->tabPage_delete->Location = System::Drawing::Point(4, 71);
			this->tabPage_delete->Name = L"tabPage_delete";
			this->tabPage_delete->Padding = System::Windows::Forms::Padding(3);
			this->tabPage_delete->Size = System::Drawing::Size(575, 260);
			this->tabPage_delete->TabIndex = 2;
			// 
			// imageList_tabControl
			// 
			this->imageList_tabControl->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"imageList_tabControl.ImageStream")));
			this->imageList_tabControl->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList_tabControl->Images->SetKeyName(0, L"color.png");
			this->imageList_tabControl->Images->SetKeyName(1, L"faces.png");
			this->imageList_tabControl->Images->SetKeyName(2, L"delete.png");
			// 
			// pictureBox_poweroffPad
			// 
			this->pictureBox_poweroffPad->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox_poweroffPad.Image")));
			this->pictureBox_poweroffPad->Location = System::Drawing::Point(260, 958);
			this->pictureBox_poweroffPad->Name = L"pictureBox_poweroffPad";
			this->pictureBox_poweroffPad->Size = System::Drawing::Size(32, 32);
			this->pictureBox_poweroffPad->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox_poweroffPad->TabIndex = 21;
			this->pictureBox_poweroffPad->TabStop = false;
			// 
			// pictureBox_powerOffLM
			// 
			this->pictureBox_powerOffLM->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox_powerOffLM.Image")));
			this->pictureBox_powerOffLM->Location = System::Drawing::Point(416, 958);
			this->pictureBox_powerOffLM->Name = L"pictureBox_powerOffLM";
			this->pictureBox_powerOffLM->Size = System::Drawing::Size(32, 32);
			this->pictureBox_powerOffLM->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox_powerOffLM->TabIndex = 22;
			this->pictureBox_powerOffLM->TabStop = false;
			// 
			// checkBoxVideo
			// 
			this->checkBoxVideo->Appearance = System::Windows::Forms::Appearance::Button;
			this->checkBoxVideo->AutoSize = true;
			this->checkBoxVideo->FlatAppearance->BorderColor = System::Drawing::SystemColors::ButtonShadow;
			this->checkBoxVideo->FlatAppearance->BorderSize = 2;
			this->checkBoxVideo->FlatAppearance->CheckedBackColor = System::Drawing::Color::Green;
			this->checkBoxVideo->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBoxVideo->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"checkBoxVideo.Image")));
			this->checkBoxVideo->Location = System::Drawing::Point(1709, 912);
			this->checkBoxVideo->Name = L"checkBoxVideo";
			this->checkBoxVideo->Size = System::Drawing::Size(70, 70);
			this->checkBoxVideo->TabIndex = 25;
			this->checkBoxVideo->UseVisualStyleBackColor = true;
			this->checkBoxVideo->CheckedChanged += gcnew System::EventHandler(this, &MyMainWindowsForm::checkBoxVideo_CheckedChanged);
			// 
			// buttonPhoto
			// 
			this->buttonPhoto->FlatAppearance->BorderSize = 0;
			this->buttonPhoto->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonPhoto->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"buttonPhoto.Image")));
			this->buttonPhoto->Location = System::Drawing::Point(1820, 912);
			this->buttonPhoto->Name = L"buttonPhoto";
			this->buttonPhoto->Size = System::Drawing::Size(70, 70);
			this->buttonPhoto->TabIndex = 26;
			this->buttonPhoto->UseVisualStyleBackColor = true;
			this->buttonPhoto->Click += gcnew System::EventHandler(this, &MyMainWindowsForm::buttonPhoto_Click);
			// 
			// textBox_saveFile
			// 
			this->textBox_saveFile->Location = System::Drawing::Point(1517, 958);
			this->textBox_saveFile->Name = L"textBox_saveFile";
			this->textBox_saveFile->Size = System::Drawing::Size(167, 22);
			this->textBox_saveFile->TabIndex = 27;
			this->textBox_saveFile->Text = L"c:\\Record";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(1517, 912);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(84, 30);
			this->button1->TabIndex = 28;
			this->button1->Text = L"Ouvrir";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyMainWindowsForm::button1_Click);
			// 
			// pictureBoxTitle
			// 
			this->pictureBoxTitle->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBoxTitle.Image")));
			this->pictureBoxTitle->Location = System::Drawing::Point(495, 50);
			this->pictureBoxTitle->Name = L"pictureBoxTitle";
			this->pictureBoxTitle->Size = System::Drawing::Size(317, 68);
			this->pictureBoxTitle->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBoxTitle->TabIndex = 29;
			this->pictureBoxTitle->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(244, 150);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(239, 25);
			this->label1->TabIndex = 8;
			this->label1->Text = L"Déplacement automatique";
			// 
			// checkBox_automatic_mouvement
			// 
			this->checkBox_automatic_mouvement->AutoSize = true;
			this->checkBox_automatic_mouvement->Location = System::Drawing::Point(516, 150);
			this->checkBox_automatic_mouvement->Name = L"checkBox_automatic_mouvement";
			this->checkBox_automatic_mouvement->Size = System::Drawing::Size(18, 17);
			this->checkBox_automatic_mouvement->TabIndex = 9;
			this->checkBox_automatic_mouvement->UseVisualStyleBackColor = true;
			this->checkBox_automatic_mouvement->CheckedChanged += gcnew System::EventHandler(this, &MyMainWindowsForm::checkBox_automatic_mouvement_CheckedChanged);
			// 
			// MyMainWindowsForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->ClientSize = System::Drawing::Size(1902, 1005);
			this->Controls->Add(this->pictureBoxTitle);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox_saveFile);
			this->Controls->Add(this->buttonPhoto);
			this->Controls->Add(this->checkBoxVideo);
			this->Controls->Add(this->pictureBox_powerOffLM);
			this->Controls->Add(this->pictureBox_poweroffPad);
			this->Controls->Add(this->tabControl);
			this->Controls->Add(this->pictureBox_LeapMotion);
			this->Controls->Add(this->pictureBox_KeyBoard);
			this->Controls->Add(this->pictureBox_Pad);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MyMainWindowsForm";
			this->Text = L"VOLATUS";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox_Pad))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox_KeyBoard))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox_LeapMotion))->EndInit();
			this->tabControl->ResumeLayout(false);
			this->tabPageFace->ResumeLayout(false);
			this->tabPageFace->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
			this->tabPageColor->ResumeLayout(false);
			this->tabPageColor->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_saturation))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_ErrorMargin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_hue))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox_poweroffPad))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox_powerOffLM))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxTitle))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

			timer1->Start();
		}


		void adaptResolution(System::Windows::Forms::Control::ControlCollection ^ listOfControls)
		{
			int widthOrigin = 1920 ;
			int heightOrigin = 1080;
			
			int widthCurrent = GetSystemMetrics(SM_CXSCREEN);
			int heightCurrent = GetSystemMetrics(SM_CYSCREEN);

			double scaleWidth = (double) widthCurrent / ((double)widthOrigin );
			double scaleHeight = (double) heightCurrent / ((double)heightOrigin );

			for each (Control^ element in listOfControls)
			{

				for each (Control^ child in element->Controls)
					adaptResolution(element->Controls);

				element->Size = System::Drawing::Size((int)(element->Size.Width *scaleWidth), (int)(element->Size.Height*scaleHeight));
				element->Location = System::Drawing::Point((int)(element->Location.X*scaleWidth), (int)(element->Location.Y*scaleHeight));

				element->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif",6 , System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));

			}
			this->Refresh();
			
		}

#pragma endregion


	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {

				 //update logo of command
				 {
					 if(_mid->isGamePadConnected)
						 pictureBox_poweroffPad->Visible = false;
					 else
						 pictureBox_poweroffPad->Visible = true;

					 if(_mid->isLeapmotionConnected)
						 pictureBox_powerOffLM->Visible = false;
					 else
						 pictureBox_powerOffLM->Visible = true;


					 int difftime = 1500;
					 System::Drawing::Color off = System::Drawing::SystemColors::WindowFrame;
					 System::Drawing::Color on = System::Drawing::Color::Teal;

					 if (clock() - _mid->last_Keyboard_command_ms < difftime)
					 {
						 this->pictureBox_KeyBoard->BackColor = on;
						 this->pictureBox_Pad->BackColor = off;
						 this->pictureBox_LeapMotion->BackColor = off;
					 }

					 else if (clock() - _mid->last_GamePad_command_ms < difftime)
					 {
						 this->pictureBox_KeyBoard->BackColor = off;
						 this->pictureBox_Pad->BackColor = on;
						 this->pictureBox_LeapMotion->BackColor = off;
					 }

					 else if (clock() - _mid->last_LeapMotion_command_ms < difftime)
					 {
						 this->pictureBox_KeyBoard->BackColor = off;
						 this->pictureBox_Pad->BackColor = off;
						 this->pictureBox_LeapMotion->BackColor = on;
					 }	
					 else
					 {
						 this->pictureBox_KeyBoard->BackColor = off;
						 this->pictureBox_Pad->BackColor = off;
						 this->pictureBox_LeapMotion->BackColor = off;
					 }
				 }

				 //update pictureBox1
				 {
					 Mat frame;
					 _vm->custom_frame().copyTo(frame);
					 if(frame.empty()) 
						 return;

					 pictureBox1->Image  = gcnew    //replacement of imshow
						 System::Drawing::Bitmap(frame.size().width,frame.size().height,frame.step,
						 System::Drawing::Imaging::PixelFormat::Format24bppRgb,(System::IntPtr) frame.ptr());
					 pictureBox1->Refresh();
				 }

				 //update pictureBox2
				 {
					 if(_vm->_is_detected_Faces || _vm->_is_detected_HLS)
					 {
						 Mat FrameWithDetection = _vm->lastFrameWithDetection;
						 if(FrameWithDetection.empty()) 
							 pictureBox2->Image = nullptr;

						 else
						 {		//Specific format for the image (HLS instead of BGR/RGB
							 if(_vm->_is_detected_HLS)
								 pictureBox2->Image  = gcnew    //replacement of imshow
									 System::Drawing::Bitmap(FrameWithDetection.size().width,FrameWithDetection.size().height,FrameWithDetection.step,
									 System::Drawing::Imaging::PixelFormat::Format8bppIndexed,(System::IntPtr) FrameWithDetection.ptr());
							 
							 else if(_vm->_is_detected_Faces)
							 {
								 pictureBox2->Image  = gcnew    //replacement of imshow
									 System::Drawing::Bitmap(FrameWithDetection.size().width,FrameWithDetection.size().height,FrameWithDetection.step,
									 System::Drawing::Imaging::PixelFormat::Format24bppRgb,(System::IntPtr) FrameWithDetection.ptr());

								 labelLatency->Text = "Latence : "+_vm->latency_find_faces.ToString();
								 labelFPS->Text = "FPS : "+((int)_vm->fps).ToString();
							 }	 
						 }
					 }

					 else
						 pictureBox2->Image = nullptr;

					 pictureBox2->Refresh();
				 }
			 }

	private: System::Void trackBar_hue_Scroll(System::Object^  sender, System::EventArgs^  e) {
				 label_hue->Text = (trackBar_hue->Value).ToString();
				 _vm->hls_hue = trackBar_hue->Value;
			 }

	private: System::Void trackBar_ErrorMargin_Scroll(System::Object^  sender, System::EventArgs^  e) {
				 label_ErrorMargin->Text = (trackBar_ErrorMargin->Value).ToString();
				 _vm->hls_ErrorMargin = trackBar_ErrorMargin->Value;
			 }

	private: System::Void trackBar_saturation_Scroll(System::Object^  sender, System::EventArgs^  e) {
				 label_saturation->Text = (trackBar_saturation->Value).ToString();
				 _vm->hls_saturation = trackBar_saturation->Value;
			 }

	private: System::Void radioButton_center_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			 }
	private: System::Void radioButton_zoom_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			 }
	private: System::Void tabControl1_indexChanged(System::Object^  sender, System::EventArgs^  e) {

				 if(tabPageFace->Visible)
				 {
					 _vm->setIsDetectedFaces(true);
					 _vm->_is_detected_HLS = false;
				 }

				 else if(tabPageColor->Visible)
				 {
					 _vm->setIsDetectedFaces(false);
					 _vm->_is_detected_HLS = true;
				 }

				 else if(tabPage_delete->Visible)
				 {
					 _vm->setIsDetectedFaces(false);
					 _vm->_is_detected_HLS = false;
				 }
			 }

	private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {

				 _vm->scale = (int)numericUpDown1->Value;
			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
					 textBox_saveFile->Text = folderBrowserDialog1->SelectedPath;
			 }
	private: System::Void checkBoxVideo_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(checkBoxVideo->Checked)
				 {
					 std::string path(msclr::interop::marshal_as<std::string>(textBox_saveFile->Text));
					  _vm->startRecording(path);
				 }
				 else
					 _vm->stopRecording(); 
			 }
private: System::Void buttonPhoto_Click(System::Object^  sender, System::EventArgs^  e) {
				std::string path(msclr::interop::marshal_as<std::string>(textBox_saveFile->Text));

				int i = 1;
				while (true)
				{
					ostringstream pathToCheck;
					pathToCheck<<path<<"\\Photo_"<<i<<".jpeg";

					//To not erase data
					if(_vm->isCorrectPath(pathToCheck.str()) == false)
					{
							cv::imwrite(pathToCheck.str(), _vm->custom_frame());
							break;
					}

					i++;
				}
		 }

private: System::Void pictureBox1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			
			 _vm->getHSL(cv::Point(e->X, e->Y));

			 label_hue->Text = _vm->hls_hue.ToString();
			 trackBar_hue->Value = _vm->hls_hue;
			 
			 label_saturation->Text = _vm->hls_saturation.ToString();
			 trackBar_saturation->Value = _vm->hls_saturation;

			/* Bitmap^ bmp = (Bitmap^) pictureBox1->Image;

			 cout <<e->X<<" - "<<e->Y<<endl;
			 Color pixelColor = bmp->GetPixel(e->X, e->Y);

			 
			 float h = pixelColor.GetHue();
			 float s = pixelColor.GetSaturation();

			 cout<<h<<" - "<<s<<endl;*/
		 }
private: System::Void checkBox_automatic_mouvement_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 _vm->_is_automatic_mouvement = (checkBox_automatic_mouvement->Checked)?true:false;
		 }
};
}
