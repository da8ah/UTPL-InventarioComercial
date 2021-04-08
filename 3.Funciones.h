#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <String>
#include <String.h>
#include <locale.h>
using namespace std;
FILE *archivo;
FILE *archivoAux;
FILE *archivoComprador;
FILE *archivoCompradorAux;
char direccion[] = "./Archivos/Inventario.csv";
char direccionAux[] = "./Archivos/InventarioAux.csv";
class Administrador
{
private:
    string pseudonimo = "T";

private:
    string pass = "10";

public:
    string getPseudonimo()
    {
        return pseudonimo;
    }

public:
    string getPass()
    {
        return pass;
    }
};
struct Registro
{
    int numero;
    char abastecedora[10];
    char descripcion[35];
    int cantidad;
    double precioUnitario;
    int iva;
    double subtotal;
    double total;
};

char encabezado[] = "N°;Abastecedora;Descripción;Cantidad;Precio Unitario;Impuesto;Subtotal;Total\n";
Administrador administrador;
// PROTOTIPO DE LOS MÉTODOS:
// Administrador:
void ingresoInventario();
double calcularSubtotal(double b, int c);
double calcularTotal(double b, int c);
void verInventario();
void modificarRegistros();
Registro *editorDeRegistro(Registro *registroModificar);
void buscarRegistro();
void eliminarRegistro();
// Otros:
void imprimirRegistro(Registro *registroImprimir);

// MÉTODOS PARA USUARIO TIPO: ADMINISTRADOR
void ingresoInventario()
{
    setlocale(LC_ALL, "spanish");
    setlocale(LC_NUMERIC, "english");

    // Comprobar que el archivo existe
    archivo = fopen(direccion, "r");
    if (archivo == NULL)
    {
        fclose(archivo);
        archivo = fopen(direccion, "w");
        fprintf(archivo, "%d %s\n", 0, "registros.");
        fputs(encabezado, archivo);
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "# ARCHIVO NO ENCONTRADO # Se creó un nuevo archivo correctamente..." << endl;
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "(Ruta) " << direccion << endl;
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        system("PAUSE");
        system("cls");
    }
    fclose(archivo);

    // Variables:
    int opcion;
    int totalRegistros;
    Registro *registroTemporal = ((struct Registro *)malloc(sizeof(struct Registro)));

    // Proceso:
    bool bandera = true;
    do
    {
        for (int vaciar = 0; vaciar < 10; vaciar++)
        {
            registroTemporal->abastecedora[vaciar] = ' ';
        }
        for (int vaciar = 0; vaciar < 35; vaciar++)
        {
            registroTemporal->descripcion[vaciar] = ' ';
        }

        // Ingreso de datos del nuevo registro
        archivo = fopen(direccion, "r");
        fscanf(archivo, "%d", &totalRegistros);
        fclose(archivo);
        totalRegistros++;
        registroTemporal->numero = totalRegistros;

        cout << "INGRESO DE DATOS" << endl;
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Ingrese la abastecedora: ";
        cin.getline(registroTemporal->abastecedora, 11);
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Ingrese una descripción: ";
        cin.getline(registroTemporal->descripcion, 36);
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        do
        {
            cout << "Ingrese cantidad de productos: ";
            cin >> registroTemporal->cantidad;
            if (registroTemporal->cantidad > 1000 || registroTemporal->cantidad <= 0)
            {
                cout << "# La cantidad debe estar en un rango entre 1 a 1000. #" << endl;
                registroTemporal->cantidad = -1;
            }
        } while (registroTemporal->cantidad == -1);
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        do
        {
            cout << "Ingrese precio por unidad: ";
            cin >> registroTemporal->precioUnitario;
            if (registroTemporal->precioUnitario > 1000000)
            {
                cout << "# Si esto es una prueba déjame advertirte que no puedes alcanzar el millón. Intenta nuevamente. #" << endl;
                registroTemporal->precioUnitario = -1;
            }
            else if (registroTemporal->precioUnitario < 0)
            {
                cout << "# El precio por unidad debe ser mayor a 0. #" << endl;
                registroTemporal->precioUnitario = -1;
            }
        } while (registroTemporal->precioUnitario == -1);
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        do
        {
            cout << "Ingrese el (%) del impuesto: ";
            cin >> registroTemporal->iva;
            if (registroTemporal->iva > 15 || registroTemporal->iva < 0)
            {
                cout << "# El impuesto debe estar en un rango entre 0% a 15%. #" << endl;
                registroTemporal->iva = -1;
            }
        } while (registroTemporal->iva == -1);
        registroTemporal->subtotal = calcularSubtotal(registroTemporal->precioUnitario, registroTemporal->iva);
        registroTemporal->total = calcularTotal(registroTemporal->subtotal, registroTemporal->cantidad);

        // Editor del Registro
        registroTemporal = editorDeRegistro(registroTemporal);

        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "(1)GUARDAR\t(Otro)Descartar" << endl;
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
        case 1:
            // Escritura del registro en el archivo
            archivo = fopen(direccion, "a");
            fprintf(archivo, "%d;", registroTemporal->numero);
            for (int j = 0; j < 10; j++)
            {
                fprintf(archivo, "%c", registroTemporal->abastecedora[j]);
            }
            fprintf(archivo, ";");
            for (int j = 0; j < 35; j++)
            {
                fprintf(archivo, "%c", registroTemporal->descripcion[j]);
            }
            fprintf(archivo, ";%d;%.2f;%d;%.2f;%.2f\n", registroTemporal->cantidad, registroTemporal->precioUnitario,
                    registroTemporal->iva, registroTemporal->subtotal, registroTemporal->total);
            fclose(archivo);

            // Actualización del total de registros
            archivo = fopen(direccion, "r+");
            fprintf(archivo, "%d %s\n", totalRegistros, "registros.");
            fclose(archivo);

            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cout << "* REGISTRO GUARDADO CORRECTAMENTE *" << endl;
            break;
        default:
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cout << "# Registro Descartado #" << endl;
            break;
        }

        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "(1)AGREGAR NUEVO\t(Otro)Salir" << endl;
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
        case 1:
            system("cls");
            break;
        default:
            bandera = false;
            cout << "************************************************************************************************************" << endl;
            cout << "VOLVIENDO AL MENÚ PRINCIPAL..." << endl;
            cout << "************************************************************************************************************" << endl;
            system("PAUSE");
            system("cls");
            break;
        }
    } while (bandera);
}
double calcularSubtotal(double b, int c)
{
    double a;
    return a = (((b * c) / 100) + b);
}
double calcularTotal(double b, int c)
{
    double a;
    return a = b * c;
}

