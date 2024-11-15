package assignment02;

import javafx.fxml.FXML;
import javafx.scene.control.ProgressBar;

public class Controller {
    @FXML
    private ProgressBar toxicWasteLevel;

    @FXML
    public void initialize() { 
        toxicWasteLevel.setProgress(0.00);
    }

    void setToxicWasteLevel(double level) {
        if(toxicWasteLevel == null) {
            return;
        }

        if(level < 0.0) {
            toxicWasteLevel.setProgress(0);
        }
        else if(level > 1.0) {
            toxicWasteLevel.setProgress(1);
        }
        else {
            toxicWasteLevel.setProgress(level);
        }
    }

    double getToxicWasteLevel() {
        if(toxicWasteLevel == null) {
            return -1;
        }

        return toxicWasteLevel.getProgress();
    }
}
