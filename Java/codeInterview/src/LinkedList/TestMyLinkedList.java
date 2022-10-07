package LinkedList;

public class TestMyLinkedList {

	public TestMyLinkedList() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {

		  MyLinkedList ilist = new MyLinkedList();
		  ilist.pushFront(4);
		  ilist.pushFront(9);

		  MyLinkedList strlist = new MyLinkedList();
		  strlist.pushFront("string 1");
		  strlist.pushFront("another");
		  strlist.pushFront("and another");
		  System.out.println("Should be 3.  Size of string list is : " + strlist.Size() );

		 System.out.println(strlist.popFront());
		  System.out.println(strlist.popFront());
		  System.out.println(strlist.popFront());

		  System.out.println("Should be 0.  Size of string list is : " + strlist.Size());;
		  strlist.pushBack("string 1");
		  System.out.println( "front: " + strlist.Front());
		  System.out.println( "Should be 1.  Size of string list is : " + strlist.Size());
		  strlist.pushBack("another");
		  System.out.println("Should be 2.  Size of string list is : " + strlist.Size());
		  strlist.pushBack("and another");
		  System.out.println("Should be 3.  Size of string list is : " + strlist.Size());

		  System.out.println("front: " + strlist.Front() );
		  System.out.println("pop_back:");
		 System.out.println(strlist.popBack());
		 System.out.println(strlist.popBack());
		 System.out.println(strlist.popBack());

		  strlist.AddBefore(0, "string 1");
		  strlist.AddBefore(0, "another");
		  strlist.AddBefore(0, "and another");
		  
		  System.out.println("Should be 3.  Size of string list is : " + strlist.Size());
		  System.out.println("Front:" + strlist.Front() + "  Back:" + strlist.Back()); 

		  strlist.Erase(0);
		  System.out.println( "Front:" + strlist.Front() + "  Back:" + strlist.Back()); 
		  strlist.Erase(1);
		  System.out.println("Front:" + strlist.Front() + "  Back:" + strlist.Back());

		  strlist.AddBefore(0, "string 1");
		  strlist.AddBefore(0, "another");
		  strlist.AddBefore(0, "and another");
		  for(int i=1; i <= 4;i++)
		    System.out.println( "倒数第 " + i +"个节点:"  + strlist.ValueNFromEnd(i));
		  System.out.println( "Should be 4.  Size of string list is : " + strlist.Size()); 
		  strlist.Reverse();
		  for(int i=1; i < 5;i++)
		    System.out.println( "倒数第 " + i +"个节点:"  + strlist.ValueNFromEnd(i));
	}

}
