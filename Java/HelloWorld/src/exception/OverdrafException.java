package exception;

public class OverdrafException extends Exception{
	private double deficit;
	public OverdrafException(String message, double deficit) {
		// TODO Auto-generated constructor stub
		super(message);
		this.deficit = deficit;
	}
	public double getDeficit() {
		return deficit;
	}
}
