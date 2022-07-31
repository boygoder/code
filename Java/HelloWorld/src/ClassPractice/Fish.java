package ClassPractice;

public class Fish extends Animal implements Pet{
	private String name;
	public Fish() {
		// TODO Auto-generated constructor stub
		super(0);
	}
	
	@Override
	public String getName() {
		// TODO Auto-generated method stub
		return this.name;
	}

	@Override
	public void setName(String name) {
		// TODO Auto-generated method stub
		this.name = name;
	}

	@Override
	public void walk() {
		// TODO Auto-generated method stub
		System.out.println("Fish has no leg,so it can't work.");
	}

	@Override
	public void eat() {
		// TODO Auto-generated method stub
		System.out.println("Big fish eats small fish.");
	}

}
