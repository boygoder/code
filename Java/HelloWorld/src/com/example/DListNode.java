package com.example;


public class DListNode{
    private Object item_;
    private DListNode next_;
    public Object getItem_() {
		return item_;
	}
	public void setItem_(Object item_) {
		this.item_ = item_;
	}
	public DListNode getNext_() {
		return next_;
	}
	public void setNext_(DListNode next_) {
		this.next_ = next_;
	}
	public DListNode getPrevous_() {
		return prevous_;
	}
	public void setPrevous_(DListNode prevous_) {
		this.prevous_ = prevous_;
	}
	private DListNode prevous_;
    public DListNode()
    {
    	this.next_ = null;
    	this.prevous_ = null;
    	this.item_ = null;
    }
    public DListNode(Object item,DListNode next,DListNode prevous)
    {
    	this.item_ = item;
    	this.prevous_ = prevous;
    	this.next_ = next;
    }
    public static void main(String[] args) {
        DListNode sentinel =  new DListNode();
        sentinel =new DListNode(null,sentinel.getPrevous_(),sentinel.getNext_());
    }
}