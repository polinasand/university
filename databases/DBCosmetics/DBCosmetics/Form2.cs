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
                //color
                adapter = new SqlDataAdapter(sqlColors, connection);
                ds = new DataSet();
                adapter.Fill(ds, "Color");
                comboBox1.DisplayMember = "Name";
                comboBox1.ValueMember = "Id";
                comboBox1.DataSource = ds.Tables["Color"];

                comboBoxColor.DisplayMember = "Name";
                comboBoxColor.ValueMember = "Id";
                comboBoxColor.DataSource = ds.Tables["Color"];

                //collection
                adapter = new SqlDataAdapter(sqlCollections, connection);
                ds = new DataSet();
                adapter.Fill(ds, "Collection");
                comboBoxCollection.DisplayMember = "Name";
                comboBoxCollection.ValueMember = "Id";
                comboBoxCollection.DataSource = ds.Tables["Collection"];

                //finish
                adapter = new SqlDataAdapter(sqlFinishes, connection);
                ds = new DataSet();
                adapter.Fill(ds, "Finish");
                comboBoxFinish.DisplayMember = "Name";
                comboBoxFinish.ValueMember = "Id";
                comboBoxFinish.DataSource = ds.Tables["Finish"];

                //types
                adapter = new SqlDataAdapter(sqlCosmTypes, connection);
                ds = new DataSet();
                adapter.Fill(ds, "CosmType");
                comboBoxType.DisplayMember = "Name";
                comboBoxType.ValueMember = "Id";
                comboBoxType.DataSource = ds.Tables["CosmType"];

                //store
                adapter = new SqlDataAdapter(sqlStores, connection);
                ds = new DataSet();
                adapter.Fill(ds, "Store");
                comboBox2.DisplayMember = "Name";
                comboBox2.ValueMember = "Id";
                comboBox2.DataSource = ds.Tables["Store"];
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
                string sql = String.Format("SELECT * FROM Products INNER JOIN Colors on Products.ColorId=Colors.Id WHERE Colors.Name={0}", comboBox1.Text);
                adapter = new SqlDataAdapter(sql, connection);
                DataSet ds = new DataSet();
                adapter.Fill(ds);
                dataGridView1.DataSource = ds.Tables[0];

            }
        }

        private void buttonRequest2_Click(object sender, EventArgs e)
        {
            
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                connection.Open();
                string sql = String.Format("SELECT * FROM Products WHERE ColorId={0} and CosmTypeId={1} and CollectionId={2} and FinishId={3}", comboBoxColor.ValueMember.ToString(), comboBoxType.ValueMember, comboBoxCollection.ValueMember.ToString(), comboBoxFinish.ValueMember.ToString());
                adapter = new SqlDataAdapter(sql, connection);
                DataSet ds = new DataSet();
                adapter.Fill(ds);
                dataGridView1.DataSource = ds.Tables[0];
                //SqlCommand command = new SqlCommand(sql, connection);

                //dataGridView1.DataSource = command.ExecuteReader();

            }
        }
    }
}
