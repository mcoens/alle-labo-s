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
using System.IO.Ports;

namespace ArduinoCom
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            geefPoorten();
        }

        SerialPort arduinoPoort = new SerialPort();

        void geefPoorten()
        {
            String[] poorten = SerialPort.GetPortNames();
            foreach (String poort in poorten) {
                comboBoxPoorten.Items.Add(poort);
            }
        }

        private void buttonOpen_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if(comboBoxPoorten.Text == "")
                {
                    MessageBox.Show("Geef een poort in");
                } else
                {
                    arduinoPoort.PortName = comboBoxPoorten.Text;
                    arduinoPoort.BaudRate = Convert.ToInt32(9600);
                    try
                    {
                        arduinoPoort.Open();
                        MessageBox.Show("Poort geopend");
                    } catch(Exception fout)
                    {
                        MessageBox.Show(fout.Message);
                    }
                    
                }
            } catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void textBoxStuur_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.Key == Key.Enter)
            {
                arduinoPoort.WriteLine(textBoxStuur.Text);
                textBoxStuur.Text = "";
            }
        }

        private void buttonClose_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                arduinoPoort.Close();
                MessageBox.Show("Poort gesloten");
            } catch(Exception close)
            {
                MessageBox.Show(close.Message);
            }
        }
    }
}
