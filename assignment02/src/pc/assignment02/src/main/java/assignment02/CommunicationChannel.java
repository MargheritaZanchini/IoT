package assignment02;

public interface CommunicationChannel {
	void sendMessage(String msg);
	String receiveMessage() throws InterruptedException;
	boolean isMessageAvailable();
    void closeChannel();
}
