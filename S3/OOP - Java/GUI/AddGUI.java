import javax.swing.*;
import java.awt.event.*;
class AddGUI extends JFrame implements ActionListener
{
    JButton ad;
    JLabel heading;
    JTextField num1,num2,res;
    AddGUI()
    {
        super("Addition Application");
        ad=new JButton("Add");
        num1=new JTextField(10);
        num2=new JTextField(10);
        res=new JTextField(10);
        heading=new JLabel("Calculator");
        add(ad);
        add(res);
        add(num1);
        add(num2);
        add(heading);
        setLayout(null);
        ad.setBounds(125,10,75,200);
        heading.setBounds(10,20,100,20);        
        num1.setBounds(10,60,100,20);
        num2.setBounds(10,100,100,20);
        res.setBounds(10,150,100,20);
       
        setSize(400,300);
        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        ad.addActionListener(this);
    }
    public void actionPerformed(ActionEvent ae)
    {
        Object source=ae.getSource();
        int n1,n2,result;
        n1=Integer.parseInt(num1.getText());
        n2=Integer.parseInt(num2.getText());
        if (source==ad)
        {
            result=n1+n2;
            res.setText(Integer.toString(result));
        }
    }
    public static void main(String args[])
    {
        AddGUI obj=new AddGUI();
    }
}