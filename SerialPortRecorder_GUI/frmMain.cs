using System;

using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace SerialPortRecorder
{

    public partial class frmMain : Form
    {

        #region Native Methods - DllImport's

#if DEBUG
        [DllImport("ByteStreamRecordD.dll", EntryPoint = "PortRecorder_Initialize")]
#else
        [DllImport("ByteStreamRecord.dll", EntryPoint = "PortRecorder_Initialize")]
#endif
        private static extern void PortRecorder_Initialize();

#if DEBUG
        [DllImport("ByteStreamRecordD.dll", EntryPoint = "PortRecorder_GetTotalBytesRecorded")]
#else
        [DllImport("ByteStreamRecord.dll", EntryPoint = "PortRecorder_GetTotalBytesRecorded")]
#endif
        private static extern UInt32 PortRecorder_GetTotalBytesRecorded(Int32 i32ID);


#if DEBUG
        [DllImport("ByteStreamRecordD.dll", EntryPoint = "PortRecorder_DeInitialize")]
#else
        [DllImport("ByteStreamRecord.dll", EntryPoint = "PortRecorder_DeInitialize")]
#endif
        private static extern void PortRecorder_DeInitialize();


#if DEBUG
        [DllImport("ByteStreamRecordD.dll", EntryPoint = "PortRecorder_AddSerialPort")]
#else
        [DllImport("ByteStreamRecord.dll", EntryPoint = "PortRecorder_AddSerialPort")]
#endif
        private static extern int PortRecorder_AddSerialPort(int iComPortNumber,
							                                 int iBaudRate,
							                                 int iDataBits,
							                                 int iParity,
							                                 int iStopBits,
							                                 int iFlowControl);

#if DEBUG
        [DllImport("ByteStreamRecordD.dll", EntryPoint = "PortRecorder_AddSerialPort")]
#else
        [DllImport("ByteStreamRecord.dll", EntryPoint = "PortRecorder_AddSerialPort")]
#endif
        private static extern int PortRecorder_AddNonStandardSerialPort(int iComPortNumber,
							                                            string wszComPort,
							                                            int iBaudRate,
							                                            int iDataBits,
							                                            int iParity,
							                                            int iStopBits,
							                                            int iFlowControl);



#if DEBUG
        [DllImport("ByteStreamRecordD.dll", EntryPoint = "PortRecorder_AddJ1939Port")]
#else
        [DllImport("ByteStreamRecord.dll", EntryPoint = "PortRecorder_AddJ1939Port")]
#endif
        private static extern int PortRecorder_AddJ1939Port(int iCANPortNumber,
							                                int iCANBaudRate);



#if DEBUG
        [DllImport("ByteStreamRecordD.dll", EntryPoint = "PortRecorder_StartRecording")]
#else
        [DllImport("ByteStreamRecord.dll", EntryPoint = "PortRecorder_StartRecording")]
#endif
        private static extern void PortRecorder_StartRecording();

#if DEBUG
        [DllImport("ByteStreamRecordD.dll", EntryPoint = "PortRecorder_StopRecording")]
#else
        [DllImport("ByteStreamRecord.dll", EntryPoint = "PortRecorder_StopRecording")]
#endif
        private static extern bool PortRecorder_StopRecording();

        #endregion


        bool m_bRecording = false;

        public frmMain()
        {
            PortRecorder_Initialize();

            InitializeComponent();
        }

        private void cmdExit_Click(object sender, EventArgs e)
        {
            this.Hide();
            this.Close();
        }



        private void cmdAddNewPort_Click(object sender, EventArgs e)
        {
            using (frmAddPort addPortForm = new frmAddPort())
            {
                DialogResult rc = addPortForm.ShowDialog();
                if (rc == DialogResult.OK)
                {
                    PortToRecord portToRecord = addPortForm.PortToRecord;

                    int iPortID;

                    if (!portToRecord.IsCAN)
                        iPortID =  PortRecorder_AddSerialPort(portToRecord.Port.Value,
                                                              portToRecord.Baud,
                                                              portToRecord.DataBits,
                                                              (int)portToRecord.Parity,
                                                              (int)portToRecord.StopBits,
                                                              -1);
                    else
                        iPortID = PortRecorder_AddJ1939Port(portToRecord.Port.Value,
                                                            portToRecord.Baud);
                    portToRecord.PortID = iPortID;

                    if (!lstPorts.Items.Contains(portToRecord))
                    {
                        lstPorts.Items.Add(portToRecord);
                        lstPortsBytesRecorded.Items.Add(0);
                    }

                    cmdStartRecording.Enabled = lstPorts.Items.Count > 0;
                }
            }

            this.BringToFront();
        }


        private void cmdStartRecording_Click(object sender, EventArgs e)
        {
            if (!m_bRecording)
            {
                PortRecorder_StartRecording();
                timerBytesRecordedUpdater.Enabled = true;
                cmdStartRecording.Text = "STOP RECORDING";
            }
            else
            {
                PortRecorder_StopRecording();
                timerBytesRecordedUpdater.Enabled = false;
                cmdStartRecording.Text = "Start Recording";
            }

            m_bRecording = !m_bRecording;
        }


        private void timerBytesRecordedUpdater_Tick(object sender, EventArgs e)
        {
            for (int idx = 0; idx < lstPorts.Items.Count; ++idx)
            {
                PortToRecord portToRecord = lstPorts.Items[idx] as PortToRecord;
                if (portToRecord == null)
                    continue;

                lstPortsBytesRecorded.Items[idx] = PortRecorder_GetTotalBytesRecorded(portToRecord.PortID);
            }
        }

        private void lstPorts_SelectedIndexChanged(object sender, EventArgs e)
        {
            cmdDeletePort.Enabled = lstPorts.SelectedIndex >= 0;
        }

        private void cmdDeletePort_Click(object sender, EventArgs e)
        {
            lstPorts.Items.RemoveAt(lstPorts.SelectedIndex);
            cmdStartRecording.Enabled = lstPorts.Items.Count > 0;
        }

    }  // public partial class Form1 : Form

}  // namespace SerialPortRecorder