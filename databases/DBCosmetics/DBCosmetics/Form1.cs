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
    public partial class Form1 : Form
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
        DataSet ds1;
       
        SqlCommandBuilder commandBuilder;
        public Form1()
        {
            InitializeComponent();

            
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                connection.Open();
                SqlDataAdapter adapterProducts = new SqlDataAdapter(sqlProducts, connection);
                ds1 = new DataSet();
                adapterProducts.Fill(ds1);
                dataGridView1.DataSource = ds1.Tables[0];
                dataGridView1.Columns["Id"].ReadOnly = true;
               

                SqlDataAdapter adapterFinishes = new SqlDataAdapter(sqlFinishes, connection);
                DataSet ds2 = new DataSet();
                adapterProducts.Fill(ds2);
                dataGridView2.DataSource = ds2.Tables[0];
                dataGridView2.Columns["Id"].ReadOnly = true;
               

                SqlDataAdapter adapterStores = new SqlDataAdapter(sqlStores, connection);
                DataSet ds3 = new DataSet();
                adapterStores.Fill(ds3);
                dataGridView3.DataSource = ds3.Tables[0];
                dataGridView3.Columns["Id"].ReadOnly = true;
               

                SqlDataAdapter adapterStocks = new SqlDataAdapter(sqlStocks, connection);
                DataSet ds4 = new DataSet();
                adapterStocks.Fill(ds4);
                dataGridView4.DataSource = ds4.Tables[0];
                dataGridView4.Columns["Id"].ReadOnly = true;
               

                SqlDataAdapter adapterWorkers = new SqlDataAdapter(sqlWorkers, connection);
                DataSet ds5 = new DataSet();
                adapterWorkers.Fill(ds5);
                dataGridView5.DataSource = ds5.Tables[0];
                dataGridView5.Columns["Id"].ReadOnly = true;
                

                SqlDataAdapter adapterPositions = new SqlDataAdapter(sqlPositions, connection);
                DataSet ds6 = new DataSet();
                adapterPositions.Fill(ds6);
                dataGridView6.DataSource = ds6.Tables[0];
                dataGridView6.Columns["Id"].ReadOnly = true;
                

                SqlDataAdapter adapterCosmTypes = new SqlDataAdapter(sqlCosmTypes, connection);
                DataSet ds7 = new DataSet();
                adapterCosmTypes.Fill(ds7);
                dataGridView7.DataSource = ds7.Tables[0];
                dataGridView7.Columns["Id"].ReadOnly = true;
                
                SqlDataAdapter adapterCollections = new SqlDataAdapter(sqlCollections, connection);
                DataSet ds8 = new DataSet();
                adapterCollections.Fill(ds8);
                dataGridView8.DataSource = ds8.Tables[0];
                dataGridView8.Columns["Id"].ReadOnly = true;
          

                SqlDataAdapter adapterColors = new SqlDataAdapter(sqlColors, connection);
                DataSet ds9 = new DataSet();
                adapterColors.Fill(ds9);
                dataGridView9.DataSource = ds9.Tables[0];
                dataGridView9.Columns["Id"].ReadOnly = true;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            MessageBox.Show("You wanna delete selected rows from ALL the tables. Are you sure?", "Danger");
            foreach (DataGridViewRow row in dataGridView1.SelectedRows)
            {
                dataGridView1.Rows.Remove(row);
            }
            foreach (DataGridViewRow row in dataGridView2.SelectedRows)
            {
                dataGridView2.Rows.Remove(row);
            }
            foreach (DataGridViewRow row in dataGridView3.SelectedRows)
            {
                dataGridView3.Rows.Remove(row);
            }
            foreach (DataGridViewRow row in dataGridView4.SelectedRows)
            {
                dataGridView4.Rows.Remove(row);
            }
            foreach (DataGridViewRow row in dataGridView5.SelectedRows)
            {
                dataGridView5.Rows.Remove(row);
            }
            foreach (DataGridViewRow row in dataGridView6.SelectedRows)
            {
                dataGridView6.Rows.Remove(row);
            }
            foreach (DataGridViewRow row in dataGridView7.SelectedRows)
            {
                dataGridView7.Rows.Remove(row);
            }
            foreach (DataGridViewRow row in dataGridView8.SelectedRows)
            {
                dataGridView8.Rows.Remove(row);
            }
            foreach (DataGridViewRow row in dataGridView9.SelectedRows)
            {
                dataGridView9.Rows.Remove(row);
            }

        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                connection.Open();
                
                adapter = new SqlDataAdapter(sqlProducts, connection);
                ds1 = new DataSet();
                adapter.Fill(ds1);
                commandBuilder = new SqlCommandBuilder(adapter);
                adapter.InsertCommand = new SqlCommand("sp_CreateProduct", connection);
                adapter.InsertCommand.CommandType = CommandType.StoredProcedure;
                adapter.InsertCommand.Parameters.Add(new SqlParameter("@price", SqlDbType.Int, 0, "Price"));
                adapter.InsertCommand.Parameters.Add(new SqlParameter("@quantity", SqlDbType.Int, 0, "Quantity"));
                adapter.InsertCommand.Parameters.Add(new SqlParameter("@collectionId", SqlDbType.Int, 0, "CollectionId"));
                adapter.InsertCommand.Parameters.Add(new SqlParameter("@cosmTypeId", SqlDbType.Int, 0, "CosmTypeId"));
                adapter.InsertCommand.Parameters.Add(new SqlParameter("@colorId", SqlDbType.Int, 0, "ColorId"));
                adapter.InsertCommand.Parameters.Add(new SqlParameter("@finishId", SqlDbType.Int, 0, "FinishId"));

                SqlParameter parameter = adapter.InsertCommand.Parameters.Add("@Id", SqlDbType.Int, 0, "Id");
                parameter.Direction = ParameterDirection.Output;
                
                adapter.Update(ds1);
            }
        }
    }
}
