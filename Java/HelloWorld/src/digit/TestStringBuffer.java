package digit;

public class TestStringBuffer {

	public TestStringBuffer() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		String str = "";
		StringBuffer strbuf = new StringBuffer(str);
		System.out.println(System.currentTimeMillis());
		for(int i=0; i<10000;i++)
		{
			str+=getString(10);
		}
		System.out.println(System.currentTimeMillis());
		for(int i=0; i< 100000;i++)
		{
			strbuf.append(getString(10));
		}
		System.out.println(System.currentTimeMillis());
		
	}

	private static void testStringBuffer() {
		String str = "StringBuffer";
		StringBuffer strbuf = new StringBuffer(str);
		strbuf.append(" append");
		System.out.println(strbuf);
		strbuf.delete(4,5);
		System.out.println(strbuf);
		strbuf.insert(4,'n');
		System.out.println(strbuf);
		strbuf.reverse();
		System.out.println(strbuf);
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
