import java.awt.*;
import java.awt.event.*;
class Mouse extends Frame implements MouseListener
{
    Label message, xcoor,ycoor;
    TextField t1,t2;
    Mouse()
    {
        super("Mouse application");
        xcoor=new Label("X coordinate:");
        ycoor=new Label("Y coordinate:");
        message=new Label("Mouse Events");
        t1=new TextField(10);
        t2=new TextField(10);
        add(message);
        add(xcoor);
        add(ycoor);
        add(t1);
        add(t2);
        setLayout(null);
        xcoor.setBounds(20,40,80,15);
        ycoor.setBounds(20,70,80,15);
        t1.setBounds(100,40,100,15);
        t2.setBounds(100,80,100,15);
        message.setBounds(20,100,100,75);
        setSize(400,300);
        setVisible(true);
        this.addMouseListener(this);
    }
    public void mouseClicked(MouseEvent me)
    {
        int xc=me.getX();
        int yc=me.getY();
        t1.setText(Integer.toString(xc));
        t2.setText(Integer.toString(yc));
        message.setText("Mouse Clicked");
    }
    public void mouseEntered(MouseEvent me)
    {
        message.setText("Mouse Entered");
    }
    public void mouseExited(MouseEvent me)
    {
        message.setText("Mouse exited");
    }
    public void mousePressed(MouseEvent me)
    {
        int bt=me.getButton();
        if (bt==1)
        {
            message.setText("Left button clicked");
        }
        else if(bt==3)
        {
            message.setText("Right button clicked");
        }
    }
    public void mouseReleased(MouseEvent me)
    {

    }
    public static void main(String args[])
    {
        Mouse m1=new Mouse();
    }
  
}