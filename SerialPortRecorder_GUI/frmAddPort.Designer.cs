namespace SerialPortRecorder
{
    partial class frmAddPort
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;
        private System.Windows.Forms.MainMenu mainMenu1;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.mainMenu1 = new System.Windows.Forms.MainMenu();
            this.cmdPresetS100_1587EcmPort = new System.Windows.Forms.Button();
            this.panelPresets = new System.Windows.Forms.Panel();
            this.cmdPresetS200_1587EcmPort = new System.Windows.Forms.Button();
            this.cmdPresetS100_1939EcmPort = new System.Windows.Forms.Button();
            this.cmdPresetS100_GpsPort = new System.Windows.Forms.Button();
            this.panelAdvanced = new System.Windows.Forms.Panel();
            this.cboDataBits = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.cboParities = new System.Windows.Forms.ComboBox();
            this.cboStopBits = new System.Windows.Forms.ComboBox();
            this.cboBaudRate = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.cmdCancel = new System.Windows.Forms.Button();
            this.cmdAdd = new System.Windows.Forms.Button();
            this.cboTraditionalComPorts = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.rcmdPresetPanel = new System.Windows.Forms.RadioButton();
            this.rcmdAdvancedPanel = new System.Windows.Forms.RadioButton();
            this.panelPresets.SuspendLayout();
            this.panelAdvanced.SuspendLayout();
            this.SuspendLayout();
            // 
            // cmdPresetS100_1587EcmPort
            // 
            this.cmdPresetS100_1587EcmPort.Location = new System.Drawing.Point(9, 9);
            this.cmdPresetS100_1587EcmPort.Name = "cmdPresetS100_1587EcmPort";
            this.cmdPresetS100_1587EcmPort.Size = new System.Drawing.Size(260, 34);
            this.cmdPresetS100_1587EcmPort.TabIndex = 30;
            this.cmdPresetS100_1587EcmPort.Text = "S100 J1587 ECM Preset";
            this.cmdPresetS100_1587EcmPort.Click += new System.EventHandler(this.cmdPresetS100_1587EcmPort_Click);
            // 
            // panelPresets
            // 
            this.panelPresets.Controls.Add(this.cmdPresetS200_1587EcmPort);
            this.panelPresets.Controls.Add(this.cmdPresetS100_1939EcmPort);
            this.panelPresets.Controls.Add(this.cmdPresetS100_GpsPort);
            this.panelPresets.Controls.Add(this.cmdPresetS100_1587EcmPort);
            this.panelPresets.Location = new System.Drawing.Point(17, 77);
            this.panelPresets.Name = "panelPresets";
            this.panelPresets.Size = new System.Drawing.Size(277, 301);
            // 
            // cmdPresetS200_1587EcmPort
            // 
            this.cmdPresetS200_1587EcmPort.Location = new System.Drawing.Point(8, 123);
            this.cmdPresetS200_1587EcmPort.Name = "cmdPresetS200_1587EcmPort";
            this.cmdPresetS200_1587EcmPort.Size = new System.Drawing.Size(260, 34);
            this.cmdPresetS200_1587EcmPort.TabIndex = 33;
            this.cmdPresetS200_1587EcmPort.Text = "S200 J1587 ECM Preset";
            this.cmdPresetS200_1587EcmPort.Click += new System.EventHandler(this.cmdPresetS200_1587EcmPort_Click);
            // 
            // cmdPresetS100_1939EcmPort
            // 
            this.cmdPresetS100_1939EcmPort.Location = new System.Drawing.Point(9, 69);
            this.cmdPresetS100_1939EcmPort.Name = "cmdPresetS100_1939EcmPort";
            this.cmdPresetS100_1939EcmPort.Size = new System.Drawing.Size(260, 34);
            this.cmdPresetS100_1939EcmPort.TabIndex = 32;
            this.cmdPresetS100_1939EcmPort.Text = "S100 J1939 ECM Preset";
            this.cmdPresetS100_1939EcmPort.Click += new System.EventHandler(this.cmdPresetS100_1939EcmPort_Click);
            // 
            // cmdPresetS100_GpsPort
            // 
            this.cmdPresetS100_GpsPort.Location = new System.Drawing.Point(9, 242);
            this.cmdPresetS100_GpsPort.Name = "cmdPresetS100_GpsPort";
            this.cmdPresetS100_GpsPort.Size = new System.Drawing.Size(260, 34);
            this.cmdPresetS100_GpsPort.TabIndex = 31;
            this.cmdPresetS100_GpsPort.Text = "S100 GPS Preset";
            this.cmdPresetS100_GpsPort.Click += new System.EventHandler(this.cmdPresetS100_GpsPort_Click);
            // 
            // panelAdvanced
            // 
            this.panelAdvanced.Controls.Add(this.cboDataBits);
            this.panelAdvanced.Controls.Add(this.label7);
            this.panelAdvanced.Controls.Add(this.cboParities);
            this.panelAdvanced.Controls.Add(this.cboStopBits);
            this.panelAdvanced.Controls.Add(this.cboBaudRate);
            this.panelAdvanced.Controls.Add(this.label6);
            this.panelAdvanced.Controls.Add(this.label5);
            this.panelAdvanced.Controls.Add(this.label4);
            this.panelAdvanced.Controls.Add(this.cmdCancel);
            this.panelAdvanced.Controls.Add(this.cmdAdd);
            this.panelAdvanced.Controls.Add(this.cboTraditionalComPorts);
            this.panelAdvanced.Controls.Add(this.label1);
            this.panelAdvanced.Location = new System.Drawing.Point(17, 77);
            this.panelAdvanced.Name = "panelAdvanced";
            this.panelAdvanced.Size = new System.Drawing.Size(277, 301);
            this.panelAdvanced.Visible = false;
            // 
            // cboDataBits
            // 
            this.cboDataBits.Location = new System.Drawing.Point(158, 200);
            this.cboDataBits.Name = "cboDataBits";
            this.cboDataBits.Size = new System.Drawing.Size(111, 23);
            this.cboDataBits.TabIndex = 36;
            this.cboDataBits.SelectedIndexChanged += new System.EventHandler(this.cboDataBits_SelectedIndexChanged);
            // 
            // label7
            // 
            this.label7.Location = new System.Drawing.Point(45, 203);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(100, 20);
            this.label7.Text = "Data Bits:";
            this.label7.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // cboParities
            // 
            this.cboParities.Location = new System.Drawing.Point(158, 154);
            this.cboParities.Name = "cboParities";
            this.cboParities.Size = new System.Drawing.Size(111, 23);
            this.cboParities.TabIndex = 35;
            this.cboParities.SelectedIndexChanged += new System.EventHandler(this.cboParities_SelectedIndexChanged);
            // 
            // cboStopBits
            // 
            this.cboStopBits.Location = new System.Drawing.Point(158, 108);
            this.cboStopBits.Name = "cboStopBits";
            this.cboStopBits.Size = new System.Drawing.Size(111, 23);
            this.cboStopBits.TabIndex = 34;
            this.cboStopBits.SelectedIndexChanged += new System.EventHandler(this.cboStopBits_SelectedIndexChanged);
            // 
            // cboBaudRate
            // 
            this.cboBaudRate.Location = new System.Drawing.Point(158, 62);
            this.cboBaudRate.Name = "cboBaudRate";
            this.cboBaudRate.Size = new System.Drawing.Size(111, 23);
            this.cboBaudRate.TabIndex = 33;
            this.cboBaudRate.SelectedIndexChanged += new System.EventHandler(this.cboBaudRate_SelectedIndexChanged);
            // 
            // label6
            // 
            this.label6.Location = new System.Drawing.Point(45, 157);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(100, 20);
            this.label6.Text = "Parity:";
            this.label6.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label5
            // 
            this.label5.Location = new System.Drawing.Point(52, 111);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(100, 20);
            this.label5.Text = "Stop Bits:";
            this.label5.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(52, 65);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(100, 20);
            this.label4.Text = "Baud Rate:";
            this.label4.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // cmdCancel
            // 
            this.cmdCancel.Location = new System.Drawing.Point(166, 242);
            this.cmdCancel.Name = "cmdCancel";
            this.cmdCancel.Size = new System.Drawing.Size(103, 43);
            this.cmdCancel.TabIndex = 32;
            this.cmdCancel.Text = "Cancel";
            // 
            // cmdAdd
            // 
            this.cmdAdd.Enabled = false;
            this.cmdAdd.Location = new System.Drawing.Point(21, 242);
            this.cmdAdd.Name = "cmdAdd";
            this.cmdAdd.Size = new System.Drawing.Size(103, 43);
            this.cmdAdd.TabIndex = 31;
            this.cmdAdd.Text = "Add";
            // 
            // cboTraditionalComPorts
            // 
            this.cboTraditionalComPorts.Location = new System.Drawing.Point(158, 16);
            this.cboTraditionalComPorts.Name = "cboTraditionalComPorts";
            this.cboTraditionalComPorts.Size = new System.Drawing.Size(111, 23);
            this.cboTraditionalComPorts.TabIndex = 30;
            this.cboTraditionalComPorts.SelectedIndexChanged += new System.EventHandler(this.cboTraditionalComPorts_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(8, 19);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(144, 20);
            this.label1.Text = "Traditional COM Port:";
            this.label1.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // rcmdPresetPanel
            // 
            this.rcmdPresetPanel.Checked = true;
            this.rcmdPresetPanel.Location = new System.Drawing.Point(26, 51);
            this.rcmdPresetPanel.Name = "rcmdPresetPanel";
            this.rcmdPresetPanel.Size = new System.Drawing.Size(100, 20);
            this.rcmdPresetPanel.TabIndex = 1;
            this.rcmdPresetPanel.Text = "Presets";
            this.rcmdPresetPanel.CheckedChanged += new System.EventHandler(this.rcmdPanelChooser_CheckedChanged);
            // 
            // rcmdAdvancedPanel
            // 
            this.rcmdAdvancedPanel.Location = new System.Drawing.Point(194, 51);
            this.rcmdAdvancedPanel.Name = "rcmdAdvancedPanel";
            this.rcmdAdvancedPanel.Size = new System.Drawing.Size(100, 20);
            this.rcmdAdvancedPanel.TabIndex = 2;
            this.rcmdAdvancedPanel.TabStop = false;
            this.rcmdAdvancedPanel.Text = "Advanced";
            this.rcmdAdvancedPanel.CheckedChanged += new System.EventHandler(this.rcmdPanelChooser_CheckedChanged);
            // 
            // frmAddPort
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.AutoScroll = true;
            this.ClientSize = new System.Drawing.Size(314, 401);
            this.ControlBox = false;
            this.Controls.Add(this.rcmdAdvancedPanel);
            this.Controls.Add(this.rcmdPresetPanel);
            this.Controls.Add(this.panelPresets);
            this.Controls.Add(this.panelAdvanced);
            this.MaximizeBox = false;
            this.Menu = this.mainMenu1;
            this.MinimizeBox = false;
            this.Name = "frmAddPort";
            this.Text = "Add Port";
            this.Load += new System.EventHandler(this.frmAddPort_Load);
            this.panelPresets.ResumeLayout(false);
            this.panelAdvanced.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button cmdPresetS100_1587EcmPort;
        private System.Windows.Forms.Panel panelPresets;
        private System.Windows.Forms.Button cmdPresetS100_GpsPort;
        private System.Windows.Forms.Panel panelAdvanced;
        private System.Windows.Forms.ComboBox cboDataBits;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox cboParities;
        private System.Windows.Forms.ComboBox cboStopBits;
        private System.Windows.Forms.ComboBox cboBaudRate;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button cmdCancel;
        private System.Windows.Forms.Button cmdAdd;
        private System.Windows.Forms.ComboBox cboTraditionalComPorts;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.RadioButton rcmdPresetPanel;
        private System.Windows.Forms.RadioButton rcmdAdvancedPanel;
        private System.Windows.Forms.Button cmdPresetS100_1939EcmPort;
        private System.Windows.Forms.Button cmdPresetS200_1587EcmPort;
    }
}