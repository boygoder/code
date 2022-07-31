package ClassPractice;

public interface Pet {
	public String getName();
	public void setName(String name);
	default public void play()
	{
		System.out.println("正在玩耍");
	};
}
