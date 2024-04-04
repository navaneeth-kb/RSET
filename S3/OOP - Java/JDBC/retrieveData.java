import java.sql.*;
class DisplayData
{
    public static void main(String args[ ])
    {
        try
        {
            int numrows = 0;
            Class.forName("com.mysql.jdbc.Driver");
            Connection con =
            DriverManager.getConnection("jdbc:mysql://localhost:3306/college","root","pass");
            Statement stm = con.createStatement();
            String qry = "select * from student";
            ResultSet rs = stm.executeQuery(qry);
            while(rs.next())
            {
                System.out.println(rs.getInt(1)+"\t"+rs.getString(2)+"\t"+rs.getDouble(3));
                numrows++;
            }
            if(numrows>0)
            {
                System.out.println(numrows+" rows retrieved!");
            }
            else
            {
                System.out.println("Data not found");
            }
            rs.close();
            stm.close();
            con.close();
        }
        catch(ClassNotFoundException e)
        {
            System.out.println(e);
        }
        catch(SQLException e)
        {
            System.out.println(e);
        }
    }
}
