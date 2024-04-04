import javax.swing.*;
import java.awt.event.*;
class color extends JFrame implements ActionListener,Runnable
{
    JTextField t1;
    JButton b1;
    color()
    {
        super("Rocket Launch");
        t1=new JTextField(10);
        b1=new JButton("Launch");
        add(t1);
        add(b1);
        setLayout(null);
        t1.setBounds(10,30,100,20);
        b1.setBounds(10,70,100,20);
        setSize(400,300);
        setVisible(true);
        b1.addActionListener(this);

    }
    public void actionPerformed(ActionEvent ae)
    {
        Object source=ae.getSource();
        if(source==b1)
        {
            Thread t=new Thread(this);
            t.start();
        }
    }
    public void run()
    {
        try
        {
            for(int i=10;i>-1;i--)
            {
                t1.setText(Integer.toString(i));
                if(i==1)
                {
                    getContentPane().setBackground(java.awt.Color.RED);
                    Thread.sleep(1000);
                }
                else if(i==2)
                {
                    getContentPane().setBackground(java.awt.Color.BLACK);
                    Thread.sleep(1000);
                }
                else if(i==3)
                {
                    getContentPane().setBackground(java.awt.Color.RED);
                    Thread.sleep(1000);
                }
                else
                {
                    //getContentPane().setBackground(java.awt.color.RED);
                    Thread.sleep(500);
                }
            }

        }
        catch(InterruptedException e)
        {
            System.out.println("Caught exception"+e);
        }
    }
    public static void main(String[] args) {
        color c1=new color();
    }
}
