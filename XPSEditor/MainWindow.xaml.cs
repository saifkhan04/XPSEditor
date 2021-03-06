﻿using System;
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
using Microsoft.Win32;

namespace XPSEditor
{
    using XPSLib.Cpp.CLI;
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            XPSApi.InitializeLibrary(Environment.CurrentDirectory + "XPSLib.CPP.dll");
        }
        private void _Save(object sender, EventArgs e)
        {
            using (var wrapper = new XPSApi())
            {
                wrapper.CreateDefaultXPSFile();
            }
        }
    }
}
