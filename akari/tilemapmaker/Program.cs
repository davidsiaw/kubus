using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;
using System.IO;
using System.Drawing;
using System.Runtime.InteropServices;

namespace tilemapmaker
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            //Bitmap b = new Bitmap(@"D:\gcc\akari\res\boy.png");

            

            //Bitmap b2 = new Bitmap(b.Width * 2, b.Height * 2);
            //using (Graphics g = Graphics.FromImage(b2))
            //{
            //    g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
            //    g.DrawImage(b, 0, 0, b2.Width, b2.Height);
            //}

            //var bits = b2.LockBits(new Rectangle(0, 0, b2.Width, b2.Height), System.Drawing.Imaging.ImageLockMode.ReadWrite, System.Drawing.Imaging.PixelFormat.Format32bppArgb);

            //var green = Marshal.ReadInt32(bits.Scan0);

            //for (int x = 0; x < b2.Width; x++)
            //{
            //    for (int y = 0; y < b2.Height; y++)
            //    {
            //        var index = x * 4 + y * b2.Width * 4;
            //        var col = Marshal.ReadInt32(bits.Scan0, index);
            //        if (col == green)
            //        {
            //            Marshal.WriteInt32(bits.Scan0, index, 0);
            //        }
            //    }
            //}
            //b2.UnlockBits(bits);

            //b2.Save(@"D:\gcc\akari\res\boy2.png");

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
