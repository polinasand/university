namespace DBCosmetics
{
    partial class Form2
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
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.label1 = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.buttonRequest1 = new System.Windows.Forms.Button();
            this.comboBoxCollection = new System.Windows.Forms.ComboBox();
            this.buttonRequest2 = new System.Windows.Forms.Button();
            this.comboBoxColor = new System.Windows.Forms.ComboBox();
            this.comboBoxType = new System.Windows.Forms.ComboBox();
            this.comboBoxFinish = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(586, 12);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowHeadersWidth = 51;
            this.dataGridView1.RowTemplate.Height = 24;
            this.dataGridView1.Size = new System.Drawing.Size(618, 506);
            this.dataGridView1.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 49);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(161, 17);
            this.label1.TabIndex = 1;
            this.label1.Text = "Find products that have ";
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(173, 46);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(81, 24);
            this.comboBox1.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(260, 49);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(58, 17);
            this.label2.TabIndex = 3;
            this.label2.Text = "color in ";
            // 
            // comboBox2
            // 
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Location = new System.Drawing.Point(311, 46);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(85, 24);
            this.comboBox2.TabIndex = 4;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(402, 49);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(40, 17);
            this.label3.TabIndex = 5;
            this.label3.Text = "store";
            // 
            // buttonRequest1
            // 
            this.buttonRequest1.Location = new System.Drawing.Point(471, 36);
            this.buttonRequest1.Name = "buttonRequest1";
            this.buttonRequest1.Size = new System.Drawing.Size(82, 46);
            this.buttonRequest1.TabIndex = 6;
            this.buttonRequest1.Text = "button1";
            this.buttonRequest1.UseVisualStyleBackColor = true;
            this.buttonRequest1.Click += new System.EventHandler(this.buttonRequest1_Click);
            // 
            // comboBoxCollection
            // 
            this.comboBoxCollection.FormattingEnabled = true;
            this.comboBoxCollection.Location = new System.Drawing.Point(173, 133);
            this.comboBoxCollection.Name = "comboBoxCollection";
            this.comboBoxCollection.Size = new System.Drawing.Size(88, 24);
            this.comboBoxCollection.TabIndex = 8;
            // 
            // buttonRequest2
            // 
            this.buttonRequest2.Location = new System.Drawing.Point(444, 142);
            this.buttonRequest2.Name = "buttonRequest2";
            this.buttonRequest2.Size = new System.Drawing.Size(75, 43);
            this.buttonRequest2.TabIndex = 9;
            this.buttonRequest2.Text = "button1";
            this.buttonRequest2.UseVisualStyleBackColor = true;
            this.buttonRequest2.Click += new System.EventHandler(this.buttonRequest2_Click);
            // 
            // comboBoxColor
            // 
            this.comboBoxColor.FormattingEnabled = true;
            this.comboBoxColor.Location = new System.Drawing.Point(173, 163);
            this.comboBoxColor.Name = "comboBoxColor";
            this.comboBoxColor.Size = new System.Drawing.Size(88, 24);
            this.comboBoxColor.TabIndex = 10;
            // 
            // comboBoxType
            // 
            this.comboBoxType.FormattingEnabled = true;
            this.comboBoxType.Location = new System.Drawing.Point(173, 193);
            this.comboBoxType.Name = "comboBoxType";
            this.comboBoxType.Size = new System.Drawing.Size(88, 24);
            this.comboBoxType.TabIndex = 11;
            // 
            // comboBoxFinish
            // 
            this.comboBoxFinish.FormattingEnabled = true;
            this.comboBoxFinish.Location = new System.Drawing.Point(173, 223);
            this.comboBoxFinish.Name = "comboBoxFinish";
            this.comboBoxFinish.Size = new System.Drawing.Size(88, 24);
            this.comboBoxFinish.TabIndex = 12;
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1216, 594);
            this.Controls.Add(this.comboBoxFinish);
            this.Controls.Add(this.comboBoxType);
            this.Controls.Add(this.comboBoxColor);
            this.Controls.Add(this.buttonRequest2);
            this.Controls.Add(this.comboBoxCollection);
            this.Controls.Add(this.buttonRequest1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.comboBox2);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.dataGridView1);
            this.Name = "Form2";
            this.Text = "Form2";
            this.Load += new System.EventHandler(this.Form2_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button buttonRequest1;
        private System.Windows.Forms.ComboBox comboBoxCollection;
        private System.Windows.Forms.Button buttonRequest2;
        private System.Windows.Forms.ComboBox comboBoxColor;
        private System.Windows.Forms.ComboBox comboBoxType;
        private System.Windows.Forms.ComboBox comboBoxFinish;
    }
}