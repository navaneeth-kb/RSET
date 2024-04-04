import java.util.*;
import java.io.*;
class copy
{
    public static void main(String[] args) throws IOException 
    {
        String line;
        FileReader fin=new FileReader("test.txt");
        FileWriter fout=new FileWriter("output.txt");
        Scanner fscan=new Scanner(fin);
        while((fscan.hasNextLine())==true)
        {
            line=fscan.nextLine();
            fout.write(line+"\n");
        }
        fin.close();
        fout.close();
        fscan.close();
    }
}
