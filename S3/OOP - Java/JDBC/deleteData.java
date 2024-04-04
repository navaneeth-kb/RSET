import java.sql.*;
import java.util.*;
class DeleteData
{
    public static void main(String args[ ]) throws ClassNotFoundException, SQLException
    {
        int count, rn;
        Class.forName("com.mysql.jdbc.Driver");
        Connection con =
        DriverManager.getConnection("jdbc:mysql://localhost:3306/college","root","pass");
        Statement stm = con.createStatement();
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter Roll No:");
        rn = scan.nextInt();
        String qry = "delete from student where rollno = "+rn;
        count = stm.executeUpdate(qry);
        if(count!=0)
        {
            System.out.println("Data Deleted");
        }
        else
        {
            System.out.println("Deletion Failed");
        }
        stm.close();
        con.close();
    }
}
