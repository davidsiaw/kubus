namespace tilemapmaker
{
    partial class CharacterMaker
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btn_loadPalette = new System.Windows.Forms.Button();
            this.btn_savePalette = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.btn_loadsprite = new System.Windows.Forms.Button();
            this.btn_save = new System.Windows.Forms.Button();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.pixelEditor1 = new tilemapmaker.PixelEditor();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.splitContainer3 = new System.Windows.Forms.SplitContainer();
            this.mode_punchPaste = new System.Windows.Forms.RadioButton();
            this.mode_paste = new System.Windows.Forms.RadioButton();
            this.pe_clipboard = new tilemapmaker.PixelEditor();
            this.mode_copy = new System.Windows.Forms.RadioButton();
            this.num_rectanglesize = new System.Windows.Forms.NumericUpDown();
            this.mode_rectangle = new System.Windows.Forms.RadioButton();
            this.num_circlesize = new System.Windows.Forms.NumericUpDown();
            this.mode_circle = new System.Windows.Forms.RadioButton();
            this.mode_dot = new System.Windows.Forms.RadioButton();
            this.splitContainer4 = new System.Windows.Forms.SplitContainer();
            this.pixelEditor4 = new tilemapmaker.PixelEditor();
            this.pixelEditor3 = new tilemapmaker.PixelEditor();
            this.pixelEditor2 = new tilemapmaker.PixelEditor();
            this.btn_rotateCW = new System.Windows.Forms.Button();
            this.btn_rotateCCW = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pixelEditor1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer3)).BeginInit();
            this.splitContainer3.Panel1.SuspendLayout();
            this.splitContainer3.Panel2.SuspendLayout();
            this.splitContainer3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pe_clipboard)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_rectanglesize)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_circlesize)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer4)).BeginInit();
            this.splitContainer4.Panel1.SuspendLayout();
            this.splitContainer4.Panel2.SuspendLayout();
            this.splitContainer4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pixelEditor4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pixelEditor3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pixelEditor2)).BeginInit();
            this.SuspendLayout();
            // 
            // btn_loadPalette
            // 
            this.btn_loadPalette.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.btn_loadPalette.Location = new System.Drawing.Point(0, 160);
            this.btn_loadPalette.Name = "btn_loadPalette";
            this.btn_loadPalette.Size = new System.Drawing.Size(531, 23);
            this.btn_loadPalette.TabIndex = 2;
            this.btn_loadPalette.Text = "Load Palette";
            this.btn_loadPalette.UseVisualStyleBackColor = true;
            this.btn_loadPalette.Click += new System.EventHandler(this.btn_loadPalette_Click);
            // 
            // btn_savePalette
            // 
            this.btn_savePalette.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.btn_savePalette.Location = new System.Drawing.Point(0, 183);
            this.btn_savePalette.Name = "btn_savePalette";
            this.btn_savePalette.Size = new System.Drawing.Size(531, 23);
            this.btn_savePalette.TabIndex = 3;
            this.btn_savePalette.Text = "Save Palette";
            this.btn_savePalette.UseVisualStyleBackColor = true;
            this.btn_savePalette.Click += new System.EventHandler(this.btn_savePalette_Click);
            // 
            // panel1
            // 
            this.panel1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel1.Location = new System.Drawing.Point(0, 491);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(80, 32);
            this.panel1.TabIndex = 5;
            // 
            // btn_loadsprite
            // 
            this.btn_loadsprite.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.btn_loadsprite.Location = new System.Drawing.Point(0, 477);
            this.btn_loadsprite.Name = "btn_loadsprite";
            this.btn_loadsprite.Size = new System.Drawing.Size(294, 23);
            this.btn_loadsprite.TabIndex = 7;
            this.btn_loadsprite.Text = "Load Sprites";
            this.btn_loadsprite.UseVisualStyleBackColor = true;
            this.btn_loadsprite.Click += new System.EventHandler(this.btn_loadsprite_Click);
            // 
            // btn_save
            // 
            this.btn_save.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.btn_save.Location = new System.Drawing.Point(0, 500);
            this.btn_save.Name = "btn_save";
            this.btn_save.Size = new System.Drawing.Size(294, 23);
            this.btn_save.TabIndex = 8;
            this.btn_save.Text = "Save Sprite";
            this.btn_save.UseVisualStyleBackColor = true;
            this.btn_save.Click += new System.EventHandler(this.btn_save_Click);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.pixelEditor1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.splitContainer2);
            this.splitContainer1.Size = new System.Drawing.Size(1250, 733);
            this.splitContainer1.SplitterDistance = 715;
            this.splitContainer1.TabIndex = 9;
            // 
            // pixelEditor1
            // 
            this.pixelEditor1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pixelEditor1.drawMouseUnderlay = null;
            this.pixelEditor1.highlightheight = 0;
            this.pixelEditor1.highlightwidth = 0;
            this.pixelEditor1.Location = new System.Drawing.Point(0, 0);
            this.pixelEditor1.Name = "pixelEditor1";
            this.pixelEditor1.ShowTileArea = false;
            this.pixelEditor1.Size = new System.Drawing.Size(715, 733);
            this.pixelEditor1.TabIndex = 0;
            this.pixelEditor1.TabStop = false;
            // 
            // splitContainer2
            // 
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Name = "splitContainer2";
            this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.Controls.Add(this.splitContainer3);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.pixelEditor2);
            this.splitContainer2.Panel2.Controls.Add(this.btn_loadPalette);
            this.splitContainer2.Panel2.Controls.Add(this.btn_savePalette);
            this.splitContainer2.Size = new System.Drawing.Size(531, 733);
            this.splitContainer2.SplitterDistance = 523;
            this.splitContainer2.TabIndex = 0;
            // 
            // splitContainer3
            // 
            this.splitContainer3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer3.Location = new System.Drawing.Point(0, 0);
            this.splitContainer3.Name = "splitContainer3";
            // 
            // splitContainer3.Panel1
            // 
            this.splitContainer3.Panel1.Controls.Add(this.btn_rotateCCW);
            this.splitContainer3.Panel1.Controls.Add(this.btn_rotateCW);
            this.splitContainer3.Panel1.Controls.Add(this.mode_punchPaste);
            this.splitContainer3.Panel1.Controls.Add(this.mode_paste);
            this.splitContainer3.Panel1.Controls.Add(this.pe_clipboard);
            this.splitContainer3.Panel1.Controls.Add(this.mode_copy);
            this.splitContainer3.Panel1.Controls.Add(this.num_rectanglesize);
            this.splitContainer3.Panel1.Controls.Add(this.mode_rectangle);
            this.splitContainer3.Panel1.Controls.Add(this.num_circlesize);
            this.splitContainer3.Panel1.Controls.Add(this.mode_circle);
            this.splitContainer3.Panel1.Controls.Add(this.mode_dot);
            this.splitContainer3.Panel1.Controls.Add(this.panel1);
            this.splitContainer3.Panel1MinSize = 80;
            // 
            // splitContainer3.Panel2
            // 
            this.splitContainer3.Panel2.Controls.Add(this.splitContainer4);
            this.splitContainer3.Size = new System.Drawing.Size(531, 523);
            this.splitContainer3.SplitterDistance = 80;
            this.splitContainer3.TabIndex = 0;
            // 
            // mode_punchPaste
            // 
            this.mode_punchPaste.Appearance = System.Windows.Forms.Appearance.Button;
            this.mode_punchPaste.AutoSize = true;
            this.mode_punchPaste.Dock = System.Windows.Forms.DockStyle.Top;
            this.mode_punchPaste.Location = new System.Drawing.Point(0, 252);
            this.mode_punchPaste.Name = "mode_punchPaste";
            this.mode_punchPaste.Size = new System.Drawing.Size(80, 23);
            this.mode_punchPaste.TabIndex = 14;
            this.mode_punchPaste.TabStop = true;
            this.mode_punchPaste.Text = "Punch Paste";
            this.mode_punchPaste.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.mode_punchPaste.UseVisualStyleBackColor = true;
            this.mode_punchPaste.CheckedChanged += new System.EventHandler(this.mode_punchPaste_CheckedChanged);
            // 
            // mode_paste
            // 
            this.mode_paste.Appearance = System.Windows.Forms.Appearance.Button;
            this.mode_paste.AutoSize = true;
            this.mode_paste.Dock = System.Windows.Forms.DockStyle.Top;
            this.mode_paste.Location = new System.Drawing.Point(0, 229);
            this.mode_paste.Name = "mode_paste";
            this.mode_paste.Size = new System.Drawing.Size(80, 23);
            this.mode_paste.TabIndex = 13;
            this.mode_paste.TabStop = true;
            this.mode_paste.Text = "Tattoo Paste";
            this.mode_paste.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.mode_paste.UseVisualStyleBackColor = true;
            this.mode_paste.CheckedChanged += new System.EventHandler(this.mode_paste_CheckedChanged);
            // 
            // pe_clipboard
            // 
            this.pe_clipboard.Dock = System.Windows.Forms.DockStyle.Top;
            this.pe_clipboard.drawMouseUnderlay = null;
            this.pe_clipboard.highlightheight = 0;
            this.pe_clipboard.highlightwidth = 0;
            this.pe_clipboard.Location = new System.Drawing.Point(0, 132);
            this.pe_clipboard.Name = "pe_clipboard";
            this.pe_clipboard.ShowTileArea = false;
            this.pe_clipboard.Size = new System.Drawing.Size(80, 97);
            this.pe_clipboard.TabIndex = 12;
            this.pe_clipboard.TabStop = false;
            // 
            // mode_copy
            // 
            this.mode_copy.Appearance = System.Windows.Forms.Appearance.Button;
            this.mode_copy.AutoSize = true;
            this.mode_copy.Dock = System.Windows.Forms.DockStyle.Top;
            this.mode_copy.Location = new System.Drawing.Point(0, 109);
            this.mode_copy.Name = "mode_copy";
            this.mode_copy.Size = new System.Drawing.Size(80, 23);
            this.mode_copy.TabIndex = 11;
            this.mode_copy.TabStop = true;
            this.mode_copy.Text = "Copy";
            this.mode_copy.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.mode_copy.UseVisualStyleBackColor = true;
            this.mode_copy.CheckedChanged += new System.EventHandler(this.mode_copy_CheckedChanged);
            // 
            // num_rectanglesize
            // 
            this.num_rectanglesize.Dock = System.Windows.Forms.DockStyle.Top;
            this.num_rectanglesize.Location = new System.Drawing.Point(0, 89);
            this.num_rectanglesize.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.num_rectanglesize.Name = "num_rectanglesize";
            this.num_rectanglesize.Size = new System.Drawing.Size(80, 20);
            this.num_rectanglesize.TabIndex = 10;
            this.num_rectanglesize.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // mode_rectangle
            // 
            this.mode_rectangle.Appearance = System.Windows.Forms.Appearance.Button;
            this.mode_rectangle.AutoSize = true;
            this.mode_rectangle.Dock = System.Windows.Forms.DockStyle.Top;
            this.mode_rectangle.Location = new System.Drawing.Point(0, 66);
            this.mode_rectangle.Name = "mode_rectangle";
            this.mode_rectangle.Size = new System.Drawing.Size(80, 23);
            this.mode_rectangle.TabIndex = 9;
            this.mode_rectangle.TabStop = true;
            this.mode_rectangle.Text = "Rectangle";
            this.mode_rectangle.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.mode_rectangle.UseVisualStyleBackColor = true;
            this.mode_rectangle.CheckedChanged += new System.EventHandler(this.mode_rectangle_CheckedChanged);
            // 
            // num_circlesize
            // 
            this.num_circlesize.Dock = System.Windows.Forms.DockStyle.Top;
            this.num_circlesize.Location = new System.Drawing.Point(0, 46);
            this.num_circlesize.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.num_circlesize.Name = "num_circlesize";
            this.num_circlesize.Size = new System.Drawing.Size(80, 20);
            this.num_circlesize.TabIndex = 8;
            this.num_circlesize.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // mode_circle
            // 
            this.mode_circle.Appearance = System.Windows.Forms.Appearance.Button;
            this.mode_circle.AutoSize = true;
            this.mode_circle.Dock = System.Windows.Forms.DockStyle.Top;
            this.mode_circle.Location = new System.Drawing.Point(0, 23);
            this.mode_circle.Name = "mode_circle";
            this.mode_circle.Size = new System.Drawing.Size(80, 23);
            this.mode_circle.TabIndex = 7;
            this.mode_circle.TabStop = true;
            this.mode_circle.Text = "Circle";
            this.mode_circle.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.mode_circle.UseVisualStyleBackColor = true;
            this.mode_circle.CheckedChanged += new System.EventHandler(this.mode_circle_CheckedChanged);
            // 
            // mode_dot
            // 
            this.mode_dot.Appearance = System.Windows.Forms.Appearance.Button;
            this.mode_dot.AutoSize = true;
            this.mode_dot.Dock = System.Windows.Forms.DockStyle.Top;
            this.mode_dot.Location = new System.Drawing.Point(0, 0);
            this.mode_dot.Name = "mode_dot";
            this.mode_dot.Size = new System.Drawing.Size(80, 23);
            this.mode_dot.TabIndex = 6;
            this.mode_dot.TabStop = true;
            this.mode_dot.Text = "Dot";
            this.mode_dot.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.mode_dot.UseVisualStyleBackColor = true;
            this.mode_dot.CheckedChanged += new System.EventHandler(this.mode_dot_CheckedChanged);
            // 
            // splitContainer4
            // 
            this.splitContainer4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer4.Location = new System.Drawing.Point(0, 0);
            this.splitContainer4.Name = "splitContainer4";
            // 
            // splitContainer4.Panel1
            // 
            this.splitContainer4.Panel1.Controls.Add(this.pixelEditor4);
            // 
            // splitContainer4.Panel2
            // 
            this.splitContainer4.Panel2.Controls.Add(this.pixelEditor3);
            this.splitContainer4.Panel2.Controls.Add(this.btn_loadsprite);
            this.splitContainer4.Panel2.Controls.Add(this.btn_save);
            this.splitContainer4.Size = new System.Drawing.Size(447, 523);
            this.splitContainer4.SplitterDistance = 149;
            this.splitContainer4.TabIndex = 0;
            // 
            // pixelEditor4
            // 
            this.pixelEditor4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pixelEditor4.drawMouseUnderlay = null;
            this.pixelEditor4.highlightheight = 0;
            this.pixelEditor4.highlightwidth = 0;
            this.pixelEditor4.Location = new System.Drawing.Point(0, 0);
            this.pixelEditor4.Name = "pixelEditor4";
            this.pixelEditor4.ShowTileArea = false;
            this.pixelEditor4.Size = new System.Drawing.Size(149, 523);
            this.pixelEditor4.TabIndex = 6;
            this.pixelEditor4.TabStop = false;
            // 
            // pixelEditor3
            // 
            this.pixelEditor3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pixelEditor3.drawMouseUnderlay = null;
            this.pixelEditor3.highlightheight = 0;
            this.pixelEditor3.highlightwidth = 0;
            this.pixelEditor3.Location = new System.Drawing.Point(0, 0);
            this.pixelEditor3.Name = "pixelEditor3";
            this.pixelEditor3.ShowTileArea = false;
            this.pixelEditor3.Size = new System.Drawing.Size(294, 477);
            this.pixelEditor3.TabIndex = 4;
            this.pixelEditor3.TabStop = false;
            // 
            // pixelEditor2
            // 
            this.pixelEditor2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pixelEditor2.drawMouseUnderlay = null;
            this.pixelEditor2.highlightheight = 0;
            this.pixelEditor2.highlightwidth = 0;
            this.pixelEditor2.Location = new System.Drawing.Point(0, 0);
            this.pixelEditor2.Name = "pixelEditor2";
            this.pixelEditor2.ShowTileArea = false;
            this.pixelEditor2.Size = new System.Drawing.Size(531, 160);
            this.pixelEditor2.TabIndex = 1;
            this.pixelEditor2.TabStop = false;
            // 
            // btn_rotateCW
            // 
            this.btn_rotateCW.Dock = System.Windows.Forms.DockStyle.Top;
            this.btn_rotateCW.Location = new System.Drawing.Point(0, 275);
            this.btn_rotateCW.Name = "btn_rotateCW";
            this.btn_rotateCW.Size = new System.Drawing.Size(80, 23);
            this.btn_rotateCW.TabIndex = 15;
            this.btn_rotateCW.Text = "Rotate Right";
            this.btn_rotateCW.UseVisualStyleBackColor = true;
            this.btn_rotateCW.Click += new System.EventHandler(this.btn_rotateCW_Click);
            // 
            // btn_rotateCCW
            // 
            this.btn_rotateCCW.Dock = System.Windows.Forms.DockStyle.Top;
            this.btn_rotateCCW.Location = new System.Drawing.Point(0, 298);
            this.btn_rotateCCW.Name = "btn_rotateCCW";
            this.btn_rotateCCW.Size = new System.Drawing.Size(80, 23);
            this.btn_rotateCCW.TabIndex = 16;
            this.btn_rotateCCW.Text = "Rotate Left";
            this.btn_rotateCCW.UseVisualStyleBackColor = true;
            this.btn_rotateCCW.Click += new System.EventHandler(this.btn_rotateCCW_Click);
            // 
            // CharacterMaker
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1250, 733);
            this.Controls.Add(this.splitContainer1);
            this.Name = "CharacterMaker";
            this.Text = "CharacterMaker";
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pixelEditor1)).EndInit();
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
            this.splitContainer2.ResumeLayout(false);
            this.splitContainer3.Panel1.ResumeLayout(false);
            this.splitContainer3.Panel1.PerformLayout();
            this.splitContainer3.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer3)).EndInit();
            this.splitContainer3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pe_clipboard)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_rectanglesize)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.num_circlesize)).EndInit();
            this.splitContainer4.Panel1.ResumeLayout(false);
            this.splitContainer4.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer4)).EndInit();
            this.splitContainer4.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pixelEditor4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pixelEditor3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pixelEditor2)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private PixelEditor pixelEditor1;
        private PixelEditor pixelEditor2;
        private System.Windows.Forms.Button btn_loadPalette;
        private System.Windows.Forms.Button btn_savePalette;
        private PixelEditor pixelEditor3;
        private System.Windows.Forms.Panel panel1;
        private PixelEditor pixelEditor4;
        private System.Windows.Forms.Button btn_loadsprite;
        private System.Windows.Forms.Button btn_save;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.SplitContainer splitContainer3;
        private System.Windows.Forms.RadioButton mode_dot;
        private System.Windows.Forms.SplitContainer splitContainer4;
        private System.Windows.Forms.NumericUpDown num_rectanglesize;
        private System.Windows.Forms.RadioButton mode_rectangle;
        private System.Windows.Forms.NumericUpDown num_circlesize;
        private System.Windows.Forms.RadioButton mode_circle;
        private System.Windows.Forms.RadioButton mode_paste;
        private PixelEditor pe_clipboard;
        private System.Windows.Forms.RadioButton mode_copy;
        private System.Windows.Forms.RadioButton mode_punchPaste;
        private System.Windows.Forms.Button btn_rotateCCW;
        private System.Windows.Forms.Button btn_rotateCW;

    }
}