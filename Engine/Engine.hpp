/**
 * @file Engine.hpp
 * @brief Deklaracja klasy Engine - głównego silnika aplikacji
 * @ingroup Engine
 * 
 * Klasa Engine zarządza oknem aplikacji, pętlą główną, obsługą zdarzeń,
 * czasem oraz logowaniem. Stanowi centralny komponent aplikacji wykorzystującej SFML.
 */

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <fstream>
#include <memory>
#include <chrono>

/**
 * @class Engine
 * @brief Główna klasa silnika aplikacji
 * 
 * Klasa odpowiedzialna za inicjalizację okna, zarządzanie pętlą główną,
 * obsługę zdarzeń wejścia (klawiatura, mysz), zarządzanie czasem oraz logowanie.
 * Stanowi bazę dla aplikacji graficznych i gier.
 */
class Engine {
public:
    /**
     * @brief Konstruktor klasy Engine
     */
    Engine();
    
    /**
     * @brief Destruktor klasy Engine
     */
    ~Engine();

    /**
     * @brief Inicjalizuje silnik i tworzy główne okno
     * @param title Tytuł okna
     * @param screenWidth Szerokość okna w pikselach (domyślnie: 800)
     * @param screenHeight Wysokość okna w pikselach (domyślnie: 600)
     * @param fullscreenMode Czy uruchomić w trybie pełnoekranowym (domyślnie: false)
     * @param targetFps Docelowa liczba klatek na sekundę (domyślnie: 60)
     * @return true jeśli inicjalizacja się powiodła, false w przeciwnym razie
     */
    bool init(const std::string& title,
              unsigned int screenWidth = 800,
              unsigned int screenHeight = 600,
              bool fullscreenMode = false,
              unsigned int targetFps = 60);

    /**
     * @brief Ustawia kolor czyszczenia okna
     * @param color Kolor tła okna
     */
    void setClearColor(const sf::Color& color);
    
    /**
     * @brief Ustawia tytuł okna
     * @param title Nowy tytuł okna
     */
    void setWindowTitle(const std::string& title);
    
    /**
     * @brief Włącza lub wyłącza obsługę myszy
     * @param enable true aby włączyć mysz, false aby wyłączyć
     */
    void enableMouse(bool enable);
    
    /**
     * @brief Włącza lub wyłącza obsługę klawiatury
     * @param enable true aby włączyć klawiaturę, false aby wyłączyć
     */
    void enableKeyboard(bool enable);

    /**
     * @brief Pobiera wskaźnik do okna SFML
     * @return Wskaźnik do sf::RenderWindow
     */
    sf::RenderWindow* getWindow();
    
    /**
     * @brief Pobiera rozmiar okna
     * @return Rozmiar okna jako sf::Vector2u
     */
    sf::Vector2u getWindowSize() const;
    
    /**
     * @brief Sprawdza, czy okno jest w trybie pełnoekranowym
     * @return true jeśli pełnoekranowy, false w przeciwnym razie
     */
    bool isFullscreen() const { return fullscreen; }
    
    /**
     * @brief Pobiera docelową liczbę FPS
     * @return Docelowa liczba klatek na sekundę
     */
    unsigned int getFPS() const { return fps; }
    
    /**
     * @brief Sprawdza, czy silnik jest uruchomiony
     * @return true jeśli uruchomiony, false w przeciwnym razie
     */
    bool isRunning() const { return isRunning1; }

    /**
     * @brief Rozpoczyna nową klatkę (czyści okno)
     */
    void beginFrame();
    
    /**
     * @brief Kończy klatkę (wyświetla zawartość)
     */
    void endFrame();

    /**
     * @brief Pobiera czas od ostatniej klatki
     * @return Czas delta w sekundach
     */
    float getDeltaTime() const;
    
    /**
     * @brief Pobiera całkowity czas działania silnika
     * @return Całkowity czas w sekundach
     */
    float getElapsedTime() const;

    /**
     * @brief Sprawdza, czy klawisz jest wciśnięty
     * @param key Sprawdzany klawisz
     * @return true jeśli klawisz jest wciśnięty, false w przeciwnym razie
     */
    bool isKeyPressed(sf::Keyboard::Key key) const;
    
    /**
     * @brief Sprawdza, czy przycisk myszy jest wciśnięty
     * @param button Sprawdzany przycisk myszy
     * @return true jeśli przycisk jest wciśnięty, false w przeciwnym razie
     */
    bool isMouseButtonPressed(sf::Mouse::Button button) const;
    
    /**
     * @brief Pobiera pozycję myszy względem okna
     * @return Pozycja myszy w pikselach okna
     */
    sf::Vector2i getMousePosition() const;
    
    /**
     * @brief Pobiera pozycję myszy w koordynatach świata (z uwzględnieniem widoku)
     * @return Pozycja myszy w koordynatach świata
     */
    sf::Vector2f getMouseWorldPosition() const;

    /**
     * @brief Uruchamia główną pętlę silnika
     */
    void mainLoop();
    
    /**
     * @brief Zamyka silnik i zwalnia zasoby
     */
    void shutdown();

    /**
     * @brief Loguje wiadomość do konsoli i pliku
     * @param message Wiadomość do zalogowania
     */
    void log(const std::string& message);
    
    /**
     * @brief Loguje błąd do konsoli i pliku
     * @param message Wiadomość błędu do zalogowania
     */
    void logError(const std::string& message);
    
    /**
     * @brief Loguje ostrzeżenie do konsoli i pliku
     * @param message Wiadomość ostrzeżenia do zalogowania
     */
    void logWarning(const std::string& message);

    /**
     * @brief Ustawia aktualny widok okna
     * @param view Nowy widok
     */
    void setView(const sf::View& view);
    
    /**
     * @brief Pobiera aktualny widok okna
     * @return Aktualny widok
     */
    const sf::View& getView() const;
    
    /**
     * @brief Resetuje widok do domyślnego
     */
    void resetView();
    
    /**
     * @brief Powiększa/pomniejsza aktualny widok
     * @param factor Współczynnik skalowania (>1 pomniejsza, <1 powiększa)
     */
    void zoom(float factor);
    
    /**
     * @brief Przesuwa aktualny widok
     * @param offsetX Przesunięcie w osi X
     * @param offsetY Przesunięcie w osi Y
     */
    void moveView(float offsetX, float offsetY);

private:
    sf::RenderWindow window;        ///< Główne okno renderowania
    bool fullscreen;                ///< Flaga trybu pełnoekranowego
    bool mouseEnabled;              ///< Flaga włączenia myszy
    bool keyboardEnabled;           ///< Flaga włączenia klawiatury
    unsigned int fps;               ///< Docelowa liczba FPS
    bool isRunning1;                ///< Flaga działania silnika
    sf::Color clearColor;           ///< Kolor czyszczenia okna

    sf::Clock frameClock;           ///< Zegar do pomiaru czasu klatki
    sf::Time deltaTime;             ///< Czas od ostatniej klatki
    sf::Time elapsedTime;           ///< Całkowity czas działania

    std::ofstream logFile;          ///< Strumień pliku logów

    /**
     * @brief Obsługuje zdarzenia SFML
     */
    void handleEvents();
    
    /**
     * @brief Aktualizuje stan silnika (do przesłonięcia w klasach pochodnych)
     */
    void update();
    
    /**
     * @brief Renderuje klatkę (do przesłonięcia w klasach pochodnych)
     */
    void render();

    // Wyłączenie kopiowania
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
};

#endif