package com.ClassAndObject;

public class New {
	public int num;
	public static void main(String[] args) {
		New n1 = new New();
		New n2 =  new New();
		System.out.println("n1:"+n1);//查看地址
		System.out.println("n1"+n2);
	}
}
