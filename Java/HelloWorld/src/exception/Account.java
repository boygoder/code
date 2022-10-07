package exception;

public class Account {
	protected double balance;
	
	public Account(double _balance) {
		// TODO Auto-generated constructor stub
		balance = _balance;
	}
	public double getBalance() {
		return balance;
	}
	public void deposit(double a) {
		balance +=a;
	}
	public void withdraw(double s) throws OverdrafException{
		double deficit = balance - s;
		if(deficit < 0) {
			throw new OverdrafException("账户余额不足", deficit);
		}
	}
	
	
	public static void main(String[] args) {
		Account a = new Account(100);
		try {
			a.withdraw(500);
		} catch (OverdrafException e) {
			System.out.println(e.getMessage()+e.getDeficit());
			e.printStackTrace();
		}
	}

}
