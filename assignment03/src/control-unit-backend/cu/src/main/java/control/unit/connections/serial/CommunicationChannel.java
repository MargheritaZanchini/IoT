package control.unit.connections.serial;

import jssc.SerialPort;

/**
 * Interface for Serial Communication
 * 
 * @author Alessandro Ricci
 * @see https://github.com/aricci303/
 */
public interface CommunicationChannel {
    /**
     * Send a Message Through the Communication Channel
     * 
     * @param msg
     * @return If the Message was Sent Successfully
     */
	boolean sendMessage(String msg);

    /**
     * Receive a Message Through the Communication Channel
     * 
     * @return The Received Message
     * @throws InterruptedException
     */
    String receiveMessage() throws InterruptedException;

    /**
     * Check if a Message is Available
     * 
     * @return If a Message is Available
     */
    boolean isMessageAvailable();
	
    /**
     * Close the Communication Channel
     */
    void closeChannel();

    /**
     * Check if the Channel is Opened
     * 
     * @return If the Channel is Opened
     */
    boolean isOpened();

    /**
     * Get the Serial Port Object
     * 
     * @return The Serial Port
     */
    SerialPort getSerialPort();
}
