package LinkedList;

public class MyLinkedList {
	private ListNode head = null;
	private ListNode tail = null;
	public MyLinkedList() {
		// TODO Auto-generated constructor stub
	}
//    - [x] size() —— 返回链表中数据元素的个数
	public int Size()
	{
		int size=0;
		ListNode current = head;
		while(current!=null)
		{
			current = current.getNext();
			size+=1;
		}
		return size;
	}
//    - [x] empty() —— 若链表为空则返回一个布尔值 true
	public boolean Empty()
	{
		return head==null?true:false;
	}
//    - [x] value_at(index) —— 返回第 n 个元素的值（从0开始计算）
	public Object valueAt(int index)
	{
			ListNode current = head;
			for(int i=0; i < index && current!=null;i++)
			{
				current = current.getNext();
			}
			if(current == null)
			{
				System.err.println("valueAt: index out of range");
				System.exit(1);
			}
			return current.getItem();
		
	}
//    - [x] push_front(value) —— 添加元素到链表的首部
	public void pushFront(Object value)
	{
		ListNode newNode = new ListNode(value,head);
		head = newNode;
		if(tail==null)
		{
			tail  = newNode;
		}
	}
//    - [x] pop_front() —— 删除首部元素并返回其值
	public Object popFront()
	{
		if(head ==null)
		{
			System.err.println("popFront: empty list");
			System.exit(1);
		}
		Object item  = head.getItem();
		head =  head.getNext();
		if(head==null)
		{
			tail = null;
		}
		return item;
	}
//    - [x] push_back(value) —— 添加元素到链表的尾部
	public void pushBack(Object value)
	{
		ListNode newNode = new ListNode(value,null);
		if(head==null)//列表为空
		{
			tail = newNode;
			head = newNode;
		}
		else
		{
			tail.setNext(newNode);
			tail = newNode;
		}
	}
//    - [x] pop_back() —— 删除尾部元素并返回其值
	public Object popBack()
	{
		if(tail==null)
		{
			System.err.println("popBack: empylist");
			System.exit(1);
		}
		
		Object item = tail.getItem();
		if(head ==tail)
		{
			head = tail = null;
		}
		else
		{
			ListNode current = head, prevous = null;
			while(current!=tail)
			{
				prevous = current;
				current = current.getNext();
			}
			prevous.setNext(current.getNext());
			tail = prevous;
		}
		return item;
		
	}
//    - [x] front() —— 返回首部元素的值
	public Object Front()
	{
		if(head==null)
		{
			System.err.println("Front: empty list");
			System.exit(1);
		}
		return head.getItem();
	}
//    - [x] back() —— 返回尾部元素的值
	public Object Back()
	{
		if(tail==null)
		{
			System.err.println("Back: empty list");
			System.exit(1);
		}
		return tail.getItem();
	}
	//    - [x] AddBefore(index, value) 
	public void AddBefore(int index ,Object value)
	{
		ListNode newNode  =  new ListNode(value);

		ListNode current = head,prevous =null;
		int i = 0;
		for(i=0; i <index && current!=null;i++)
		{
			prevous = current;
			current = current.getNext();
		}

		if (i != index) {
			System.err.println("insert: index out of range");
			System.exit(1);
		}
		//在head前插入
		if(current == head)
		{
			newNode.setNext(current);;
			if(tail ==null)
			{
				tail = newNode;
			}
			head = newNode;
		}
		//在中间插入
		else
		{
			newNode.setNext(current);
			prevous.setNext(newNode);
		}
	}
	//    - [x] erase(index) —— 删除指定索引的节点
	public void Erase(int index)
	{
		
		//是否为空链表
		  if (head == null) {
			    System.err.println("Erase: List is empty.");
			    System.exit(1);
			  }
		
		 //current找到要删除的节点,prevous指向前一个
		ListNode current = head,prevous =null;
		int i = 0;
		for(i=0; i <index && current!=null;i++)
		{
			prevous = current;
			current = current.getNext();
		}

		if (i != index) {
			System.err.println("insert: index out of range");
			System.exit(1);
		}
		
		
		//如果删除的是head，prevous为null, 修改head
		if(current == head)
		{
			head = current.getNext();
			//再看tail是否需要修改
			if(current == tail)
			{
				tail = prevous;
			}
		}
		//否则，prevous不为null,修改链接关系
		else
		{
			prevous.setNext(current.getNext());
			//再看tail是否需要修改
			if(current == tail)
			{
				tail = prevous;
			}
		}
		


	}
//    - [x] value_n_from_end(n) —— 返回倒数第 n 个节点的值
		public Object ValueNFromEnd(int index)
		{
			if(index < 1 || head == null)
			{
				System.err.println("ValueNFromEnd: list is empty");
				System.exit(1);
			}
			 ListNode current = head;
			 ListNode match = head;

			  int i;
			  for (i = 0; i < index && current!=null; ++i) {
			    current = current.getNext();
			  }

			  if (i != index) {
			    System.err.println("Index out of bounds.");
			    System.exit(1);
			  }

			  while (current != null) {
			    match = match.getNext();
			    current = current.getNext();
			  }

			  return match.getItem();
		}
//    - [x] reverse() —— 逆序链表
		public void Reverse()
		{
			if(head != tail)
			{
				ListNode prevous = null,current = head,next = null;
				while(current!=null)
				{
					next = current.getNext();
					current.setNext(prevous);
					prevous = current;
					current = next;
				}
				tail = head;
				head = prevous;
			}
		}
//    - [x] remove_value(value) —— 删除链表中指定值的第一个元素
		public void RemoveValue(Object value)
		{
			ListNode prevous = null, current = head; 
			while(current!=null)
			{
				if(current.getItem() == value)
				{
					if(current == head)
					{
						head = current.getNext();
					}
					else
					{
						prevous.setNext(current.getNext());
					}
					
					if(current == tail)
					{
						tail = prevous;
					}
				}
				
				prevous = current;
				current = current.getNext();
			}
			
		}
}






