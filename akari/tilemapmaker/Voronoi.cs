using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using vor_statep = System.IntPtr;
using System.Drawing;

namespace tilemapmaker
{
    class Voronoi : IDisposable
    {
        vor_statep state;
        public Voronoi()
        {
            state = vor_CreateState();
        }

        public Size Size
        {
            get
            {
                uint w, h;
                vor_GetDeviceSize(state, out w, out h);
                return new Size((int)w, (int)h);
            }
            set
            {
                vor_SetDeviceSize(state, (uint)value.Width, (uint)value.Height);
            }
        }

        public Point[] Points
        {
            set
            {
                vor_SetPoints(state, (uint)value.Length, Marshal.SizeOf(new Point()), value);
            }
        }

        public void CalculateDiagram()
        {
            vor_CalcDiagram(state);
        }

        public Bitmap GetDiagram()
        {
            Dictionary<int, int> colorDict = new Dictionary<int, int>();
            colorDict[-1] = 0x00ffffff;
            colorDict[0] = 0x00ff0000;
            colorDict[1] = 0x0000ff00;
            colorDict[2] = 0x000000ff;
            colorDict[3] = 0x00ff00ff;

            Bitmap b = new Bitmap(Size.Width, Size.Height, 4 * Size.Width, System.Drawing.Imaging.PixelFormat.Format32bppRgb, vor_GetIndexDiagram(state));

            var bd = b.LockBits(new Rectangle(0, 0, b.Width, b.Height), System.Drawing.Imaging.ImageLockMode.ReadWrite, System.Drawing.Imaging.PixelFormat.Format32bppRgb);


            for (int x = 0; x < b.Width; x++)
            {
                for (int y = 0; y < b.Height; y++)
                {
                    int idx = Marshal.ReadInt32(bd.Scan0, x * 4 + y * 4 * b.Width);
                    Marshal.WriteInt32(bd.Scan0, x * 4 + y * 4 * b.Width, colorDict[idx%4]);
                }
            }

            b.UnlockBits(bd);
            return b;
        }
    
        [StructLayout(LayoutKind.Sequential)]
        public struct Point
        {
            public Point(float x, float y) { this.x = x; this.y = y; }
            public float x, y;
        }

        [DllImport("libvoronoidll")]
        extern static vor_statep vor_CreateState();
        [DllImport("libvoronoidll")]
        extern static void vor_DestroyState(ref vor_statep state);
        [DllImport("libvoronoidll")]
        extern static void vor_SetDeviceSize(vor_statep state, uint width, uint height);
        [DllImport("libvoronoidll")]
        extern static void vor_GetDeviceSize(vor_statep state, out uint width, out uint height);
        [DllImport("libvoronoidll")]
        extern static void vor_SetPoints(vor_statep state, uint num, int stride, [MarshalAs(UnmanagedType.LPArray)] Point[] data);
        [DllImport("libvoronoidll")]
        extern static void vor_CalcDiagram(vor_statep state);
        [DllImport("libvoronoidll")]
        extern static IntPtr vor_GetIndexDiagram(vor_statep state);

        public void Dispose()
        {
            vor_DestroyState(ref state);
        }
    }
}