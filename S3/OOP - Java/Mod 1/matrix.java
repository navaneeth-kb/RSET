import java.util.Scanner;

class matrix
{
    public static void main(String args[])
    {
        int arr[][]=new int[20][30];
        Scanner scan=new Scanner(System.in);
        int r,c,i,j;
        r=scan.nextInt();
        c=scan.nextInt();
        System.out.println("Enter elements:");
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
                arr[i][j]=scan.nextInt();
            }
        }
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
                System.out.print(arr[i][j]+"\t");
            }
            System.out.print("\n");
        }       
    }
}
