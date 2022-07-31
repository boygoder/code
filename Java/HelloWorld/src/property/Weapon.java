package property;

public class Weapon extends Item{
	int damage_;
	
	@Override
	public boolean disposable() {
		// TODO Auto-generated method stub
		return false;
	}

	public static void main(String[] args) {
		Weapon w1 = new Weapon();
		w1.damage_=65;
		w1.name_="破甲弓";
		w1.price_ = 500;
		System.out.println("name:"+w1.name_+" price: "+w1.price_+" damage:" + w1.damage_);
	}
}
