class Display
{
    void print()
    {
        try
        {
            System.out.println("##");
            Thread.sleep(500);
            System.out.println("@@");
        }
        catch(InterruptedException e)
        {
            System.out.println("Excepttion interruppted");
        }
    }
}
class T implements Runnable
{
    T()
    {
        Thread t1=new Thread(this);
        Thread t2=new Thread(this);
        t1.start();
        t2.start();
    }
    Display d1=new Display();
    public void run()
    {
        synchronized(d1)
        {
            d1.print();
        }
    }
}
class Thread_Syn
{
    public static void main(String args[])
    {
        T te=new T();
    }
}