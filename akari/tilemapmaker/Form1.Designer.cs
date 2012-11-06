namespace tilemapmaker
{
    partial class Form1
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
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.tc_main = new System.Windows.Forms.TabControl();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.splitContainer4 = new System.Windows.Forms.SplitContainer();
            this.button3 = new System.Windows.Forms.Button();
            this.flow_basictiles = new System.Windows.Forms.FlowLayoutPanel();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.tc_topLeft = new System.Windows.Forms.TabControl();
            this.tab_file = new System.Windows.Forms.TabPage();
            this.btn_savetiles = new System.Windows.Forms.Button();
            this.btn_downlevel = new System.Windows.Forms.Button();
            this.btn_uplevel = new System.Windows.Forms.Button();
            this.btn_loadtilemap = new System.Windows.Forms.Button();
            this.splitContainer3 = new System.Windows.Forms.SplitContainer();
            this.tc_tileLists = new System.Windows.Forms.TabControl();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.flow_tiles = new System.Windows.Forms.FlowLayoutPanel();
            this.btn_makefont = new System.Windows.Forms.Button();
            this.draggableMap1 = new tilemapmaker.DraggableMap();
            this.btn_loadtiles = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.tc_main.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer4)).BeginInit();
            this.splitContainer4.Panel1.SuspendLayout();
            this.splitContainer4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            this.tc_topLeft.SuspendLayout();
            this.tab_file.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer3)).BeginInit();
            this.splitContainer3.Panel1.SuspendLayout();
            this.splitContainer3.SuspendLayout();
            this.tc_tileLists.SuspendLayout();
            this.tabPage3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.draggableMap1)).BeginInit();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.tc_main);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.splitContainer2);
            this.splitContainer1.Size = new System.Drawing.Size(1330, 702);
            this.splitContainer1.SplitterDistance = 999;
            this.splitContainer1.TabIndex = 0;
            // 
            // tc_main
            // 
            this.tc_main.Controls.Add(this.tabPage2);
            this.tc_main.Controls.Add(this.tabPage1);
            this.tc_main.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tc_main.Location = new System.Drawing.Point(0, 0);
            this.tc_main.Name = "tc_main";
            this.tc_main.SelectedIndex = 0;
            this.tc_main.Size = new System.Drawing.Size(999, 702);
            this.tc_main.TabIndex = 1;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.draggableMap1);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(991, 676);
            this.tabPage2.TabIndex = 0;
            this.tabPage2.Text = "Map";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.splitContainer4);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(991, 676);
            this.tabPage1.TabIndex = 1;
            this.tabPage1.Text = "Basic Tiles";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // splitContainer4
            // 
            this.splitContainer4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer4.Location = new System.Drawing.Point(3, 3);
            this.splitContainer4.Name = "splitContainer4";
            // 
            // splitContainer4.Panel1
            // 
            this.splitContainer4.Panel1.Controls.Add(this.button3);
            this.splitContainer4.Panel1.Controls.Add(this.flow_basictiles);
            this.splitContainer4.Panel1.Controls.Add(this.button2);
            this.splitContainer4.Panel1.Controls.Add(this.button1);
            this.splitContainer4.Size = new System.Drawing.Size(985, 670);
            this.splitContainer4.SplitterDistance = 852;
            this.splitContainer4.TabIndex = 0;
            // 
            // button3
            // 
            this.button3.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.button3.Location = new System.Drawing.Point(0, 601);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(852, 23);
            this.button3.TabIndex = 3;
            this.button3.Text = "Create 12 Auto Tile";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.autoTile12_Click);
            // 
            // flow_basictiles
            // 
            this.flow_basictiles.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flow_basictiles.Location = new System.Drawing.Point(0, 0);
            this.flow_basictiles.Name = "flow_basictiles";
            this.flow_basictiles.Size = new System.Drawing.Size(852, 624);
            this.flow_basictiles.TabIndex = 0;
            // 
            // button2
            // 
            this.button2.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.button2.Location = new System.Drawing.Point(0, 624);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(852, 23);
            this.button2.TabIndex = 2;
            this.button2.Text = "Create 9-4 Auto Tile";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.autoTile94_Click);
            // 
            // button1
            // 
            this.button1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.button1.Location = new System.Drawing.Point(0, 647);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(852, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "Create Simple Tile";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.simpleTile_Click);
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
            this.splitContainer2.Panel1.Controls.Add(this.tc_topLeft);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.splitContainer3);
            this.splitContainer2.Size = new System.Drawing.Size(327, 702);
            this.splitContainer2.SplitterDistance = 274;
            this.splitContainer2.TabIndex = 1;
            // 
            // tc_topLeft
            // 
            this.tc_topLeft.Alignment = System.Windows.Forms.TabAlignment.Right;
            this.tc_topLeft.Controls.Add(this.tab_file);
            this.tc_topLeft.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tc_topLeft.Location = new System.Drawing.Point(0, 0);
            this.tc_topLeft.Multiline = true;
            this.tc_topLeft.Name = "tc_topLeft";
            this.tc_topLeft.SelectedIndex = 0;
            this.tc_topLeft.Size = new System.Drawing.Size(327, 274);
            this.tc_topLeft.TabIndex = 0;
            // 
            // tab_file
            // 
            this.tab_file.Controls.Add(this.btn_makefont);
            this.tab_file.Controls.Add(this.btn_loadtiles);
            this.tab_file.Controls.Add(this.btn_savetiles);
            this.tab_file.Controls.Add(this.btn_downlevel);
            this.tab_file.Controls.Add(this.btn_uplevel);
            this.tab_file.Controls.Add(this.btn_loadtilemap);
            this.tab_file.Location = new System.Drawing.Point(4, 4);
            this.tab_file.Name = "tab_file";
            this.tab_file.Padding = new System.Windows.Forms.Padding(3);
            this.tab_file.Size = new System.Drawing.Size(300, 266);
            this.tab_file.TabIndex = 0;
            this.tab_file.Text = "File";
            this.tab_file.UseVisualStyleBackColor = true;
            // 
            // btn_savetiles
            // 
            this.btn_savetiles.Dock = System.Windows.Forms.DockStyle.Top;
            this.btn_savetiles.Location = new System.Drawing.Point(3, 72);
            this.btn_savetiles.Name = "btn_savetiles";
            this.btn_savetiles.Size = new System.Drawing.Size(294, 23);
            this.btn_savetiles.TabIndex = 3;
            this.btn_savetiles.Text = "Save Tiles";
            this.btn_savetiles.UseVisualStyleBackColor = true;
            this.btn_savetiles.Click += new System.EventHandler(this.btn_savetiles_Click);
            // 
            // btn_downlevel
            // 
            this.btn_downlevel.Dock = System.Windows.Forms.DockStyle.Top;
            this.btn_downlevel.Location = new System.Drawing.Point(3, 49);
            this.btn_downlevel.Name = "btn_downlevel";
            this.btn_downlevel.Size = new System.Drawing.Size(294, 23);
            this.btn_downlevel.TabIndex = 2;
            this.btn_downlevel.Text = "Down Level";
            this.btn_downlevel.UseVisualStyleBackColor = true;
            this.btn_downlevel.Click += new System.EventHandler(this.btn_downlevel_Click);
            // 
            // btn_uplevel
            // 
            this.btn_uplevel.Dock = System.Windows.Forms.DockStyle.Top;
            this.btn_uplevel.Location = new System.Drawing.Point(3, 26);
            this.btn_uplevel.Name = "btn_uplevel";
            this.btn_uplevel.Size = new System.Drawing.Size(294, 23);
            this.btn_uplevel.TabIndex = 1;
            this.btn_uplevel.Text = "Up Level";
            this.btn_uplevel.UseVisualStyleBackColor = true;
            this.btn_uplevel.Click += new System.EventHandler(this.btn_uplevel_Click);
            // 
            // btn_loadtilemap
            // 
            this.btn_loadtilemap.Dock = System.Windows.Forms.DockStyle.Top;
            this.btn_loadtilemap.Location = new System.Drawing.Point(3, 3);
            this.btn_loadtilemap.Name = "btn_loadtilemap";
            this.btn_loadtilemap.Size = new System.Drawing.Size(294, 23);
            this.btn_loadtilemap.TabIndex = 0;
            this.btn_loadtilemap.Text = "Load TileMap";
            this.btn_loadtilemap.UseVisualStyleBackColor = true;
            this.btn_loadtilemap.Click += new System.EventHandler(this.btn_loadtilemap_Click);
            // 
            // splitContainer3
            // 
            this.splitContainer3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer3.Location = new System.Drawing.Point(0, 0);
            this.splitContainer3.Name = "splitContainer3";
            this.splitContainer3.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer3.Panel1
            // 
            this.splitContainer3.Panel1.Controls.Add(this.tc_tileLists);
            this.splitContainer3.Size = new System.Drawing.Size(327, 424);
            this.splitContainer3.SplitterDistance = 235;
            this.splitContainer3.TabIndex = 1;
            // 
            // tc_tileLists
            // 
            this.tc_tileLists.Controls.Add(this.tabPage3);
            this.tc_tileLists.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tc_tileLists.Location = new System.Drawing.Point(0, 0);
            this.tc_tileLists.Name = "tc_tileLists";
            this.tc_tileLists.SelectedIndex = 0;
            this.tc_tileLists.Size = new System.Drawing.Size(327, 235);
            this.tc_tileLists.TabIndex = 0;
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.flow_tiles);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage3.Size = new System.Drawing.Size(319, 209);
            this.tabPage3.TabIndex = 0;
            this.tabPage3.Text = "Tiles";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // flow_tiles
            // 
            this.flow_tiles.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flow_tiles.Location = new System.Drawing.Point(3, 3);
            this.flow_tiles.Name = "flow_tiles";
            this.flow_tiles.Size = new System.Drawing.Size(313, 203);
            this.flow_tiles.TabIndex = 0;
            // 
            // btn_makefont
            // 
            this.btn_makefont.Dock = System.Windows.Forms.DockStyle.Top;
            this.btn_makefont.Location = new System.Drawing.Point(3, 118);
            this.btn_makefont.Name = "btn_makefont";
            this.btn_makefont.Size = new System.Drawing.Size(294, 23);
            this.btn_makefont.TabIndex = 4;
            this.btn_makefont.Text = "Make Font";
            this.btn_makefont.UseVisualStyleBackColor = true;
            this.btn_makefont.Click += new System.EventHandler(this.btn_makefont_Click);
            // 
            // draggableMap1
            // 
            this.draggableMap1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.draggableMap1.Location = new System.Drawing.Point(3, 3);
            this.draggableMap1.Name = "draggableMap1";
            this.draggableMap1.Size = new System.Drawing.Size(985, 670);
            this.draggableMap1.TabIndex = 0;
            this.draggableMap1.TabStop = false;
            // 
            // btn_loadtiles
            // 
            this.btn_loadtiles.Dock = System.Windows.Forms.DockStyle.Top;
            this.btn_loadtiles.Location = new System.Drawing.Point(3, 95);
            this.btn_loadtiles.Name = "btn_loadtiles";
            this.btn_loadtiles.Size = new System.Drawing.Size(294, 23);
            this.btn_loadtiles.TabIndex = 5;
            this.btn_loadtiles.Text = "Load Tiles";
            this.btn_loadtiles.UseVisualStyleBackColor = true;
            this.btn_loadtiles.Click += new System.EventHandler(this.btn_loadtiles_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1330, 702);
            this.Controls.Add(this.splitContainer1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.tc_main.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.splitContainer4.Panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer4)).EndInit();
            this.splitContainer4.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
            this.splitContainer2.ResumeLayout(false);
            this.tc_topLeft.ResumeLayout(false);
            this.tab_file.ResumeLayout(false);
            this.splitContainer3.Panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer3)).EndInit();
            this.splitContainer3.ResumeLayout(false);
            this.tc_tileLists.ResumeLayout(false);
            this.tabPage3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.draggableMap1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.TabControl tc_topLeft;
        private System.Windows.Forms.TabPage tab_file;
        private System.Windows.Forms.Button btn_loadtilemap;
        private DraggableMap draggableMap1;
        private System.Windows.Forms.Button btn_downlevel;
        private System.Windows.Forms.Button btn_uplevel;
        private System.Windows.Forms.TabControl tc_main;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.TabControl tc_tileLists;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.FlowLayoutPanel flow_tiles;
        private System.Windows.Forms.SplitContainer splitContainer3;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.SplitContainer splitContainer4;
        private System.Windows.Forms.FlowLayoutPanel flow_basictiles;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button btn_savetiles;
        private System.Windows.Forms.Button btn_makefont;
        private System.Windows.Forms.Button btn_loadtiles;
    }
}

