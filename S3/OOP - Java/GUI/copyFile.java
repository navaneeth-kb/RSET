import java.io.*;
import javax.swing.*;
import java.awt.event.*;
class copyFile extends JFrame implements ActionListener
{
    JTextField t1,t2;
    JButton b1;
    copyFile()
    {
        super("Copy file");
        t1=new JTextField(10);
        t2=new JTextField(10);
        b1=new JButton("Copy");
        add(t1);
        add(t2);
        add(b1);
        setLayout(null);
        t1.setBounds(10,30,100,20);
        t2.setBounds(10,70,100,20);
        b1.setBounds(10,110,100,20);
        setSize(400,300);
        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        b1.addActionListener(this);

    }
    public void actionPerformed(ActionEvent ae)
    {
        try
        {
            Object source=ae.getSource();
            int i;
            char c;
            
            if(source==b1)
            {
                String f1=t1.getText();
                String fname1=f1+".txt";
                String f2=t2.getText();
                String fname2=f2+".txt";
                FileReader fin=new FileReader(fname1);
                FileWriter fout=new FileWriter(fname2);
                while((i=fin.read())!=-1)
                {
                    c=(char)i;
                    if(c=='a' || c=='e' || c=='i' || c=='o' || c=='u' || c=='A' || c=='E' || c=='I' || c=='O' || c=='U')
                    {
                        fout.write("$");
                    }
                    else
                    {
                        fout.write(i);
                    }
                }
                fin.close();
                fout.close();
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
    }
    public static void main(String args[])
    {
        copyFile c1=new copyFile();
    }
}
