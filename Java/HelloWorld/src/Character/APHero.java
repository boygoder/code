package Character;

public class APHero extends Hero implements AP,Mortal {
	public APHero(String name,float hp)
	{
		super(name,hp);
	}
	
	@Override
	public void kill(Mortal m) {
		// TODO Auto-generated method stub
		System.out.println("击杀者：APHero "+this.name);
		m.die();
	}
	@Override
	public void magicalAttack() {
		// TODO Auto-generated method stub
		System.out.println("火球术");
	}
	@Override
public void die() {
	// TODO Auto-generated method stub
	System.out.println("魔法英雄"+this.name+"死去");
}

	@Override
	public void attack(Hero h) {
		// TODO Auto-generated method stub
		System.out.println(this.name+"使用了魔法攻击");
	}
	
	
}
