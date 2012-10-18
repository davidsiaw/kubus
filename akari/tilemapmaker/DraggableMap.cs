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
    public partial class DraggableMap : PictureBox, IMessageFilter
    {
        public Tile[,,] map;
        int camx, camy;
        float zoom = 1;
        int level = 0;

        public DraggableMap()
        {
            InitializeComponent();
            Application.AddMessageFilter(this);
            map = new Tile[50, 50, 3];
        }

        public void UpLevel()
        {
            level++;
            if (level >= map.GetLength(2))
            {
                level = map.GetLength(2) - 1;
            }
            Refresh();
        }

        public void DownLevel()
        {
            level--;
            if (level < 0)
            {
                level = 0;
            }
            Refresh();
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
                if (RightClick != null)
                {
                    RightClick(this, e);
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

        Point? highlightTile = null;

        public void HighlightTile(int tilex, int tiley)
        {
            highlightTile = new Point(tilex, tiley);
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

        public void PutTile(int tilex, int tiley, Tile t)
        {
            try
            {
                map[tilex, tiley, level] = t;
            }
            catch { }
            Refresh();
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
            camx += (int)((newmapposx-mapposx) * zoom);
            camy += (int)((newmapposy-mapposy) * zoom);

            Refresh();
        }

        protected override void OnPaint(PaintEventArgs pe)
        {
        }

        public Image img;

        

        public event Action<DraggableMap, MouseEventArgs> RightClick;

        Pen borderpen = new Pen(Brushes.Magenta, 10);
        string text = "kami";

        protected override void OnPaintBackground(PaintEventArgs pevent)
        {
            text = "x=" + mousex + " y=" + mousey + " tilex=" + (mousex / Tile.tilesize) + " tiley=" + (mousey / Tile.tilesize) + " level=" + level;

            Graphics g = pevent.Graphics;
            g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
            g.FillRectangle(Brushes.Black, pevent.ClipRectangle);

            g.TranslateTransform(camx, camy);
            g.ScaleTransform(zoom, zoom);
            borderpen.LineJoin = System.Drawing.Drawing2D.LineJoin.Round;

            g.DrawRectangle(borderpen, new Rectangle(0, 0, map.GetLength(0) * Tile.tilesize, map.GetLength(1) * Tile.tilesize));

            if (img != null)
            {
                g.DrawImage(img, 0, 0);
            }

            ColorMatrix matrix = new ColorMatrix();
            matrix.Matrix33 = 0.5f; //opacity 0 = completely transparent, 1 = completely opaque

            ImageAttributes translucent = new ImageAttributes();
            translucent.SetColorMatrix(matrix, ColorMatrixFlag.Default, ColorAdjustType.Bitmap);


            for (int lvl = 0; lvl < map.GetLength(2); lvl++)
            {
                for (int x = 0; x < map.GetLength(0); x++)
                {
                    for (int y = 0; y < map.GetLength(1); y++)
                    {
                        if (map[x, y, lvl] != null)
                        {
                            Tile t = map[x, y, lvl];
                            if (lvl != level)
                            {
                                g.DrawImage(t.GetBitmap(t.Surroundings(map, x,y,lvl), (uint)(Environment.TickCount / 250)),
                                    new Rectangle(x * Tile.tilesize, y * Tile.tilesize, Tile.tilesize, Tile.tilesize),
                                    0, 0, Tile.tilesize, Tile.tilesize, GraphicsUnit.Pixel, translucent);
                            }
                            else
                            {
                                g.DrawImage(t.GetBitmap(t.Surroundings(map, x, y, lvl), (uint)(Environment.TickCount / 250)), x * Tile.tilesize, y * Tile.tilesize);
                            }
                        }
                    }
                }
            }

            if (highlightTile != null)
            {
                g.DrawRectangle(new Pen(Brushes.White, 3), new Rectangle(highlightTile.Value.X * Tile.tilesize, highlightTile.Value.Y * Tile.tilesize, Tile.tilesize, Tile.tilesize));
                g.DrawRectangle(Pens.Red, new Rectangle(highlightTile.Value.X * Tile.tilesize, highlightTile.Value.Y * Tile.tilesize, Tile.tilesize, Tile.tilesize));
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
