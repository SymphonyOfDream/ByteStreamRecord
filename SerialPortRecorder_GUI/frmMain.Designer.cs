namespace SerialPortRecorder
{
    partial class frmMain
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
            this.cmdAddNewPort = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.lstPorts = new System.Windows.Forms.ListBox();
            this.cmdStartRecording = new System.Windows.Forms.Button();
            this.cmdExit = new System.Windows.Forms.Button();
            this.lstPortsBytesRecorded = new System.Windows.Forms.ListBox();
            this.lblPortsByteCount = new System.Windows.Forms.Label();
            this.timerBytesRecordedUpdater = new System.Windows.Forms.Timer();
            this.cmdDeletePort = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // cmdAddNewPort
            // 
            this.cmdAddNewPort.Location = new System.Drawing.Point(15, 28);
            this.cmdAddNewPort.Name = "cmdAddNewPort";
            this.cmdAddNewPort.Size = new System.Drawing.Size(135, 35);
            this.cmdAddNewPort.TabIndex = 0;
            this.cmdAddNewPort.Text = "Add New Port...";
            this.cmdAddNewPort.Click += new System.EventHandler(this.cmdAddNewPort_Click);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(15, 84);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(163, 20);
            this.label1.Text = "Ports to be Recorded:";
            // 
            // lstPorts
            // 
            this.lstPorts.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.lstPorts.Location = new System.Drawing.Point(15, 102);
            this.lstPorts.Name = "lstPorts";
            this.lstPorts.Size = new System.Drawing.Size(226, 194);
            this.lstPorts.TabIndex = 2;
            this.lstPorts.SelectedIndexChanged += new System.EventHandler(this.lstPorts_SelectedIndexChanged);
            // 
            // cmdStartRecording
            // 
            this.cmdStartRecording.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.cmdStartRecording.Enabled = false;
            this.cmdStartRecording.Location = new System.Drawing.Point(15, 311);
            this.cmdStartRecording.Name = "cmdStartRecording";
            this.cmdStartRecording.Size = new System.Drawing.Size(135, 35);
            this.cmdStartRecording.TabIndex = 3;
            this.cmdStartRecording.Text = "Start Recording";
            this.cmdStartRecording.Click += new System.EventHandler(this.cmdStartRecording_Click);
            // 
            // cmdExit
            // 
            this.cmdExit.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdExit.Location = new System.Drawing.Point(243, 311);
            this.cmdExit.Name = "cmdExit";
            this.cmdExit.Size = new System.Drawing.Size(105, 35);
            this.cmdExit.TabIndex = 4;
            this.cmdExit.Text = "Exit";
            this.cmdExit.Click += new System.EventHandler(this.cmdExit_Click);
            // 
            // lstPortsBytesRecorded
            // 
            this.lstPortsBytesRecorded.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lstPortsBytesRecorded.Location = new System.Drawing.Point(243, 102);
            this.lstPortsBytesRecorded.Name = "lstPortsBytesRecorded";
            this.lstPortsBytesRecorded.Size = new System.Drawing.Size(105, 194);
            this.lstPortsBytesRecorded.TabIndex = 5;
            // 
            // lblPortsByteCount
            // 
            this.lblPortsByteCount.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lblPortsByteCount.Location = new System.Drawing.Point(243, 84);
            this.lblPortsByteCount.Name = "lblPortsByteCount";
            this.lblPortsByteCount.Size = new System.Drawing.Size(105, 20);
            this.lblPortsByteCount.Text = "Bytes Recorded:";
            // 
            // timerBytesRecordedUpdater
            // 
            this.timerBytesRecordedUpdater.Interval = 1000;
            this.timerBytesRecordedUpdater.Tick += new System.EventHandler(this.timerBytesRecordedUpdater_Tick);
            // 
            // cmdDeletePort
            // 
            this.cmdDeletePort.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.cmdDeletePort.Enabled = false;
            this.cmdDeletePort.Location = new System.Drawing.Point(213, 28);
            this.cmdDeletePort.Name = "cmdDeletePort";
            this.cmdDeletePort.Size = new System.Drawing.Size(135, 35);
            this.cmdDeletePort.TabIndex = 8;
            this.cmdDeletePort.Text = "Delete Port";
            this.cmdDeletePort.Click += new System.EventHandler(this.cmdDeletePort_Click);
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.AutoScroll = true;
            this.ClientSize = new System.Drawing.Size(380, 361);
            this.ControlBox = false;
            this.Controls.Add(this.cmdDeletePort);
            this.Controls.Add(this.lstPortsBytesRecorded);
            this.Controls.Add(this.cmdExit);
            this.Controls.Add(this.cmdStartRecording);
            this.Controls.Add(this.lstPorts);
            this.Controls.Add(this.cmdAddNewPort);
            this.Controls.Add(this.lblPortsByteCount);
            this.Controls.Add(this.label1);
            this.MaximizeBox = false;
            this.Menu = this.mainMenu1;
            this.MinimizeBox = false;
            this.Name = "frmMain";
            this.Text = "Port Recorder";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button cmdAddNewPort;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ListBox lstPorts;
        private System.Windows.Forms.Button cmdStartRecording;
        private System.Windows.Forms.Button cmdExit;
        private System.Windows.Forms.ListBox lstPortsBytesRecorded;
        private System.Windows.Forms.Label lblPortsByteCount;
        private System.Windows.Forms.Timer timerBytesRecordedUpdater;
        private System.Windows.Forms.Button cmdDeletePort;
    }
}

