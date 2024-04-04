import java.sql.*;
import java.util.*;
class InsertData
{
    public static void main(String args[ ]) throws ClassNotFoundException, SQLException
    {
        int rno, count;
        double cgpa;
        String nam;
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter Student Data");
        nam = scan.nextLine( );
        rno = scan.nextInt( );
        cgpa = scan.nextDouble( );
        Class.forName("com.mysql.jdbc.Driver");
        Connection con =
        DriverManager.getConnection("jdbc:mysql://localhost:3306/college","root","pass");
        Statement stm = con.createStatement();
        String qry = "insert into student (rollno,name,cgpa) values ("+rno+",'"+nam+"',"+cgpa+")";
        count = stm.executeUpdate(qry);
        if(count==1)
        {
            System.out.println("Data inserted successfully !");
        }
        else
        {
            System.out.println("Data insertion failed !");
        }
        stm.close();
        con.close();
    }
}
