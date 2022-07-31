package com.example;

import java.util.Arrays;

class gold {
		public static void main(String[] args) {
			//goldnum();
			//minNum();
			//arrayCopy();
			useArrays();
		}
		public static  void useArrays()
		{
			int a[] = new int[] { 18, 62, 68, 82, 65, 9 };

			//Arrays.fill(a, 5);//使用同一个值，填充整个数组
			
			// copyOfRange(int[] original, int from, int to)
			// 第一个参数表示源数组
			// 第二个参数表示开始位置(取得到)
			// 第三个参数表示结束位置(取不到)
//			int[] b = Arrays.copyOfRange(a, 0, 3);
//
//			for (int i = 0; i < b.length; i++) {
//				System.out.print(b[i] + " ");
//			}
			
//			String content = Arrays.toString(a);
//	        System.out.println(content);
			
			System.out.println("排序之前 :");
	        System.out.println(Arrays.toString(a));
	        Arrays.sort(a);
	        System.out.println("排序之后:");
	        System.out.println(Arrays.toString(a));
	        
	        //需要注意的是，使用binarySearch进行查找之前，必须使用sort进行排序
	        System.out.println("数字 62出现的位置:"+Arrays.binarySearch(a, 62));
		}
		public static void arrayCopy()
		{
			int[] a = new int[5 + (int)(5*Math.random())];
			int[] b = new int[5 + (int)(5*Math.random())];
			int[] c = new int[a.length+b.length];
			for(int i = 0; i < a.length; i++)
			{
				a[i] = (int)(100*Math.random());
			}
			for(int i =0; i < b.length; i++)
			{
				b[i] = (int)(100*Math.random());
			}
			System.arraycopy(a, 0, c, 0, a.length);
			System.arraycopy(b, 0, c, a.length, b.length);
			for(int each:a)
			{
				System.out.print(each+" ");
			}
			System.out.println();
			for(int each:b)
			{
				System.out.print(each+" ");
			}
			System.out.println();
			for(int each : c)
			{
				System.out.print(each+" ");
			}
			
		}
	    public  static void minNum() {
	        int[] a = new int[5];//作为int类型的数组，默认值是0
	        a[0] = (int) (Math.random() * 100);
	        a[1] = (int) (Math.random() * 100);
	        a[2] = (int) (Math.random() * 100);
	        a[3] = (int) (Math.random() * 100);
	        a[4] = (int) (Math.random() * 100);
	         
	        System.out.println("数组中的各个随机数是:");
	        for (int i = 0; i < a.length; i++)
	            System.out.println(a[i]);
	         
//	        System.out.println("本练习的目的是，找出最小的一个值: ");
//	        int min = a[0];
//	        for(int i = 1; i < a.length;i++)
//	        {
//	        	if(a[i] < min)
//	        	{
//	        		min = a[i];
//	        	}
//	        }
//	        System.out.println(min);
	        
//	        System.out.println("本练习的目的是，反转数组："+a.length/2);
//	        for(int i=0; i < a.length/2; i++)
//	        {
//	        	int temp = a[i];
//	        	a[i] = a[a.length-i-1];
//	        	a[a.length-i-1] = temp;
//	        }
//	        System.out.println("反转数组中的各个随机数是:");
//	        for (int i = 0; i < a.length; i++)
//	            System.out.println(a[i]);
//	    System.out.println("本练习的目的是，插入排序：");
//	    for(int i=0;i < a.length-1; i++)
//	    {
//	    	for(int j=i+1; j < a.length;j++)
//	    	{
//	    		if(a[j] < a[i])
//	    		{
//	    			int tmp = a[i];
//	    			a[i] = a[j];
//	    			a[j] = tmp;
//	    		}
//	    	}
//	        System.out.println("数组中的各个随机数是:");
//	        for (int k = 0; k < a.length; k++)
//	            System.out.print(a[k]+" ");
//	        System.out.println();
//	    }
//	    System.out.println("本次练习的目的是，冒泡排序：");
//	    for(int i = 0; i < a.length-1; i ++)
//	    {
//	    	for(int j=0; j < a.length-1-i; j++)
//	    	{
//	    		if(a[j] > a[j+1])
//	    		{
//	    			int tmp = a[j];
//	    			a[j] = a[j+1];
//	    			a[j+1] = tmp;
//	    		}
//	    	}
//	        for (int k = 0; k < a.length; k++)
//	            System.out.print(a[k]+" ");
//	        System.out.println();
//	    }
	    }
		public static  void goldnum() {
			int record_i=0,record_j=0;
			double sub = 0.618,value=0.618;
			for(int i = 1; i <=20; i ++)
			{
				for(int j = 1; j <=20; j ++)
				{
					if(i%2==0 && j%2==0)
					{
						break;
					}
					if(Math.abs((double)i/(double)j - 0.618) < sub)
					{
						value = Math.abs((double) i / (double) j );
						sub = Math.abs((double) i / (double) j- 0.618);
						record_i = i;
						record_j = j;
					}
				}
			}
			System.out.println(record_i+","+record_j+","+value);
		}
}
