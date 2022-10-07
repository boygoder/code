package LinkedList;

public class ListNode {
	private Object item_ = null;
	private ListNode next_ = null;
	
	
	public Object getItem() {
		return item_;
	}
	public void setItem(Object item_) {
		this.item_ = item_;
	}

	public ListNode getNext() {
		return next_;
	}
	public void setNext(ListNode next_) {
		this.next_ = next_;
	}
	public ListNode() {
		// TODO Auto-generated constructor stub
	}
	public ListNode(Object item,ListNode next)
	{
		item_ = item;
		next_ = next;
	}
	public  ListNode(Object item)
	{
		this(item,null);
	}
}