void verInventario()
{
    setlocale(LC_ALL, "spanish");
    setlocale(LC_NUMERIC, "english");

    // Archivo
    archivo = fopen(direccion, "r");

    if (archivo == NULL)
    {
        cout << "************************************************************************************************************" << endl;
        cout << "# NO EXISTEN REGISTROS # VOLVIENDO AL MENÚ PRINCIPAL..." << endl;
        cout << "************************************************************************************************************" << endl;
    }
    else
    {
        // Variables
        Registro *registroGuardado = ((struct Registro *)malloc(sizeof(struct Registro)));
        int totalRegistros = 0;
        char encabezado[100];
        char palabra[15];
        char descartar;

        for (int vaciar = 0; vaciar < 10; vaciar++)
        {
            registroGuardado->abastecedora[vaciar] = ' ';
        }
        for (int vaciar = 0; vaciar < 15; vaciar++)
        {
            palabra[vaciar] = ' ';
        }
        for (int vaciar = 0; vaciar < 35; vaciar++)
        {
            registroGuardado->descripcion[vaciar] = ' ';
        }
        for (int vaciar = 0; vaciar < 100; vaciar++)
        {
            encabezado[vaciar] = ' ';
        }

        // Lectura de Archivo e Impresión de Registros
        fscanf(archivo, "%d", &totalRegistros);
        fgets(palabra, 15, archivo);
        fgets(encabezado, 100, archivo);
        printf("%d %s", totalRegistros, palabra);
        printf("N°;Abastecedora;Descripción\t\t\t;Cantidad;Precio Unitario;Impuesto;Subtotal;Total\t\n");
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        while (registroGuardado->numero != totalRegistros && totalRegistros > 0)
        {
            fscanf(archivo, "%d", &registroGuardado->numero);
            fscanf(archivo, "%c", &descartar);
            for (int i = 0; i < 10; i++)
            {
                fscanf(archivo, "%[^;]c", &registroGuardado->abastecedora[i]);
            }
            fscanf(archivo, "%c", &descartar);
            for (int i = 0; i < 35; i++)
            {
                fscanf(archivo, "%[^;]c", &registroGuardado->descripcion[i]);
            }
            fscanf(archivo, "%c%d%c%lf%c%d%c%lf%c%lf", &descartar, &registroGuardado->cantidad,
                   &descartar, &registroGuardado->precioUnitario, &descartar, &registroGuardado->iva,
                   &descartar, &registroGuardado->subtotal, &descartar, &registroGuardado->total);
            imprimirRegistro(registroGuardado);
        }
    }
    fclose(archivo);
    cout << "------------------------------------------------------------------------------------------------------------" << endl;
}

