package Character;

public class MyStringBuffer implements IStringBuffer{
	private static int basesize = 16;
	private static int growsize =2;
	private static int decentsize = 4;
	private char[] arr_;
	private int capacity_ = basesize;
	private int size_;
    @Override
    public String toString() {
    	char[] printstr = new char[size_];
    	for(int i=0; i < size_;i++)
    	{
    		printstr[i] = arr_[i];
    	}
        return new String(printstr);
    }
	public char getCharAt(int index)
	{
		if(index <0 || index >= size_)
		{
			System.out.println("getCharAt:index out of range");
			throw new IllegalArgumentException();
		}
		else
		{
			return arr_[index];
		}
	}
	public void resize(int imaginesize)//更改长度
	{
		if(imaginesize>size_)
		{
			while(capacity_ < imaginesize)
			{
				char[] newarr = new char[2*capacity_];
				for(int i=0; i < size_;i++)
				{
					newarr[i] = arr_[i];
				}
				arr_ = newarr;
				capacity_ *= 2;
			}
		}
		else if(imaginesize <size_)
		{
			while(size_ < capacity_ /4)
			{
				char[] newarr = new char[capacity_/2];
				for(int i=0; i< size_;i++)
				{
					newarr[i] = arr_[i];
				}
				arr_ = newarr;
				capacity_/=2;
			}
		}
	}
    public void append(String str)//追加字符串
    {
    	int appendsize = str.length();
    	resize(size_+appendsize);
    	for(int i = 0; i < appendsize; i++)
    	{
    		arr_[size_+i] = str.charAt(i);
    	}
    	size_+=appendsize;
    }
    public void append(char c)  //追加字符
    {
    	resize(size_+1);
    	arr_[size_] = c;
    	size_+=1;
    }
    public void insert(int pos,char b) //指定位置插入字符
    {
    	assert(pos>=0);
    	resize(size_+1);
    	for(int i = size_;i > pos;i--)
    	{
    		arr_[i] = arr_[i-1];
    	}
    	arr_[pos] = b;
    	size_+=1;
    }
    public void insert(int pos,String b)//指定位置插入字符串
    {
    	assert(pos>=0);
    	int insertsize = b.length();
    	resize(size_+insertsize);
    	for(int i = size_+insertsize-1; i > pos + insertsize -1; i--)
    	{
    		arr_[i] = arr_[i-insertsize];
    	}
    	for(int i = 0; i < insertsize;i++)
    	{
    		arr_[i+pos] = b.charAt(i);
    	}
    	size_+=insertsize;
    }
    public void delete(int start) //从开始位置删除剩下的
    {
    	assert(start>=0);
    	size_= start;
    	resize(size_-1);
    }
    public void delete(int start,int end) //从开始位置删除结束位置-1
    {
    	assert(start>=0 && start < end && end <=size_);
    	for(int i = start; i < size_ -(end-start); i++)
    	{
    		arr_[i] = arr_[i+end-start];
    	}
    	size_ -= end-start;
    	resize(size_-1);
    }
    public void reverse() //反转
    {
    	char[] reversestr = new char[size_];
    	for(int i=0; i < size_;i++)
    	{
    		reversestr[i] = arr_[size_-1-i];
    	}
    	arr_ = reversestr;
    }
    public int length() //返回长度
    {
    	return this.size_;
    }
	public MyStringBuffer() {
		// TODO Auto-generated constructor stub
		arr_ =  new char[basesize];
		size_ = 0;
		capacity_ =basesize;
	}
	public MyStringBuffer(int size)
	{
		int truesize = basesize;
		while(truesize < size)
		{
			truesize*=growsize;
		}
		capacity_ = truesize;
		arr_ = new char[capacity_];
		size =0;
	}
	public MyStringBuffer(String str)
	{
		int size = str.length();
		int truesize = basesize;
		while(truesize < size)
		{
			truesize+=growsize;
		}
		capacity_ = truesize;
		arr_ = new char[capacity_];
		for(int i=0; i < size; i++)
		{
			arr_[i] = str.charAt(i);
		}
		size_ = size;
	}
	public MyStringBuffer(MyStringBuffer str)
	{
		int size = str.length();
		int truesize = basesize;
		while(truesize < size)
		{
			truesize+=growsize;
		}
		capacity_ = truesize;
		arr_ = new char[capacity_];
		for(int i=0; i < size; i++)
		{
			arr_[i] = str.getCharAt(i);
		}
		size_ = size;
	}
	
    public static void main(String[] args) {
    		StringBuffer strbuf = new StringBuffer("");
    		MyStringBuffer mystrbuf = new MyStringBuffer();
    		System.out.println(System.currentTimeMillis());
    		for(int i=0; i < 1000000;i++)
    		{
    			mystrbuf.append((char)i);
    		}
    		System.out.println(System.currentTimeMillis());
    		for(int i=0; i< 1000000;i++)
    		{
    			strbuf.append(i);
    		}
    		System.out.println(System.currentTimeMillis());
    }
}
