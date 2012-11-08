using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.IO;
using BlueBlocksLib.UITools;
using OpenTK;
using System.Runtime.InteropServices;
using System.Drawing.Imaging;
using BlueBlocksLib.FileAccess;

namespace tilemapmaker
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            draggableMap1.map = new Tile[200, 200, 3];

            System.Windows.Forms.Timer t = new System.Windows.Forms.Timer();
            t.Interval = 250;
            t.Tick += new EventHandler((o, e) => draggableMap1.Refresh());
            t.Start();

            draggableMap1.RightClick += new Action<DraggableMap, MouseEventArgs>(draggableMap1_RightClick);
            draggableMap1.RightClickDrag += new Action<DraggableMap, MouseEventArgs>(draggableMap1_RightClickDrag);
            DragDropTools.EnableFileDrop(draggableMap1, x => x.ToList().ForEach(file => OpenFile(file)));
        }

        void draggableMap1_RightClickDrag(DraggableMap dmap, MouseEventArgs obj)
        {
            int x, y;
            draggableMap1.GetMapPos(obj, out x, out y);
            draggableMap1.PutTile(x / Tile.tilesize, y / Tile.tilesize, paintTile);
        }

        void draggableMap1_RightClick(DraggableMap dmap, MouseEventArgs obj)
        {
            int x, y;
            draggableMap1.GetMapPos(obj, out x, out y);
            draggableMap1.PutTile(x / Tile.tilesize, y / Tile.tilesize, paintTile);
        }

        SimpleTile currentTile = null;
        SimpleTile selectedBasicTile = null;
        Tile paintTile = null;

        private void btn_loadtilemap_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.ShowDialog();
            if (!string.IsNullOrEmpty(ofd.FileName))
            {
                OpenFile(ofd.FileName);
            }
        }

        private void OpenFile(string filename)
        {
            var img = Image.FromFile(filename);
            string name = Path.GetFileNameWithoutExtension(filename);
            tc_topLeft.TabPages.Add(name, name);

            DraggableMap dm = new DraggableMap();
            tc_topLeft.TabPages[name].Controls.Add(dm);

            Button basicTile = new Button();
            basicTile.Click += new EventHandler(basicTile_Click);
            basicTile.Text = "Create Basic Tile";
            basicTile.Dock = DockStyle.Bottom;

            tc_topLeft.TabPages[name].Controls.Add(basicTile);

            Button autoTile12 = new Button();
            autoTile12.Click += new EventHandler((obj, evt) => {
                AutoTile12 at12 = new AutoTile12();
                DraggableMap dmap = ((Button)obj).Tag as DraggableMap;
                
                int x, y;
                dmap.GetHighlightedTile(out x, out y);

                for (int i = 0; i < AutoTile12.tileToRawTileIndex.Length; i++)
                {
                    Rectangle rect = AutoTile12.tileToRawTileIndex[i];
                    SimpleTile st = GetSelectedTile(dmap, rect.X + x * Tile.tilesize, rect.Y + y * Tile.tilesize);
                    at12.rawtiles[i] = st;
                }

                AddAutotile12(at12, at12);
            });
            autoTile12.Tag = dm;
            autoTile12.Text = "Create Autotile";
            autoTile12.Dock = DockStyle.Bottom;
            autoTile12.Enabled = false;

            tc_topLeft.TabPages[name].Controls.Add(autoTile12);

            dm.map = new Tile[img.Width / Tile.tilesize, img.Height / Tile.tilesize, 1];
            dm.img = img;
            dm.Dock = DockStyle.Fill;
            dm.RightClick += new Action<DraggableMap, MouseEventArgs>((dmap, evt) =>
            {
                int x, y;
                dmap.GetMapPos(evt, out x, out y);

                SimpleTile st = GetSelectedTile(dmap, x, y);

                currentTile = st;

                if (dmap.highlightwidth == 3 && dmap.highlightheight == 4)
                {
                    autoTile12.Enabled = true;
                }
                else
                {
                    autoTile12.Enabled = false;
                }
            });
            dm.RightClickDrag += new Action<DraggableMap, MouseEventArgs>((dmap, evt) =>
            {
                int x, y;
                dmap.GetMapPos(evt, out x, out y);

                int tilex = x / Tile.tilesize;
                int tiley = y / Tile.tilesize;

                int htilex, htiley;
                dmap.GetHighlightedTile(out htilex, out htiley);

                dmap.HighlightTile(Math.Min(tilex, htilex), Math.Min(tiley, htiley));

                int dx = Math.Max(Math.Abs(tilex - htilex + 1), 1);
                int dy = Math.Max(Math.Abs(tiley - htiley + 1), 1);

                dmap.highlightwidth = dx;
                dmap.highlightheight = dy;

                if (dx == 3 && dy == 4)
                {
                    autoTile12.Enabled = true;
                }
                else
                {
                    autoTile12.Enabled = false;
                }

            });

        }

        private static SimpleTile GetSelectedTile(DraggableMap dmap, int x, int y)
        {
            int tilex = x / Tile.tilesize;
            int tiley = y / Tile.tilesize;
            dmap.HighlightTile(tilex, tiley);

            Bitmap b = new Bitmap(Tile.tilesize, Tile.tilesize);
            using (Graphics g = Graphics.FromImage(b))
            {
                g.DrawImage(
                    dmap.img,
                    new Rectangle(0, 0, Tile.tilesize, Tile.tilesize),
                    new Rectangle(tilex * Tile.tilesize, tiley * Tile.tilesize, Tile.tilesize, Tile.tilesize),
                    GraphicsUnit.Pixel);
            }
            SimpleTile st = new SimpleTile(b);
            return st;
        }

        void basicTile_Click(object sender, EventArgs e)
        {
            if (currentTile != null)
            {
                AddBasicTile(currentTile);
            }
        }

        private void AddBasicTile(SimpleTile tile)
        {
            RadioButton btn = new RadioButton();
            btn.Appearance = Appearance.Button;
            btn.Size = new System.Drawing.Size(40, 40);
            btn.Image = tile.GetBitmap(0, 0);
            btn.Tag = tile;
            btn.Click += new EventHandler((o, evt) =>
            {
                selectedBasicTile = (SimpleTile)((RadioButton)o).Tag;
                var tp = splitContainer4.Panel2;
                tp.Controls.Clear();
                int d = Tile.tilesize / 2;

                if (selectedBasicTile is SimpleTile)
                {
                    var st = selectedBasicTile as SimpleTile;

                    for (int i = 0; i < 4; i++)
                    {
                        Rectangle r = AutoTile94.tileToRawTileIndex[i];
                        PictureBox pb = new PictureBox();
                        pb.Location = new Point(r.X / d * 20, r.Y / d * 20 + 30);
                        pb.Size = new Size(r.Width + 6, r.Height + 6);
                        pb.Image = st.bmp[i];
                        pb.Tag = new KeyValuePair<SimpleTile, int>(st, i);
                        pb.Click += new EventHandler((ob, ev) =>
                        {
                            PictureBox thepb = (PictureBox)ob;
                            KeyValuePair<SimpleTile, int> theat = (KeyValuePair<SimpleTile, int>)thepb.Tag;
                            thepb.Image = currentTile.GetBitmap(0, 0);
                            theat.Key.bmp[theat.Value] = currentTile.bmp[0];
                        });
                        tp.Controls.Add(pb);
                    }
                }

            });
            flow_basictiles.Controls.Add(btn);
        }

        void autoTile12_Click(object sender, EventArgs e)
        {
            if (selectedBasicTile != null)
            {
                Tile autotile = selectedBasicTile;
                AutoTile12 at = new AutoTile12();
                AddAutotile12(autotile, at);

            }
        }

        private void AddAutotile12(Tile autotile, AutoTile12 at)
        {

            RadioButton btn = new RadioButton();
            btn.Appearance = Appearance.Button;
            btn.Size = new System.Drawing.Size(40, 40);
            btn.Image = autotile.GetBitmap(0, 0);

            int t = Tile.tilesize;
            var twelve = new Bitmap(t * 3, t * 4);
            using (Graphics g = Graphics.FromImage(twelve))
            {
                for (int x = 0; x < 3; x++)
                {
                    for (int y = 0; y < 4; y++)
                    {
                        g.DrawImage(autotile.GetBitmap(0, 0), t * x, t * y);
                    }
                }
            }

            btn.Tag = at;
            btn.Click += new EventHandler((o, evt) =>
            {
                paintTile = (Tile)((RadioButton)o).Tag;
                populatePanel2WithTileEditor();
            });
            flow_tiles.Controls.Add(btn);
        }

        void autoTile94_Click(object sender, EventArgs e)
        {
            if (selectedBasicTile != null)
            {
                Tile autotile = selectedBasicTile;
                AutoTile94 at = new AutoTile94();
                AddAutotile94(autotile, at);

            }
        }

        private void AddAutotile94(Tile autotile, AutoTile94 at)
        {

            RadioButton btn = new RadioButton();
            btn.Appearance = Appearance.Button;
            btn.Size = new System.Drawing.Size(40, 40);
            btn.Image = autotile.GetBitmap(0, 0);

            int t = Tile.tilesize;
            var nine = new Bitmap(t * 3, t * 3);
            var four = new Bitmap(t * 2, t * 2);
            using (Graphics g = Graphics.FromImage(nine))
            {
                for (int x = 0; x < 3; x++)
                {
                    for (int y = 0; y < 3; y++)
                    {
                        g.DrawImage(autotile.GetBitmap(0, 0), t * x, t * y);
                    }
                }
            }

            using (Graphics g = Graphics.FromImage(four))
            {
                for (int x = 0; x < 2; x++)
                {
                    for (int y = 0; y < 2; y++)
                    {
                        g.DrawImage(autotile.GetBitmap(0, 0), t * x, t * y);
                    }
                }
            }


            btn.Tag = at;
            btn.Click += new EventHandler((o, evt) =>
            {
                paintTile = (Tile)((RadioButton)o).Tag;
                populatePanel2WithTileEditor();
            });
            flow_tiles.Controls.Add(btn);
        }

        void simpleTile_Click(object sender, EventArgs e)
        {
            if (selectedBasicTile != null)
            {
                AddSimpleTile(selectedBasicTile);
            }
        }

        private void AddSimpleTile(SimpleTile basicTile)
        {
            RadioButton btn = new RadioButton();
            btn.Appearance = Appearance.Button;
            btn.Size = new System.Drawing.Size(40, 40);
            btn.Image = basicTile.GetBitmap(0, 0);
            btn.Tag = basicTile;
            btn.Click += new EventHandler((o, evt) =>
            {
                paintTile = (Tile)((RadioButton)o).Tag;
                populatePanel2WithTileEditor();
            });
            flow_tiles.Controls.Add(btn);
        }

        private void btn_uplevel_Click(object sender, EventArgs e)
        {
            draggableMap1.UpLevel();
        }

        private void btn_downlevel_Click(object sender, EventArgs e)
        {
            draggableMap1.DownLevel();
        }

        private void populatePanel2WithTileEditor()
        {
            int d = Tile.tilesize / 2;
            var tp = splitContainer3.Panel2;
            tp.Controls.Clear();

            if (paintTile != null)
            {
                if (paintTile is AutoTile94)
                {
                    var at = paintTile as AutoTile94;
                    Label lbl = new Label();
                    lbl.Text = "Edit Autotile";
                    lbl.Location = new Point(0, 0);
                    tp.Controls.Add(lbl);
                    for (int i = 0; i < 9; i++)
                    {
                        Rectangle r = AutoTile94.tileToRawTileIndex[i];
                        PictureBox pb = new PictureBox();
                        pb.Location = new Point(r.X / d * 20, r.Y / d * 20 + 30);
                        pb.Size = new Size(r.Width + 6, r.Height + 6);
                        pb.Image = at.rawtiles[i].GetBitmap(0, 0);
                        pb.Tag = new KeyValuePair<AutoTile94, int>(at, i);
                        pb.Click += new EventHandler((o, ev) =>
                        {
                            PictureBox thepb = (PictureBox)o;
                            KeyValuePair<AutoTile94, int> theat = (KeyValuePair<AutoTile94, int>)thepb.Tag;
                            thepb.Image = selectedBasicTile.GetBitmap(0, 0);
                            theat.Key.rawtiles[theat.Value] = selectedBasicTile;
                        });
                        tp.Controls.Add(pb);
                    }

                    for (int i = 9; i < 13; i++)
                    {
                        Rectangle r = AutoTile94.tileToRawTileIndex[i];
                        PictureBox pb = new PictureBox();
                        pb.Location = new Point(r.X / d * 20 + 150, r.Y / d * 20 + 30);
                        pb.Size = new Size(r.Width + 6, r.Height + 6);
                        pb.Image = at.rawtiles[i].GetBitmap(0, 0);
                        pb.Tag = new KeyValuePair<AutoTile94, int>(at, i);
                        pb.Click += new EventHandler((o, ev) =>
                        {
                            PictureBox thepb = (PictureBox)o;
                            KeyValuePair<AutoTile94, int> theat = (KeyValuePair<AutoTile94, int>)thepb.Tag;
                            if (selectedBasicTile == null) { return; }
                            thepb.Image = selectedBasicTile.GetBitmap(0, 0);
                            theat.Key.rawtiles[theat.Value] = selectedBasicTile;
                        });
                        tp.Controls.Add(pb);
                    }

                }
                else if (paintTile is AutoTile12)
                {
                    var at = paintTile as AutoTile12;
                    Label lbl = new Label();
                    lbl.Text = "Edit Autotile";
                    lbl.Location = new Point(0, 0);
                    tp.Controls.Add(lbl);
                    for (int i = 0; i < 11; i++)
                    {
                        Rectangle r = AutoTile12.tileToRawTileIndex[i];
                        PictureBox pb = new PictureBox();
                        pb.Location = new Point(r.X / d * 20, r.Y / d * 20 + 30);
                        pb.Size = new Size(r.Width + 6, r.Height + 6);
                        pb.Image = at.rawtiles[i].GetBitmap(0, 0);
                        pb.Tag = new KeyValuePair<AutoTile12, int>(at, i);
                        pb.Click += new EventHandler((o, ev) =>
                        {
                            PictureBox thepb = (PictureBox)o;
                            KeyValuePair<AutoTile12, int> theat = (KeyValuePair<AutoTile12, int>)thepb.Tag;
                            if (selectedBasicTile == null) { return; }
                            thepb.Image = selectedBasicTile.GetBitmap(0, 0);
                            theat.Key.rawtiles[theat.Value] = selectedBasicTile;
                        });
                        tp.Controls.Add(pb);
                    }
                }
                else if (paintTile is SimpleTile)
                {
                    var st = paintTile as SimpleTile;

                    for (int i = 0; i < 4; i++)
                    {
                        Rectangle r = AutoTile94.tileToRawTileIndex[i];
                        PictureBox pb = new PictureBox();
                        pb.Location = new Point(r.X / d * 20, r.Y / d * 20 + 30);
                        pb.Size = new Size(r.Width + 6, r.Height + 6);
                        pb.Image = st.bmp[i];
                        pb.Tag = new KeyValuePair<SimpleTile, int>(st, i);
                        pb.Click += new EventHandler((o, ev) =>
                        {
                            PictureBox thepb = (PictureBox)o;
                            KeyValuePair<SimpleTile, int> theat = (KeyValuePair<SimpleTile, int>)thepb.Tag;
                            thepb.Image = selectedBasicTile.GetBitmap(0, 0);
                            theat.Key.bmp[theat.Value] = selectedBasicTile.bmp[theat.Value];
                        });
                        tp.Controls.Add(pb);
                    }
                }
            }

            tp.Refresh();
        }


        private void btn_savetiles_Click(object sender, EventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.ShowDialog();
            if (string.IsNullOrEmpty(sfd.FileName))
            {
                return;
            }
            for (int i = 256; i < 8192; i *= 2)
            {
                using (FormattedWriter tiles = new FormattedWriter(sfd.FileName + ".tiles"))
                {
                    bool bigenough = true;
                    List<BasicTileFormat> tf = new List<BasicTileFormat>();
                    using (Bitmap bmp = new Bitmap(i, i))
                    {
                        int curx = 0;
                        int cury = 0;
                        using (Graphics g = Graphics.FromImage(bmp))
                        {
                            int count = 0;
                            tiles.Write(flow_tiles.Controls.Count);
                            foreach (Control ctl in flow_tiles.Controls)
                            {
                                if (ctl.Tag is SimpleTile)
                                {
                                    tiles.Write(TileType.SIMPLE);
                                    var st = ctl.Tag as SimpleTile;
                                    var res = InsertSimpleTile(tf, bmp, ref curx, ref cury, g, ref count, st);
                                    if (!res)
                                    {
                                        bigenough = false;
                                        break;
                                    }
                                    tiles.Write(st.num);
                                }
                                else if (ctl.Tag is AutoTile)
                                {
                                    var at = ctl.Tag as AutoTile;
                                    tiles.Write(at.Type);

                                    List<int> atfs = new List<int>();

                                    foreach (var st in at.rawtiles)
                                    {
                                        var res = InsertSimpleTile(tf, bmp, ref curx, ref cury, g, ref count, st);
                                        if (!res)
                                        {
                                            bigenough = false;
                                            break;
                                        }
                                        atfs.Add(st.num);
                                    }

                                    AutoTileFormat atf = new AutoTileFormat();
                                    atf.numOfTiles = atfs.Count;
                                    atf.basictiles = atfs.ToArray();
                                    tiles.Write(atf);
                                }
                            }
                        }

                        if (bigenough)
                        {
                            bmp.Save(sfd.FileName + ".png", ImageFormat.Png);
                            using (FormattedWriter basictiles = new FormattedWriter(sfd.FileName + ".basictiles"))
                            {
                                basictiles.Write((int)tf.Count);
                                foreach (var tile in tf)
                                {
                                    basictiles.Write(tile);
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }


        private static bool InsertSimpleTile(List<BasicTileFormat> tf, Bitmap bmp, ref int curx, ref int cury, Graphics g, ref int count, SimpleTile st)
        {
            st.num = count++;

            if (curx + st.bmp.Length * Tile.tilesize > bmp.Width)
            {
                curx = 0;
                cury += Tile.tilesize;

                if (cury >= bmp.Height)
                {
                    return false;
                }
            }

            tf.Add(new BasicTileFormat()
            {
                numframes = st.bmp.Length,
                width = (float)Tile.tilesize / bmp.Size.Width,
                height = (float)Tile.tilesize / bmp.Size.Height,
                x1 = (float)curx / bmp.Size.Width,
                y1 = ((float)cury + Tile.tilesize) / bmp.Size.Height,
                x2 = ((float)curx + Tile.tilesize) / bmp.Size.Width,
                y2 = ((float)cury + Tile.tilesize) / bmp.Size.Height,
                x3 = ((float)curx + Tile.tilesize) / bmp.Size.Width,
                y3 = (float)cury / bmp.Size.Height,
                x4 = (float)curx / bmp.Size.Width,
                y4 = (float)cury / bmp.Size.Height,
            });

            foreach (Bitmap frame in st.bmp)
            {
                g.DrawImage(frame, curx, cury);
                curx += Tile.tilesize;
            }

            return true;
        }


        private void btn_makefont_Click(object sender, EventArgs e)
        {
            Font f = new Font(FontFamily.GenericMonospace, 10);
            FontWindow fw = new FontWindow(f);
            fw.Show();
        }

        private void btn_loadtiles_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.ShowDialog();
            if (string.IsNullOrEmpty(ofd.FileName))
            {
                return;
            }
            string basename = Path.Combine(Path.GetDirectoryName(ofd.FileName), Path.GetFileNameWithoutExtension(ofd.FileName));
            string basictilesname = basename + ".basictiles";
            string tilesname = basename + ".tiles";
            string pngname = basename + ".png";
            if (!File.Exists(basictilesname) || !File.Exists(tilesname))
            {
                return;
            }

            using (Bitmap bmp = new Bitmap(pngname))
            {
                using (FormattedReader tiles = new FormattedReader(tilesname))
                using (FormattedReader basictiles = new FormattedReader(basictilesname))
                {
                    var btff = basictiles.Read<BasicTilesFileFormat>();
                    var simpletiles = btff.tiles.Select(x => new SimpleTile(x, bmp)).ToArray();
                    //foreach (var st in simpletiles)
                    //{
                    //    AddBasicTile(st);
                    //}

                    var tff = tiles.Read<TilesFileFormat>();
                    foreach (var tile in tff.tiles)
                    {
                        if (tile.type == TileType.SIMPLE)
                        {
                            AddSimpleTile(simpletiles[tile.simp[0].basictile]);
                        }
                        else if (tile.type == TileType.AUTOTILE12)
                        {
                            AutoTile12 at = new AutoTile12(simpletiles, tile.auto[0].basictiles);
                            AddAutotile12(at, at);
                        }
                        else if (tile.type == TileType.AUTOTILE94)
                        {
                            AutoTile94 at = new AutoTile94(simpletiles, tile.auto[0].basictiles);
                            AddAutotile94(at, at);
                        }
                    }
                }
            }
        }

        private void btn_makeCharacter_Click(object sender, EventArgs e)
        {
            CharacterMaker cm = new CharacterMaker();
            cm.Show();
        }


    }
}
