package Character;

import property.Item;

public abstract class Hero {
	public String name= "hero1";  
	public float hp=1000;
	float armor=0;
	int moveSpeed=400;
	int money=200;
	
    // 非静态内部类，只有一个外部类对象存在的时候，才有意义
    // 战斗成绩只有在一个英雄对象存在的时候才有意义
    class BattleScore {
        int kill;
        int die;
        int assit;
 
        public void legendary() {
            if (kill >= 8)
                System.out.println(name + "超神！");
            else
                System.out.println(name + "尚未超神！");
        }
    }
 
    private static void battleWin(){
        System.out.println("battle win");
    }
     
    //敌方的水晶
    static class EnemyCrystal{
        int hp=5000;
         
        //如果水晶的血量为0，则宣布胜利
        public void checkIfVictory(){
            if(hp==0){
                Hero.battleWin();
                 
                //静态内部类不能直接访问外部类的对象属性
                System.out.println(name + " win this game");
            }
        }
    }
  
     

     
    
	public Hero(){
		System.out.println("Hero的构造方法");
	}
    public Hero(String name){
        System.out.println("Hero的有一个参数的构造方法 ");
        this.name = name;
    }
	public Hero(String name,float hp)
	{
		this.name = name;
		this.hp = hp;
	}
	public Hero(
		String name,
		float hp,
		float armor,
		int moveSpeed)
	{
		this(name,hp);
		this.armor = armor;
		this.moveSpeed = moveSpeed;
		System.out.println("name: "+name+" hp: "+hp + " armor: "+armor + "moveSpeed: " + moveSpeed);
	}
	@Override
	public String toString()
	{
		return this.name;
	}
	@Override
	public void finalize()
	{
		System.out.println("正在回收……");
	}
	public void useItem(Item i)
	{
		System.out.println("hero use item");
		i.effect();
	}
	public void kill(Mortal m)
	{
		System.out.print("击杀者：Hero ");
		m.die();
	}
	public abstract void attack(Hero h);
	
	
	public static void main(String[] args) {
        
        ADHero Garon =  new ADHero("Garon");
        BattleScore score = Garon.new BattleScore();
        score.die = 0;
        score.kill  = 9;
        score.legendary();
        Hero. EnemyCrystal crystal =  new Hero.EnemyCrystal();
        
        
        final int damage = 100;
        //与匿名类的区别在于，本地类有了自定义的类名
        class SomeHero extends Hero{
            public void attack(Hero h)  {
                System.out.println( name+ " 新的进攻手段,造成伤害"+damage);
            }
        }
         
        SomeHero h  =new SomeHero();
        h.name ="地卜师";
        h.attack(Garon);
	}
}


