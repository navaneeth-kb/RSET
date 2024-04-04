interface ISolid
{
    double PI=3.14;
    void getVolume();
}
class Cylinder implements ISolid
{
    double radius,height;
    void setData(double r,double h)
    {
        radius=r;
        height=h;
    }
    public void getVolume()
    {
        double vol;
        vol=PI*radius*radius*radius;
        System.out.println("The volume is"+vol);
    }

}
class Cone implements ISolid
{
    double radius,height;
    void setData(double r,double h)
    {
        radius=r;
        height=h;
    }
    public void getVolume()
    {
        double vol;
        vol=0.33*PI*radius*radius*height;
        System.out.println("The volume is"+vol);
    }

}
class interface2
{
    public static void main(String args[])
    {
        Cylinder c1=new Cylinder();
        c1.setData(2.5,1.5);
        c1.getVolume();
        Cone c2=new Cone();
        c2.setData(1.5,2.4);
        c2.getVolume();
    }
}
