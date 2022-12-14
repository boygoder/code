package digit;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class TestDate {

	public TestDate() {
		// TODO Auto-generated constructor stub
	}
	public static void main(String[] args) {
		Date d = new Date(122,5,1,1,0,0);
		Calendar  c = Calendar.getInstance();
		c.setTime(d);
		System.out.println(c.getTime());
		
		c.add(Calendar.MONTH, 2);
		c.set(Calendar.DAY_OF_MONTH, 1);
		System.out.println(c.getTime());
		c.add(Calendar.DAY_OF_MONTH,-3);
		System.out.println("下个月的倒数第三天:\t" +c.getTime());
	}
	private static void sortDate() {
		Date[] date = new Date[9];
		for(int i=0; i < date.length; i++)
		{
			date[i] = randomDate();
		}
		for(int i =0; i< date.length-1;i++)
		{
			for(int j=0; j < date.length-1-i;j++)
			{
				if(date[j].getTime() > date[j+1].getTime() )
				{
					Date tmp = date[j];
					date[j] = date[j+1];
					date[j+1] =tmp;
				}
			}
		}
		
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		for(int i=0; i< date.length;i++)
		{
			System.out.print(sdf.format(date[i])+" ");
		}
	}
	
	private static Date randomDate()
	{
		Date d1 = new Date(70,0,1,8,0,0);
		Date d2 = new Date(100,11,31,23,59,59);
		long randomms = (long)(Math.random()*(d2.getTime() - d1.getTime()) + d1.getTime());
		Date randomdate = new Date(randomms);
		return randomdate;
	}
}
