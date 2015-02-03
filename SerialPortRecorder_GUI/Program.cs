using System;

using System.Collections.Generic;
using System.Windows.Forms;

namespace SerialPortRecorder
{
    public class PortToRecord : IEquatable<PortToRecord>
    {
        /// <summary>
        /// Set by native code function return value
        /// </summary>
        public int PortID { get; set; }

        public bool IsCAN { get; set; }
        public SimpleSerialPort Port { get; set; }
        public int Baud { get; set; }
        public System.IO.Ports.StopBits StopBits { get; set; }
        public int DataBits { get; set; }
        public System.IO.Ports.Parity Parity { get; set; }

        string m_strUserFriendlyName = null;
        public string UserFriendlyName
        {
            get
            {
                if (string.IsNullOrEmpty(m_strUserFriendlyName))
                    return string.Format("{0} - {1} baud/{2} sb/{3} db/{4} par",
                                         Port,
                                         (int)Baud,
                                         (int)StopBits,
                                         DataBits,
                                         (int)Parity);

                return m_strUserFriendlyName;
            }

            set
            {
                if (string.IsNullOrEmpty(value))
                    m_strUserFriendlyName = null;

                m_strUserFriendlyName = value;
            }
        }

        public PortToRecord()
        {
            this.PortID = -1;
            this.Port = SimpleSerialPort.CreateInvalid();
        }


        public override string ToString()
        {
            return UserFriendlyName;
        }


        public override int GetHashCode()
        {
            return this.ToString().GetHashCode();
        }


        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;

            return this.Equals(obj as PortToRecord);
        }

        #region IEquatable<PortToRecord> Members

        public bool Equals(PortToRecord other)
        {
            if (other == null)
                return false;

            return this.Port.Equals(other.Port);
        }

        #endregion
    }


    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [MTAThread]
        static void Main()
        {
            Application.Run(new frmMain());
        }
    }
}