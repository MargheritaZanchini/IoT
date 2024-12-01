package assignment02;

import java.util.concurrent.*;
import jssc.*;

public class SerialChannel implements CommunicationChannel, SerialPortEventListener {
    private static final int QUEUE_SIZE = 100;

    private final SerialPort serialPort;
    private final BlockingQueue<String> queue;
    private StringBuffer currentMessage = new StringBuffer("");

    public SerialChannel(String port, int rate) throws SerialPortException {
        this.queue = new ArrayBlockingQueue<String>(QUEUE_SIZE);
        
        this.serialPort = new SerialPort(port);
        this.serialPort.openPort();
        this.serialPort.setParams(rate, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);
        this.serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN | SerialPort.FLOWCONTROL_RTSCTS_OUT);
        this.serialPort.addEventListener(this);
    }

    @Override
    public void sendMessage(String msg) {
        try {
            synchronized (serialPort) {
                serialPort.writeString(msg + "\n");
            }
        } catch (SerialPortException ex) {
            ex.printStackTrace();
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


    public void serialEvent(SerialPortEvent event) {
        /* if there are bytes received in the input buffer */
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
}
