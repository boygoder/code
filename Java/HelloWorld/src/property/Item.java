package property;

public abstract class Item extends Object{
		String name_ = "长剑";
		int price_ = 200;
		
		public void buy()
		{
			System.out.println("购买了"+this.name_);
		}
		public void effect()
		{
			System.out.println("效果：未知");
		}
		public Item() {};
		public  Item(String name,int price)
		{
			name_ = name;
			price_ = price;
		}
		public abstract boolean disposable();
	
		
		@Override
		public boolean equals(Object obj) {
			// TODO Auto-generated method stub
			boolean itemEqual = false;
			if(obj instanceof Item && ((Item) obj).price_ == this.price_)
			{
				itemEqual = true;
			}
			return itemEqual;
		}
		@Override
		public String toString() {
			// TODO Auto-generated method stub
			return this.name_+this.price_;
		}
		@Override
		protected void finalize() throws Throwable {
			// TODO Auto-generated method stub
			System.out.println("对象回收中……");
			super.finalize();
		}
		public static void main(String[] args) {
			Item i = new Item() {
					public boolean disposable()
					{
						return true;
					}
			};
			
			System.out.println(i.disposable());
			
		}

}
