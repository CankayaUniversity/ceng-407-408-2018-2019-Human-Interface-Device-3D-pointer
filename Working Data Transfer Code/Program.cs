using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;
using System.IO.Ports;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;

namespace ConsoleApp1
{
	class Program
	{
		static void Main(string[] args)
		{
			SerialPort sp = new SerialPort("COM3", 9600);

			sp.Open();
			sp.ReadTimeout = 100; // causes delay

            byte[] buff = new byte[3];
			
			while (true)
			{
                // string a = sp.ReadLine();
                int a = sp.Read(buff, 0, 3);


                //Console.Clear();

                Console.WriteLine(buff[0]+ " " + buff[1] + " " + buff[2]);                
			}

	}
}
			// use here
			//string s = sp.ReadLine();
			//string[] spls = s.Split('#');
			//int uS1 = Convert.ToInt32(spls[0]);
			//int uS2 = Convert.ToInt32(spls[1]);
			//int uS3 = Convert.ToInt32(spls[2]);

			//float[] L = new float[3];

}
