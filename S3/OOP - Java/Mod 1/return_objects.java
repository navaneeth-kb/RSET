class Rectangle
{
    int len,bre;
    void getData()
    {
        System.out.println("The length is"+len);
        System.out.println("The breadth is"+bre);   
    }

}
class Shape
{
    Rectangle setData(int l,int b)
    {
       Rectangle r=new Rectangle();
       r.len=l;
       r.bre=b;
       return r;
    }
}
class return_objects
{
    public static void main(String args[])
    {
        Shape s1=new Shape();
        Rectangle r1=s1.setData(5,6);
        r1.getData();
    }
}