//Codigo realizado por Armando Yañez

#include <SFML/Graphics.hpp>
#include <iostream>

int main(){
// Configuraciones de la pantalla
    float ancho = 800;
    float alto = 600;

    // Creamos la ventana
    sf::RenderWindow window(sf::VideoMode(ancho, alto), "PAPU PONG");

    // Linea punteada
    int cantidadLinea = alto / 30;
    float espaciado = 0;
    std::vector<sf::RectangleShape> LineaPunteada(cantidadLinea); // Usamos std::vector para tamaño dinámico

    // Generamos las líneas punteadas
    for (int i = 0; i < cantidadLinea; ++i) {
        LineaPunteada[i].setPosition(ancho / 2, alto - espaciado);
        LineaPunteada[i].setSize(sf::Vector2f(3, 10));
        LineaPunteada[i].setFillColor(sf::Color::White);

        espaciado += 30;
    }

    //Rectangulos de los jugadores
    sf::RectangleShape player1, player2;

    //Configuracion tamaño
    player1.setSize(sf::Vector2f (10, alto/6));
    player2.setSize(sf::Vector2f (10, alto/6));

    //Configuracion posicion
    player1.setPosition(10, alto/2-((alto/6)/2));
    player2.setPosition(ancho-20, alto/2-((alto/6)/2));

    //Le asignamos colores
    player1.setFillColor(sf::Color::Magenta);
    player2.setFillColor(sf::Color::Red);

    //Velocidad
    float velocidad = 0.1;


    //Pelota
    sf::CircleShape pelota;

    //Le damos un tamaño
    pelota.setRadius(10);

    //Pocision inicial
    pelota.setPosition(ancho / 2 - 10, alto / 2 - 10);

    //Velocidad de pelota
    sf::Vector2f velocidadPelota;

    //Numero random para la pocision de la pelota
    int direccionInicial = std::rand() % 4;

    switch (direccionInicial) {
        case 0:
            velocidadPelota = sf::Vector2f(-0.02f, -0.02f);
            break;
        case 1:
            velocidadPelota = sf::Vector2f(0.02f, -0.02f);
            break;
        case 2:
            velocidadPelota = sf::Vector2f(-0.02f, 0.02f);
            break;
        case 3:
            velocidadPelota = sf::Vector2f(0.02f, 0.02f);
            break;
    }

    //Color de la pelota
    pelota.setFillColor(sf::Color::White);

    //Creamos los textos de los puntuajes
    sf::Text p1score;
    sf::Text p2score;

    sf::Font font, font1;
    if (!font.loadFromFile("../Retrocompute.ttf")) {
        std::cerr<<"Error al cargar la fuentes";
    }

    //Fuentes para los textos
    p1score.setFont(font);
    p2score.setFont(font);

    // asignamos el tamaño y el color de los textos
    p1score.setCharacterSize(30);
    p2score.setCharacterSize(30);
    p1score.setFillColor(sf::Color::Magenta);
    p2score.setFillColor(sf::Color::Red);

    // Posiciones iniciales de los textos
    p1score.setPosition(ancho / 4, 20);
    p2score.setPosition(3 * ancho / 4, 20);

    //Controladores del puntuaje
    int intscorep1 = 0;
    int intscorep2 = 0;

    p1score.setString("0");
    p2score.setString("0");


    //Creamos textos para titulos de victoria o derrota
    sf::Text victoriap1, victoriap2;

    //Configiracion de los titulos de ganador
    victoriap1.setString("P2 WINNER");
    victoriap1.setFont(font);
    victoriap1.setCharacterSize(100);
    victoriap1.setFillColor(sf::Color::Magenta);
    victoriap1.setPosition(ancho / 2 - victoriap1.getGlobalBounds().width / 2, alto / 2 - victoriap1.getGlobalBounds().height);

    victoriap2.setString("P2 WINNER");
    victoriap2.setFont(font);
    victoriap2.setCharacterSize(100);
    victoriap2.setFillColor(sf::Color::Red);
    victoriap2.setPosition(ancho / 2 - victoriap2.getGlobalBounds().width / 2, alto / 2 - victoriap2.getGlobalBounds().height);

    //Bucle principal
    while (window.isOpen()) {

        //Manejo de eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Movimiento de la pelota
        pelota.move(velocidadPelota);

        // Colision vertical
        if (pelota.getPosition().y < 0 || pelota.getPosition().y + 2 * 10 > alto) {
            velocidadPelota.y = -velocidadPelota.y;
        }

        // colison con player1 y player2
        if (pelota.getGlobalBounds().intersects(player1.getGlobalBounds()) ||
            pelota.getGlobalBounds().intersects(player2.getGlobalBounds())) {
            velocidadPelota.x = -velocidadPelota.x;

            //Aumentamos la velocidad un poco
            //Verificamos si la velocidad es negativa o psitiva y segun eso restamos o sumamos la velocidad
            velocidadPelota.x += (velocidadPelota.x > 0) ? 0.005 : -0.005;
        }

        // Colision horizontal
        if (pelota.getPosition().x < 0 || pelota.getPosition().x + 2 * 10 > ancho) {

            if(pelota.getPosition().x < 0){
                intscorep2++;
                p2score.setString(std::to_string(intscorep2));
            }else if( pelota.getPosition().x + 2 * 10 > ancho){
                intscorep1++;
                p1score.setString(std::to_string(intscorep1));
            }

            // El primerp en llegar a 7
            if (intscorep1 >= 7 || intscorep2 >= 7) {
                if (intscorep1 >= 7) {
                    window.draw(victoriap1);
                } else {
                    window.draw(victoriap2);
                }

                window.display();
                sf::sleep(sf::seconds(1.0f)); // esperar 1 segundo

                // reinicair contadores
                intscorep1 = 0;
                intscorep2 = 0;
                p1score.setString("0");
                p2score.setString("0");
            }

            // Pocision inicial de la pelota
            pelota.setPosition(ancho / 2 - 10, alto / 2 - 10);

            // Nuevo indice random
            direccionInicial = std::rand() % 4;
            switch (direccionInicial) {
                case 0:
                    velocidadPelota = sf::Vector2f(-0.02f, -0.02f);
                    break;
                case 1:
                    velocidadPelota = sf::Vector2f(0.02f, -0.02f);
                    break;
                case 2:
                    velocidadPelota = sf::Vector2f(-0.02f, 0.02f);
                    break;
                case 3:
                    velocidadPelota = sf::Vector2f(0.02f, 0.02f);
                    break;
            }
        }

        // Controles del player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player1.getPosition().y > 0) {
            player1.move(0, -velocidad);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player1.getPosition().y + player1.getSize().y < alto) {
            player1.move(0, velocidad);
        }

        // Controles del player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player2.getPosition().y > 0) {
            player2.move(0, -velocidad);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player2.getPosition().y + player2.getSize().y < alto) {
            player2.move(0, velocidad);
        }

        // Limpiamos la ventana
        window.clear();

        // Dibujar figuras
        for (int i = 0; i < cantidadLinea; ++i) {
            window.draw(LineaPunteada[i]);
        }

        //Dibujar rectangulos del jugador 1 y 2
        window.draw(player1);
        window.draw(player2);

        window.draw(pelota);

        window.draw(p1score);
        window.draw(p2score);


        // Mostramos la ventana
        window.display();
    }

    return 0;
}