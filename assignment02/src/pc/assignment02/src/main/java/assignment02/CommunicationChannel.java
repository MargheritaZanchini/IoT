package assignment02;

public interface CommunicationChannel {
	boolean sendMessage(String msg);
	String receiveMessage() throws InterruptedException;
	boolean isMessageAvailable();
    void closeChannel();
}
