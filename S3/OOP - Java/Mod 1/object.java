class Rectangle
{
    int len,bre;
    void setData(int l,int b)
    {
        len=l;
        bre=b;
    }
    void getData()
    {
        System.out.println("The length is"+len);
        System.out.println("The bredth is"+bre);
    }
}
class Double
{
    void doubleDimension(Rectangle r)
    {
        r.len=r.len*2;
        r.bre=r.bre*2;
    }
}
class object
{
    public static void main(String args[])
    {
        Rectangle r1=new Rectangle();
        r1.setData(2,3);
        r1.getData();
        Double d1=new Double();
        d1.doubleDimension(r1);
        r1.getData();
    }
}
