package property;

public class Armor  extends Item{
	int grade_;
	public int getGrade_() {
		return grade_;
	}
	
	public void setGrade_(int grade_) {
		this.grade_ = grade_;
	}
	public Armor() {};
	public  Armor(String name,int price,int grade)
	{
		super(name,price);
		grade_ = grade;
	}
	
	
	@Override
	public boolean disposable() {
		// TODO Auto-generated method stub
		return false;
	}

	public static  void main(String[] args) {
		Armor a1 = new Armor("皇麟宝甲",1000,5);
		System.out.println("name:"+a1.name_+"price:"+a1.price_+"grade:"+a1.grade_);
	
	}
}
