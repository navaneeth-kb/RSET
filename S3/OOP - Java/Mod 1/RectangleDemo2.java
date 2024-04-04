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
        System.out.println("The breadth is"+bre);
    }
    void getArea()
    {
        int area;
        area=len*bre;
        System.out.println("The area is"+area);
    }
}
class Cuboid extends Rectangle
{
    int hei;
    void setData(int l,int b, int h)
    {
        super.setData(l,b);
        hei=h;
    }
    void getData()
    {
        super.getData();
        System.out.println("The height is"+hei);
    }
    void getArea()
    {
        int area;
        area=len*bre*hei;
        System.out.println("The area is"+area);
    }
}
class RectangleDemo2
{
    public static void main(String args[])
    {
        Cuboid c1=new Cuboid();
        c1.setData(3,5);
        c1.getData();
        c1.getArea();
        c1.setData(2,3,4);
        c1.getData();
        c1.getArea();
    }
}