package Character;

public interface Mortal {
	default void die()
	{
		System.out.println("人皆有一死");
	}
}
