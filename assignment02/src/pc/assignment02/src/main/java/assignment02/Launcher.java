package assignment02;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

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
            new SerialCommChannel("COM8", 9600, controller);
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
            CLOSE_FUNCTION.apply(-1);
        }

        primaryStage.show();
    }
}
