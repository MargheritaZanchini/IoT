#pragma once

/**
 * \brief System Mode Class
 * 
 * This class is responsible for managing the system mode (manual / automatic).
 */
class SystemManager {
public:
    /**
     * \brief System Mode Enumeration
     */
    enum Mode {
        MANUAL, /** Manual Mode */
        AUTOMATIC /** Automatic Mode */
    };

    /**
     * \brief Creates New System Mode Instance
     */
    SystemManager();
    
    /**
     * \brief Sets the Current System Mode
     */
    void setMode(Mode mode);

    /**
     * \brief Gets the Current System Mode
     */
    Mode getMode() const;
    
    /**
     * \brief Switches the Current System Mode
     */
    void switchMode();

private:
    Mode _currentMode; /** Current System Mode */
};