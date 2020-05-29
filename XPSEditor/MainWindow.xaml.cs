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
using Microsoft.Win32;
using System.IO;


namespace XPSEditor
{
    using XPSLib.Cpp.CLI;
   
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        XPSApi Xpsapiwrapper;
        string m_fontpath = " ";
        float m_size;
        string m_path1 = "";
        string m_input = "";
        System.Collections.Generic.Dictionary<string, List<string>> fontNameToFiles = new Dictionary<string, List<string>>();


        public MainWindow()
        { 
            InitializeComponent();
            XPSApi.InitializeLibrary(Environment.CurrentDirectory + "XPSLib.CPP.dll");
            Xpsapiwrapper = new XPSApi();
            Xpsapiwrapper.CreateBlankXPSFile();
            cmbFontSize.ItemsSource = new List<double>() { 8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72 };
        }
        
        
        private void Menu_SaveAs(object sender, EventArgs e)
        {
           
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            if (saveFileDialog.ShowDialog() == true)
            {
                m_path1 = saveFileDialog.FileName;
                m_path1 = System.IO.Path.GetFullPath(m_path1);
            }
            if (!(string.IsNullOrEmpty(m_path1)))
            {
                Xpsapiwrapper.SavefiletoLocation(m_path1);
            }

        }

        private void Menu_New(object sender, EventArgs e)
        {

        }

        private void Menu_Open(object sender,EventArgs e)
        {
            
           
        }

        private void Menu_Save(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(m_path1))
            {
                SaveFileDialog saveFileDialog = new SaveFileDialog();
                if (saveFileDialog.ShowDialog() == true)
                {
                    m_path1 = saveFileDialog.FileName;
                    m_path1 = System.IO.Path.GetFullPath(m_path1);
                }
                Xpsapiwrapper.SaveChanges(m_path1);              
            }
            else
            {
                Xpsapiwrapper.SaveChanges(m_path1);
            }
        }
       
        //Function call to change paper size....
        private void Papersize(object sender, EventArgs e)
        {
            MenuItem item = sender as MenuItem;
            string selec = item.Header as string;
            if(string.Compare(selec,"letter")==0)
            {
                Xpsapiwrapper.ChangePageSize(816.0f, 1056.0f);
            }
            else if(string.Compare(selec,"A4")==0)
            {
                Xpsapiwrapper.ChangePageSize(796.8f, 1123.2f);
            }
            else if (string.Compare(selec,"A5") == 0)
            {

                Xpsapiwrapper.ChangePageSize(556.8f, 796.8f);
            }
            else if (string.Compare(selec,"A3") == 0)
            {
                Xpsapiwrapper.ChangePageSize(1123.2f, 1584f);
            }
        }

        // Function call to insert picture.....
         private void Picture_insert(object sender, EventArgs e)
        {
            string imagepath ="";
            OpenFileDialog op = new OpenFileDialog();
            op.Title = "Select a picture";
            op.Filter = "All supported graphics|*.jpg;*.jpeg;*.png|" +
              "JPEG (*.jpg;*.jpeg)|*.jpg;*.jpeg|" +
              "Portable Network Graphic (*.png)|*.png";
            if (op.ShowDialog() == true)
            {
                imagepath=op.FileName;
                imagepath = System.IO.Path.GetFullPath(imagepath);
               
            }
            if (!(string.IsNullOrEmpty(imagepath)))
            {
                Xpsapiwrapper.InsertPicture(imagepath);
            }   
        }

        //Function to load fontnames in comboBox......
        private void comboBoxFonts_Loaded(object sender, RoutedEventArgs e)
        {
            List<string> copy = new List<string>();
            foreach (var fontFile in Directory.GetFiles(Environment.GetFolderPath(Environment.SpecialFolder.Fonts)))
            {
                var fc = new System.Drawing.Text.PrivateFontCollection();
                if (File.Exists(fontFile))
                    fc.AddFontFile(fontFile);

                if ((!fc.Families.Any()))
                    continue;
                var name = fc.Families[0].Name;
               
                        List<string> files;
                        if (!fontNameToFiles.TryGetValue(name, out files))
                        {
                            copy.Add(name);
                            files = new List<string>();
                            fontNameToFiles[name] = files;
                        }

                        files.Add(fontFile);      
                
            }
            comboBoxFonts.ItemsSource = copy;
            comboBoxFonts.SelectedIndex = 0;

        }

        //Function to select the fonts from combobox....

        private void comboBoxFonts_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            string s = comboBoxFonts.Items.GetItemAt(comboBoxFonts.SelectedIndex).ToString();
            var result = GetFilesForFont(s);
         
         
             m_fontpath = result[0];
            
            m_fontpath = System.IO.Path.GetFullPath(m_fontpath);

        }

        // Function for text input box opening....
        private void Text_Insert(object sender, RoutedEventArgs e)
        {

            InputBox.Visibility = System.Windows.Visibility.Visible;

        }

        // Function to change fontsize.....
        private void cmbFontSize_TextChanged(object sender, TextChangedEventArgs e)
        {
            string fontsize = cmbFontSize.Items.GetItemAt(cmbFontSize.SelectedIndex).ToString();
            m_size= float.Parse(fontsize);
        }


        private void YesButton_Click(object sender, RoutedEventArgs e)
        {
            // YesButton Clicked! Let's hide our InputBox and handle the input text.
            InputBox.Visibility = System.Windows.Visibility.Collapsed;

            // Inserting text in to the page.....
              m_input = InputTextBox.Text;
            if (!(string.IsNullOrEmpty(m_input)))
            {
                Xpsapiwrapper.InsertText(m_fontpath, m_size, m_input);
            }

            // Clear InputBox.
            InputTextBox.Text = String.Empty;
        }

        private void NoButton_Click(object sender, RoutedEventArgs e)
        {
            // NoButton Clicked! 
            InputBox.Visibility = System.Windows.Visibility.Collapsed;

            // Clear InputBox.
            InputTextBox.Text = String.Empty;
        }

        //Function to get the font file.....     
        private List<string> GetFilesForFont(string fontName)
        {
                 
            List<string> result;
            if (!fontNameToFiles.TryGetValue(fontName, out result))
                return null;

            return result;
        }
    }
}

