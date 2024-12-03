package assignment02;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Launcher extends Application {
    public static final String APPLICATION_NAME = "OPERATOR DASHBOARD";
    public static final String APPLICATION_LAYOUT = "Main.fxml";
    public static final boolean APPLICATION_RESIZABLE = false;

    public static final String SERIAL_PORT = "COM8";
    public static final int BAUD_RATE = 9600;

    private final FXMLLoader sceneLoader = new FXMLLoader(getClass().getResource(APPLICATION_LAYOUT));

    @Override
    public void start(final Stage primaryStage) throws Exception {
        final Parent root = sceneLoader.load();
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
