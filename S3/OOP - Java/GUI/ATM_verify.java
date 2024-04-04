import java.io.*;
import java.util.*;
import javax.swing.*;
import java.awt.event.*;
class ATM extends JFrame implements ActionListener
{
    JButton verify,details;
    JTextField ano,pass,name,bal,rs;
    ATM()
    {
        super("ATM");
        verify=new JButton("Verify");
        details=new JButton ("Details");
        ano=new JTextField("ano",10);
        pass=new JTextField("pass",10);
        name=new JTextField ("name",10);
        bal=new JTextField("bal",10);
        rs=new JTextField("rs",10);
        add(verify);
        add(details);
        add(ano);
        add(pass);
        add(name);
        add(bal);
        add(rs);
        setLayout(null);
        verify.setBounds(120,30,100,30);
        details.setBounds(120,70,100,30);
        ano.setBounds(10,20,100,20);
        pass.setBounds(10,60,100,20);
        rs.setBounds(10,250,100,20);
        name.setBounds(10,140,100,20);
        bal.setBounds(10,180,100,20);
        setSize(400,300);
        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        verify.addActionListener(this);
        details.addActionListener(this);
    }
    public void actionPerformed(ActionEvent ae)
    {
        try
        {

            Object source=ae.getSource();
            int flag=0;
            int ac= Integer.parseInt(ano.getText());
            int ps= Integer.parseInt(pass.getText());
            if (source==verify)
            {
                FileReader acc=new FileReader("accno.txt");
                FileReader pss=new FileReader("pin.txt");
                int pcount=0,acount=0;
                Scanner fscan1=new Scanner(acc);
                Scanner fscan2=new Scanner(pss);
                while(fscan1.hasNextInt()==true)
                {
                    int a=fscan1.nextInt();
                    
                    if (a!=ac)
                    {
                        acount++;
                    } else {
                        break;
                    }
                }
                while (fscan2.hasNextInt()==true)
                {
                    int b=fscan2.nextInt();
                    if (b!=ps)
                    {
                        pcount++;
                    } else {
                        break;
                    }
                }
                if (acount==pcount)
                {
                    flag=1;
                    rs.setText("verified");
                }
                else
                {
                    rs.setText("Not verified");
                }
                acc.close();
                pss.close();
                fscan1.close();
                fscan2.close();
            }
        }
        catch(FileNotFoundException e)
        {
            rs.setText("file nott found");
        }
        catch(IOException e)
        {
            rs.setText("IO exceeption caught");
        }
    }
    public static void main(String args[])
    {
        ATM obj=new ATM();
    }
}
