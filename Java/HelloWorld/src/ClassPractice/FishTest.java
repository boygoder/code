package ClassPractice;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class FishTest {

	@Test
	void test() {
		Fish Fish2= new Fish();
		System.out.println(Fish2.getName());
		Fish2.setName("miaomiao");
		System.out.println(Fish2.getName());
		Fish2.walk();
		Fish2.eat();
		Fish2.play();
	}

}
