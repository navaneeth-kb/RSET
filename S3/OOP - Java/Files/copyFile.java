import java.io.*;
class copyFile
{
    public static void main(String args[]) throws IOException
    {
        int i;
        char c;
        FileReader fin=new FileReader("input.txt");
        FileWriter fout=new FileWriter("output.txt");
        while((i=fin.read())!=-1)
        {
            c=(char)i;
            System.out.println(c);
            fout.write(c);
        }
        fin.close();
        fout.close();
    }
}