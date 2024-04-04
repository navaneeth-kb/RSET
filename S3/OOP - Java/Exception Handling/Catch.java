import java.util.*;
class Catch
{
    public static void main(String args[])
    {
        double a,b,q;
        Scanner scan=new Scanner(System.in);
        a=scan.nextInt();
        b=scan.nextInt();
        try
        {
            q=a/b;
            System.out.println("The result is"+q);
        }
        catch(ArithmeticException e)
        {
            System.out.println("Exception is"+e);
        }
    }
}
