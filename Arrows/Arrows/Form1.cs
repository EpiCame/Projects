using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Arrows
{
    public partial class Form1 : Form
    {
        int H = 800, W = 1400;
        int[] v;
        int n = 100;
        int L = 100;
        Button b;
        private void Form1_Load(object sender, EventArgs e)
        {
            this.Width = W;
            this.Height = H;
            label1.Left = W / 2 - 200;
        }
        void Reseteaza_Interfata()
        {
            pictureBox1.Visible = true;
            pictureBox2.Visible = true;
            pictureBox3.Visible = true;
            pictureBox4.Visible = true;
            pictureBox5.Visible = true;
            button1.Visible = true;
            label1.Visible = true;
            button1.Enabled = true;

        }
        public void Start_Game()
        {
            
            b = new Button();
            b.Top = 10;
            b.Left = W - 70;
            b.Width = 40;
            b.Height = 40;
            b.Visible = true;
            b.Enabled = true;
            b.Image = Image.FromFile("inapoi.png");
            b.ImageLayout = stretch;
            b.Click += new EventHandler(b_Click);
            this.Controls.Add(b);

        }
        private void b_Click(object sender, EventArgs e)
        {
            Reseteaza_Interfata();
            b.Enabled = false;
            b.Visible = false;
        }
        public void button1_Click(object sender, EventArgs e)
        {
            pictureBox1.Visible = false;
            pictureBox2.Visible = false;
            pictureBox3.Visible = false;
            pictureBox4.Visible = false;
            pictureBox5.Visible = false;
            button1.Visible = false;
            button1.Enabled = false;
            label1.Visible = false;
            Start_Game();
        }
        
        
        public Form1()
        {
            InitializeComponent();
        }
       

        
    }
}
