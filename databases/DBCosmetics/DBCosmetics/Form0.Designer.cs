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
            this.buttonGet = new System.Windows.Forms.Button();
            this.buttonSQL = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonGet
            // 
            this.buttonGet.Location = new System.Drawing.Point(599, 22);
            this.buttonGet.Name = "buttonGet";
            this.buttonGet.Size = new System.Drawing.Size(152, 68);
            this.buttonGet.TabIndex = 0;
            this.buttonGet.Text = "button1";
            this.buttonGet.UseVisualStyleBackColor = true;
            this.buttonGet.Click += new System.EventHandler(this.buttonGet_Click);
            // 
            // buttonSQL
            // 
            this.buttonSQL.Location = new System.Drawing.Point(599, 122);
            this.buttonSQL.Name = "buttonSQL";
            this.buttonSQL.Size = new System.Drawing.Size(151, 79);
            this.buttonSQL.TabIndex = 1;
            this.buttonSQL.Text = "button2";
            this.buttonSQL.UseVisualStyleBackColor = true;
            this.buttonSQL.Click += new System.EventHandler(this.buttonSQL_Click);
            // 
            // Form0
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
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