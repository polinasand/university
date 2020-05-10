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

        DataSet ds1;
        SqlDataAdapter adapterProducts;
        SqlDataAdapter adapterFinishes;
        DataSet ds2;
        SqlDataAdapter adapterStores;
        DataSet ds3;
        SqlDataAdapter adapterStocks;
        DataSet ds4;
        SqlDataAdapter adapterWorkers;
        DataSet ds5;
        SqlDataAdapter adapterPositions;
        DataSet ds6;
        SqlDataAdapter adapterCosmTypes;
        DataSet ds7;
        SqlDataAdapter adapterCollections;
        DataSet ds8;
        SqlDataAdapter adapterColors;
        DataSet ds9;
        
        SqlCommandBuilder commandBuilder;
        SqlParameter parameter;
        public Form1()
        {
            InitializeComponent();

            
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                connection.Open();
                 adapterProducts = new SqlDataAdapter(sqlProducts, connection);
                 ds1 = new DataSet();
                 adapterProducts.Fill(ds1);
                 dataGridView1.DataSource = ds1.Tables[0];
                 dataGridView1.Columns["Id"].ReadOnly = true;


                 adapterFinishes = new SqlDataAdapter(sqlFinishes, connection);
                 ds2 = new DataSet();
                 adapterFinishes.Fill(ds2);
                 dataGridView2.DataSource = ds2.Tables[0];
                 dataGridView2.Columns["Id"].ReadOnly = true;


                 adapterStores = new SqlDataAdapter(sqlStores, connection);
                 ds3 = new DataSet();
                 adapterStores.Fill(ds3);
                 dataGridView3.DataSource = ds3.Tables[0];
                 dataGridView3.Columns["Id"].ReadOnly = true;


                 adapterStocks = new SqlDataAdapter(sqlStocks, connection);
                 ds4 = new DataSet();
                 adapterStocks.Fill(ds4);
                 dataGridView4.DataSource = ds4.Tables[0];
                 dataGridView4.Columns["Id"].ReadOnly = true;


                 adapterWorkers = new SqlDataAdapter(sqlWorkers, connection);
                 ds5 = new DataSet();
                 adapterWorkers.Fill(ds5);
                 dataGridView5.DataSource = ds5.Tables[0];
                 dataGridView5.Columns["Id"].ReadOnly = true;


                 adapterPositions = new SqlDataAdapter(sqlPositions, connection);
                 ds6 = new DataSet();
                 adapterPositions.Fill(ds6);
                 dataGridView6.DataSource = ds6.Tables[0];
                 dataGridView6.Columns["Id"].ReadOnly = true;


                 adapterCosmTypes = new SqlDataAdapter(sqlCosmTypes, connection);
                 ds7 = new DataSet();
                 adapterCosmTypes.Fill(ds7);
                 dataGridView7.DataSource = ds7.Tables[0];
                 dataGridView7.Columns["Id"].ReadOnly = true;

                 adapterCollections = new SqlDataAdapter(sqlCollections, connection);
                 ds8 = new DataSet();
                 adapterCollections.Fill(ds8);
                 dataGridView8.DataSource = ds8.Tables[0];
                 dataGridView8.Columns["Id"].ReadOnly = true;


                 adapterColors = new SqlDataAdapter(sqlColors, connection);
                 ds9 = new DataSet();
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
                //products
                adapterProducts = new SqlDataAdapter(sqlProducts, connection);
                
                commandBuilder = new SqlCommandBuilder(adapterProducts);
                adapterProducts.InsertCommand = new SqlCommand("INSERT INTO Products " +
                    "(Price, Quantity, CollectionId, CosmTypeId, FinishId, ColorId)" +
                    "  VALUES (@price, @quantity, @collectionId, @cosmTypeId, @finishId, @colorId) SET @Id=SCOPE_IDENTITY()",
                connection);
                
                adapterProducts.InsertCommand.Parameters.Add(new SqlParameter("@price", SqlDbType.Int, 0, "Price"));
                adapterProducts.InsertCommand.Parameters.Add(new SqlParameter("@quantity", SqlDbType.Int, 12, "Quantity"));
                adapterProducts.InsertCommand.Parameters.Add(new SqlParameter("@collectionId", SqlDbType.Int, 0, "CollectionId"));
                adapterProducts.InsertCommand.Parameters.Add(new SqlParameter("@finishId", SqlDbType.Int, 0, "FinishId"));
                adapterProducts.InsertCommand.Parameters.Add(new SqlParameter("@colorId", SqlDbType.Int, 0, "ColorId"));
                adapterProducts.InsertCommand.Parameters.Add(new SqlParameter("@cosmTypeId", SqlDbType.Int, 0, "CosmTypeId"));

                parameter = adapterProducts.InsertCommand.Parameters.Add("@Id", SqlDbType.Int, 0, "Id");
                parameter.Direction = ParameterDirection.Output;

                adapterProducts.Update(ds1);

                //finish
                adapterFinishes = new SqlDataAdapter(sqlFinishes, connection);
                
                commandBuilder = new SqlCommandBuilder(adapterFinishes);
                adapterFinishes.InsertCommand = new SqlCommand("INSERT INTO Finishes " +
                    "(Name)" +
                    " VALUES (@name) SET @Id=SCOPE_IDENTITY()",
                connection);

                adapterFinishes.InsertCommand.Parameters.Add(new SqlParameter("@name", SqlDbType.VarChar, 50, "Name"));
             
                parameter = adapterFinishes.InsertCommand.Parameters.Add("@Id", SqlDbType.Int, 0, "Id");
                parameter.Direction = ParameterDirection.Output;

                adapterFinishes.Update(ds2);

                //Stores
                adapterStores = new SqlDataAdapter(sqlStores, connection);

                commandBuilder = new SqlCommandBuilder(adapterStores);
                adapterStores.InsertCommand = new SqlCommand("INSERT INTO Stores " +
                    "(Name, Address)" +
                    " VALUES (@name, @address) SET @Id=SCOPE_IDENTITY()",
                connection);

                adapterStores.InsertCommand.Parameters.Add(new SqlParameter("@name", SqlDbType.VarChar, 50, "Name"));
                adapterStores.InsertCommand.Parameters.Add(new SqlParameter("@address", SqlDbType.VarChar, 50, "Address"));

                parameter = adapterStores.InsertCommand.Parameters.Add("@Id", SqlDbType.Int, 0, "Id");
                parameter.Direction = ParameterDirection.Output;

                adapterStores.Update(ds3);

                //Stock
                adapterStocks = new SqlDataAdapter(sqlStocks, connection);

                commandBuilder = new SqlCommandBuilder(adapterStocks);
                adapterStocks.InsertCommand = new SqlCommand("INSERT INTO Stock " +
                    "(StoreId, ProductId, Quantity)" +
                    " VALUES (@storeId, @productId, @quantity) SET @Id=SCOPE_IDENTITY()",
                connection);

                adapterStocks.InsertCommand.Parameters.Add(new SqlParameter("@storeId", SqlDbType.Int, 0, "StoreId"));
                adapterStocks.InsertCommand.Parameters.Add(new SqlParameter("@productId", SqlDbType.Int, 0, "ProductId"));
                adapterStocks.InsertCommand.Parameters.Add(new SqlParameter("@quantity", SqlDbType.Int, 0, "Quantity"));

                parameter = adapterStocks.InsertCommand.Parameters.Add("@Id", SqlDbType.Int, 0, "Id");
                parameter.Direction = ParameterDirection.Output;

                adapterStocks.Update(ds4);
                //Workers;
                adapterWorkers = new SqlDataAdapter(sqlWorkers, connection);

                commandBuilder = new SqlCommandBuilder(adapterWorkers);
                adapterWorkers.InsertCommand = new SqlCommand("INSERT INTO Workers " +
                    "(Name, StoreId, PositionId)" +
                    " VALUES (@name, @storeId, @positionId) SET @Id=SCOPE_IDENTITY()",
                connection);
                adapterWorkers.InsertCommand.Parameters.Add(new SqlParameter("@name", SqlDbType.VarChar, 50, "Name"));
                adapterWorkers.InsertCommand.Parameters.Add(new SqlParameter("@storeId", SqlDbType.Int, 0, "StoreId"));
                adapterWorkers.InsertCommand.Parameters.Add(new SqlParameter("@positionId", SqlDbType.Int, 0, "PositionId"));

                parameter = adapterWorkers.InsertCommand.Parameters.Add("@Id", SqlDbType.Int, 0, "Id");
                parameter.Direction = ParameterDirection.Output;

                adapterWorkers.Update(ds5);

                //Positions;
                adapterPositions = new SqlDataAdapter(sqlPositions, connection);

                commandBuilder = new SqlCommandBuilder(adapterPositions);
                adapterPositions.InsertCommand = new SqlCommand("INSERT INTO Positions " +
                    "(Name)" +
                    " VALUES (@name) SET @Id=SCOPE_IDENTITY()",
                connection);
                adapterPositions.InsertCommand.Parameters.Add(new SqlParameter("@name", SqlDbType.VarChar, 50, "Name"));

                parameter = adapterPositions.InsertCommand.Parameters.Add("@Id", SqlDbType.Int, 0, "Id");
                parameter.Direction = ParameterDirection.Output;

                adapterPositions.Update(ds6);

                //CosmTypes;
                adapterCosmTypes = new SqlDataAdapter(sqlCosmTypes, connection);

                commandBuilder = new SqlCommandBuilder(adapterCosmTypes);
                adapterCosmTypes.InsertCommand = new SqlCommand("INSERT INTO CosmTypes " +
                    "(Name)" +
                    " VALUES (@name) SET @Id=SCOPE_IDENTITY()",
                connection);
                adapterCosmTypes.InsertCommand.Parameters.Add(new SqlParameter("@name", SqlDbType.VarChar, 50, "Name"));

                parameter = adapterCosmTypes.InsertCommand.Parameters.Add("@Id", SqlDbType.Int, 0, "Id");
                parameter.Direction = ParameterDirection.Output;

                adapterCosmTypes.Update(ds7);

                //Collections;
                adapterCollections = new SqlDataAdapter(sqlCollections, connection);

                commandBuilder = new SqlCommandBuilder(adapterCollections);
                adapterCollections.InsertCommand = new SqlCommand("INSERT INTO Collections " +
                    "(Name, Info)" +
                    " VALUES (@name, @Info) SET @Id=SCOPE_IDENTITY()",
                connection);
                adapterCollections.InsertCommand.Parameters.Add(new SqlParameter("@name", SqlDbType.VarChar, 50, "Name"));
                adapterCollections.InsertCommand.Parameters.Add(new SqlParameter("@info", SqlDbType.VarChar, 50, "Info"));

                parameter = adapterCollections.InsertCommand.Parameters.Add("@Id", SqlDbType.Int, 0, "Id");
                parameter.Direction = ParameterDirection.Output;

                adapterCollections.Update(ds8);
                //Colors;
                adapterColors = new SqlDataAdapter(sqlColors, connection);

                commandBuilder = new SqlCommandBuilder(adapterColors);
                adapterColors.InsertCommand = new SqlCommand("INSERT INTO Colors " +
                    "(Name)" +
                    " VALUES (@name) SET @Id=SCOPE_IDENTITY()",
                connection);
                adapterColors.InsertCommand.Parameters.Add(new SqlParameter("@name", SqlDbType.VarChar, 50, "Name"));

                parameter = adapterColors.InsertCommand.Parameters.Add("@Id", SqlDbType.Int, 0, "Id");
                parameter.Direction = ParameterDirection.Output;

                adapterColors.Update(ds9);
            }
            
        }
    }
}
