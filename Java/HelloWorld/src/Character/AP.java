package Character;

public interface AP {
	//public static final int resistphysics = 100;
	public void magicalAttack();//声明
	default public void attack()
	{
		System.out.println("magic attack");
	};
 
}
