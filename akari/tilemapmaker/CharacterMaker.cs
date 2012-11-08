using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace tilemapmaker
{
    public partial class CharacterMaker : Form
    {
        Color currentcolor = Color.White;

        public CharacterMaker()
        {
            InitializeComponent();
            pixelEditor1.RightClick += new Action<PixelEditor, MouseEventArgs>(pixelEditor1_RightClick);
            pixelEditor1.RightClickDrag += new Action<PixelEditor, MouseEventArgs>(pixelEditor1_RightClick);

            pixelEditor2.RightClick += new Action<PixelEditor, MouseEventArgs>(pixelEditor2_RightClick);
            pixelEditor2.RightClickDrag += new Action<PixelEditor, MouseEventArgs>(pixelEditor2_RightClick);

            pixelEditor3.RightClick += new Action<PixelEditor, MouseEventArgs>(pixelEditor3_RightClick);
            pixelEditor3.RightClickDrag += new Action<PixelEditor, MouseEventArgs>(pixelEditor3_RightClick);

            panel1.BackColor = currentcolor;

            spritemap = new Bitmap(192, 256);
            pixelEditor3.SetBitmap(spritemap);
            SelectTile(0, 0);
        }

        Bitmap spritemap;
        Bitmap sprite;
        int initialx;
        int initialy;

        void pixelEditor3_RightClick(PixelEditor arg1, MouseEventArgs arg2)
        {
            int x, y;
            arg1.GetMapPos(arg2, out x, out y);

            SelectTile(x, y);
        }

        private void SelectTile(int x, int y)
        {
            initialx = x / 48 * 48;
            initialy = y / 64 * 64;

            pixelEditor3.HighlightTile(initialx, initialy);
            pixelEditor3.highlightheight = 64;
            pixelEditor3.highlightwidth = 48;

            if (sprite != null)
            {
                sprite.Dispose();
            }
            sprite = new Bitmap(48, 64);
            using (Graphics g = Graphics.FromImage(sprite))
            {
                g.DrawImage(spritemap, new Rectangle(0, 0, sprite.Width, sprite.Height), new Rectangle(initialx, initialy, 48, 64), GraphicsUnit.Pixel);
            }
            pixelEditor1.SetBitmap(sprite);
            pixelEditor1.Refresh();
        }

        void pixelEditor2_RightClick(PixelEditor arg1, MouseEventArgs arg2)
        {
            int x, y;
            arg1.GetMapPos(arg2, out x, out y);
            pixelEditor2.HighlightTile(x, y);
            currentcolor = pixelEditor2.GetTile(x, y);
            panel1.BackColor = currentcolor;
        }

        void pixelEditor1_RightClick(PixelEditor arg1, MouseEventArgs arg2)
        {
            int x,y;
            arg1.GetMapPos(arg2, out x, out y);
            pixelEditor1.PutTile(x, y, currentcolor);

            using (Graphics g = Graphics.FromImage(spritemap))
            {
                g.DrawImage(sprite, new Rectangle(initialx, initialy, 48, 64), new Rectangle(0, 0, sprite.Width, sprite.Height), GraphicsUnit.Pixel);
            }
            pixelEditor3.Refresh();
        }

        private void btn_loadPalette_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.ShowDialog();
            if (!string.IsNullOrEmpty(ofd.FileName))
            {
                Bitmap bmp = new Bitmap(ofd.FileName);
                pixelEditor2.SetBitmap(bmp);
            }
        }

        private void btn_savePalette_Click(object sender, EventArgs e)
        {

        }
    }
}
