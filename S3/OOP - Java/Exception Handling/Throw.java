import java.util.*;
class Throw
{
    public static void main(String args[])
    {
        double r,area;
        Scanner scan=new Scanner(System.in);
        r=scan.nextInt();
        try
        {
            if(r<0)
            {
                throw new Exception("Enter +ve radius");

            }
            area=3.14*r*r;
            System.out.println("The area is"+area);
        }
        catch(Exception e)
        {
            System.out.println("Exception is"+e);
        }
    }
}