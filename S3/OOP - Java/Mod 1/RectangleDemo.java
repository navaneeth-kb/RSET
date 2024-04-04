class Rectangle
{
    int len,bre;
    Rectangle(int l,int b)
    {
        len=l;
        bre=b;
    }
    void getData()
    {
        System.out.println("The length is"+len);
        System.out.println("The breadth is"+bre);
    }
    int getArea()
    {
        int area;
        area=len*bre;
        return area;
    }
}
class RectangleDemo
{
    public static void main(String args[])
    {
        Rectangle r=new Rectangle(5,3);
        r.getData();
        int a;
        a=r.getArea();
        System.out.println(a);
    }
}
