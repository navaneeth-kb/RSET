import java.util.*;
class array
{    
    public static void main(String args[])
    {
        int arr[]=new int[50];
        int count=0,n,i;
        Scanner scan=new Scanner(System.in);
        n=scan.nextInt();
        for(i=0;i<n;i++)
        {
            arr[i]=scan.nextInt();
        }
        for(i=0;i<n;i++)
        {
            System.out.println(arr[i]+"\t");
            if (arr[i]%7==0)
            {
                count++;
            }
        }
        System.out.println(count);
    }
}
