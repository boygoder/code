package property;

public class MagicPortion extends Item{
	public void effect() {
		// TODO Auto-generated method stub
		System.out.println("效果：回蓝");
	}
	
	@Override
	public boolean disposable() {
		// TODO Auto-generated method stub
		return true;
	}

	public static void main(String[] args) {
		MagicPortion m = new MagicPortion();
		m.effect();
	}
}
