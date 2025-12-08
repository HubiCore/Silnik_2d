/**
 * @file BitmapObject.hpp
 * @brief Deklaracja klasy BitmapObject
 * @ingroup BitmapObject
 * 
 * Klasa BitmapObject reprezentuje obiekt bitmapowy, który może być rysowany i transformowany.
 * Dziedziczy po klasach DrawableObject i TransformableObject, wykorzystując SFML do renderowania.
 */

#ifndef BITMAPOBJECT_HPP
#define BITMAPOBJECT_HPP

#include "../DrawableObject.hpp"
#include "../TransformableObject.hpp"
#include <SFML/Graphics.hpp>
#include <string>

/**
 * @class BitmapObject
 * @brief Klasa reprezentująca bitmapę jako obiekt graficzny
 * 
 * Klasa umożliwia ładowanie obrazów bitmapowych, ich wyświetlanie oraz przekształcenia geometryczne.
 * Wykorzystuje SFML do przechowywania i renderowania obrazów przez sprite'y.
 */
class BitmapObject : public DrawableObject, public TransformableObject {
private:
    sf::Image image;        ///< Przechowuje załadowany obraz bitmapowy
    sf::Texture texture;    ///< Tekstura utworzona z obrazu
    sf::Sprite sprite;      ///< Sprite używany do renderowania i transformacji

public:
    /**
     * @brief Domyślny konstruktor
     * 
     * Tworzy pusty obiekt bitmapowy bez załadowanego obrazu.
     */
    BitmapObject() = default;
    
    /**
     * @brief Konstruktor z ładowaniem obrazu
     * @param path Ścieżka do pliku obrazu
     * 
     * Tworzy obiekt bitmapowy i ładuje obraz z podanej ścieżki.
     * Obraz jest konwertowany na teksturę i przypisywany do sprite'a.
     */
    explicit BitmapObject(const std::string& path);

    /**
     * @brief Zwraca typ obiektu
     * @return String "BitmapObject"
     */
    std::string getType() const override { return "BitmapObject"; }

    /**
     * @brief Aktualizuje stan obiektu (implementacja domyślna)
     * 
     * Metoda wymagana przez interfejs, ale w tej implementacji nie wykonuje żadnych działań.
     */
    void update() override {}
    
    /**
     * @brief Rysuje obiekt (implementacja domyślna)
     * 
     * Metoda wymagana przez interfejs, ale w tej implementacji nie wykonuje żadnych działań.
     * Rzeczywiste rysowanie odbywa się przez metodę draw(PrimitiveRenderer&).
     */
    void draw() override {}

    /**
     * @brief Rysuje bitmapę na rendererze
     * @param renderer Referencja do renderera prymitywów
     * 
     * Metoda renderuje sprite'a na oknie docelowym renderera.
     * Wymaga, aby renderer miał ustawione okno docelowe (target).
     */
    void draw(PrimitiveRenderer& renderer) override;

    /**
     * @brief Przesuwa bitmapę o podane wartości
     * @param dx Przesunięcie wzdłuż osi X
     * @param dy Przesunięcie wzdłuż osi Y
     * 
     * Metoda wykorzystuje sf::Sprite::move do przesunięcia sprite'a.
     */
    void translate(float dx, float dy) override;
    
    /**
     * @brief Obraca bitmapę o podany kąt
     * @param angleDeg Kąt obrotu w stopniach
     * 
     * Metoda wykorzystuje sf::Sprite::rotate do obrócenia sprite'a.
     * Obrót odbywa się względem aktualnego punktu odniesienia sprite'a.
     */
    void rotate(float angleDeg) override;
    
    /**
     * @brief Skaluje bitmapę o podany współczynnik
     * @param factor Współczynnik skalowania
     * 
     * Metoda wykorzystuje sf::Sprite::scale do jednolitego skalowania sprite'a w obu osiach.
     */
    void scale(float factor) override;

    /**
     * @brief Ładuje obraz z pliku
     * @param path Ścieżka do pliku obrazu
     * @return true jeśli ładowanie się powiodło, false w przeciwnym razie
     * 
     * Metoda ładuje obraz, tworzy z niego teksturę i przypisuje teksturę do sprite'a.
     */
    bool loadFromFile(const std::string& path);
};

#endif