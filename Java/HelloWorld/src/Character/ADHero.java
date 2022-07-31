package Character;

import property.Item;
import property.LifePortion;
import property.MagicPortion;

public class ADHero   extends Hero implements AD,Mortal {
	int moveSpeed = 100;
	public ADHero() 
	{
		super("");
		System.out.println("ADHero的构造方法");
	};
	public ADHero(String name)
	{
		super(name);
		System.out.println("ADHero的有一个参数的构造方法");
	}
	public ADHero(String name,float hp)
	{
		super(name,hp);
	}
	public int getMoveSpeed()
	{
		return this.moveSpeed;
	}
	public int getSuperMoveSpeed()
	{
		return super.moveSpeed;
	}
	public void useItem(Item i)
	{
	    System.out.println("adhero use item");
	    super.useItem(i);
	}

	@Override
	public  void kill(Mortal m) {
		// TODO Auto-generated method stub
		System.out.println("击杀者：ADHero ");
		m.die();
	}
	@Override
	public void die() {
		// TODO Auto-generated method stub
		System.out.println("物理英雄"+this.name+"死去");
	}
		
		public String getName() {
			return this.name;
		}

		@Override
		public void physicalAttack() {
			// TODO Auto-generated method stub
			System.out.println("坚如磐石");
		}
		@Override
		public void attack(Hero h)
		{
			System.out.println(this.name+"使用物理攻击");
		}
		public static void main(String[] args) {
	        ADHero ad = new ADHero();
//	        ADHero ad1 = new ADHero("GaRON");
//	        System.out.println("this:"+ad1.getMoveSpeed());
//	        System.out.println("super:"+ad1.getSuperMoveSpeed());
//	        LifePortion life = new LifePortion();
//	        MagicPortion magic =  new MagicPortion();
//	        ad1.useItem(life);
		}
}
