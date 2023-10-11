#include "SFML\Graphics.hpp"
#include "TileMaps.cpp"
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    // Crea la ventana
    sf::RenderWindow window(sf::VideoMode(512, 256), "Tilemap");

    // Pregunta al usuario qué mapa desea cargar
    int selectedMap;
    std::cout << "Seleccioni el mapa (1 o 2): ";
    std::cin >> selectedMap;

    // Define el nombre del archivo del mapa seleccionado
    std::string mapFileName;

    if (selectedMap == 1)
    {
        mapFileName = "map_data.txt"; // Si selecciona "mapa 1", cargar "map_data.txt"
    }
    else if (selectedMap == 2)
    {
        mapFileName = "mapa2.txt"; // Si selecciona "mapa 2", cargar "mapa2.txt" (o el nombre que desees)
    }
    else
    {
        std::cerr << "Selección de mapa no válida." << std::endl;
        return -1;
    }

    // Abrir el archivo del mapa seleccionado
    std::ifstream mapFile(mapFileName);
    if (!mapFile.is_open())
    {
        std::cerr << "No s'ha pogut obrir el fitxer del mapa." << std::endl;
        return -1;
    }

    // Leer los datos del mapa desde el archivo
    std::vector<int> level;
    int tile;
    while (mapFile >> tile)
    {
        level.push_back(tile);
    }

    mapFile.close(); // Cerrar el archivo del mapa

    TileMaps map;
    if (!map.load("Tilemap.png", sf::Vector2u(32, 32), level.data(), 16, 8))
        return -1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(map);
        window.display();
    }
    return 0;
}
