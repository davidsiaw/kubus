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

        Dictionary<int, Bitmap> tileCache = new Dictionary<int, Bitmap>();

        public IEnumerable<Tuple<byte, SimpleTile>> GetTiles()
        {
            // fill the cache
            for (uint tick = 0; tick < 4; tick++)
                for (int i = 0; i < 256; i++)
                {
                    GetBitmap((byte)i, tick);
                }
            HashSet<byte> validSurrounds = new HashSet<byte>();
            foreach (var kvpair in tileCache)
            {
                byte sur;
                int tick;
                GetSurroundingAndTickFromKey(kvpair.Key, out sur, out tick);
                validSurrounds.Add(sur);
            }
            foreach (var validSurround in validSurrounds)
            {
                SimpleTile st = new SimpleTile(new Bitmap(Tile.tilesize, Tile.tilesize));
                for (uint i = 0; i < 4; i++)
                {
                    st.bmp[i] = GetBitmap(validSurround, i);
                }
                yield return new Tuple<byte, SimpleTile>(validSurround, st);
            }
        }

        public static int MakeKeyFromSurroundingAndTick(byte surroundings, uint tick)
        {
            int key = surroundings | (int)((tick % 4) << 8);
            return key;
        }

        public static void GetSurroundingAndTickFromKey(int key, out byte surrounding, out int tick)
        {
            surrounding = (byte)(key & 0xff);
            tick = key >> 8;
        }

        protected Bitmap GetBitmap(byte surroundings, uint tick, Rectangle[] corner, byte[,] posAndMaskToTile)
        {
            if ((surroundings & 0xf0) == 0)
            {
                surroundings &= 0xf0;
            }
            int key = MakeKeyFromSurroundingAndTick(surroundings, tick);
            if (!tileCache.ContainsKey(key))
            {
                Bitmap b = new Bitmap(Tile.tilesize, Tile.tilesize);
                tileCache[key] = b;
                using (Graphics g = Graphics.FromImage(b))
                {
                    g.DrawImage(
                        rawtiles[posAndMaskToTile[
                            (int)SubTilePos.TopRight,
                            getCornerMask(SubTilePos.TopRight, surroundings)]].GetBitmap(surroundings, tick),
                        corner[(int)SubTilePos.TopRight],
                        corner[(int)SubTilePos.TopRight],
                        GraphicsUnit.Pixel);

                    g.DrawImage(
                        rawtiles[posAndMaskToTile[
                            (int)SubTilePos.BottomRight,
                            getCornerMask(SubTilePos.BottomRight, surroundings)]].GetBitmap(surroundings, tick),
                        corner[(int)SubTilePos.BottomRight],
                        corner[(int)SubTilePos.BottomRight],
                        GraphicsUnit.Pixel);

                    g.DrawImage(
                        rawtiles[posAndMaskToTile[
                            (int)SubTilePos.BottomLeft,
                            getCornerMask(SubTilePos.BottomLeft, surroundings)]].GetBitmap(surroundings, tick),
                        corner[(int)SubTilePos.BottomLeft],
                        corner[(int)SubTilePos.BottomLeft],
                        GraphicsUnit.Pixel);

                    g.DrawImage(
                        rawtiles[posAndMaskToTile[
                            (int)SubTilePos.TopLeft,
                            getCornerMask(SubTilePos.TopLeft, surroundings)]].GetBitmap(surroundings, tick),
                        corner[(int)SubTilePos.TopLeft],
                        corner[(int)SubTilePos.TopLeft],
                        GraphicsUnit.Pixel);
                }
            }
            return tileCache[key];
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

        public AutoTile12(SimpleTile[] simpletiles, AutoTileFormatEntry[] autoTileFormatEntry)
            : base(11)
        {
            Dictionary<byte, SimpleTile> surrounds = new Dictionary<byte, SimpleTile>();
            foreach (var atfe in autoTileFormatEntry)
            {
                surrounds[atfe.surround] = simpletiles[atfe.basictile];
            }
            rawtiles[0] = surrounds[0xc4];
            rawtiles[1] = surrounds[0xdc];
            rawtiles[2] = surrounds[0x98];
            rawtiles[3] = surrounds[0xb9];
            rawtiles[4] = surrounds[0x31];
            rawtiles[5] = surrounds[0x73];
            rawtiles[6] = surrounds[0x62];
            rawtiles[7] = surrounds[0xe6];
            rawtiles[8] = surrounds[0xff];
            rawtiles[9] = surrounds[0xf0];
            rawtiles[10] = surrounds[0];

        }

        public override Bitmap GetBitmap(byte surroundings, uint tick)
        {
            return GetBitmap(surroundings, tick, corner, posAndMaskToTile);
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

        public override Bitmap GetBitmap(byte surroundings, uint tick)
        {
            return GetBitmap(surroundings, tick, corner, posAndMaskToTile);
        }

    }
}
