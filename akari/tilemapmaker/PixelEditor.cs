using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Drawing.Imaging;

namespace tilemapmaker
{
    public partial class PixelEditor : PictureBox
    {
        public Bitmap map = new Bitmap(128, 192);
        int camx, camy;
        float zoom = 1;

        public PixelEditor()
        {
            InitializeComponent();
        }

        public void SetBitmap(Bitmap bmp)
        {
            map = bmp;
        }

        bool dragging = false;
        int dragfromx, dragfromy;
        int origcamx, origcamy;

        protected override void OnMouseDown(MouseEventArgs e)
        {
            if ((e.Button & System.Windows.Forms.MouseButtons.Left) != 0)
            {
                dragging = true;
                dragfromx = e.X;
                dragfromy = e.Y;

                origcamx = camx;
                origcamy = camy;
            }
            if ((e.Button & System.Windows.Forms.MouseButtons.Right) != 0)
            {
                if (RightClick != null)
                {
                    RightClick(this, e);
                }
            }
        }

        protected override void OnMouseUp(MouseEventArgs e)
        {
            if ((e.Button & System.Windows.Forms.MouseButtons.Left) != 0)
            {
                dragging = false;
            }
        }

        int mousex;
        int mousey;
        protected override void OnMouseMove(MouseEventArgs e)
        {
            if (dragging)
            {
                camx = origcamx + e.X - dragfromx;
                camy = origcamy + e.Y - dragfromy;
            }

            if ((e.Button & System.Windows.Forms.MouseButtons.Right) != 0)
            {
                if (RightClickDrag != null)
                {
                    RightClickDrag(this, e);
                }
            }
            GetMapPos(e, out mousex, out mousey);
            Refresh();
        }


        public void GetMapPos(MouseEventArgs e, out int mapposx, out int mapposy)
        {

            mapposx = (int)((e.X - camx) / zoom);
            mapposy = (int)((e.Y - camy) / zoom);
        }

        public int highlightwidth { get; set; }
        public int highlightheight { get; set; }

        Point? highlightTile = null;

        public void HighlightTile(int tilex, int tiley)
        {
            highlightTile = new Point(tilex, tiley);
            highlightwidth = 1;
            highlightheight = 1;
        }

        public void GetHighlightedTile(out int tilex, out int tiley)
        {
            tilex = 0;
            tiley = 0;
            if (highlightTile != null)
            {
                tilex = highlightTile.Value.X;
                tiley = highlightTile.Value.Y;
            }
        }

        public void PutTile(int tilex, int tiley, Color t)
        {
            try
            {
                map.SetPixel(tilex, tiley, t);
            }
            catch { }
            Refresh();
        }

        public Color GetTile(int tilex, int tiley)
        {
            try
            {
                return map.GetPixel(tilex, tiley);
            }
            catch { }
            return Color.White;
        }

        protected override void OnMouseWheel(MouseEventArgs e)
        {
            int mapposx;
            int mapposy;
            GetMapPos(e, out mapposx, out mapposy);

            if (e.Delta > 0)
            {
                zoom *= 2;

            }
            else
            {
                zoom /= 2;
            }

            int newmapposx;
            int newmapposy;
            GetMapPos(e, out newmapposx, out newmapposy);
            camx += (int)((newmapposx - mapposx) * zoom);
            camy += (int)((newmapposy - mapposy) * zoom);

            Refresh();
        }

        protected override void OnPaint(PaintEventArgs pe)
        {
        }

        public Image img;



        public event Action<PixelEditor, MouseEventArgs> RightClick;
        public event Action<PixelEditor, MouseEventArgs> RightClickDrag;

        Pen borderpen = new Pen(Brushes.Magenta, 0.5f);
        string text = "kami";

        protected override void OnPaintBackground(PaintEventArgs pevent)
        {
            text = "x=" + mousex + " y=" + mousey + " tilex=" + (mousex  ) + " tiley=" + (mousey  );

            Graphics g = pevent.Graphics;
            g.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.Half;
            g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
            g.FillRectangle(Brushes.Black, pevent.ClipRectangle);

            g.TranslateTransform(camx, camy);
            g.ScaleTransform(zoom, zoom);
            borderpen.LineJoin = System.Drawing.Drawing2D.LineJoin.Round;

            g.DrawRectangle(borderpen, new Rectangle(0, 0, map.Width  , map.Height  ));

            if (img != null)
            {
                g.DrawImage(img, 0, 0);
            }

            ColorMatrix matrix = new ColorMatrix();
            matrix.Matrix33 = 0.5f; //opacity 0 = completely transparent, 1 = completely opaque

            ImageAttributes translucent = new ImageAttributes();
            translucent.SetColorMatrix(matrix, ColorMatrixFlag.Default, ColorAdjustType.Bitmap);

            g.DrawImage(map, 0f, 0f, map.Width, map.Height);

            if (highlightTile != null)
            {
                g.DrawRectangle(new Pen(Brushes.White, 0.3f),
                    new Rectangle(
                        highlightTile.Value.X ,
                        highlightTile.Value.Y ,
                         highlightwidth,
                         highlightheight));

                g.DrawRectangle(new Pen(Brushes.Red, 0.1f),
                    new Rectangle(
                        highlightTile.Value.X ,
                        highlightTile.Value.Y ,
                          highlightwidth,
                          highlightheight));
            }

            g.ScaleTransform(1 / zoom, 1 / zoom);
            g.TranslateTransform(-camx, -camy);

            g.DrawString(text, new Font(new FontFamily(System.Drawing.Text.GenericFontFamilies.SansSerif), 10), Brushes.White, new PointF(2, 2));

        }


        public bool PreFilterMessage(ref Message m)
        {
            if (m.Msg == 0x20a)
            {
                // WM_MOUSEWHEEL, find the control at screen position m.LParam
                Point pos = new Point(m.LParam.ToInt32() & 0xffff, m.LParam.ToInt32() >> 16);
                IntPtr hWnd = WindowFromPoint(pos);
                if (hWnd != IntPtr.Zero && hWnd != m.HWnd && Control.FromHandle(hWnd) != null)
                {
                    SendMessage(hWnd, m.Msg, m.WParam, m.LParam);
                    return true;
                }
            }
            return false;
        }

        // P/Invoke declarations
        [DllImport("user32.dll")]
        private static extern IntPtr WindowFromPoint(Point pt);
        [DllImport("user32.dll")]
        private static extern IntPtr SendMessage(IntPtr hWnd, int msg, IntPtr wp, IntPtr lp);
    }
}
