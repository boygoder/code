package com.example;

class HelloWorld {

	public static void main(String[] args) {
		System.out.println("hello world");
		//1.整数型
		byte b=1;//8bits
		short s =200;//16bits
		int i = 300;//32bits
		long l= 400;//64bits
		//超过范围会编译错误
		//byte b2 = 200;
		//2.字符型
		char c  = '中';//单引号，16bits
		//超过一个字符会编译错误
		//char c2 = '中国';
		//3.浮点型
		float f1 = 54.321f;//32bits
		double f2 = 54.321;//64bits
		//默认的小数值是double，需要加f声明为double类型；
		//float f = 54.321;
		//4.布尔型 1bit 不能直接使用0,1赋值
		boolean b1 = true;
		boolean b2 = false;
		//String类型
		String str = "Hello Java";
		
		
		
		long val = 26L; //以L结尾的字面值表示long型
        int decVal = 26; //默认就是int型
        int hexVal = 0x1a; //16进制
        int oxVal = 032; //8进制
        int binVal = 0b11010; //2进制
        
        float f3 = 123.4F;// 以F结尾的字面值表示float类型
        float f4 = 1.234e2F;//科学计数法
        double d1 = 123.4;// 默认就是double类型
        double d2 = 1.234e2;// 科学计数法表示double
        
        //以下是转义字符
        char tab = '\t'; //制表符
        char carriageReturn = '\r'; //回车
        char newLine = '\n'; //换行
        char doubleQuote = '\"'; //双引号
        char singleQuote = '\''; //单引号
        char backslash = '\\'; //反斜杠
        
        

        //查看一个整数对应的二进制的方法：
        int i2 = 200;
        System.out.println(Integer.toBinaryString(i2));
        
        //final 当一个变量被final修饰的时候，该变量只有一次赋值的机会
        //final修饰的全局变量必须初始化时赋值
        final int i3 = 4;
        
        
	}
		//终结外部循环
	    public  void endOutLoop() {
	        //打印单数    
	        outloop: //outloop这个标示是可以自定义的比如outloop1,ol2,out5
	        for (int i = 0; i < 10; i++) {
	             
	            for (int j = 0; j < 10; j++) {
	                System.out.println(i+":"+j);
	                if(0==j%2) 
	                    break outloop; //如果是双数，结束外部循环
	            }
	             
	        }
	         
	    }
	   //public void method1(final int j) {
	    //    j = 5; //不能执行
	    //}
}