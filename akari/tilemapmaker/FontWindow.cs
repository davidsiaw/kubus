using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;
using BlueBlocksLib.FileAccess;

namespace tilemapmaker
{
    public partial class FontWindow : Form
    {

        Font font;
        public FontWindow(Font font)
        {
            InitializeComponent();
            this.font = font;
        }

        [StructLayout(LayoutKind.Sequential)]
        struct FontInfo
        {
            public uint chr;
            public float width;
            public float height;
            public float x1, y1;
            public float x2, y2;
            public float x3, y3;
            public float x4, y4;
        }

        private void FontWindow_Load(object sender, EventArgs e)
        {

            Thread t = new Thread(() =>
            {
                int posx = 0;
                int posy = 0;
                Bitmap b = new Bitmap(256, 256);
                using (Graphics g = Graphics.FromImage(b))
                {
                    g.FillRectangle(new SolidBrush(Color.FromArgb(128, Color.Black)), new Rectangle(0, 0, 256, 256));
                }

                List<FontInfo> fis = new List<FontInfo>();

                for (uint i = 32; i < 256; i++)
                {
                    Invoke(new Action(() => pictureBox1.Image = b));

                    Bitmap dummy = new Bitmap(256, 256);
                    using (Graphics dummyg = Graphics.FromImage(dummy))
                    {
                        string chr = ((char)i).ToString();
                        var size = dummyg.MeasureString(chr, font, 100);
                        var sizetypo = dummyg.MeasureString(chr, font, 100, StringFormat.GenericTypographic);
                        int advance = (int)size.Width;

                        Invoke(new Action(() =>
                        {
                            if (posx + advance > b.Width)
                            {
                                posx = 0;
                                posy += (int)size.Height + 1;
                            }

                            using (Graphics g = Graphics.FromImage(b))
                            {
                                g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAliasGridFit;
                                
                                g.DrawString(chr, font, Brushes.White, posx, posy);
                            }

                            FontInfo fi = new FontInfo()
                            {
                                chr = i,
                                width = sizetypo.Width+1,
                                height = sizetypo.Height,
                                x1 = (float)((double)posx / b.Size.Width),
                                y1 = (float)(((double)posy + sizetypo.Height) / b.Size.Height),
                                x2 = (float)(((double)posx + sizetypo.Width+1) / b.Size.Width),
                                y2 = (float)(((double)posy + sizetypo.Height) / b.Size.Height),
                                x3 = (float)(((double)posx + sizetypo.Width+1) / b.Size.Width),
                                y3 = (float)((double)posy / b.Size.Height),
                                x4 = (float)((double)posx / b.Size.Width),
                                y4 = (float)((double)posy / b.Size.Height),
                            };
                            fis.Add(fi);

                            Refresh();
                        }));


                        posx += advance;
                    }
                }

                BeginInvoke(new Action(() => {
                    SaveFileDialog sfd = new SaveFileDialog();
                    sfd.ShowDialog();
                    if (string.IsNullOrEmpty(sfd.FileName))
                    {
                        return;
                    }
                    b.Save(sfd.FileName + ".png");
                    using (FormattedWriter fw = new FormattedWriter(sfd.FileName + ".font"))
                    {
                        fw.Write((int)fis.Count);
                        foreach (var fi in fis)
                        {
                            fw.Write(fi);
                        }
                    }

                }));
            });
            t.Start();
        }
    }
}
