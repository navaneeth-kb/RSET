import java.util.*;
class MatAddTran
{
	public static void main(String args[])
	{
		System.out.println("Navaneeth K.B   Roll no.:6");
		int a[][]=new int[50][50];
		int b[][]=new int[50][50];
		int sum[][]=new int[50][50];
		Scanner scan=new Scanner(System.in);
		int m1,n1,m2,n2,i,j;
		System.out.println("Enter the dimensions of first matrix:");
		m1=scan.nextInt();
		n1=scan.nextInt();
		System.out.println("Enter the elements of first matrix:");
		for (i=0;i<m1;i++)
		{
			for (j=0;j<n1;j++)
			{
				a[i][j]=scan.nextInt();
			}
		}
		System.out.println("Enter the dimensions of second matrix:");
		m2=scan.nextInt();
		n2=scan.nextInt();
		System.out.println("Enter the elements of second matrix:");
		for (i=0;i<m2;i++)
		{
			for (j=0;j<n2;j++)
			{
				b[i][j]=scan.nextInt();
			}
		}
		if (m1==m2 && n1==n2)
		{
			for (i=0;i<m1;i++)
			{
				for (j=0;j<n1;j++)
				{
					sum[i][j]=a[i][j]+b[i][j];
				}
			}
		}
		else 
		{
			System.out.println("Addition is not possible");
			
		}
		System.out.println("Sum of two matrices is:");
		for (i=0;i<m1;i++)
		{
			for (j=0;j<n1;j++)
			{
				System.out.print(sum[i][j]+"\t");
			}
			System.out.print("\n");
		}
		System.out.println("Transpose of first matrix is:");
		for (i=0;i<n1;i++)
		{
			for (j=0;j<m1;j++)
			{
				System.out.print(sum[j][i]+"\t");
			}
			System.out.print("\n");
		}
	}
}
