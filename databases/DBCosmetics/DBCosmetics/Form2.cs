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

                comboBox6.DisplayMember = "Name";
                comboBox6.ValueMember = "Id";
                comboBox6.DataSource = ds.Tables["Store"];
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
                string sql = String.Format("SELECT Products.Id FROM Products " +
                    "where Products.Id in" +
                    "(select Stock.ProductId from Stock" +
                    "where Stock.StoreId in" +
                    "(select Stores.Id from Stores" +
                    "where Stores.Name='{1}'))" +
                    //"and Products.ColorId in " +
                    //"(select Colors.Id from Colors where Colors.Name='{0}')", 
                    comboBox1.Text,
                    comboBox2.Text);


                //SqlCommand command = new SqlCommand(sql, connection);
                adapter = new SqlDataAdapter(sql, connection);
                DataSet ds = new DataSet();
                adapter.Fill(ds);
                dataGridView1.DataSource = ds.Tables[0];
                //dataGridView1.DataSource = command.ExecuteReader();

            }
        }

        private void buttonRequest2_Click(object sender, EventArgs e)
        {

            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                connection.Open();
                string sql;
                if (comboBoxSql2.Text == "Products")
                {
                    sql = String.Format("SELECT * FROM Products " +
                    "WHERE ColorId in" +
                    "(select Id from Colors where Name='{0}')" +
                    "and CosmTypeId in" +
                    "(select Id from CosmTypes where Name='{1}')" +
                    "and CollectionId in" +
                    "(select Id from Collections where Name='{2}')" +
                    "and FinishId in" +
                    "(select Id from Finishes where Name='{3}')", comboBoxColor.Text, comboBoxType.Text, comboBoxCollection.Text, comboBoxFinish.Text);
                }
                else
                {
                    sql = String.Format("SELECT * FROM Stores inner join " +
                        "(Stock inner join " +
                        "(Products inner join Colors on Products.ColorId=Colors.Id and " +
                        "Products inner join Colections on Collections.Id=Products.CollectionId and " +
                        "Products inner join CosmTypes on CosmTypes.Id=Products.CosmTypeId and " +
                        "Products inner join Finishes on Finishes.Id=Products.FinishId)" +
                        "on Stock.ProductId=Products.Id)" +
                        "on Stock.StoreId=Stores.Id" +
                        "where  Colors.Name='{0}' and" +
                        "CosmTypes.Name='{1}' and" +
                        "Collections.Name='{2}' and" +
                        "Finishes.Name='{3}'"
                        

                    , comboBoxColor.Text, comboBoxType.Text, comboBoxCollection.Text, comboBoxFinish.Text);
                }
                adapter = new SqlDataAdapter(sql, connection);
                DataSet ds = new DataSet();
                adapter.Fill(ds);
                dataGridView1.DataSource = ds.Tables[0];


            }
        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void buttonRequest3_Click(object sender, EventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                connection.Open();
                string sql;
                if (comboBox5.Text == "in")
                {
                    if (comboBox3.Text != "Finish")
                    {
                        sql = String.Format("SELECT * FROM {0}s where Id in " +
                        "(select {0}Id from Products where Id in" +
                        "(select ProductId from Stock where StoreId in" +
                        "(select Id from Stores where Name='{1}')))"
                    , comboBox3.Text, comboBox6.Text);
                    }
                    else
                    {
                        sql = String.Format("SELECT * FROM {0}es where Id in " +
                        "(select {0}Id from Products where Id in" +
                        "(select ProductId from Stock where StoreId in" +
                        "(select Id from Stores where Name='{1}')))"
                    , comboBox3.Text, comboBox6.Text);
                    }
                }
                else
                {
                    if (comboBox3.Text != "Finish")
                    {
                        sql = String.Format("SELECT * FROM {0}s where Id not in " +
                        "(select {0}Id from Products where Id in" +
                        "(select ProductId from Stock where StoreId in" +
                        "(select Id from Stores where Name='{1}')))"
                    , comboBox3.Text, comboBox6.Text);
                    }
                    else
                    {
                        sql = String.Format("SELECT * FROM {0}es where Id not in " +
                        "(select {0}Id from Products where Id in" +
                        "(select ProductId from Stock where StoreId in" +
                        "(select Id from Stores where Name='{1}')))"
                    , comboBox3.Text, comboBox6.Text);
                    }
                }
                adapter = new SqlDataAdapter(sql, connection);
                DataSet ds = new DataSet();
                adapter.Fill(ds);
                dataGridView1.DataSource = ds.Tables[0];

            }
        }

        private void buttonRequest4_Click(object sender, EventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                connection.Open();
                string sql;
                if (comboBox3.Text != "Finish")
                {
                    sql = String.Format("SELECT * FROM {0}s where Id in " +
                    "(select {0}Id from Products where Id in" +
                    "(select ProductId from Stock where StoreId in" +
                    "(select Id from Stores where Name='{1}')))"
                , comboBox3.Text, comboBox6.Text);
                }
                else
                {
                    sql = String.Format("SELECT * FROM {0}es where Id in " +
                    "(select {0}Id from Products where Id in" +
                    "(select ProductId from Stock where StoreId in" +
                    "(select Id from Stores where Name='{1}')))"
                , comboBox3.Text, comboBox6.Text);
                }
                adapter = new SqlDataAdapter(sql, connection);
                DataSet ds = new DataSet();
                adapter.Fill(ds);
                dataGridView1.DataSource = ds.Tables[0];
            }
        }

        private void buttonRequest5_Click(object sender, EventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                connection.Open();
                string sql;
                sql = String.Format("SELECT * FROM Products where "
                    + "Price>={0} and Price<={1}"
                , textBox2.Text, textBox3.Text);
                adapter = new SqlDataAdapter(sql, connection);
                DataSet ds = new DataSet();
                adapter.Fill(ds);
                dataGridView1.DataSource = ds.Tables[0];
            }
        }

    }
}
