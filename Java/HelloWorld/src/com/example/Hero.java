package com.example;

import javax.security.auth.AuthPermission;
import javax.security.auth.callback.NameCallback;
class Hero {
	String name;
	float hp;
	float armor;
	int moveSpeed;
	int death;
	int kills;
	int assists;
	int money;
	String deathWords;
	String killWords;
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
		public static void main(String[] args) {
		Hero garen = new Hero();
		garen.name = "盖伦";
		garen.hp = 616.28f;
		garen.armor = 27.536f;
		garen.moveSpeed = 350;
		System.out.println("速度："+garen.moveSpeed);
		garen.killWords="坚如磐石";
		garen.addSpeed(100);
		System.out.println("增加速度:"+garen.moveSpeed);
		garen.legendary();
		garen.recovery(100.22f);
		Hero teemo = new Hero();
		teemo.name = "提莫";
		teemo.hp = 383f;
		teemo.armor = 14f;
		teemo.moveSpeed = 330;
	}
}
