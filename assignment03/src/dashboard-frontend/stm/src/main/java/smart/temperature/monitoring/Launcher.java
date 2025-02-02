package smart.temperature.monitoring;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import io.vertx.core.*;
import io.vertx.mqtt.*;

/**
 *  Main Class of the JavaFX Application (Smart Temperature Monitoring)
 * 
 *  @see Application
 */
public class Launcher extends Application {
    public static final String APPLICATION_NAME = "Smart Temperature Monitoring"; /** Application Name */
    public static final String APPLICATION_LAYOUT = "STM.fxml"; /** Application Layout Filename (resources) */
    public static final boolean APPLICATION_RESIZABLE = false; /** Application Resizable Flag */

    // public static final String SERIAL_PORT = "COM8"; /** Serial Port Name */
    // public static final int BAUD_RATE = 9600; /** Baud Rate */

    @Override
    public void start(final Stage primaryStage) throws Exception {
        final Parent root = FXMLLoader.load(getClass().getResource(APPLICATION_LAYOUT));
        final Scene scene = new Scene(root);
        
        primaryStage.setScene(scene);
        primaryStage.setTitle(APPLICATION_NAME);
        primaryStage.setResizable(APPLICATION_RESIZABLE);
        primaryStage.setOnCloseRequest((closeRequest) -> {
            Platform.exit();
            System.exit(0);
        });

        primaryStage.show();
    }
}