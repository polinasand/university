using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace DBCosmetics
{
    public partial class Form2 : Form
    {
        string connectionString = @"Data Source=DESKTOP-10OKRJ9\SQLEXPRESS; Initial Catalog=DatabaseCosmetics;Integrated Security=True";
        string sqlProducts = "SELECT * FROM Products";
        string sqlFinishes = "SELECT * FROM Finishes";
        string sqlColors = "SELECT * FROM Colors";
        string sqlStores = "SELECT * FROM Stores";
        string sqlStocks = "SELECT * FROM Stock";
        string sqlWorkers = "SELECT * FROM Workers";
        string sqlPositions = "SELECT * FROM Positions";
        string sqlCosmTypes = "SELECT * FROM CosmTypes";
        string sqlCollections = "SELECT * FROM Collections";
        SqlDataAdapter adapter;
        DataSet ds;
        public Form2()
        {
            InitializeComponent();
            
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                connection.Open();

                adapter = new SqlDataAdapter(sqlColors, connection);
                DataSet ds = new DataSet();
                adapter.Fill(ds, "Color");
                comboBox1.DisplayMember = "Name";
                comboBox1.ValueMember = "Id";
                comboBox1.DataSource = ds.Tables["Color"];

                adapter = new SqlDataAdapter(sqlStores, connection);
                ds = new DataSet();
                adapter.Fill(ds, "Store");
                comboBox1.DisplayMember = "Name";
                comboBox1.ValueMember = "Id";
                comboBox1.DataSource = ds.Tables["Store"];
            }
        }

        private void Form2_Load(object sender, EventArgs e)
        {
           
        }

        private void buttonRequest1_Click(object sender, EventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                connection.Open();
                string sql = "SELECT * FROM Products WHERE Products.ColorId == @";
                adapter = new SqlDataAdapter(sqlColors, connection);
                DataSet ds = new DataSet();
                adapter.Fill(ds, "Color");
                comboBox1.DisplayMember = "Name";
                comboBox1.ValueMember = "Id";
                comboBox1.DataSource = ds.Tables["Color"];

                adapter = new SqlDataAdapter(sqlStores, connection);
                ds = new DataSet();
                adapter.Fill(ds, "Store");
                comboBox1.DisplayMember = "Name";
                comboBox1.ValueMember = "Id";
                comboBox1.DataSource = ds.Tables["Store"];
            }
        }
    }
}
