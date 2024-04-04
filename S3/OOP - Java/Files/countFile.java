import java.util.*;
import java.io.*;
class countFile
{
    public static void main(String args[]) throws IOException
    {
        int count=0;
        String input,word;
        Scanner scan=new Scanner(System.in);
        System.out.println("Enter word:");
        input=scan.next();
        FileReader fin=new FileReader("test.txt");
        Scanner fscan=new Scanner(fin);
        while((fscan.hasNext())==true)
        {
            word=fscan.next();
            if(word.equalsIgnoreCase(input))
            {
                count++;
            }
        }
        System.out.println(count);
    }
}