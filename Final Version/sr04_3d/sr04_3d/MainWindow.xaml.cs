using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using System.IO.Ports;

namespace sr04_3d
{
    using System.Windows.Media;
    using System.Windows.Media.Media3D;
    using HelixToolkit.Wpf;
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    
    public partial class MainWindow : Window
    {
        
        static HelixViewport3D viewport;
        //static BoxVisual3D box;
        BoxVisual3D box = new BoxVisual3D();
        int _Z=0;
        int oX, oY, oZ ;

        SerialPort serial = new SerialPort();
        string recieved_data;

        public MainWindow()
        {
           InitializeComponent();
           Create3DViewPort();
        }


        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            
        }


        private void Create3DViewPort()
        {
            //var viewport = new HelixViewport3D();
            HelixViewport3D viewport = new HelixViewport3D();
            this.grid.Children.Add(viewport);
            var lights = new DefaultLights();
            viewport.Children.Add(new GridLinesVisual3D());
            viewport.Children.Add(lights);
            box.Width = 6;
            box.Height = 6;
            box.Length = 6;
            box.Fill = Brushes.Yellow;
            viewport.Children.Add(box);

            BoxVisual3D bPlane = new BoxVisual3D();
            bPlane.Height = 1;
            bPlane.Width = 30;
            bPlane.Length = 30;
            bPlane.Fill = Brushes.Pink;
            bPlane.Center = new Point3D(35, 30, -1);

            // Plane3D bPlane = new Plane3D();
            viewport.Children.Add(bPlane);


            BoxVisual3D cPlane = new BoxVisual3D();
            cPlane.Height = 30;
            cPlane.Width = 1;
            cPlane.Length = 30;
            cPlane.Fill = Brushes.Pink;
            cPlane.Center = new Point3D(35, 15, 14);
            viewport.Children.Add(cPlane);

            BoxVisual3D dPlane = new BoxVisual3D();
            dPlane.Height = 30;
            dPlane.Width = 30;
            dPlane.Length = 1;
            dPlane.Fill = Brushes.Pink;
            dPlane.Center = new Point3D(20, 30, 14);
            viewport.Children.Add(dPlane);

            BoxVisual3D ePlane = new BoxVisual3D();
            ePlane.Height = 30;
            ePlane.Width = 30;
            ePlane.Length = 1;
            ePlane.Fill = Brushes.Pink;
            ePlane.Center = new Point3D(50, 30, 14);
            viewport.Children.Add(ePlane);


        }

        private void BUp_Click(object sender, RoutedEventArgs e)
        {
            //viewport.Children.Add(box);
            _Z++;
            box.Center = new Point3D(0, 0, _Z);

        }

        private void BDown_Click(object sender, RoutedEventArgs e)
        {
            _Z--;
            box.Center = new Point3D(0, 0, _Z);

        }

        //*-------------------------- Serial
        private void Connect_Comms(object sender, RoutedEventArgs e)
        {
            if (bConnect.Content == "Connect")
            {
                //Sets up serial port
                serial.PortName = Comm_Port_Names.Text;
                serial.BaudRate = 9600;
                serial.Handshake = System.IO.Ports.Handshake.None;
                serial.Parity = Parity.None;
                serial.DataBits = 8;
                serial.StopBits = StopBits.Two;
                serial.ReadTimeout = 200;
                serial.WriteTimeout = 50;
                serial.Open();

                //Sets button State and Creates function call on data recieved
                bConnect.Content = "Disconnect";
                serial.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(Recieve);

            }
            else
            {
                try // just in case serial port is not open could also be acheved using if(serial.IsOpen)
                {
                    serial.Close();
                    bConnect.Content = "Connect";
                }
                catch
                {
                }
            }
        }


        private delegate void UpdateUiTextDelegate(string text);
        private void Recieve(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            // Collecting the characters received to our 'buffer' (string).
            try
            {
                recieved_data = serial.ReadLine();

                // string gg = serial.ReadExisting();


                App.Current.Dispatcher.Invoke((Action)delegate // <--- HERE
                {
                    Console.WriteLine("Received: " + recieved_data);
                    SplitDataSendToGraph(recieved_data);
                });

            }
            catch { }
        }

        void moveBoxTo(int X, int Y, int Z)
        {
            Z--;
            Y-=3;
            if (((X - 1 > oX) || (X + 1 < oX)) || ((Y - 1 > oY) || (Y + 1 < oY)) || ((Z - 1 > oZ) || (Z + 1 < oZ)))
            {
                if (Z < 2) Z = 2;
                if (Z > 25) Z = 25;
                oX = X; oY = Y; oZ = Z;
            box.Center = new Point3D(X-3, Y-3, Z);
            }
        }
        void SplitDataSendToGraph(string RxData)
        {
            string[] MrxData = RxData.Split('#');
            try
            {
                moveBoxTo(Convert.ToInt32(MrxData[0]), Convert.ToInt32(MrxData[1]), Convert.ToInt32(MrxData[2]));
            }
            catch { Console.WriteLine("No solution"); }
        }

        private void ComboBox_DropDownOpened(object sender, EventArgs e)
        {
            this.Comm_Port_Names.Items.Clear();
            foreach (string s in System.IO.Ports.SerialPort.GetPortNames())
            {
                Comm_Port_Names.Items.Add(s);
            }
        }

        private void BConnect_Click(object sender, RoutedEventArgs e)
        {

        }


        //****************
    }
}
