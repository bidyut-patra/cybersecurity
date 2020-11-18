using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
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

namespace target
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            this.DataContext = MainViewModel.Instance;
        }
    }

    public class MainViewModel
    {
        public ObservableCollection<ThreadInfo> Threads { get; set; }

        private static MainViewModel _instance;
        public static MainViewModel Instance
        {
            get
            {
                if (_instance == null)
                {
                    _instance = new MainViewModel();
                }
                return _instance;
            }
        }

        private MainViewModel()
        {
            this.Threads = new ObservableCollection<ThreadInfo>();
        }
    }

    public class ThreadInfo
    {
        public string Name { get; set; }
        public int Identifier { get; set; }
        public ProcessThread Thread { get; set; }

        public ThreadInfo()
        {
            this.Name = "Default";
        }
    }
}
