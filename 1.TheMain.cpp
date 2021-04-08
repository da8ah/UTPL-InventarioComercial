#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <String>
#include <String.h>
#include <locale.h>
#include "2.Menu.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "spanish");
    setlocale(LC_NUMERIC, "english");
    opcionTipoUsuario();
    return 0;
}
