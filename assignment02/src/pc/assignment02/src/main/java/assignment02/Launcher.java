package assignment02;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import jssc.SerialPortList;

import java.io.IOException;
import java.util.function.Function;

public class Launcher extends Application {
    private static final String APPLICATION_NAME = "OPERATOR DASHBOARD";
    private static final String APPLICATION_LAYOUT = "Main.fxml";
    private static final boolean APPLICATION_RESIZABLE = false;

    private final Function<Integer, Void> CLOSE_FUNCTION = (input) -> {
        Platform.exit();
        System.exit(input);
        return null;
    };

    private final FXMLLoader LOADER = new FXMLLoader(getClass().getResource(APPLICATION_LAYOUT));
    private Parent root;
    private Scene scene;

    private Controller controller;
    private SerialCommChannel serialCommChannel;

    @Override
    public void start(final Stage primaryStage) {
        try {
            root = LOADER.load();
        }
        catch (IOException error) {
            System.err.println("File FXML Not Found! " + error.getMessage());
            CLOSE_FUNCTION.apply(-1);
        }

        scene = new Scene(root);
        controller = LOADER.getController();
        
        primaryStage.setScene(scene);
        primaryStage.setTitle(APPLICATION_NAME);
        primaryStage.setResizable(APPLICATION_RESIZABLE);
        primaryStage.setOnCloseRequest((closeRequest) -> CLOSE_FUNCTION.apply(0));
    
        try {
            String portName = findCorrectPort();
            if (portName != null) {
                serialCommChannel = new SerialCommChannel("COM8", 9600, controller); //new SerialCommChannel(portName, 9600, controller);
            } else {
                System.err.println("No suitable COM port found.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        primaryStage.show();
    }

    private String findCorrectPort() {
        String[] portNames = SerialPortList.getPortNames();
        for (String portName : portNames) {
            try {
                SerialCommChannel testChannel = new SerialCommChannel(portName, 9600, controller);
                // If we reach here, the port is correct
                testChannel.close();
                return portName;
            } catch (Exception e) {
                // Ignore and try next port
            }
        }
        return null; // No suitable port found
    }
}
