package digit;

import java.util.Arrays;

public class TestNumber {

	public TestNumber() {
		// TODO Auto-generated constructor stub
	}
	public static void main(String[] args) {
			//firstBig();
		 	//tongueTwister();
			//bsb();
			//compareStr();
		
		
	}
	private static void compareStr()
	{
		String[] str = new String[100];
		for(int i=0; i <str.length;i++)
		{
			str[i] = getString(2);
		}
		String onestr="";
		for(int i=0; i < str.length;i++)
		{
			onestr+=str[i] + " ";
		}
		String newstr="";
		for(int i=0; i <str.length;i++)
		{
			int start = onestr.indexOf(str[i]);
			int end = onestr.lastIndexOf(str[i]);
			if(start!=end && !newstr.contains(str[i]))
			{
				newstr+=str[i]+" ";
			}
		}
		Arrays.sort(str);
		for(int i=0; i<str.length;i++)
		{
			System.out.print(str[i]+" ");
		}
		System.out.println();
		System.out.println(newstr);
	}
	private static void bsb()
	{
		String str = "lengendary";
		String newstr ="";
		for(int i=0; i < str.length();i++)
		{
			char c = str.charAt(i);
			if(i%2==0)
			{
				c = Character.toUpperCase(c);
			}
			newstr+=c;
		}
		System.out.println(newstr);
	}
	private static void tongueTwister()
	{
		String tongue  ="peter piper picked a peck of pickled peppers";
		String[] splittongue = tongue.split(" ");
		int num=0;
		for(int i=0; i <splittongue.length;i++)
		{
			char start = splittongue[i].charAt(0);
			if(start=='p')
			{
				num++;
			}
		}
		System.out.println(num);
	}
	private static void firstBig()
	{
		String str = "let there be light";
		System.out.println(str);
		String[] splitstr = str.split(" ");
		String str2 ="";
		for(int i=0; i < splitstr.length;i++)
		{
			char big = Character.toUpperCase(splitstr[i].charAt(0));
			str2 = str2+big;
			
			for(int j=1; j < splitstr[i].length();j++)
			{
				str2 = str2+splitstr[i].charAt(j);
			}
			
			if(i!=splitstr.length-1)
			{
				str2+=" ";
			}
		}
		System.out.println(str2);
	}
	
	private static String crackPass(String pass,int length)
	{
		if(length==0)
		{
			return "";
		}
		else
		{
			String prevous = crackPass(pass,length-1);
			for(int i=48; i < 122;i++)
			{
				char c = (char)i;
				if(c == pass.charAt(length-1))
				{
					prevous+=c;
				}
			}
			if(prevous.length() == length)
			{
					return prevous;
			}
			else
			{
				System.out.println("can not find");
			}
		}
		return pass;
	}
	private static void sortString() {
		String[] str = new String[8];
		for(int i=0; i< str.length;i++)
		{
			str[i] = getString();
		}
		for(int i=0; i < str.length;i++)
		{
			System.out.print(" "+str[i]);
		}
		System.out.println();
		for(int i=0; i < str.length-1;i++)
		{
			for(int j = 0;  j < str.length -i-1; j++)
			{
				char  c1 = Character.toUpperCase(str[j].charAt(0));
				char c2 = Character.toUpperCase(str[j+1].charAt(0));
				if(c1 > c2)
				{
					String tmp = str[j];
					str[j] = str[j+1];
					str[j+1] = tmp;
				}
			}
		}
		for(int i=0; i < str.length;i++)
		{
			System.out.print(" "+str[i]);
		}
	}
	private static String getString(int length) {
		char[] randomChar = new char[length];
		for(int i=0; i < randomChar.length;i++){
			int random1 = (int) (3*Math.random());
			if(random1 ==0)
			{
				randomChar[i] =  (char) ((int)'0' + (int)(10 * Math.random()));
			}
			else if(random1==1)
			{
				randomChar[i] =  (char) ((int)'a' + (int)(26 * Math.random()));
			}
			else if(random1==2)
			{
				randomChar[i] =  (char) ((int)'A' + (int)(26 * Math.random()));
			}
		}
		String str = new String(randomChar);
//		System.out.println(str);
		return str;
	}
}
