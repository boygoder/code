package Character;

public class TestGiantDragon {
	 
    public static void main(String[] args) {
        //通过new实例化会报错
//      GiantDragon g = new GiantDragon();
         
        //只能通过getInstance得到对象
         
        GiantDragon g1 = GiantDragon.getInstance();
        GiantDragon.setInstanceHp(100);
        System.out.println(GiantDragon.getHp());
        GiantDragon g2 = GiantDragon.getInstance();
        g2.setHp(200);
        System.out.println(GiantDragon.getHp());
       GiantDragon.setHp(300);
       System.out.println(g2.getHp());
        GiantDragon g3 = GiantDragon.getInstance();
         
        //都是同一个对象
        System.out.println(g1==g2);
        System.out.println(g1==g3);
    }
}
