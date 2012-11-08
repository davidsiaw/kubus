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
            this.pixelEditor3 = new tilemapmaker.PixelEditor();
            this.pixelEditor2 = new tilemapmaker.PixelEditor();
            this.pixelEditor1 = new tilemapmaker.PixelEditor();
            this.pixelEditor4 = new tilemapmaker.PixelEditor();
            ((System.ComponentModel.ISupportInitialize)(this.pixelEditor3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pixelEditor2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pixelEditor1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pixelEditor4)).BeginInit();
            this.SuspendLayout();
            // 
            // btn_loadPalette
            // 
            this.btn_loadPalette.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btn_loadPalette.Location = new System.Drawing.Point(685, 360);
            this.btn_loadPalette.Name = "btn_loadPalette";
            this.btn_loadPalette.Size = new System.Drawing.Size(190, 23);
            this.btn_loadPalette.TabIndex = 2;
            this.btn_loadPalette.Text = "Load Palette";
            this.btn_loadPalette.UseVisualStyleBackColor = true;
            this.btn_loadPalette.Click += new System.EventHandler(this.btn_loadPalette_Click);
            // 
            // btn_savePalette
            // 
            this.btn_savePalette.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btn_savePalette.Location = new System.Drawing.Point(881, 360);
            this.btn_savePalette.Name = "btn_savePalette";
            this.btn_savePalette.Size = new System.Drawing.Size(234, 23);
            this.btn_savePalette.TabIndex = 3;
            this.btn_savePalette.Text = "Save Palette";
            this.btn_savePalette.UseVisualStyleBackColor = true;
            this.btn_savePalette.Click += new System.EventHandler(this.btn_savePalette_Click);
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.Location = new System.Drawing.Point(685, 322);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(430, 32);
            this.panel1.TabIndex = 5;
            // 
            // pixelEditor3
            // 
            this.pixelEditor3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.pixelEditor3.highlightheight = 0;
            this.pixelEditor3.highlightwidth = 0;
            this.pixelEditor3.Location = new System.Drawing.Point(881, 12);
            this.pixelEditor3.Name = "pixelEditor3";
            this.pixelEditor3.Size = new System.Drawing.Size(234, 304);
            this.pixelEditor3.TabIndex = 4;
            this.pixelEditor3.TabStop = false;
            // 
            // pixelEditor2
            // 
            this.pixelEditor2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.pixelEditor2.highlightheight = 0;
            this.pixelEditor2.highlightwidth = 0;
            this.pixelEditor2.Location = new System.Drawing.Point(685, 389);
            this.pixelEditor2.Name = "pixelEditor2";
            this.pixelEditor2.Size = new System.Drawing.Size(430, 220);
            this.pixelEditor2.TabIndex = 1;
            this.pixelEditor2.TabStop = false;
            // 
            // pixelEditor1
            // 
            this.pixelEditor1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.pixelEditor1.highlightheight = 0;
            this.pixelEditor1.highlightwidth = 0;
            this.pixelEditor1.Location = new System.Drawing.Point(12, 12);
            this.pixelEditor1.Name = "pixelEditor1";
            this.pixelEditor1.Size = new System.Drawing.Size(667, 597);
            this.pixelEditor1.TabIndex = 0;
            this.pixelEditor1.TabStop = false;
            // 
            // pixelEditor4
            // 
            this.pixelEditor4.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.pixelEditor4.highlightheight = 0;
            this.pixelEditor4.highlightwidth = 0;
            this.pixelEditor4.Location = new System.Drawing.Point(775, 12);
            this.pixelEditor4.Name = "pixelEditor4";
            this.pixelEditor4.Size = new System.Drawing.Size(100, 304);
            this.pixelEditor4.TabIndex = 6;
            this.pixelEditor4.TabStop = false;
            // 
            // CharacterMaker
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1127, 621);
            this.Controls.Add(this.pixelEditor4);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.pixelEditor3);
            this.Controls.Add(this.btn_savePalette);
            this.Controls.Add(this.btn_loadPalette);
            this.Controls.Add(this.pixelEditor2);
            this.Controls.Add(this.pixelEditor1);
            this.Name = "CharacterMaker";
            this.Text = "CharacterMaker";
            ((System.ComponentModel.ISupportInitialize)(this.pixelEditor3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pixelEditor2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pixelEditor1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pixelEditor4)).EndInit();
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

    }
}