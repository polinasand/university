namespace DBCosmetics
{
    partial class Form0
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form0));
            this.buttonGet = new System.Windows.Forms.Button();
            this.buttonSQL = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonGet
            // 
            this.buttonGet.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.buttonGet.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("buttonGet.BackgroundImage")));
            this.buttonGet.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttonGet.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.buttonGet.Location = new System.Drawing.Point(28, 12);
            this.buttonGet.Name = "buttonGet";
            this.buttonGet.Size = new System.Drawing.Size(380, 480);
            this.buttonGet.TabIndex = 0;
            this.buttonGet.UseVisualStyleBackColor = true;
            this.buttonGet.Click += new System.EventHandler(this.buttonGet_Click);
            // 
            // buttonSQL
            // 
            this.buttonSQL.BackColor = System.Drawing.Color.White;
            this.buttonSQL.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("buttonSQL.BackgroundImage")));
            this.buttonSQL.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttonSQL.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.buttonSQL.Location = new System.Drawing.Point(428, 12);
            this.buttonSQL.Name = "buttonSQL";
            this.buttonSQL.Size = new System.Drawing.Size(380, 480);
            this.buttonSQL.TabIndex = 1;
            this.buttonSQL.UseVisualStyleBackColor = false;
            this.buttonSQL.Click += new System.EventHandler(this.buttonSQL_Click);
            // 
            // Form0
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(832, 532);
            this.Controls.Add(this.buttonSQL);
            this.Controls.Add(this.buttonGet);
            this.Name = "Form0";
            this.Text = "Form0";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonGet;
        private System.Windows.Forms.Button buttonSQL;
    }
}