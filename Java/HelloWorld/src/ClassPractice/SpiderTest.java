package ClassPractice;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class SpiderTest {

	@Test
	void test() {
		Spider s =  new Spider();
		s.eat();
		s.walk();
	}

}