void modificarRegistros()
{
    setlocale(LC_ALL, "spanish");
    setlocale(LC_NUMERIC, "english");

    // Variables de control:
    bool bandera = true;
    bool encontrado = false;
    int control;
    int control_registro;

    // PROCESO Y PROCEDIMIENTOS:
    while (bandera)
    {
        // Variables para modificar el registro
        Registro *registroModificar = ((struct Registro *)malloc(sizeof(struct Registro)));
        int totalRegistros = 0;
        char encabezado[100];
        char palabra[15];
        char descartar;
        for (int vaciar = 0; vaciar < 10; vaciar++)
        {
            registroModificar->abastecedora[vaciar] = ' ';
        }
        for (int vaciar = 0; vaciar < 15; vaciar++)
        {
            palabra[vaciar] = ' ';
        }
        for (int vaciar = 0; vaciar < 35; vaciar++)
        {
            registroModificar->descripcion[vaciar] = ' ';
        }
        for (int vaciar = 0; vaciar < 100; vaciar++)
        {
            encabezado[vaciar] = ' ';
        }

        verInventario();

        // Búsqueda del registro seleccionado en el archivo original
        /* Nota: (Modificar)
         1 Se lee el archivo original y se escribe en el archivo auxiliar iterativamente cada registro.
         2 Cuando se encuentra el registro seleccionado se modifican sus atributos.
         3 Si el usuario desea confirma los cambios o los descarta.
        */
        // Lectura del archivo original antes de iterar
        archivo = fopen(direccion, "r");
        fscanf(archivo, "%d", &totalRegistros);
        fgets(palabra, 15, archivo);
        fgets(encabezado, 100, archivo);
        if (totalRegistros > 0)
        {
            cout << "Seleccione el registro: ";
            cin >> control_registro;

            // Escritura en el archivoAux antes de iterar
            archivoAux = fopen(direccionAux, "w");
            fprintf(archivoAux, "%d %s\n", totalRegistros, "registros.");
            fputs(encabezado, archivoAux);

            while (registroModificar->numero != totalRegistros)
            {
                // Lectura iterativa de registros del archivo original
                fscanf(archivo, "%d", &registroModificar->numero);
                fscanf(archivo, "%c", &descartar);
                for (int i = 0; i < 10; i++)
                {
                    fscanf(archivo, "%[^;]c", &registroModificar->abastecedora[i]);
                }
                fscanf(archivo, "%c", &descartar);
                for (int i = 0; i < 35; i++)
                {
                    fscanf(archivo, "%[^;]c", &registroModificar->descripcion[i]);
                }
                fscanf(archivo, "%c%d%c%lf%c%d%c%lf%c%lf", &descartar, &registroModificar->cantidad,
                       &descartar, &registroModificar->precioUnitario, &descartar, &registroModificar->iva,
                       &descartar, &registroModificar->subtotal, &descartar, &registroModificar->total);

                // En caso de encontrar el registro seleccionado
                if (registroModificar->numero == control_registro)
                {
                    cout << "------------------------------------------------------------------------------------------------------------" << endl;
                    cout << "REGISTRO SELECCIONADO" << endl;
                    cout << "------------------------------------------------------------------------------------------------------------" << endl;

                    // Editor del Registro
                    registroModificar = editorDeRegistro(registroModificar);

                    encontrado = true;
                }

                // Escritura iterativa de registros en archivoAux
                fprintf(archivoAux, "%d;", registroModificar->numero);
                for (int k = 0; k < 10; k++)
                {
                    fprintf(archivoAux, "%c", registroModificar->abastecedora[k]);
                }
                fprintf(archivoAux, ";");
                for (int k = 0; k < 35; k++)
                {
                    fprintf(archivoAux, "%c", registroModificar->descripcion[k]);
                }
                fprintf(archivoAux, ";%d;%.2f;%d;%.2f;%.2f\n", registroModificar->cantidad, registroModificar->precioUnitario,
                        registroModificar->iva, registroModificar->subtotal, registroModificar->total);
            }

            // Cierre de Archivos
            fclose(archivo);
            fclose(archivoAux);

            // Finalizando
            if (encontrado == false)
            {
                // Se elimina el archivo auxiliar porque no se realizaron cambios
                remove(direccionAux);
                cout << endl;
                cout << "# REGISTRO NO ENCONTRADO #" << endl;
                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                cout << "(1)VOLVER A BUSCAR\t(Otro)Salir" << endl;
                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                cin >> control;
                cin.ignore();
                switch (control)
                {
                case 1:
                    system("cls");
                    break;
                default:
                    cout << "************************************************************************************************************" << endl;
                    cout << "# NINGÚN CAMBIO EFECTUADO # VOLVIENDO AL MENÚ PRINCIPAL..." << endl;
                    cout << "************************************************************************************************************" << endl;
                    system("PAUSE");
                    system("cls");
                    bandera = false;
                    break;
                }
            }
            else
            {
                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                cout << "(1)GUARDAR Y SALIR\t(Otro)Descartar Cambios" << endl;
                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                cin >> control;
                cin.ignore();
                switch (control)
                {
                case 1:
                    // Se reemplaza el archivo original por el archivoAux con los cambios realizados
                    remove(direccion);
                    rename(direccionAux, direccion);
                    cout << "************************************************************************************************************" << endl;
                    cout << "GUARDADO CORRECTAMENTE. VOLVIENDO AL MENÚ PRINCIPAL..." << endl;
                    cout << "************************************************************************************************************" << endl;
                    break;
                default:
                    // Se elimina el archivo auxiliar porque no se realizaron cambios
                    remove(direccionAux);
                    cout << "************************************************************************************************************" << endl;
                    cout << "# NINGÚN CAMBIO EFECTUADO # VOLVIENDO AL MENÚ PRINCIPAL..." << endl;
                    cout << "************************************************************************************************************" << endl;
                    break;
                }
                bandera = false;
                system("PAUSE");
                system("cls");
            }
        }
        else
        {
            bandera = false;
            fclose(archivo);
            system("PAUSE");
            system("cls");
        }
    }
}

