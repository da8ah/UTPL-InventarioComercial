#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <String>
#include <String.h>
#include <stdexcept>
#include <locale.h>
#include "3.Funciones.h"
using namespace std;

void validarAdministrador();
void primerRegistroAux();
void comoAdministrador();

void opcionTipoUsuario()
{
    setlocale(LC_ALL, "spanish");
    setlocale(LC_NUMERIC, "english");

    bool bandera = true;
    int control;

    do
    {
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "\t****** ***** ***** *   * ****  *****     \t\t****** ***** ***** *   *  ****  " << endl;
        cout << "\t  **     *   *     **  * *   * *   *     \t\t  **   *     *     **  * *    * " << endl;
        cout << "\t  **     *   ****  * * * *   * *****     \t\t  **   ****  *     * * * *    * " << endl;
        cout << "\t  **     *   *     *  ** *   * *   *     \t\t  **   *     *     *  ** *    * " << endl;
        cout << "\t  **   ***** ***** *   * ****  *   *     \t\t  **   ***** ***** *   *  ****  * * * " << endl;
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Adquirir algún bien o servicio.\t\tFinalizar sesión." << endl;
        cout << "\t(1)ADMINISTRADOR\t\t\t(Otro)SALIR" << endl;
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Opción>> ";
        cin >> control;
        switch (control)
        {
        case 1:
            system("cls");
            validarAdministrador();
            break;
        default:
            bandera = false;
            break;
        }
    } while (bandera);
}

void validarAdministrador()
{
    setlocale(LC_ALL, "spanish");
    setlocale(LC_NUMERIC, "english");

    bool bandera = true;
    string pseudonimo;
    string pass;
    int control;

    do
    {
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "\t****** ***** ***** *   * ****  *****     \t\t****** ***** ***** *   *  ****  " << endl;
        cout << "\t  **     *   *     **  * *   * *   *     \t\t  **   *     *     **  * *    * " << endl;
        cout << "\t  **     *   ****  * * * *   * *****     \t\t  **   ****  *     * * * *    * " << endl;
        cout << "\t  **     *   *     *  ** *   * *   *     \t\t  **   *     *     *  ** *    * " << endl;
        cout << "\t  **   ***** ***** *   * ****  *   *     \t\t  **   ***** ***** *   *  ****  * * * " << endl;
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Autenticarse como Administrador(a):" << endl;
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Usuario: ";
        cin >> pseudonimo;
        if (administrador.getPseudonimo() == pseudonimo)
        {
            cout << "Contraseña: ";
            cin >> pass;
            cin.ignore();
            if (administrador.getPass() == pass)
            {
                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                cout << "¡Bienvenido(a)!" << endl;
                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                system("PAUSE");
                system("cls");
                comoAdministrador();
                bandera = false;
            }
            else
            {
                cout << endl;
                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                cout << "# CONTRASEÑA INCORRECTA # Intente nuevamente..." << endl;
                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                system("PAUSE");
                system("cls");
            }
        }
        else
        {
            cout << endl;
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cout << "# USUARIO INCORRECTO # Intente nuevamente..." << endl;
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            system("PAUSE");
            system("cls");
        }
    } while (bandera);
}

void comoAdministrador()
{
    setlocale(LC_ALL, "spanish");
    setlocale(LC_NUMERIC, "english");

    bool bandera = true;
    int control;
    do
    {
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "ACCIONES de Administrador(a):" << endl;
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "(1)AGREGAR PRODUCTOS: Ingresar nuevo producto." << endl;
        cout << "(2)VER PRODUCTOS: Abrir el inventario." << endl;
        cout << "(3)MODIFICAR PRODUCTO: Editar los parámetros de un producto." << endl;
        cout << "(4)ELIMINAR PRODUCTO: Eliminar del almacen un producto." << endl;
        cout << "(Otro)SALIR: Volver al menú." << endl;
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Opción>> ";
        cin >> control;
        cin.ignore();
        switch (control)
        {
        case 1:
            system("cls");
            ingresoInventario();
            break;
        case 2:
            system("cls");
            verInventario();
            system("PAUSE");
            system("cls");
            break;
        case 3:
            system("cls");
            modificarRegistros();
            break;
        case 4:
            system("cls");
            eliminarRegistro();
            break;
        default:
            bandera = false;
            break;
        }
    } while (bandera);
}