package assignment02;

import java.util.concurrent.*;

import javafx.application.Platform;
import jssc.*;

public class SerialCommChannel implements CommChannel, SerialPortEventListener {
    private SerialPort serialPort;
    private BlockingQueue<String> queue;
    private StringBuffer currentMsg = new StringBuffer("");
    private Controller controller;
    private Thread readThread;
    private volatile boolean running = true;

    public SerialCommChannel(String port, int rate, Controller controller) throws Exception {
        this.controller = controller;
        queue = new ArrayBlockingQueue<String>(100);

        serialPort = new SerialPort(port);
        serialPort.openPort();

        serialPort.setParams(rate,
                             SerialPort.DATABITS_8,
                             SerialPort.STOPBITS_1,
                             SerialPort.PARITY_NONE);

        serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN | 
                                      SerialPort.FLOWCONTROL_RTSCTS_OUT);

        serialPort.addEventListener(this);

        // Start the read thread
        readThread = new Thread(this::readLoop);
        readThread.start();
    }

    private void readLoop() {
        while (running) {
            try {
                String message = queue.take();
                processMessage(message);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }

    @Override
    public void serialEvent(final SerialPortEvent event) {
        if (!event.isRXCHAR()) return;

        try {
            String msg = serialPort.readString(event.getEventValue()).replaceAll("\r", "");
            currentMsg.append(msg);

            while (true) {
                String msg2 = currentMsg.toString();
                int index = msg2.indexOf("\n");
                if (index >= 0) {
                    String completeMsg = msg2.substring(0, index);
                    queue.put(completeMsg);
                    currentMsg = new StringBuffer(msg2.substring(index + 1));
                } else {
                    break;
                }
            }
        } catch (Exception ex) {
            ex.printStackTrace();
            System.out.println("Error in receiving string from COM-port: " + ex);

            }
        }

    private void processMessage(String message) {
        message = message.replace("\n", "");
        System.out.println("Received message: " + message);
        if (message.startsWith("[WasteLevel]")) {
            try {
                double wasteLevel = Double.parseDouble(message.substring("[WasteLevel]".length()).trim());
                Platform.runLater(() -> controller.setWasteLevel(wasteLevel));
            } catch (NumberFormatException e) {
                e.printStackTrace();
            }
        } else if (message.startsWith("[Temperature]")) {
            try {
                double temperature = Double.parseDouble(message.substring("[Temperature]".length()).trim());
                Platform.runLater(() -> controller.setTemperature(temperature));
            } catch (NumberFormatException e) {
                e.printStackTrace();
            }
        } else {
            return;
        }
    }

    public void close() {
        running = false;
        readThread.interrupt();
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
	public void sendMsg(String msg) {
		char[] array = (msg+"\n").toCharArray();
		byte[] bytes = new byte[array.length];
		for (int i = 0; i < array.length; i++){
			bytes[i] = (byte) array[i];
		}
		try {
			synchronized (serialPort) {
				serialPort.writeBytes(bytes);
			}
		} catch(Exception ex){
			ex.printStackTrace();
		}
	}

	@Override
	public String receiveMsg() throws InterruptedException {
		return queue.take();
	}

	@Override
	public boolean isMsgAvailable() {
		return !queue.isEmpty();
	}
}