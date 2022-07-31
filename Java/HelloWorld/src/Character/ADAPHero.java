package Character;

public class ADAPHero extends Hero implements AD,AP,Mortal{
	public ADAPHero() {};
	public ADAPHero(String name,float hp)
	{
		super(name,hp);
	}
	@Override
	public void physicalAttack() {
		// TODO Auto-generated method stub
		System.out.println("坚如磐石2.0");
	}

	@Override
	public void magicalAttack() {
		// TODO Auto-generated method stub
		System.out.println("火球术2.0");
	}

	@Override
	public void die() {
		// TODO Auto-generated method stub
		System.out.println("混合英雄"+this.name+"死去");
	}
	@Override
	public void attack(Hero h) {
		// TODO Auto-generated method stub
		System.out.println(this.name+"使用了物理魔法攻击");
	}
	@Override
	public void attack()
	{
		AD.super.attack();
		AP.super.attack();
	}
	public static void main(String[] args) {
		ADAPHero adap =  new ADAPHero("Garon",1000);
		adap.attack();
	}

}
