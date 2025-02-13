package control.unit.connections.serial;

import java.util.concurrent.*;
import jssc.*;

/**
 * A Communication Channel that uses a Serial Port
 * 
 * @author Alessandro Ricci
 * 
 * @see CommunicationChannel CommunicationChannel (Implemented Interface)
 * @see SerialPortEventListener SerialPortEventListener (Implemented Interface)
 * @see https://github.com/aricci303/ Author's GitHub Profile
 */
public class SerialChannel implements CommunicationChannel, SerialPortEventListener {
    private static final int QUEUE_SIZE = 100; /** Queue Size for Storing Messages */

    private final SerialPort serialPort; /** Serial Port Object */
    private final BlockingQueue<String> queue; /** Blocking Queue for Storing Messages */
    private StringBuffer currentMessage = new StringBuffer(""); /** Current Message Buffer */

    /**
     * Constructor for SerialChannel
     * 
     * @param port Serial Port Name
     * @param rate Baud Rate
     * 
     * @throws SerialPortException
     */
    public SerialChannel(String port, int rate) throws SerialPortException {
        this.queue = new ArrayBlockingQueue<String>(QUEUE_SIZE);
        
        this.serialPort = new SerialPort(port);
        this.serialPort.openPort();
        this.serialPort.setParams(rate, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);
        this.serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN | SerialPort.FLOWCONTROL_RTSCTS_OUT);
        this.serialPort.addEventListener(this);
    }

    @Override
    public boolean sendMessage(String msg) {
		char[] array = (msg+"\n").toCharArray();
		byte[] bytes = new byte[array.length];
		for (int i = 0; i < array.length; i++){
			bytes[i] = (byte) array[i];
		}
		try {
			synchronized (serialPort) {
                return serialPort.writeBytes(bytes);
			}
		} catch(Exception ex){
			ex.printStackTrace();
            return false;
		}
	}

    @Override
    public String receiveMessage() throws InterruptedException {
        return queue.take();
    }

    @Override
    public boolean isMessageAvailable() {
        return !queue.isEmpty();
    }

    @Override
    public void closeChannel() {
        try {
            if (serialPort != null) {
                serialPort.removeEventListener();
                serialPort.closePort();
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    @Override
    public void serialEvent(SerialPortEvent event) {
        if (event.isRXCHAR()) {
            try {
                String msg = serialPort.readString(event.getEventValue());
                msg = msg.replaceAll("\r", "");

                currentMessage.append(msg);

                boolean goAhead = true;

                while(goAhead) {
                    String msg2 = currentMessage.toString();
                    int index = msg2.indexOf("\n");
                    if (index >= 0) {
                        queue.put(msg2.substring(0, index));
                        currentMessage = new StringBuffer("");
                        if (index + 1 < msg2.length()) {
                            currentMessage.append(msg2.substring(index + 1)); 
                        }
                    } else {
                        goAhead = false;
                    }
                }

            } catch (Exception ex) {
                ex.printStackTrace();
                System.out.println("Error in receiving string from COM-port: " + ex);
            }
        }
    }

    @Override
    public boolean isOpened() {
        return serialPort.isOpened();
    }

    @Override
    public SerialPort getSerialPort() {
        return serialPort;
    }
}
