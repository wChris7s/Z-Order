#include <iostream>
#include <bitset>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>

// C++23 - CLION

using std::cout, std::endl, std::vector, std::string, std::bitset;

#define DATA_S 5000
#define RAND_MX_NUMBER 15
#define LL unsigned long long

LL Dimension1(LL PUNTOXi, LL PUNTOXj){
    return pow(PUNTOXi - PUNTOXj, 2);
}
LL DimensionN(LL PUNTOXi, LL PUNTOXj){
    LL res = {};
    for(int i = 0; i < 10; i++){
        res = res + (Dimension1(PUNTOXi, PUNTOXj));
    }
    return sqrt(res);
}

// KNN TO-DO

LL zOrder10(vector<string> Points){ // 10 dimensiones -> Points(10) -> Max 8 bits
    // Estrategia Fin a Inicio
    // Intercalado de Bits
    string result;
    result = result +
            Points[7][0] + Points[6][0] + Points[5][0] + Points[4][0] + Points[3][0] + Points[2][0] + Points[1][0] + Points[0][0] +
            Points[7][1] + Points[6][1] + Points[5][1] + Points[4][1] + Points[3][1] + Points[2][1] + Points[1][1] + Points[0][1] +
            Points[7][2] + Points[6][2] + Points[5][2] + Points[4][2] + Points[3][2] + Points[2][2] + Points[1][2] + Points[0][2] +
            Points[7][3] + Points[6][3] + Points[5][3] + Points[4][3] + Points[3][3] + Points[2][3] + Points[1][3] + Points[0][3] +
            Points[7][4] + Points[6][4] + Points[5][4] + Points[4][4] + Points[3][4] + Points[2][4] + Points[1][4] + Points[0][4] +
            Points[7][5] + Points[6][5] + Points[5][5] + Points[4][5] + Points[3][5] + Points[2][5] + Points[1][5] + Points[0][5] +
            Points[7][6] + Points[6][6] + Points[5][6] + Points[4][6] + Points[3][6] + Points[2][6] + Points[1][6] + Points[0][6] +
            Points[7][7] + Points[6][7] + Points[5][7] + Points[4][7] + Points[3][7] + Points[2][7] + Points[1][7] + Points[0][7];
    LL number = bitset<64>(result).to_ullong();
    return number;
}

uint32_t calcZOrder(uint16_t xPos, uint16_t yPos)
{
    static const uint32_t MASKS[] = {0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF};
    static const uint32_t SHIFTS[] = {1, 2, 4, 8};

    uint32_t x = xPos;  // Interleave lower 16 bits of x and y, so the bits of x
    uint32_t y = yPos;  // are in the even positions and bits from y in the odd;

    x = (x | (x << SHIFTS[3])) & MASKS[3];
    x = (x | (x << SHIFTS[2])) & MASKS[2];
    x = (x | (x << SHIFTS[1])) & MASKS[1];
    x = (x | (x << SHIFTS[0])) & MASKS[0];

    y = (y | (y << SHIFTS[3])) & MASKS[3];
    y = (y | (y << SHIFTS[2])) & MASKS[2];
    y = (y | (y << SHIFTS[1])) & MASKS[1];
    y = (y | (y << SHIFTS[0])) & MASKS[0];

    const uint32_t result = x | (y << 1);
    return result;
}

int main() {
    srand((unsigned) time(nullptr));

    vector<vector<string>> DataSet_10D(DATA_S);
    vector<LL> DataSet_1D(DATA_S);
    vector<unsigned> DatosGenerados;
    vector<unsigned> tmp;
    vector<vector<string>> DatosPrueba10(10); // Obtener los 5,10,15,20 vecinos más cercanos para cada punto 10D.
    vector<LL> DatosPrueba1(10); // Obtener los 5,10,15,20 vecinos más cercanos para cada punto 1D.

    for(int i = 0; i < DATA_S; i++) {
        for (int j = 0; j < 10; j++) {
            unsigned a = 1 + rand() % RAND_MX_NUMBER;   // Genera los num aleatorios
            DatosGenerados.push_back(a);                // Almacena los datos generados
            tmp.push_back(a);                           // Almacena los valores de un punto (10 datos)
        }
        sort(tmp.begin(), tmp.end());                   // Ordena los 10 datos
        for (int j = 0; j < 10; j++) {
            DataSet_10D[i].push_back(bitset<8>(tmp[j]).to_string());   // Añade los datos en cadena de bits
        }
        tmp.clear();    // Limpia el buffer de datos
    }
    LL D1D; // Datos a una dimensión
    for (int i = 0; i < DATA_S; ++i) {
        D1D = zOrder10(DataSet_10D[i]);
        DataSet_1D[i] = D1D;    // Proyección de las 10 Dimensiones a 1 dimensión
    }

    // ----- Obtener 10 puntos al azar
    for(int i = 0; i < 10; ++i){
        unsigned ii = rand() % DATA_S;
        DatosPrueba10[i] = DataSet_10D[ii];
        DatosPrueba1[i] = DataSet_1D[ii];
    }
    // ---- Puntos Generados
    for(int i = 0; i < 10; i++){
        for (int j = 0; j < 10; ++j) {
            cout << DatosPrueba10[i][j] << " ";
        }
        cout << endl;
        cout << DatosPrueba1[i] << " - " << bitset<64>(DatosPrueba1[i]).to_string() << endl << endl;
    } cout << endl;




    return 0;
}
