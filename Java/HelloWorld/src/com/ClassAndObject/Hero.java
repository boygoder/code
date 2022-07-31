package com.ClassAndObject;
 import java.lang.System;
public class Hero {
	public String name;
	public float hp;
	float armor;
	int moveSpeed;
	int death;
	int kills;
	int assists;
	int money;
	String deathWords;
	String killWords;
	static String copyweight = "Riot games";
	public Hero() {};
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
	float getHp() {
		// TODO Auto-generated method stub
		return hp;
	}
	void addSpeed(double speed)
	{
		moveSpeed += speed; 
	}
	void legendary()
	{
		System.out.println(this.name + ":legendary");
	}
	void recovery(float blood)
	{
		System.out.println("before:"+this.hp);
		hp+=blood;
		System.out.println("after:"+this.hp);
	}
	public void attack(Hero hero)
	{
		System.out.println(name+"攻击了"+hero.name);
	}
	public void attack(Hero ...heros)
	{
		for (Hero hero : heros) {
			System.out.println(name+"同时攻击了"+hero.name);
		}
	}
	public void heal(Hero hero,float hp)
	{
		hero.hp+=hp;
		System.out.println(name+"治疗了"+hero.name+hp+"血量");
	}
	private void heal(float hp,Hero ...heros) {
		// TODO Auto-generated method stub
		for (Hero hero : heros) {
			hero.hp+=hp;
			System.out.println(name+"同时治疗了"+hero.name+hp+"血量");
		}
	}
	
    //复活
    public void revive(Hero h){
        h = new Hero("提莫",383);
    }
		public static void main(String[] args) {
			Hero Gailun = new Hero();
			Gailun.name = "盖伦";
			Gailun.hp = 2000;
			Hero Teemo = new Hero();
			Hero db = new Hero();
			Teemo.name = "提莫";
			Teemo.hp = 1000;
			db.name = "死哥";
			Teemo.hp = 2000;
			
			Hero ZuAn = new Hero("祖安怒兽",1000,200, 50);
			
			
			Gailun.attack(Teemo,db);
			
			Gailun.heal(Teemo, 100);
			Gailun.heal(100, Teemo,db);
			
			Teemo.revive(Teemo);
			System.out.println("Teemo的血量究竟是？"+Teemo.hp);
			
			Gailun.copyweight = "Google";
			System.out.println(Teemo.copyweight);
			
	}
}
