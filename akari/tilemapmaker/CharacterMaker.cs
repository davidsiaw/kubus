using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Imaging;
using System.IO;

namespace tilemapmaker
{
    public partial class CharacterMaker : Form
    {
        Color currentcolor = Color.White;

        public CharacterMaker()
        {
            InitializeComponent();

            pixelEditor1.ShowTileArea = true;
            pixelEditor1.LeftClick += new Action<PixelEditor, MouseEventArgs>(pixelEditor1_LeftClick);
            pixelEditor1.LeftClickDrag += new Action<PixelEditor, MouseEventArgs>(pixelEditor1_LeftClickDrag);

            pixelEditor2.LeftClick += new Action<PixelEditor, MouseEventArgs>(pixelEditor2_LeftClick);
            pixelEditor2.LeftClickDrag += new Action<PixelEditor, MouseEventArgs>(pixelEditor2_LeftClick);

            pixelEditor3.LeftClick += new Action<PixelEditor, MouseEventArgs>(pixelEditor3_LeftClick);
            pixelEditor3.LeftClickDrag += new Action<PixelEditor, MouseEventArgs>(pixelEditor3_LeftClick);

            panel1.BackColor = currentcolor;

            spritemap = new Bitmap(192, 256);
            pixelEditor3.SetBitmap(spritemap);
            SelectTile(0, 0);

            Timer t = new Timer();
            t.Interval = 250;
            t.Tick += new EventHandler(t_Tick);
            t.Start();

            animationlayer = new Bitmap(48, spritemap.Height);
            pixelEditor4.SetBitmap(animationlayer);

            mode_dot.Checked = true;
        }

        Bitmap animationlayer;
        int tickcount = 0;

        void t_Tick(object sender, EventArgs e)
        {
            tickcount++;
            using (Graphics g = Graphics.FromImage(animationlayer))
            {
                g.FillRectangle(Brushes.Black, 0, 0, animationlayer.Width, animationlayer.Height);
                for (int i = 0; i < 4; i++)
                {
                    g.DrawImage(spritemap, new Rectangle(0, i * 64, sprite.Width, sprite.Height), new Rectangle((tickcount % 4) * 48, i * 64, sprite.Width, sprite.Height), GraphicsUnit.Pixel);
                }
            }
            pixelEditor4.Refresh();
        }

        Bitmap spritemap;
        Bitmap sprite;
        int initialx;
        int initialy;


        void pixelEditor3_LeftClick(PixelEditor arg1, MouseEventArgs arg2)
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

        void pixelEditor2_LeftClick(PixelEditor arg1, MouseEventArgs arg2)
        {
            int x, y;
            arg1.GetMapPos(arg2, out x, out y);
            pixelEditor2.HighlightTile(x, y);
            currentcolor = pixelEditor2.GetTile(x, y);
            panel1.BackColor = currentcolor;
        }

        void pixelEditor1_LeftClickDrag(PixelEditor arg1, MouseEventArgs arg2)
        {
            if (mode_copy.Checked)
            {
                int x, y;
                arg1.GetMapPos(arg2, out x, out y);

                int tilex = x ;
                int tiley = y ;

                int htilex, htiley;
                arg1.GetHighlightedTile(out htilex, out htiley);

                int minx = Math.Min(tilex, htilex);
                int miny = Math.Min(tiley, htiley);
                arg1.HighlightTile(minx, miny);

                int dx = Math.Max(Math.Abs(tilex - htilex + 1), 1);
                int dy = Math.Max(Math.Abs(tiley - htiley + 1), 1);

                arg1.highlightwidth = dx;
                arg1.highlightheight = dy;
                UpdateClipboardWithArea(minx, miny, dx, dy);
            }
            else
            {
                pixelEditor1_LeftClick(arg1, arg2);
            }
        }

        private void UpdateClipboardWithArea(int minx, int miny, int dx, int dy)
        {
            pe_clipboard.map.Dispose();
            pe_clipboard.map = new Bitmap(pixelEditor1.highlightwidth, pixelEditor1.highlightheight);
            using (Graphics g = Graphics.FromImage(pe_clipboard.map))
            {
                g.DrawImage(pixelEditor1.map, new Rectangle(0, 0, dx, dy), new Rectangle(minx, miny, dx, dy), GraphicsUnit.Pixel);
            }
            pe_clipboard.Refresh();
        }