Registro *editorDeRegistro(Registro *registroModificar)
{
    int control;
    bool modificar = true;
    while (modificar)
    {
        system("PAUSE");
        system("cls");
        printf("N°;Abastecedora;Descripción\t\t\t;Cantidad;Precio Unitario;Impuesto;Subtotal;Total\t\n");
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        imprimirRegistro(registroModificar);
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "(1)Abastecedora" << endl;
        cout << "(2)Descripción" << endl;
        cout << "(3)Cantidad" << endl;
        cout << "(4)Precio Unitario" << endl;
        cout << "(5)Impuesto" << endl;
        cout << "(Otro)Terminar" << endl;
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Opción>> ";
        cin >> control;
        cin.ignore();
        switch (control)
        {
        case 1:
            for (int vaciar = 0; vaciar < 10; vaciar++)
            {
                registroModificar->abastecedora[vaciar] = ' ';
            }
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cout << "Ingrese el nombre de la nueva abastecedora: " << endl;
            cin.getline(registroModificar->abastecedora, 11);
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cout << "* Se cambió el nombre de la abastecedora correctamente *" << endl;
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            break;
        case 2:
            for (int vaciar = 0; vaciar < 35; vaciar++)
            {
                registroModificar->descripcion[vaciar] = ' ';
            }
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cout << "Ingrese nueva descripcion: " << endl;
            cin.getline(registroModificar->descripcion, 36);
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cout << "* Se cambió la descripción correctamente *" << endl;
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            break;
        case 3:
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            do
            {
                cout << "Ingrese nueva cantidad de productos: ";
                cin >> registroModificar->cantidad;
                if (registroModificar->cantidad > 1000 || registroModificar->cantidad <= 0)
                {
                    cout << "# La cantidad debe estar en un rango entre 1 a 1000. #" << endl;
                    registroModificar->cantidad = -1;
                }
            } while (registroModificar->cantidad == -1);
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cin.ignore();
            registroModificar->subtotal = calcularSubtotal(registroModificar->precioUnitario, registroModificar->iva);
            registroModificar->total = calcularTotal(registroModificar->subtotal, registroModificar->cantidad);
            cout << "* Cantidad cambiada y totales calculados correctamente *" << endl;
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            break;
        case 4:
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            do
            {
                cout << "Ingrese nuevo precio por unidad: ";
                cin >> registroModificar->precioUnitario;
                if (registroModificar->precioUnitario > 1000000)
                {
                    cout << "# Si esto es una prueba déjame advertirte que no puedes alcanzar el millón. Intenta nuevamente, por favor. #" << endl;
                    registroModificar->precioUnitario = -1;
                }
                else if (registroModificar->precioUnitario < 0)
                {
                    cout << "# El precio por unidad debe ser mayor a 0. #" << endl;
                    registroModificar->precioUnitario = -1;
                }
            } while (registroModificar->precioUnitario == -1);
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cin.ignore();
            registroModificar->subtotal = calcularSubtotal(registroModificar->precioUnitario, registroModificar->iva);
            registroModificar->total = calcularTotal(registroModificar->subtotal, registroModificar->cantidad);
            cout << "* Precio unitario cambiado y totales calculados correctamente *" << endl;
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            break;
        case 5:
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            do
            {
                cout << "Ingrese el nuevo (%) del impuesto: ";
                cin >> registroModificar->iva;
                if (registroModificar->iva > 15 || registroModificar->iva < 0)
                {
                    cout << "# El impuesto debe estar en un rango entre 0% a 15%. #" << endl;
                    registroModificar->iva = -1;
                }
            } while (registroModificar->iva == -1);
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cin.ignore();
            registroModificar->subtotal = calcularSubtotal(registroModificar->precioUnitario, registroModificar->iva);
            registroModificar->total = calcularTotal(registroModificar->subtotal, registroModificar->cantidad);
            cout << "* Impuesto cambiado y totales calculados correctamente *" << endl;
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            break;
        default:
            modificar = false;
            break;
        }
    }
    return registroModificar;
}

