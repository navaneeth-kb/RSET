import java.io.*;
import java.util.*;
import javax.swing.*;
import java.awt.event.*;
class ATM extends JFrame implements ActionListener
{
    JButton dep,with,tran,bal;
    JTextField ano,amt,bala,ano2;
    ATM()
    {
        super("ATM");
        dep=new JButton("Deposit");
        with=new JButton ("Withdraw");
        tran=new JButton("Transfer");
        bal=new JButton("Balance");
        ano=new JTextField(10);
        amt=new JTextField(10);
        bala=new JTextField(10);
        ano2=new JTextField(10);
        add(dep);
        add(with);
        add(tran);
        add(bal);
        add(ano);
        add(amt);
        add(bala);
        add(ano2);
        setLayout(null);
        ano.setBounds(10,30,100,20);
        amt.setBounds(10,70,100,20);
        bala.setBounds(10,110,100,20);
        ano2.setBounds(10,150,100,20);
        dep.setBounds(120,30,100,20);
        with.setBounds(120,70,100,20);
        tran.setBounds(120,110,100,20);
        bal.setBounds(120,150,100,20);
        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setSize(400,300);
        dep.addActionListener(this);
        with.addActionListener(this);
        bal.addActionListener(this);
        tran.addActionListener(this);

    }
    public void actionPerformed(ActionEvent ae)
    {
        try
        {
            Object source =ae.getSource();
            int  balance=0,amount=0,balance1=0,balance2=0;
            Scanner scan=new Scanner(System.in);
            if(source==dep)
            {
                String an=ano.getText();
                String fname=an+".txt";
                FileReader fin=new FileReader(fname);
                Scanner fscan=new Scanner(fin);
                if(fscan.hasNextInt())
                {
                    balance=fscan.nextInt();
                }
                fin.close();
                amount=Integer.parseInt(amt.getText());
                balance=balance+amount;
                FileWriter fout=new FileWriter(fname);
                fout.write(Integer.toString(balance));
                bala.setText(Integer.toString(balance));
                fout.close(); 
            }
            else if(source==with)
            {
                String an=ano.getText();
                String fname=an+".txt";
                FileReader fin=new FileReader(fname);
                Scanner fscan=new Scanner(fin);
                if(fscan.hasNextInt())
                {
                    balance=fscan.nextInt();
                }
                fin.close();
                amount=Integer.parseInt(amt.getText());
                if(amount>balance)
                {
                    throw new Exception("insufficient balance");
                }
                balance=balance-amount;
                FileWriter fout=new FileWriter(fname);
                fout.write(Integer.toString(balance));
                bala.setText(Integer.toString(balance));
                fout.close(); 
            }
            else if(source==bal)
            {
                String an=ano.getText();
                String fname=an+".txt";
                FileReader fin=new FileReader(fname);
                Scanner fscan=new Scanner(fin);
                if(fscan.hasNextInt())
                {
                    balance=fscan.nextInt();
                }
                fin.close();
                bala.setText(Integer.toString(balance));
            }
            else if(source==tran)
            {
                String an1=ano.getText();
                String fname1=an1+".txt";
                FileReader fin1=new FileReader(fname1);
                Scanner fscan1=new Scanner(fin1);
                if(fscan1.hasNextInt())
                {
                    balance1=fscan1.nextInt();
                }
                fin1.close();
                String an2=ano2.getText();
                String fname2=an2+".txt";
                FileReader fin2=new FileReader(fname2);
                Scanner fscan2=new Scanner(fin2);
                if(fscan2.hasNextInt())
                {
                    balance2=fscan2.nextInt();
                }
                fin2.close();
                amount=Integer.parseInt(amt.getText());
                if(amount>balance1)
                {
                    throw new Exception("insufficient balance");
                }
                balance1=balance1-amount;
                balance2=balance2+amount;
                FileWriter fout1=new FileWriter(fname1);
                fout1.write(Integer.toString(balance1));
                fout1.close(); 
                FileWriter fout2=new FileWriter(fname2);
                fout2.write(Integer.toString(balance2));
                fout2.close();   
                bala.setText(Integer.toString(balance1));
            }

        }
        catch(FileNotFoundException e)
        {
            System.out.println("Caught exception"+e);
        }
        catch(IOException e)
        {
            System.out.println("Caught exception"+e);
        }
        catch (Exception e)
        {
            System.out.println("Caught exception"+e);
        }


    }
    public static void main(String args[])
    {
        ATM a1=new ATM();
    }
}
