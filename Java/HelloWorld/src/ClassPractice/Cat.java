package ClassPractice;

public class Cat extends Animal implements Pet{
	private String name;
	public Cat() {
		// TODO Auto-generated constructor stub
		super(0);
	}
	public Cat(String name)
	{
		super(4);
	}
	public String getName()
	{
		return this.name;
		
	}
	
	public void setName(String name)
	{
		this.name = name;
	}
	
	public void play()
	{
		System.out.println(this.name + "正在玩耍");
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

	@Override
	public void eat() {
		// TODO Auto-generated method stub
		System.out.println("Cat eats fish.");
	}

}