void eliminarRegistro()
{
    setlocale(LC_ALL, "spanish");
    setlocale(LC_NUMERIC, "english");

    // Variables de control:
    bool bandera = true;
    bool encontrado = false;
    int control;
    int control_registro;

    // PROCESO Y PROCEDIMIENTOS:
    while (bandera)
    {
        // Variables para modificar el registro
        Registro *registroEliminar = ((struct Registro *)malloc(sizeof(struct Registro)));
        int totalRegistros = 0;
        char encabezado[100];
        char palabra[15];
        char descartar;
        for (int vaciar = 0; vaciar < 10; vaciar++)
        {
            registroEliminar->abastecedora[vaciar] = ' ';
        }
        for (int vaciar = 0; vaciar < 15; vaciar++)
        {
            palabra[vaciar] = ' ';
        }
        for (int vaciar = 0; vaciar < 35; vaciar++)
        {
            registroEliminar->descripcion[vaciar] = ' ';
        }
        for (int vaciar = 0; vaciar < 100; vaciar++)
        {
            encabezado[vaciar] = ' ';
        }

        verInventario();

        // Búsqueda del registro seleccionado en el archivo original
        /* Nota: (Eliminar)
         1 Se lee el archivo original y se escribe en el archivo auxiliar iterativamente cada registro.
         2 Cuando se encuentra el registro seleccionado se elimina y se corrigen los índices consecutivos.
         3 Si el usuario desea confirma los cambios o los descarta.
        */
        // Lectura del archivo original antes de iterar
        archivo = fopen(direccion, "r");
        fscanf(archivo, "%d", &totalRegistros);
        fgets(palabra, 15, archivo);
        fgets(encabezado, 100, archivo);

        if (totalRegistros > 0)
        {
            cout << "Seleccione el registro: ";
            cin >> control_registro;

            // Escritura en el archivoAux antes de iterar
            archivoAux = fopen(direccionAux, "w");
            fprintf(archivoAux, "%d %s\n", totalRegistros, "registros.");
            fputs(encabezado, archivoAux);

            while (registroEliminar->numero != totalRegistros)
            {
                // Lectura iterativa de registros del archivo original
                fscanf(archivo, "%d", &registroEliminar->numero);
                fscanf(archivo, "%c", &descartar);
                for (int i = 0; i < 10; i++)
                {
                    fscanf(archivo, "%[^;]c", &registroEliminar->abastecedora[i]);
                }
                fscanf(archivo, "%c", &descartar);
                for (int i = 0; i < 35; i++)
                {
                    fscanf(archivo, "%[^;]c", &registroEliminar->descripcion[i]);
                }
                fscanf(archivo, "%c%d%c%lf%c%d%c%lf%c%lf", &descartar, &registroEliminar->cantidad,
                       &descartar, &registroEliminar->precioUnitario, &descartar, &registroEliminar->iva,
                       &descartar, &registroEliminar->subtotal, &descartar, &registroEliminar->total);

                // En caso de encontrar el registro seleccionado
                if (registroEliminar->numero == control_registro)
                {
                    cout << "------------------------------------------------------------------------------------------------------------" << endl;
                    cout << "REGISTRO SELECCIONADO PARA ELIMINAR" << endl;
                    cout << "------------------------------------------------------------------------------------------------------------" << endl;

                    encontrado = true;
                }
                else if (totalRegistros > 1)
                {
                    // Escritura iterativa de registros en archivoAux
                    if (encontrado == true)
                    {
                        fprintf(archivoAux, "%d;", registroEliminar->numero - 1);
                    }
                    else
                    {
                        fprintf(archivoAux, "%d;", registroEliminar->numero);
                    }

                    for (int k = 0; k < 10; k++)
                    {
                        fprintf(archivoAux, "%c", registroEliminar->abastecedora[k]);
                    }
                    fprintf(archivoAux, ";");
                    for (int k = 0; k < 35; k++)
                    {
                        fprintf(archivoAux, "%c", registroEliminar->descripcion[k]);
                    }
                    fprintf(archivoAux, ";%d;%.2f;%d;%.2f;%.2f\n", registroEliminar->cantidad, registroEliminar->precioUnitario,
                            registroEliminar->iva, registroEliminar->subtotal, registroEliminar->total);
                }
            }

            // Cierre de Archivos
            fclose(archivo);
            fclose(archivoAux);

            // Finalizando
            if (encontrado == false)
            {
                // Se elimina el archivo auxiliar porque no se realizaron cambios
                remove(direccionAux);
                cout << endl;
                cout << "# REGISTRO NO ENCONTRADO #" << endl;
                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                cout << "(1)VOLVER A BUSCAR\t(Otro)Salir" << endl;
                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                cin >> control;
                cin.ignore();
                switch (control)
                {
                case 1:
                    system("cls");
                    break;
                default:
                    cout << "************************************************************************************************************" << endl;
                    cout << "# NINGÚN CAMBIO EFECTUADO # VOLVIENDO AL MENÚ PRINCIPAL..." << endl;
                    cout << "************************************************************************************************************" << endl;
                    system("PAUSE");
                    system("cls");
                    bandera = false;
                    break;
                }
            }
            else
            {
                cout << "(1)ELIMINAR DEFINITIVAMENTE\t(Otro)Descartar Cambios" << endl;
                cout << "------------------------------------------------------------------------------------------------------------" << endl;
                cin >> control;
                cin.ignore();
                switch (control)
                {
                case 1:
                    // Se reemplaza el archivo original por el archivoAux con los cambios realizados
                    remove(direccion);
                    rename(direccionAux, direccion);

                    // Actualización del total de registros
                    archivo = fopen(direccion, "r+");
                    fprintf(archivo, "%d %s\n", totalRegistros - 1, "registros.");
                    fclose(archivo);

                    cout << "************************************************************************************************************" << endl;
                    cout << "GUARDADO CORRECTAMENTE. VOLVIENDO AL MENÚ PRINCIPAL..." << endl;
                    cout << "************************************************************************************************************" << endl;
                    break;
                default:
                    // Se elimina el archivo auxiliar porque no se realizaron cambios
                    remove(direccionAux);
                    cout << "************************************************************************************************************" << endl;
                    cout << "# NINGÚN CAMBIO EFECTUADO # VOLVIENDO AL MENÚ PRINCIPAL..." << endl;
                    cout << "************************************************************************************************************" << endl;
                    break;
                }
                bandera = false;
                system("PAUSE");
                system("cls");
            }
        }
        else
        {
            bandera = false;
            fclose(archivo);
            system("PAUSE");
            system("cls");
        }
    }
}

// OTROS MÉTODOS:
// Imprimir un registro:
void imprimirRegistro(Registro *registroImprimir)
{
    setlocale(LC_ALL, "spanish");
    setlocale(LC_NUMERIC, "english");

    printf("(%d);", registroImprimir->numero);
    for (int i = 0; i < 10; i++)
    {
        printf("%c", registroImprimir->abastecedora[i]);
    }
    printf("\t;");
    for (int i = 0; i < 35; i++)
    {
        printf("%c", registroImprimir->descripcion[i]);
    }
    printf("\t; %d ;%.2f\t; %d ;%.2f\t;%.2f\t\n", registroImprimir->cantidad, registroImprimir->precioUnitario,
           registroImprimir->iva, registroImprimir->subtotal, registroImprimir->total);
}
