package ClassPractice;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class CatTest {

	@Test
	void test() {
		Cat cat1= new Cat();
		cat1.setName("kitten");
		System.out.println(cat1.getName());
		Cat cat2 = new Cat("miao");
		System.out.println(cat2.getName());
		cat2.setName("miaomiao");
		System.out.println(cat2.getName());
		cat2.walk();
		cat2.eat();
		cat2.play();
	}

}
