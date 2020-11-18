using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Configuration;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace target
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            this.WatchThreads();
        }

        private void WatchThreads()
        {
            Task.Factory.StartNew(() =>
            {
                while (true)
                {
                    var threads = Process.GetCurrentProcess().Threads;
                    var threadList = new ObservableCollection<ThreadInfo>();
                    for(var i = 0; i < threads.Count; i++)
                    {
                        var thread = threads[i];
                        var threadInfo = new ThreadInfo()
                        {
                            Identifier = thread.Id,
                            Thread = thread
                        };
                        threadList.Add(threadInfo);
                    }

                    Application.Current.Dispatcher.Invoke(() =>
                    {
                        MainViewModel.Instance.Threads = threadList;
                    });
                }
            });
        }
    }
}
