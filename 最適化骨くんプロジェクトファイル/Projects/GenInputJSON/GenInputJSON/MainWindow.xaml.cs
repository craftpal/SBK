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
using System.Windows.Media.Animation;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Collections.ObjectModel;
using Newtonsoft.Json;

namespace GenInputJSON
{
    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window
    {
        private ObservableCollection<CTarget> target_data;
        private ObservableCollection<CPart> parts_data;
        private string internal_error;      //エラー通知
        private bool tb_path_focused;
        private string out_path;

        public MainWindow()
        {
            InitializeComponent();
            target_data = new ObservableCollection<CTarget>();
            parts_data = new ObservableCollection<CPart>();
            this.grid_target.ItemsSource = target_data;
            this.grid_parts.ItemsSource = parts_data;
            this.miOpen.InputGestureText = "Ctrl+O";
            this.miSave.InputGestureText = "Ctrl+S";
        }

        private void set_from_json(string json)
        {
            CDataObj obj = JsonConvert.DeserializeObject<CDataObj>(json);
            target_data = new ObservableCollection<CTarget>(obj.target);
            parts_data = new ObservableCollection<CPart>(obj.parts);
            this.grid_target.ItemsSource = target_data;
            this.grid_parts.ItemsSource = parts_data;
        }

        private void add_from_json(string json)
        {
            CDataObj obj = JsonConvert.DeserializeObject<CDataObj>(json);

            var getNameWin = new Window1();
            getNameWin.ShowDialog();
            var name = getNameWin.name;

            foreach (var item in obj.parts) {
                if (name != "") item.id = "["+name+"]"+item.id;
                parts_data.Add(item);
            }

            this.grid_parts.ItemsSource = parts_data;
        }

        //このメソッドの実行後には必ずinternal_errorをチェックすること
        private string gen_json()
        {
            internal_error = "";
            //内部エラーをリセット
            internal_error = "";
            if (target_data.Count < 1)
            {
                internal_error = "差分範囲1つも入力されていません。";
                return "";
            }

            CDataObj obj = new CDataObj()
            {
                target = target_data.ToArray<CTarget>(),
                parts = parts_data.ToArray<CPart>()
            };

            int base_x;
            //参照: http://dobon.net/vb/dotnet/vb2cs/isnumeric.html
            if (!int.TryParse(tb_base_x.Text, out base_x))
            {
                MessageBox.Show("基準範囲には数値を入力してください。");
                internal_error = "Not inputed error!";
                return "";
            }

            //基準範囲をプラスしておく
            for (int i = 0, len = obj.target.Count<CTarget>(); i < len; i++)
            {
                obj.target[i].x += base_x;
            }

            return JsonConvert.SerializeObject(obj);
        }

        private void save_json_file(string path, string json)
        {
            System.IO.StreamWriter sw = new System.IO.StreamWriter(path);
            sw.Write(json);
            sw.Close();
        }

        private void start_gen_Click(object sender, RoutedEventArgs e)
        {
            var result = MessageBox.Show("最適化を開始します。", "確認", MessageBoxButton.OKCancel);

            //OKボタンが押されたとき
            if (result == MessageBoxResult.OK)
            {
                string json = gen_json();
                if (!(tb_path.Text.Length > 0)) {
                    internal_error = "出力ファイルパスが入力されていません。";
                }
                if (tb_path.Text.IndexOfAny(System.IO.Path.GetInvalidFileNameChars()) < 0) {
                    internal_error = "出力ファイルパスが有効ではありません。";
                }
                if (internal_error != "")
                {
                    MessageBox.Show(internal_error);
                    return;
                }
                //一時ファイルにjson形式でファイルを保存
                string path = "__temp__.json";
                save_json_file(path, json);

                //外部最適化プログラムを開始
                string path_clac = "PazzleClacNative.exe";
                try
                {
                    System.Diagnostics.Process p = new System.Diagnostics.Process();
                    p.StartInfo.FileName = path_clac;
                    p.StartInfo.Arguments = path+" \""+tb_path.Text+"\" "+tb_weight_x.Text+" "+tb_weight_y.Text;
                    p.StartInfo.CreateNoWindow = true;
                    p.StartInfo.UseShellExecute = false;
                    p.Start();
                    p.WaitForExit();
                    MessageBox.Show("完了しました!");
                }
                catch (System.ComponentModel.Win32Exception)
                {
                    MessageBox.Show(path_clac + " が存在しないため、計算開始できませんでした。");
                    return;
                }

                //一時ファイルを削除
                System.IO.File.Delete(path);
            }
        }

        private void tb_num_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter || e.Key == Key.Tab)
            {
                var tb = (TextBox)sender;
                tb.MoveFocus(new TraversalRequest(FocusNavigationDirection.Next));
            }
            if (e.Key < Key.D0 || e.Key > Key.D9
                && e.Key < Key.NumPad0 || e.Key > Key.NumPad9)
            {
                e.Handled = true;
            }
        }

        private void miSave_Click(object sender, RoutedEventArgs e)
        {
            string json = gen_json();
            if (internal_error != "")
            {
                MessageBox.Show(internal_error);
                return;
            }
            Microsoft.Win32.SaveFileDialog sfd = new Microsoft.Win32.SaveFileDialog();
            sfd.Filter = "JSON Files (.json) | *.json";
            bool? result = sfd.ShowDialog();
            if (result == true)
            {
                save_json_file(sfd.FileName, json);
                MessageBox.Show(sfd.FileName + "に保存しました!");
            }
        }

        private void miOpen_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog ofd = new Microsoft.Win32.OpenFileDialog();
            bool? result = ofd.ShowDialog();
            if (result == true)
            {
                System.IO.StreamReader sr = new System.IO.StreamReader(ofd.FileName);
                string json = sr.ReadToEnd();
                set_from_json(json);
                MessageBox.Show(ofd.FileName + "から読み込みを完了しました!");
            }
        }

        private void miOpenAdd_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog ofd = new Microsoft.Win32.OpenFileDialog();
            bool? result = ofd.ShowDialog();
            if (result == true)
            {
                System.IO.StreamReader sr = new System.IO.StreamReader(ofd.FileName);
                string json = sr.ReadToEnd();
                add_from_json(json);
                MessageBox.Show(ofd.FileName + "から読み込みを完了しました!");
            }
        }

        private void tb_num_x_LostFocus(object sender, RoutedEventArgs e)
        {
            int buf;
            if (!int.TryParse(((TextBox)sender).Text, out buf))
            {
                tb_base_x.Text = "0";
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            if (System.IO.File.Exists("__temp__.json"))
            {
                MessageBox.Show("計算途中と思われる一時ファイルが存在します。\n(Exists __temp__.json)");
            }
        }

        private void grid_target_KeyDown(object sender, KeyEventArgs e)
        {
            //if (e.Key == Key.Enter)
            //{
            //    grid_target.CurrentCell = new DataGridCellInfo(
            //        grid_target.CurrentCell.Item., grid_target.Columns[0]
            //        );
            //}
        }

        private void tb_path_GotFocus(object sender, RoutedEventArgs e)
        {
            var animation = new DoubleAnimation
            {
                From = tb_path.Width,
                To = this.Width - 60,
                SpeedRatio = 5.0,
            };
            tb_path.BeginAnimation(Window.WidthProperty, animation);
            tb_path_focused = true;
        }

        private void tb_path_LostFocus(object sender, RoutedEventArgs e)
        {
            var animation = new DoubleAnimation
            {
                From = tb_path.Width,
                To = 50,
                SpeedRatio = 5.0
            };
            tb_path.BeginAnimation(Window.WidthProperty, animation);
            tb_path_focused = false;
        }

        private void Window_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            if (this.tb_path_focused)
            {
                tb_path.Width = this.Width - 60;
            }
        }

        private void btOutPath_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.SaveFileDialog sfd = new Microsoft.Win32.SaveFileDialog();
            sfd.Filter = "dxf Files (.dxf) | *.dxf";
            bool? result = sfd.ShowDialog();
            if (result == true)
            {
                tb_path.Text = sfd.FileName;
            }
        }
    }

    //参考
    //http://okazuki.hatenablog.com/entry/20130218/1358172834
    public class CDataObj
    {
        public CTarget[] target { get; set; }
        public CPart[] parts { get; set; }
    }

    public class CPart
    {
        public string id { get; set; }
        public int x { get; set; }
        public int y { get; set; }
    }

    public class CTarget
    {
        public int x { get; set; }
        public int y { get; set; }
    }
}
