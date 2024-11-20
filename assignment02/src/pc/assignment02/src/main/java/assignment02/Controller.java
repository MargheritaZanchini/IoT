package assignment02;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressBar;
import javafx.beans.binding.StringBinding;
import javafx.beans.property.DoubleProperty;
import javafx.beans.property.SimpleDoubleProperty;

public class Controller {
    @FXML private ProgressBar toxicWasteLevel;
    @FXML private ProgressBar temperatureLevel;
    @FXML private Label wasteLevelLabel;
    @FXML private Label temperatureLabel;
    @FXML private Label statusLabel;
    @FXML private Button emptyButton;
    @FXML private Button restoreButton;
    
    private DoubleProperty wasteValue = new SimpleDoubleProperty(0);
    private DoubleProperty temperatureValue = new SimpleDoubleProperty(0);
    
    @FXML
    public void initialize() {
        toxicWasteLevel.progressProperty().bind(wasteValue);
        temperatureLevel.progressProperty().bind(temperatureValue);
        
        wasteLevelLabel.textProperty().bind(new StringBinding() {
            { super.bind(wasteValue); }
            @Override
            protected String computeValue() {
                return String.format("%.1f%%", wasteValue.get() * 100);
            }
        });
        
        temperatureLabel.textProperty().bind(new StringBinding() {
            { super.bind(temperatureValue); }
            @Override
            protected String computeValue() {
                return String.format("%.1f°C", temperatureValue.get() * 100); // Assumendo 100°C come massimo
            }
        });
        
        wasteValue.addListener((obs, oldVal, newVal) -> updateWasteLevelColor(newVal.doubleValue()));
        temperatureValue.addListener((obs, oldVal, newVal) -> updateTemperatureLevelColor(newVal.doubleValue()));
    }
    
    private void updateWasteLevelColor(double value) {
        if (value < 0.6) { // < 60%
            toxicWasteLevel.setStyle("-fx-accent: #00ff00;"); // Verde
        } else if (value < 0.8) { // 60-80%
            toxicWasteLevel.setStyle("-fx-accent: #ffa500;"); // Arancione
        } else { // > 80%
            toxicWasteLevel.setStyle("-fx-accent: #ff0000;"); // Rosso
        }
    }
    
    private void updateTemperatureLevelColor(double value) {
        if (value < 0.5) { // < 50°C
            temperatureLevel.setStyle("-fx-accent: #00ff00;"); // Verde
        } else if (value < 0.8) { // 50-80°C
            temperatureLevel.setStyle("-fx-accent: #ffa500;"); // Arancione
        } else { // > 80°C
            temperatureLevel.setStyle("-fx-accent: #ff0000;"); // Rosso
        }
    }
    
    public void setWasteLevel(double level) {
        wasteValue.set(level);
    }
    
    public void setTemperature(double temp) {
        temperatureValue.set(temp/100);
    }
}