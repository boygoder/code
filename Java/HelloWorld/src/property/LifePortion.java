package property;

public class LifePortion extends Item{
    public void effect(){
        System.out.println("血瓶使用后，可以回血");
    }
    @Override
	public boolean disposable() {
		// TODO Auto-generated method stub
		return true;
	}
	public static void main(String[] args) {
		LifePortion l =  new LifePortion();
		l.effect();
	}
}
