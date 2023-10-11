#pragma once
#include "SFML\Graphics.hpp"

class TileMaps : public sf::Transformable, public sf::Drawable
{
public:
	bool load(const std::string& tileset, sf::Vector2u tileSize, const int*
		tiles, unsigned int width, unsigned int height)
	{
		int CornerNumber = 6;
		//carregueu la textura del conjunt de rajoles
		if (!m_tileset.loadFromFile(tileset))
			return false;

		//Canvieru la mida de la matriu de vertex per adaptarla a la mida del nivel
		m_vertices.setPrimitiveType(sf::Triangles);
		m_vertices.resize(width * height * CornerNumber);

		//Pobla la matriu de vertexs, amb dos triagles per rajola
		for (unsigned int i = 0; i < width; ++i)
			for (unsigned int j = 0; j < height; ++j)
			{
				//Obtenim el numero de peça actual
				int tileNumber = tiles[i + j * width];
				int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
				int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

				//Obtenim un puter als vertex dels triagles de la fitxa actual
				sf::Vertex* triangles = &m_vertices[(i + j * width) * CornerNumber];

				//defineix les 6 cantonades dels dos triagles
				triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
				triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
				triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

				triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
				triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
				triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
				triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
				triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
				triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			}

	}
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		//apply the transform
		states.transform *= getTransform();

		//states.transform *= getTransform();
	   //apply the tileset texture
		states.texture = &m_tileset;
		//draw the vertex array
		target.draw(m_vertices, states);
	}
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
};