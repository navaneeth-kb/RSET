class EvenThread extends Thread
{
    EvenThread()
    {
        start();
    }
    public void run()
    {
        try
        {
            for(int i=0;i<10;i+=2)
            {
                System.out.println(i);
                Thread.sleep(500);
            }
        }
        catch(InterruptedException e)
        {
            System.out.println("Even thread interrupted");
        }
    }
}
class OddThread extends Thread
{
    OddThread()
    {
        start();
    }
    public void run()
    {
        try
        {
            for(int i=1;i<10;i+=2)
            {
                System.out.println(i);
                Thread.sleep(500);
            }
        }
        catch(InterruptedException e)
        {
            System.out.println("Odd thread interrupted");
        }
    }
}
class threadDemo
{
    public static void main(String args[])
    {
        EvenThread evobj=new EvenThread();
        OddThread odobj=new OddThread();
    }
}