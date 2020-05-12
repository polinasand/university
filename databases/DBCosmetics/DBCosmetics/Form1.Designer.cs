namespace DBCosmetics
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.dataGridView2 = new System.Windows.Forms.DataGridView();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.Product = new System.Windows.Forms.TabPage();
            this.Finish = new System.Windows.Forms.TabPage();
            this.Store = new System.Windows.Forms.TabPage();
            this.dataGridView3 = new System.Windows.Forms.DataGridView();
            this.Stock = new System.Windows.Forms.TabPage();
            this.dataGridView4 = new System.Windows.Forms.DataGridView();
            this.Worker = new System.Windows.Forms.TabPage();
            this.dataGridView5 = new System.Windows.Forms.DataGridView();
            this.Position = new System.Windows.Forms.TabPage();
            this.dataGridView6 = new System.Windows.Forms.DataGridView();
            this.Type = new System.Windows.Forms.TabPage();
            this.dataGridView7 = new System.Windows.Forms.DataGridView();
            this.Collection = new System.Windows.Forms.TabPage();
            this.dataGridView8 = new System.Windows.Forms.DataGridView();
            this.Color = new System.Windows.Forms.TabPage();
            this.dataGridView9 = new System.Windows.Forms.DataGridView();
            this.buttonDelete = new System.Windows.Forms.Button();
            this.buttonSave = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).BeginInit();
            this.tabControl1.SuspendLayout();
            this.Product.SuspendLayout();
            this.Finish.SuspendLayout();
            this.Store.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView3)).BeginInit();
            this.Stock.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView4)).BeginInit();
            this.Worker.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView5)).BeginInit();
            this.Position.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView6)).BeginInit();
            this.Type.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView7)).BeginInit();
            this.Collection.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView8)).BeginInit();
            this.Color.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView9)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView1
            // 
            this.dataGridView1.AllowUserToDeleteRows = false;
            this.dataGridView1.BackgroundColor = System.Drawing.SystemColors.ActiveCaption;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(6, 6);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowHeadersWidth = 51;
            this.dataGridView1.RowTemplate.Height = 24;
            this.dataGridView1.Size = new System.Drawing.Size(535, 382);
            this.dataGridView1.TabIndex = 0;
            // 
            // dataGridView2
            // 
            this.dataGridView2.BackgroundColor = System.Drawing.SystemColors.ActiveCaption;
            this.dataGridView2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView2.Location = new System.Drawing.Point(0, 0);
            this.dataGridView2.Name = "dataGridView2";
            this.dataGridView2.RowHeadersWidth = 51;
            this.dataGridView2.RowTemplate.Height = 24;
            this.dataGridView2.Size = new System.Drawing.Size(544, 399);
            this.dataGridView2.TabIndex = 1;
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.Product);
            this.tabControl1.Controls.Add(this.Finish);
            this.tabControl1.Controls.Add(this.Store);
            this.tabControl1.Controls.Add(this.Stock);
            this.tabControl1.Controls.Add(this.Worker);
            this.tabControl1.Controls.Add(this.Position);
            this.tabControl1.Controls.Add(this.Type);
            this.tabControl1.Controls.Add(this.Collection);
            this.tabControl1.Controls.Add(this.Color);
            this.tabControl1.Font = new System.Drawing.Font("Californian FB", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tabControl1.Location = new System.Drawing.Point(26, 12);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(555, 422);
            this.tabControl1.TabIndex = 2;
            // 
            // Product
            // 
            this.Product.Controls.Add(this.dataGridView1);
            this.Product.Location = new System.Drawing.Point(4, 30);
            this.Product.Name = "Product";
            this.Product.Padding = new System.Windows.Forms.Padding(3);
            this.Product.Size = new System.Drawing.Size(547, 388);
            this.Product.TabIndex = 0;
            this.Product.Text = "Product";
            this.Product.UseVisualStyleBackColor = true;
            // 
            // Finish
            // 
            this.Finish.Controls.Add(this.dataGridView2);
            this.Finish.Location = new System.Drawing.Point(4, 30);
            this.Finish.Name = "Finish";
            this.Finish.Size = new System.Drawing.Size(547, 388);
            this.Finish.TabIndex = 8;
            this.Finish.Text = "Finish";
            this.Finish.UseVisualStyleBackColor = true;
            // 
            // Store
            // 
            this.Store.Controls.Add(this.dataGridView3);
            this.Store.Location = new System.Drawing.Point(4, 30);
            this.Store.Name = "Store";
            this.Store.Padding = new System.Windows.Forms.Padding(3);
            this.Store.Size = new System.Drawing.Size(547, 388);
            this.Store.TabIndex = 1;
            this.Store.Text = "Store";
            this.Store.UseVisualStyleBackColor = true;
            // 
            // dataGridView3
            // 
            this.dataGridView3.BackgroundColor = System.Drawing.SystemColors.ActiveCaption;
            this.dataGridView3.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView3.Location = new System.Drawing.Point(6, 7);
            this.dataGridView3.Name = "dataGridView3";
            this.dataGridView3.RowHeadersWidth = 51;
            this.dataGridView3.RowTemplate.Height = 24;
            this.dataGridView3.Size = new System.Drawing.Size(540, 395);
            this.dataGridView3.TabIndex = 0;
            // 
            // Stock
            // 
            this.Stock.Controls.Add(this.dataGridView4);
            this.Stock.Location = new System.Drawing.Point(4, 30);
            this.Stock.Name = "Stock";
            this.Stock.Size = new System.Drawing.Size(547, 388);
            this.Stock.TabIndex = 2;
            this.Stock.Text = "Stock";
            this.Stock.UseVisualStyleBackColor = true;
            // 
            // dataGridView4
            // 
            this.dataGridView4.BackgroundColor = System.Drawing.SystemColors.ActiveCaption;
            this.dataGridView4.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView4.Location = new System.Drawing.Point(3, 3);
            this.dataGridView4.Name = "dataGridView4";
            this.dataGridView4.RowHeadersWidth = 51;
            this.dataGridView4.RowTemplate.Height = 24;
            this.dataGridView4.Size = new System.Drawing.Size(541, 397);
            this.dataGridView4.TabIndex = 0;
            // 
            // Worker
            // 
            this.Worker.Controls.Add(this.dataGridView5);
            this.Worker.Location = new System.Drawing.Point(4, 30);
            this.Worker.Name = "Worker";
            this.Worker.Size = new System.Drawing.Size(547, 388);
            this.Worker.TabIndex = 3;
            this.Worker.Text = "Worker";
            this.Worker.UseVisualStyleBackColor = true;
            // 
            // dataGridView5
            // 
            this.dataGridView5.BackgroundColor = System.Drawing.SystemColors.ActiveCaption;
            this.dataGridView5.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView5.Location = new System.Drawing.Point(4, 0);
            this.dataGridView5.Name = "dataGridView5";
            this.dataGridView5.RowHeadersWidth = 51;
            this.dataGridView5.RowTemplate.Height = 24;
            this.dataGridView5.Size = new System.Drawing.Size(543, 399);
            this.dataGridView5.TabIndex = 0;
            // 
            // Position
            // 
            this.Position.Controls.Add(this.dataGridView6);
            this.Position.Location = new System.Drawing.Point(4, 30);
            this.Position.Name = "Position";
            this.Position.Size = new System.Drawing.Size(547, 388);
            this.Position.TabIndex = 4;
            this.Position.Text = "Position";
            this.Position.UseVisualStyleBackColor = true;
            // 
            // dataGridView6
            // 
            this.dataGridView6.BackgroundColor = System.Drawing.SystemColors.ActiveCaption;
            this.dataGridView6.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView6.Location = new System.Drawing.Point(3, 0);
            this.dataGridView6.Name = "dataGridView6";
            this.dataGridView6.RowHeadersWidth = 51;
            this.dataGridView6.RowTemplate.Height = 24;
            this.dataGridView6.Size = new System.Drawing.Size(548, 400);
            this.dataGridView6.TabIndex = 0;
            // 
            // Type
            // 
            this.Type.Controls.Add(this.dataGridView7);
            this.Type.Location = new System.Drawing.Point(4, 30);
            this.Type.Name = "Type";
            this.Type.Size = new System.Drawing.Size(547, 388);
            this.Type.TabIndex = 5;
            this.Type.Text = "Type";
            this.Type.UseVisualStyleBackColor = true;
            // 
            // dataGridView7
            // 
            this.dataGridView7.BackgroundColor = System.Drawing.SystemColors.ActiveCaption;
            this.dataGridView7.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView7.Location = new System.Drawing.Point(3, 3);
            this.dataGridView7.Name = "dataGridView7";
            this.dataGridView7.RowHeadersWidth = 51;
            this.dataGridView7.RowTemplate.Height = 24;
            this.dataGridView7.Size = new System.Drawing.Size(541, 400);
            this.dataGridView7.TabIndex = 0;
            // 
            // Collection
            // 
            this.Collection.Controls.Add(this.dataGridView8);
            this.Collection.Location = new System.Drawing.Point(4, 30);
            this.Collection.Name = "Collection";
            this.Collection.Size = new System.Drawing.Size(547, 388);
            this.Collection.TabIndex = 6;
            this.Collection.Text = "Collection";
            this.Collection.UseVisualStyleBackColor = true;
            // 
            // dataGridView8
            // 
            this.dataGridView8.BackgroundColor = System.Drawing.SystemColors.ActiveCaption;
            this.dataGridView8.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView8.Location = new System.Drawing.Point(3, 0);
            this.dataGridView8.Name = "dataGridView8";
            this.dataGridView8.RowHeadersWidth = 51;
            this.dataGridView8.RowTemplate.Height = 24;
            this.dataGridView8.Size = new System.Drawing.Size(548, 400);
            this.dataGridView8.TabIndex = 0;
            // 
            // Color
            // 
            this.Color.Controls.Add(this.dataGridView9);
            this.Color.Location = new System.Drawing.Point(4, 30);
            this.Color.Name = "Color";
            this.Color.Size = new System.Drawing.Size(547, 388);
            this.Color.TabIndex = 7;
            this.Color.Text = "Color";
            this.Color.UseVisualStyleBackColor = true;
            // 
            // dataGridView9
            // 
            this.dataGridView9.BackgroundColor = System.Drawing.SystemColors.ActiveCaption;
            this.dataGridView9.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView9.Location = new System.Drawing.Point(3, 3);
            this.dataGridView9.Name = "dataGridView9";
            this.dataGridView9.RowHeadersWidth = 51;
            this.dataGridView9.RowTemplate.Height = 24;
            this.dataGridView9.Size = new System.Drawing.Size(541, 397);
            this.dataGridView9.TabIndex = 0;
            // 
            // buttonDelete
            // 
            this.buttonDelete.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(0)))), ((int)(((byte)(64)))));
            this.buttonDelete.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.buttonDelete.Font = new System.Drawing.Font("Lucida Bright", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonDelete.ForeColor = System.Drawing.Color.White;
            this.buttonDelete.Location = new System.Drawing.Point(654, 147);
            this.buttonDelete.Margin = new System.Windows.Forms.Padding(0);
            this.buttonDelete.Name = "buttonDelete";
            this.buttonDelete.Size = new System.Drawing.Size(113, 74);
            this.buttonDelete.TabIndex = 1;
            this.buttonDelete.Text = "Delete";
            this.buttonDelete.UseVisualStyleBackColor = false;
            this.buttonDelete.Click += new System.EventHandler(this.buttonDelete_Click);
            // 
            // buttonSave
            // 
            this.buttonSave.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(64)))));
            this.buttonSave.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.buttonSave.Font = new System.Drawing.Font("Lucida Bright", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonSave.ForeColor = System.Drawing.Color.White;
            this.buttonSave.Location = new System.Drawing.Point(654, 268);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(113, 77);
            this.buttonSave.TabIndex = 2;
            this.buttonSave.Text = "Save";
            this.buttonSave.UseVisualStyleBackColor = false;
            this.buttonSave.Click += new System.EventHandler(this.buttonSave_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = global::DBCosmetics.Properties.Resources._58fca4f2284ec15b9ae451f5;
            this.ClientSize = new System.Drawing.Size(853, 512);
            this.Controls.Add(this.buttonSave);
            this.Controls.Add(this.buttonDelete);
            this.Controls.Add(this.tabControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).EndInit();
            this.tabControl1.ResumeLayout(false);
            this.Product.ResumeLayout(false);
            this.Finish.ResumeLayout(false);
            this.Store.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView3)).EndInit();
            this.Stock.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView4)).EndInit();
            this.Worker.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView5)).EndInit();
            this.Position.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView6)).EndInit();
            this.Type.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView7)).EndInit();
            this.Collection.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView8)).EndInit();
            this.Color.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView9)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.DataGridView dataGridView2;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage Product;
        private System.Windows.Forms.TabPage Store;
        private System.Windows.Forms.TabPage Stock;
        private System.Windows.Forms.TabPage Worker;
        private System.Windows.Forms.TabPage Position;
        private System.Windows.Forms.TabPage Type;
        private System.Windows.Forms.TabPage Collection;
        private System.Windows.Forms.TabPage Color;
        private System.Windows.Forms.TabPage Finish;
        private System.Windows.Forms.DataGridView dataGridView3;
        private System.Windows.Forms.DataGridView dataGridView4;
        private System.Windows.Forms.DataGridView dataGridView5;
        private System.Windows.Forms.DataGridView dataGridView6;
        private System.Windows.Forms.DataGridView dataGridView7;
        private System.Windows.Forms.DataGridView dataGridView8;
        private System.Windows.Forms.DataGridView dataGridView9;
        private System.Windows.Forms.Button buttonDelete;
        private System.Windows.Forms.Button buttonSave;
    }
}

