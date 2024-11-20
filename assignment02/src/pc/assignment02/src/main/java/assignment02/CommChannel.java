package assignment02;

public interface CommChannel {

	void sendMsg(String msg);

	String receiveMsg() throws InterruptedException;

	boolean isMsgAvailable();

}
