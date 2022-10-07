package exception;

public class CheckingAccount extends Account {
	private double OverdraftProtection = 200;
	public CheckingAccount(double balance) {
		// TODO Auto-generated constructor stub
		super(balance);
	}
	public CheckingAccount(double balance, double protect) {
		super(balance);
		OverdraftProtection = protect;
	}
	
	@Override
	public void withdraw(double money) throws OverdrafException{
		double deficit = balance - money;
        if(balance>0){
            System.out.println("取款成功，余额为"+balance);
        }else if(balance>=-OverdraftProtection){
            OverdraftProtection=OverdraftProtection+balance;
            System.out.println("取款成功，透支额度余额为"+OverdraftProtection);
        }else{
            throw new OverdrafException("余额不足，取款失败",balance);
        }
	}
	public static void main(String[] args) {
        CheckingAccount ca =new CheckingAccount(100,100);

        try {
            ca.withdraw(400);
        }catch (OverdrafException e){
            e.printStackTrace();
        }
	}
}
