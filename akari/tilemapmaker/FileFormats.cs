using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BlueBlocksLib.FileAccess;
using System.Runtime.InteropServices;

namespace tilemapmaker
{
    enum TileType
    {
        SIMPLE,
        AUTOTILE,
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct BasicTileFormat
    {
        public int numframes;
        public float width;
        public float height;

        //texcoords
        public float x1, y1;
        public float x2, y2;
        public float x3, y3;
        public float x4, y4;

    }

    [StructLayout(LayoutKind.Sequential)]
    struct TileEnvelope
    {
        public TileType type;

        public int GetSimpleTile()
        {
            if (type == TileType.SIMPLE)
            {
                return 1;
            }
            return 0;
        }

        public int GetAutoTile()
        {
            if (type == TileType.AUTOTILE)
            {
                return 1;
            }
            return 0;
        }

        [ArraySize("GetSimpleTile()")]
        public SimpleTileFormat[] simp;

        [ArraySize("GetAutoTile()")]
        public AutoTileFormat[] auto;
    }

    [StructLayout(LayoutKind.Sequential)]
    struct SimpleTileFormat
    {
        public int basictile;
    }

    [StructLayout(LayoutKind.Sequential)]
    struct AutoTileFormat
    {
        public int numOfTiles;

        [ArraySize("numOfTiles")]
        public AutoTileFormatEntry[] entries;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct AutoTileFormatEntry
    {
        public byte surround;
        public int basictile;
    }

    [StructLayout(LayoutKind.Sequential)]
    struct BasicTilesFileFormat
    {
        public int numOfTiles;

        [ArraySize("numOfTiles")]
        public BasicTileFormat[] tiles;
    }

    [StructLayout(LayoutKind.Sequential)]
    struct TilesFileFormat
    {
        public int numOfTiles;

        [ArraySize("numOfTiles")]
        public TileEnvelope[] tiles;
    }

}
