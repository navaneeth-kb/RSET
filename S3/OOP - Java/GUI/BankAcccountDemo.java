import java.util.*;
class BankAccount
{
    int accno;
    double balance;
    String name;
    void setData(int a,String n,double b)
    {
        accno=a;
        balance=b;
        name=n;
    }
    void getData()
    {
        System.out.println("The account number is"+accno);
        System.out.println("The balance is"+balance);
        System.out.println("The customer name is"+name);
    }
    void Withdraw(double amt)
    {
        if(balance>=amt)
        {
            balance=balance-amt;
        }
        else
        {
            System.out.println("Insufficient balance");
        }

    }
    void Deposit(double amt)
    {
        balance=balance+amt;
        checkBalance();
    }
    void checkBalance()
    {
        System.out.println("Balance is "+balance );
    }
}
class BankAcccountDemo
{
    public static void main(String args[])
    {
        int acc;
        String nam;
        double bal;
        Scanner scan=new Scanner(System.in);
        BankAccount b1=new BankAccount();
        acc=scan.nextInt();
        scan.nextLine();
        nam=scan.nextLine();
        bal=scan.nextDouble();
        b1.setData(acc,nam,bal);
        b1.getData();
        b1.Deposit(2000);
        b1.Withdraw(200);
        b1.checkBalance();
    }
}
