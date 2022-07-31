package ClassPractice;

public abstract class Animal {
	protected int legs;
	protected Animal(int legs)
	{
		this.legs = legs;
	}
	public void walk()
	{
		System.out.println("使用"+this.legs+"条腿行走");
	}
	public abstract void eat();
}
