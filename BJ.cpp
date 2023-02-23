#include <iostream>
#include <windows.h>        // para windows


using namespace std;

//DEFINIR MAZO
int mazo[4][13];
string tipoCarta[4] = { "DIAMANTES", "PICAS", "TREBOLES", "CORAZONES" };

//VARIABLES GENERALES    
int selectSuit;
int carta;
bool escoger;
int puntuacion;
int pausa= 2000;

//VARIABLES JUGADOR

string jugador;
int cuentaJugador;
int valorComo;
bool escogerComo = false;
int eleccion;
bool mirarSeleccion = false;

//VARIABLES CRUPPIER

string rival;
int cuentaRival;

void selectCards() {
    escoger = false;

    //ELEGIMOS LA CARTA

    while (!escoger) {
        //SELECIONA UN PALO
        selectSuit = rand() % 4;
        //SELECCIONAR UNA CARTA
        carta = rand() % 13;

        //COMPROBAMOS QUE NO ESTA COGIDA LA CARTA Y LA QUITAMOS DEL MAZO
        if (mazo[selectSuit][carta] == 0)
        {
            cout << (carta + 1) << " " << tipoCarta[selectSuit] << " ";
            mazo[selectSuit][carta] = 1;
            escoger = true;
        }
        else {
            escoger = false;
        }
    }


}

int valueCards(int& cuentaCard, string& name) {
    //ASIGNAMOS EL VALOR A LAS CARTAS

    //VALOR DE LA CARTA DEL 1 AL 9
    if ((carta >= 1) && (carta <= 9)) {
        puntuacion = (carta + 1);
    }
    //VALOR DE LAS FIGURAS
    else if (carta >= 10) {
        puntuacion = 10;
    }
    //VALORES DEL AS
    if (carta == 0) {
        //ELECCION DEL VALOR AS PARA JUGADOR
        if (name == jugador) {
            cout << "\nQue valor le asignas al AS [1/11]";
            while (!escogerComo)
            {
                cin >> valorComo;
                if (valorComo == 1) {
                    puntuacion = 1;
                    escogerComo = true;
                }
                else if (valorComo == 11) {
                    puntuacion = 11;
                    escogerComo = true;
                }
            }
            valorComo = 0;
            //ELECCION DEL VALOR AS PARA CRUPIER
        }
        else if (name == rival)
            if ((carta + 11) <= 21) {
                puntuacion = 11;
            }
            else {
                puntuacion = 1;
            }
        escogerComo = false;
    }

    cuentaCard = cuentaCard + puntuacion;

    return cuentaCard;
}

void jugardorSelection() {
    while (!mirarSeleccion) {
        if (cuentaJugador == 21)
        {
            //CASO DE OBTENER UN BLACKJACK
            cout << jugador << " ha obtenido un blackjack, pasa automaticamente el turno al cruppier para intentar empatar\n";
            mirarSeleccion = true;
            break;
        }
        else if (cuentaJugador > 21) {
            //SI SE PASA LA PUNTUACION DE 21
            cout << "\n" << jugador << " ha sobrepasado 21 de puntuacion\n";
            break;
        }
        else {
            //PREGUNTAMOS SI QUIERE SEGUIR ROBANDO
            cout << "\nLa puntuacion total de " << jugador << " ahora mismo es de: " << cuentaJugador << "\n";
            cout << jugador << " quieres robar una carta o rezar para ganar?" << "\n[1] ROBAR" << "\n[2] Rezar para ganar\n";
            cin >> eleccion;

            if (eleccion == 2) {
                cout << "\n" << jugador << " no roba mas cartas";
                cout << "\nLa puntuacion final de " << jugador << " es: " << cuentaJugador << "\n";
                mirarSeleccion = true;

            }
            else if (eleccion == 1) {
                cout << "El crupier reparte otra carta a " << jugador << "\n";
                Sleep(pausa);
                selectCards();
                valueCards(cuentaJugador, jugador);
                cout << "\nLa puntuacion de " << jugador << " es: " << cuentaJugador << "\n";
            }
            else {
                cout << "ERROR: Introduce una eleccion valida [1/2]\n";
            }
        }

    }

}

void crupierSelection() {
    //FUNCION PARA SABER SI EL CRUPPIER SIGUE ROBANDO O NO
    while (cuentaRival <= cuentaJugador && cuentaJugador <= 21) {
        Sleep(pausa);
        cout << "El crupier reparte otra carta a " << rival << "\n";
        Sleep(pausa);
        selectCards();
        valueCards(cuentaRival, rival);
        cout << "\nLa puntuacion del " << rival << " es: " << cuentaRival << "\n\n";

    }

}
void checkWin() {
    //QUIEN GANA LA PARTIDA

    if (cuentaRival == 21 && cuentaJugador != 21) {
        cout << "El crupier ha obtenido un blackjack el " << rival << " gana la partida\n";
    }
    else if (cuentaRival != 21 && cuentaJugador == 21) {
        cout << jugador << " ha obtenido un blackjack el y por lo tanto gana la partida\n";
    }
    else if (cuentaRival == 21 && cuentaJugador == 21) {
        cout << jugador << " y el cruppier ha obtenido un blackjack es un empate\n";
    }
    else if (cuentaJugador > cuentaRival && cuentaJugador < 21 && cuentaRival < 21) {
        cout << jugador << " ha ganado la partida\n";
    }
    else if (cuentaJugador < 21 && cuentaRival > 21) {
        cout << jugador << " ha ganado la partida\n";
    }
    else if (cuentaJugador < cuentaRival && cuentaRival < 21 && cuentaJugador < 21) {
        cout << rival << " ha ganado la partida\n";
    }
}


void main()
{
    srand(time(NULL));
    cout << "Inserta el nombre del jugador: ";
    cin >> jugador;
    cout << "El crupier reparte dos cartas a " << jugador << "\n";
    Sleep(pausa);
    selectCards();
    valueCards(cuentaJugador, jugador);
    selectCards();
    valueCards(cuentaJugador, jugador);
    cout << "\nLa puntuacion total de " << jugador << " ahora mismo es de: " << cuentaJugador << "\n";
    cout << "\n\nComo quieres que se llame tu rival: ";
    cin >> rival;
    cout << "El crupier reparte una carta a " << rival << "\n";
    Sleep(pausa);
    selectCards();
    valueCards(cuentaRival, rival);
    cout << "\nLa puntuacion de " << rival << " es: " << cuentaRival << "\n\n";
    jugardorSelection();
    cout << "\nEl crupier reparte la segunda carta a " << rival << "\n";
    Sleep(pausa);
    selectCards();
    valueCards(cuentaRival, rival);
    cout << "\nLa puntuacion del " << rival << " es: " << cuentaRival << "\n\n";
    crupierSelection();
    checkWin();

}