//#define S100

using System;

using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;



namespace SerialPortRecorder
{

    public partial class frmAddPort : Form
    {
        public PortToRecord PortToRecord { get; private set; }


        public frmAddPort()
        {
            PortToRecord = new PortToRecord();

            InitializeComponent();

#if S100
            cmdPresetS100_1587EcmPort.Enabled = true;
            cmdPresetS100_1939EcmPort.Enabled = true;

            cmdPresetS200_1587EcmPort.Enabled = false;
#else
            cmdPresetS100_1587EcmPort.Enabled = false;
            cmdPresetS100_1939EcmPort.Enabled = false;

            cmdPresetS200_1587EcmPort.Enabled = true;
#endif
        }


        private void frmAddPort_Load(object sender, EventArgs e)
        {
            cboParities.Items.Add("");
            cboParities.Items.Add(System.IO.Ports.Parity.None);
            cboParities.Items.Add(System.IO.Ports.Parity.Odd);
            cboParities.Items.Add(System.IO.Ports.Parity.Even);
            cboParities.SelectedIndex = 0;

            cboStopBits.Items.Add("");
            cboStopBits.Items.Add(System.IO.Ports.StopBits.One);
            cboStopBits.Items.Add(System.IO.Ports.StopBits.OnePointFive);
            cboStopBits.Items.Add(System.IO.Ports.StopBits.Two);
            cboStopBits.SelectedIndex = 0;

            cboBaudRate.Items.Add("");
            foreach (SimpleSerialPort.eBaudRate baud in SimpleSerialPort.AllBaudRates)
            {
                cboBaudRate.Items.Add((int)baud);
            }
            cboBaudRate.SelectedIndex = 0;

            cboDataBits.Items.Add("");
            for (int idx = 5; idx <= 9; ++idx)
                cboDataBits.Items.Add(idx);
            cboDataBits.SelectedIndex = 0;

            cboTraditionalComPorts.Items.Add("");
            foreach (SimpleSerialPort ssp in SimpleSerialPort.GetSortedPortObjects())
                cboTraditionalComPorts.Items.Add(ssp);
            cboTraditionalComPorts.SelectedIndex = 0;
        }



        void CloseForm(DialogResult rc)
        {
            this.DialogResult = rc;
        }

        private void cmdAdd_Click(object sender, EventArgs e)
        {
            CloseForm(DialogResult.OK);
        }


        private void cmdCancel_Click(object sender, EventArgs e)
        {
            CloseForm(DialogResult.Cancel);
        }

        void ValidateSelections()
        {
            cmdAdd.Enabled
                = cboParities.SelectedIndex > 0
                && cboStopBits.SelectedIndex > 0
                && cboBaudRate.SelectedIndex > 0
                && cboDataBits.SelectedIndex > 0
                && cboTraditionalComPorts.SelectedIndex > 0;
        }

        private void cboBaudRate_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cboBaudRate.SelectedIndex > 0)
                PortToRecord.Baud = (int)cboBaudRate.SelectedItem;

            ValidateSelections();
        }

        private void cboStopBits_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cboStopBits.SelectedIndex > 0)
                PortToRecord.StopBits = (System.IO.Ports.StopBits)cboStopBits.SelectedItem;

            ValidateSelections();
        }

        private void cboParities_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cboParities.SelectedIndex > 0)
                PortToRecord.Parity = (System.IO.Ports.Parity)cboParities.SelectedItem;

            ValidateSelections();
        }

        private void cboDataBits_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cboDataBits.SelectedIndex > 0)
                PortToRecord.DataBits = (int)cboDataBits.SelectedItem;

            ValidateSelections();
        }

        private void cboTraditionalComPorts_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cboTraditionalComPorts.SelectedIndex > 0)
                PortToRecord.Port = (SimpleSerialPort)cboTraditionalComPorts.SelectedItem;

            ValidateSelections();
        }



        private void cmdPresetS100_1587EcmPort_Click(object sender, EventArgs e)
        {
            PortToRecord.IsCAN = false;

            cboTraditionalComPorts.SelectedItem = new SimpleSerialPort(3, "COM3");
            cboBaudRate.SelectedItem = (int)SimpleSerialPort.eBaudRate.Baud_9600;
            cboStopBits.SelectedItem = System.IO.Ports.StopBits.One;
            cboParities.SelectedItem = System.IO.Ports.Parity.None;
            cboDataBits.SelectedItem = 8;
            this.PortToRecord.UserFriendlyName = "ECM J1587";

            cmdAdd_Click(this, null);
        }


        private void cmdPresetS200_1587EcmPort_Click(object sender, EventArgs e) {
            PortToRecord.IsCAN = false;

            cboTraditionalComPorts.SelectedItem = new SimpleSerialPort(6, "COM6");
            cboBaudRate.SelectedItem = (int)SimpleSerialPort.eBaudRate.Baud_9600;
            cboStopBits.SelectedItem = System.IO.Ports.StopBits.One;
            cboParities.SelectedItem = System.IO.Ports.Parity.None;
            cboDataBits.SelectedItem = 8;
            this.PortToRecord.UserFriendlyName = "ECM J1587";

            cmdAdd_Click(this, null);
        }


        private void cmdPresetS100_1939EcmPort_Click(object sender, EventArgs e)
        {
            PortToRecord.IsCAN = true;

            // COM1 will be changed to CAN1 in the native layer.
            cboTraditionalComPorts.SelectedItem = new SimpleSerialPort(1, "COM1");
            PortToRecord.Baud = 250;
            this.PortToRecord.UserFriendlyName = "ECM J1939";

            cmdAdd_Click(this, null);
        }


        private void cmdPresetS100_GpsPort_Click(object sender, EventArgs e)
        {
            PortToRecord.IsCAN = false;

#if S100
            cboTraditionalComPorts.SelectedItem = new SimpleSerialPort(2, "COM2");
#else
            cboTraditionalComPorts.SelectedItem = new SimpleSerialPort(9, "COM9");
#endif

            cboBaudRate.SelectedItem = (int)SimpleSerialPort.eBaudRate.Baud_4800;
            cboStopBits.SelectedItem = System.IO.Ports.StopBits.One;
            cboParities.SelectedItem = System.IO.Ports.Parity.None;
            cboDataBits.SelectedItem = 8;
            this.PortToRecord.UserFriendlyName = "GPS";

            cmdAdd_Click(this, null);
        }


        private void rcmdPanelChooser_CheckedChanged(object sender, EventArgs e)
        {
            PortToRecord.IsCAN = false;

            if (rcmdAdvancedPanel.Checked)
            {
                panelPresets.Visible = false;
                panelPresets.SendToBack();

                panelAdvanced.Visible = true;
                panelAdvanced.BringToFront();
            }
            else
            {
                panelAdvanced.Visible = false;
                panelAdvanced.SendToBack();

                panelPresets.Visible = true;
                panelPresets.BringToFront();
            }
        }

    }  // public partial class frmAddPort : Form

}  // namespace SerialPortRecorder