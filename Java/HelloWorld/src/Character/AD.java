package Character;

public interface AD {
	public void physicalAttack();//声明
	default public void attack()
	{
		System.out.println("physics attack");
	};
}

