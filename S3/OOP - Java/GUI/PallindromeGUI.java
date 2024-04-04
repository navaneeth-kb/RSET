import java.awt.*;
import java.awt.event.*;
class PallindromeGUI extends Frame implements ActionListener
{
    Button check;
    Label l1,l2;
    TextField t1,t2;
    PallindromeGUI()
    {
        super("Pallindrome Checker");
        check=new Button("Check");
        l1=new Label("Enter word:");
        l2=new Label("Result:");
        t1=new TextField(10);
        t2=new TextField(10);
        add(check);
        add(l1);
        add(l2);
        add(t1);
        add(t2);
        setLayout(null);
        l1.setBounds(10,20,100,20);
        t1.setBounds(10,60,100,20);
        l2.setBounds(10,100,100,20);
        t2.setBounds(10,140,100,20);
        check.setBounds(125,10,75,200);
        setVisible(true);
        setSize(400,300);
        check.addActionListener(this);
    }
    public void actionPerformed(ActionEvent ae)
    {
        Object source=ae.getSource();
        String word=t1.getText();
        int len=word.length();
        String rev="";
        for(int i=len-1;i>=0;i--)
        {
            rev=rev+word.charAt(i);
        }
        if(source==check)
        {
            if(word.equalsIgnoreCase(rev)==true)
            {
                t2.setText("Pallindrome");
            }
            else
            {
                t2.setText("Not pallidrome");
            }
        }
    }
    public static void main(String args[])
    {
        PallindromeGUI p1=new PallindromeGUI();
    }
}