        void pixelEditor1_LeftClick(PixelEditor arg1, MouseEventArgs arg2)
        {
            if (mode_copy.Checked)
            {
                int x, y;
                arg1.GetMapPos(arg2, out x, out y);
                arg1.HighlightTile(x, y);
                arg1.highlightheight = 1;
                arg1.highlightwidth = 1;
                UpdateClipboardWithArea(x, y, 1, 1);
            }
            else
            {
                arg1.ApplyMouseUnderlay();

                using (Graphics g = Graphics.FromImage(spritemap))
                {
                    g.CompositingMode = System.Drawing.Drawing2D.CompositingMode.SourceCopy;
                    g.DrawImage(sprite, new Rectangle(initialx, initialy, 48, 64), new Rectangle(0, 0, sprite.Width, sprite.Height), GraphicsUnit.Pixel);
                }
            }
            pixelEditor3.Refresh();
        }

        private void btn_loadPalette_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.ShowDialog();
            if (!string.IsNullOrEmpty(ofd.FileName))
            {
                using (Bitmap bmp = new Bitmap(ofd.FileName))
                {
                    Bitmap actual = new Bitmap(bmp.Width, bmp.Height, PixelFormat.Format32bppArgb);
                    using (Graphics g = Graphics.FromImage(actual))
                    {
                        g.DrawImage(bmp, 0, 0);
                    }
                    pixelEditor2.SetBitmap(actual);
                }
            }
        }

        private void btn_savePalette_Click(object sender, EventArgs e)
        {

        }

        private void btn_loadsprite_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.ShowDialog();
            if (!string.IsNullOrEmpty(ofd.FileName))
            {
                using (Bitmap bmp = new Bitmap(ofd.FileName))
                {
                    Bitmap actual = new Bitmap(bmp.Width, bmp.Height, PixelFormat.Format32bppArgb);
                    using (Graphics g = Graphics.FromImage(actual))
                    {
                        g.DrawImage(bmp, new Rectangle(0, 0, bmp.Width, bmp.Height), new Rectangle(0, 0, bmp.Width, bmp.Height), GraphicsUnit.Pixel);
                    }
                    spritemap = actual;
                    pixelEditor3.SetBitmap(actual);
                    pixelEditor3.Refresh();
                    SelectTile(0, 0);
                }
            }
        }

        private void btn_save_Click(object sender, EventArgs e)
        {
            SaveFileDialog ofd = new SaveFileDialog();
            ofd.ShowDialog();
            if (!string.IsNullOrEmpty(ofd.FileName))
            {
                spritemap.Save(Path.Combine(Path.GetDirectoryName(ofd.FileName), Path.GetFileNameWithoutExtension(ofd.FileName) + ".png"), ImageFormat.Png);
            }
        }

        private void mode_dot_CheckedChanged(object sender, EventArgs e)
        {
            pixelEditor1.drawMouseUnderlay = (g, x, y) => {
                g.FillRectangle(new SolidBrush(currentcolor), new Rectangle(x, y, 1, 1));
            };
        }

        private void mode_circle_CheckedChanged(object sender, EventArgs e)
        {
            pixelEditor1.drawMouseUnderlay = (g, x, y) =>
            {
                int size = (int)num_circlesize.Value;
                g.FillEllipse(new SolidBrush(currentcolor), new Rectangle(x - size / 2, y - size / 2, size, size));
            };
        }

        private void mode_rectangle_CheckedChanged(object sender, EventArgs e)
        {
            pixelEditor1.drawMouseUnderlay = (g, x, y) =>
            {
                int size = (int)num_rectanglesize.Value;
                g.FillRectangle(new SolidBrush(currentcolor), new Rectangle(x - size / 2, y - size / 2, size, size));
            };
        }

        private void mode_copy_CheckedChanged(object sender, EventArgs e)
        {
            pixelEditor1.drawMouseUnderlay = (g, x, y) =>
            {
            };
        }

        private void mode_paste_CheckedChanged(object sender, EventArgs e)
        {
            pixelEditor1.drawMouseUnderlay = (g, x, y) =>
            {
                g.CompositingMode = System.Drawing.Drawing2D.CompositingMode.SourceOver;
                g.DrawImage(pe_clipboard.map, x - pe_clipboard.map.Width / 2, y - pe_clipboard.map.Height / 2);
            };
        }

        private void mode_punchPaste_CheckedChanged(object sender, EventArgs e)
        {
            pixelEditor1.drawMouseUnderlay = (g, x, y) =>
            {
                g.DrawImage(pe_clipboard.map, x - pe_clipboard.map.Width / 2, y - pe_clipboard.map.Height / 2);
            };

        }

        private void btn_rotateCW_Click(object sender, EventArgs e)
        {
            pe_clipboard.map.RotateFlip(RotateFlipType.Rotate90FlipNone);
            pe_clipboard.Refresh();
        }

        private void btn_rotateCCW_Click(object sender, EventArgs e)
        {
            pe_clipboard.map.RotateFlip(RotateFlipType.Rotate270FlipNone);
            pe_clipboard.Refresh();
        }

    }
}
