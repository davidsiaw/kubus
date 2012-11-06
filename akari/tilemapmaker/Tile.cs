using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace tilemapmaker
{
    public abstract class Tile
    {
        public const int tilesize = 32;
        public abstract Bitmap GetBitmap(byte surroundings, uint tick);

        byte isTileSame(Tile[, ,] tilemap, int x, int y, int z)
        {
            if (x >= tilemap.GetLength(0) || x < 0)
            {
                return 1;
            }
            if (y >= tilemap.GetLength(0) || y < 0)
            {
                return 1;
            }
            return this == tilemap[x, y, z] ? (byte)1 : (byte)0;
        }

        public byte Surroundings(Tile[, ,] tilemap, int x, int y, int z)
        {
            return (byte)(
                (isTileSame(tilemap, x+1, y-1, z) << 0) |
                (isTileSame(tilemap, x+1, y+1, z) << 1) |
                (isTileSame(tilemap, x-1, y+1, z) << 2) |
                (isTileSame(tilemap, x-1, y-1, z) << 3) |
                (isTileSame(tilemap, x, y-1, z) << 4) |
                (isTileSame(tilemap, x+1, y, z) << 5) |
                (isTileSame(tilemap, x, y+1, z) << 6) |
                (isTileSame(tilemap, x-1, y, z) << 7)
                );
        }
    }

    public class SimpleTile : Tile
    {
        public SimpleTile(Bitmap bmp)
        {
            for (int i = 0; i < 4; i++)
            {
                this.bmp[i] = bmp;
            }
        }

        public SimpleTile(BasicTileFormat tile, Bitmap png)
        {
            int width = (int)(tile.width * png.Width);
            int height = (int)(tile.height * png.Height);
            int left = (int)(tile.x1 * png.Width);
            int top = (int)(tile.y3* png.Height);

            for (int i = 0; i < 4; i++)
            {
                Bitmap b = new Bitmap(width, height);
                using (Graphics g = Graphics.FromImage(b))
                {
                    g.DrawImage(png, new Rectangle(0, 0, width, height), new Rectangle(left + i * width, top, width, height), GraphicsUnit.Pixel);
                }
                this.bmp[i] = b;
            }
        }

        public int num;

        public Bitmap[] bmp = new Bitmap[4];

        public override Bitmap GetBitmap(byte surroundings, uint tick)
        {
            return bmp[tick % bmp.Length];
        }
    }

    public enum SubTilePos
    {
        TopRight,
        BottomRight,
        BottomLeft,
        TopLeft,
    }

    public abstract class AutoTile : Tile
    {
        public AutoTile(int rawtilesize)
        {
            rawtiles = new SimpleTile[rawtilesize];
        }

        public readonly SimpleTile[] rawtiles;

        public abstract TileType Type { get; }

        public static byte getCornerMask(SubTilePos pos, byte surrounding)
        {
            switch (pos)
            {
                case SubTilePos.TopRight:
                    return (byte)(((surrounding >> 3) & 6) | (surrounding & 1));
                case SubTilePos.BottomRight:
                    return (byte)(((surrounding >> 4) & 6) | ((surrounding >> 1) & 1));
                case SubTilePos.BottomLeft:
                    return (byte)(((surrounding >> 5) & 6) | ((surrounding >> 2) & 1));
                case SubTilePos.TopLeft:
                    return (byte)(((surrounding >> 3) & 1) | ((surrounding >> 2) & 4) | ((surrounding >> 6) & 2));
            }
            throw new Exception("invalid pos value: " + pos);
        }

        struct AutoTileSep
        {
            public byte tr;
            public byte br;
            public byte tl;
            public byte bl;

            uint combine
            {
                get
                {
                    return (uint)((tr << 24) | (br << 16) | (tl << 8) | bl);
                }
            }

            public override bool Equals(object obj)
            {
                if (obj is AutoTileSep)
                {
                    return combine == ((AutoTileSep)obj).combine;
                }
                return false;
            }

            public override int GetHashCode()
            {
                return combine.GetHashCode();
            }
        }

        Dictionary<AutoTileSep, SimpleTile> bitmapCache = new Dictionary<AutoTileSep, SimpleTile>();
        Dictionary<byte, AutoTileSep> tileCache = new Dictionary<byte, AutoTileSep>();

        public Tuple<Tuple<byte, SimpleTile>[], SimpleTile[]> GetTiles()
        {
            // fill the cache
            for (uint tick = 0; tick < 4; tick++)
                for (int i = 0; i < 256; i++)
                {
                    GetBitmap((byte)i, tick);
                }

            var kvpairs = bitmapCache.ToArray();

            var surroundToIdx = tileCache.Select(x => new Tuple<byte, SimpleTile>(x.Key, bitmapCache[x.Value])).ToArray();
            return new Tuple<Tuple<byte, SimpleTile>[], SimpleTile[]>(surroundToIdx, kvpairs.Select(x => x.Value).ToArray());

        }

        protected Bitmap GetBitmap(byte surroundings, uint tick, Rectangle[] corner, byte[,] posAndMaskToTile)
        {
            if ((surroundings & 0xf0) == 0)
            {
                surroundings &= 0xf0;
            }

            tick %= 4;

            var ats = new AutoTileSep()
            {
                tr = posAndMaskToTile[
                        (int)SubTilePos.TopRight,
                        getCornerMask(SubTilePos.TopRight, surroundings)],
                tl = posAndMaskToTile[
                        (int)SubTilePos.TopLeft,
                        getCornerMask(SubTilePos.TopLeft, surroundings)],
                br = posAndMaskToTile[
                        (int)SubTilePos.BottomRight,
                        getCornerMask(SubTilePos.BottomRight, surroundings)],
                bl = posAndMaskToTile[
                        (int)SubTilePos.BottomLeft,
                        getCornerMask(SubTilePos.BottomLeft, surroundings)]
            };

            if (!tileCache.ContainsKey(surroundings))
            {
                tileCache[surroundings] = ats;
            }

            if (!bitmapCache.ContainsKey(ats))
            {
                bitmapCache[ats] = new SimpleTile(null);
            }

            if (bitmapCache[ats].bmp[tick] == null)
            {
                Bitmap b = new Bitmap(Tile.tilesize, Tile.tilesize);
                using (Graphics g = Graphics.FromImage(b))
                {
                    g.DrawImage(
                        rawtiles[ats.tr].GetBitmap(surroundings, tick),
                        corner[(int)SubTilePos.TopRight],
                        corner[(int)SubTilePos.TopRight],
                        GraphicsUnit.Pixel);

                    g.DrawImage(
                        rawtiles[ats.br].GetBitmap(surroundings, tick),
                        corner[(int)SubTilePos.BottomRight],
                        corner[(int)SubTilePos.BottomRight],
                        GraphicsUnit.Pixel);

                    g.DrawImage(
                        rawtiles[ats.bl].GetBitmap(surroundings, tick),
                        corner[(int)SubTilePos.BottomLeft],
                        corner[(int)SubTilePos.BottomLeft],
                        GraphicsUnit.Pixel);

                    g.DrawImage(
                        rawtiles[ats.tl].GetBitmap(surroundings, tick),
                        corner[(int)SubTilePos.TopLeft],
                        corner[(int)SubTilePos.TopLeft],
                        GraphicsUnit.Pixel);
                }
                bitmapCache[ats].bmp[tick] = b;
            }

            return bitmapCache[tileCache[surroundings]].bmp[tick];
        }
    }

    // the 12 autotile
    public class AutoTile12 : AutoTile
    {

        static readonly byte[,] posAndMaskToTile = new byte[4, 8];
        static readonly Rectangle[] corner = new Rectangle[4];
        public static readonly Rectangle[] tileToRawTileIndex = new Rectangle[11];

        static AutoTile12()
        {
            posAndMaskToTile[0, 0] = 10; posAndMaskToTile[1, 0] = 10; posAndMaskToTile[2, 0] = 10; posAndMaskToTile[3, 0] = 10;
            posAndMaskToTile[0, 1] = 0; posAndMaskToTile[1, 1] = 2; posAndMaskToTile[2, 1] = 4; posAndMaskToTile[3, 1] = 6;
            posAndMaskToTile[0, 2] = 1; posAndMaskToTile[1, 2] = 3; posAndMaskToTile[2, 2] = 5; posAndMaskToTile[3, 2] = 7;
            posAndMaskToTile[0, 3] = 2; posAndMaskToTile[1, 3] = 4; posAndMaskToTile[2, 3] = 6; posAndMaskToTile[3, 3] = 0;
            posAndMaskToTile[0, 4] = 6; posAndMaskToTile[1, 4] = 0; posAndMaskToTile[2, 4] = 2; posAndMaskToTile[3, 4] = 4;
            posAndMaskToTile[0, 5] = 7; posAndMaskToTile[1, 5] = 1; posAndMaskToTile[2, 5] = 3; posAndMaskToTile[3, 5] = 5;
            posAndMaskToTile[0, 6] = 9; posAndMaskToTile[1, 6] = 9; posAndMaskToTile[2, 6] = 9; posAndMaskToTile[3, 6] = 9;
            posAndMaskToTile[0, 7] = 8; posAndMaskToTile[1, 7] = 8; posAndMaskToTile[2, 7] = 8; posAndMaskToTile[3, 7] = 8;

            int d = Tile.tilesize / 2;
            corner[0] = new Rectangle(d, 0, d, d);
            corner[1] = new Rectangle(d, d, d, d);
            corner[2] = new Rectangle(0, d, d, d);
            corner[3] = new Rectangle(0, 0, d, d);

            int t = Tile.tilesize;
            tileToRawTileIndex[0] = new Rectangle(t * 2, t * 1, t, t);
            tileToRawTileIndex[1] = new Rectangle(t * 2, t * 2, t, t);
            tileToRawTileIndex[2] = new Rectangle(t * 2, t * 3, t, t);
            tileToRawTileIndex[3] = new Rectangle(t * 1, t * 3, t, t);
            tileToRawTileIndex[4] = new Rectangle(t * 0, t * 3, t, t);
            tileToRawTileIndex[5] = new Rectangle(t * 0, t * 2, t, t);
            tileToRawTileIndex[6] = new Rectangle(t * 0, t * 1, t, t);
            tileToRawTileIndex[7] = new Rectangle(t * 1, t * 1, t, t);
            tileToRawTileIndex[8] = new Rectangle(t * 1, t * 2, t, t);

            tileToRawTileIndex[9] = new Rectangle(t * 2, t * 0, t, t);
            tileToRawTileIndex[10] = new Rectangle(t * 0, t * 0, t, t);
        }

        public AutoTile12() : base(11)
        {
            for (int i = 0; i < rawtiles.Length; i++)
            {
                rawtiles[i] = new SimpleTile(new Bitmap(Tile.tilesize, Tile.tilesize));
            }
        }

        public AutoTile12(SimpleTile[] simpletiles, int[] basicTiles)
            : base(11)
        {
            for (int i = 0; i < rawtiles.Length; i++)
            {
                rawtiles[i] = simpletiles[basicTiles[i]];
            }
        }

        public override Bitmap GetBitmap(byte surroundings, uint tick)
        {
            return GetBitmap(surroundings, tick, corner, posAndMaskToTile);
        }

        public override TileType Type
        {
            get { return TileType.AUTOTILE12; }
        }
    }

    // the 9-4 autotile
    public class AutoTile94 : AutoTile
    {

        static readonly byte[,] posAndMaskToTile = new byte[4, 8];
        static readonly Rectangle[] corner = new Rectangle[4];
        public static readonly Rectangle[] tileToRawTileIndex = new Rectangle[13];

        static AutoTile94()
        {
            posAndMaskToTile[0, 0] = 0; posAndMaskToTile[1, 0] = 2; posAndMaskToTile[2, 0] = 4; posAndMaskToTile[3, 0] = 6;
            posAndMaskToTile[0, 1] = 0; posAndMaskToTile[1, 1] = 2; posAndMaskToTile[2, 1] = 4; posAndMaskToTile[3, 1] = 6;
            posAndMaskToTile[0, 2] = 1; posAndMaskToTile[1, 2] = 3; posAndMaskToTile[2, 2] = 5; posAndMaskToTile[3, 2] = 7;
            posAndMaskToTile[0, 3] = 2; posAndMaskToTile[1, 3] = 4; posAndMaskToTile[2, 3] = 6; posAndMaskToTile[3, 3] = 0;
            posAndMaskToTile[0, 4] = 6; posAndMaskToTile[1, 4] = 0; posAndMaskToTile[2, 4] = 2; posAndMaskToTile[3, 4] = 4;
            posAndMaskToTile[0, 5] = 7; posAndMaskToTile[1, 5] = 1; posAndMaskToTile[2, 5] = 3; posAndMaskToTile[3, 5] = 5;
            posAndMaskToTile[0, 6] = 9; posAndMaskToTile[1, 6] = 10; posAndMaskToTile[2, 6] = 11; posAndMaskToTile[3, 6] = 12;
            posAndMaskToTile[0, 7] = 8; posAndMaskToTile[1, 7] = 8; posAndMaskToTile[2, 7] = 8; posAndMaskToTile[3, 7] = 8;

            int d = Tile.tilesize / 2;
            corner[0] = new Rectangle(d, 0, d, d);
            corner[1] = new Rectangle(d, d, d, d);
            corner[2] = new Rectangle(0, d, d, d);
            corner[3] = new Rectangle(0, 0, d, d);

            int t = Tile.tilesize;
            tileToRawTileIndex[0] = new Rectangle(t * 2, t * 0, t, t);
            tileToRawTileIndex[1] = new Rectangle(t * 2, t * 1, t, t);
            tileToRawTileIndex[2] = new Rectangle(t * 2, t * 2, t, t);
            tileToRawTileIndex[3] = new Rectangle(t * 1, t * 2, t, t);
            tileToRawTileIndex[4] = new Rectangle(t * 0, t * 2, t, t);
            tileToRawTileIndex[5] = new Rectangle(t * 0, t * 1, t, t);
            tileToRawTileIndex[6] = new Rectangle(t * 0, t * 0, t, t);
            tileToRawTileIndex[7] = new Rectangle(t * 1, t * 0, t, t);
            tileToRawTileIndex[8] = new Rectangle(t * 1, t * 1, t, t);

            tileToRawTileIndex[9] = new Rectangle(t * 1, t * 0, t, t);
            tileToRawTileIndex[10] = new Rectangle(t * 1, t * 1, t, t);
            tileToRawTileIndex[11] = new Rectangle(t * 0, t * 1, t, t);
            tileToRawTileIndex[12] = new Rectangle(t * 0, t * 0, t, t);
        }

        public AutoTile94() : base(13)
        {
            for (int i = 0; i < rawtiles.Length; i++)
            {
                rawtiles[i] = new SimpleTile(new Bitmap(Tile.tilesize, Tile.tilesize));
            }
        }


        public AutoTile94(SimpleTile[] simpletiles, int[] basicTiles)
            : base(13)
        {
            for (int i = 0; i < rawtiles.Length; i++)
            {
                rawtiles[i] = simpletiles[basicTiles[i]];
            }
        }

        public override Bitmap GetBitmap(byte surroundings, uint tick)
        {
            return GetBitmap(surroundings, tick, corner, posAndMaskToTile);
        }

        public override TileType Type
        {
            get { return TileType.AUTOTILE94; }
        }

    }
}
