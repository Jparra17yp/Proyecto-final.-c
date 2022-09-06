#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

int menu(); //Función correspondiente al menú principal

int menu_productos (int user); /*Función que ejecuta un sub-menú 
                                  dedicado al apartado de productos*/

void continuar();//Función que pausa la ejecución hasta que el usuario indique
void creaStock();//Función que genera un archivo con el stock de productos
void imprimeStock();//Función que imprime el stock de productos
void modificarPrecio();//Función que permite modificar el precio de un producto
void modificarCantidad();//Función que permite modificar la cantidad de existencais de un producto
void modificarNombre();//Función que permite modificar el nombre de un producto
void modificarCodigo();//Función que permite modificar el codigo de un producto
void vaciaStoctk();//Función que elimina el archivo correspondiente al Stock
void menuModificar();//Función que invoca un menu el cual se encarga de todas las funciones modificar

typedef struct datosUsuario //struct dedicado a los datos de cada usuario
{
  char nombre[20], apellido[20], tipoDeCuenta[10];
  int cedula, numeroDeCuenta;
} d_usuario;
typedef struct datosProducto //struct dedicado a los datos de cada productos
{
  char nombre[100];
  int unidades, codigo;
  float precio;
} d_producto;

int main () {//Función principal
  int elect, op1;
  do
  {
    elect = menu_productos(1); //Llamada al sub-menú de productos
  switch (elect)
  {
  case 1:
    imprimeStock(); 
    break;
  
  case 2:
    creaStock();
    break;

  case 3:
    menuModificar();
    break;

  case 4:
    vaciaStock();
    break;
  
  case 5:
    break;

  default:
    printf("Opcion no existente");//Mensaje en caso de ingresar una respuesta no esperada
    break;
  }
  } while (elect != 5);/*Un bucle que no finalizará hasta 
                        que el usuario indique, por lo que 
                        el programa mostrará el menú constantemente*/
  
  return 0;
}

int menu_productos(int user)
{
  system("cls"); //Limpiar pantalla
  int election; 

  if(user == 1)
  {
    printf("\nBienvenido al sub-menu de productos para usuarios");
    printf("\nDigite segun sus necesidades:");
    printf("\n____________________________________________________");
    printf("\n1 - Si desea revisar el stock de productos");
    printf("\n2 - Si desea anadir productos al stock");
    printf("\n3 - Si desea modificar productos del stock");
    printf("\n4 - Si desea vaciar el stock");
    printf("\n5 - Si desea salir del sistema\n");
    scanf("%d", &election); //Guarda la elección del usuario
  }
  else if (user == 0)
  {
    printf("\nBienvenido al sub-menu de productos para clientes");
    printf("\nDigite segun sus necesidades:");
    printf("\n____________________________________________________");
    printf("\n1 - Si desea anadir productos al carro de compra");
    printf("\n2 - Si desea retirar producto del carro de compra");
    printf("\n3 - Si desea revisar su carro de compra");
    printf("\n4 - Si desea finalizar su compra");
    printf("\n5 - Si desea cancelar su compra\n");
    scanf("%d", &election); //Guarda la elección del usuario
  }
  else
  {
    printf("Ha ocurrido un error, no se le reconoce en el sistema");/*Mensaje de error en caso 
                                                                      de que la variable no coincida
                                                                      por lo cual no se le reconozca 
                                                                      ni como usuario o admin*/
  }
  return election;//Devuelve la elección
}
void continuar()
{
  printf("\n\n");/*Un mensaje para indicar a el usuario 
                                                          qué hacer cuando se pause el programa*/
  system("pause");//Pausa el programa
}
void creaStock()
{
  system("cls");//Limpia pantalla

  int n = 0; 
  FILE *archivo; //Puntero para los archivos .db
  archivo=fopen("Stock.db", "ab"); /*Busca un archivo llamado Stock, debido a los atributos 
                                    en caso de no existir lo crea y en caso de que sí, todo 
                                    lo que se escriba se añade al archivo existente en binario*/

  d_producto control;//Struct para el control del stock

  if (archivo == NULL)
  {
    printf("\nError al crear stock");//Mensaje de error en caso de no poder abrir el archivo
  }
  else
  {
    do
    {
        puts("\nDigite el nombre del producto: ");
        fflush(stdin);
        gets(control.nombre);
        printf("\nDigite el codigo del producto:");
        scanf("%d", &control.codigo);
        printf("\nDigite las existencias del producto: ");
        scanf("%d", &control.unidades);
        printf("\nDigite el precio del producto: ");
        scanf("%f", &control.precio);
        
        printf("\n\nDigite segun corresponda: "); /*Pequeño sub-menu que permite al usuario indicar el número 
                                                    de veces que va a añadir un producto*/
        printf("\n1- Si desea agregar otro producto ");
        printf("\n2 - Si desea volver al menu anterior \n");
        scanf("%d", &n);

        if (n!= 1 && n!=2)//Condicional en caso de que el usuario digite una respuesta no esperada
        {
          printf("\n\nHa ocurrido un error"
          "\nPor favor digite un el valor correspondiente a las opciones del menu\n\n");
          continuar();
        }
        
        
        fwrite(&control, sizeof(d_producto), 1, archivo);//Escribe el input del usuario en Stock
    } while(n!=2);

  }
  fclose(archivo);//Cierra archivo
}
void imprimeStock()
{

    system("cls");
    int j = 0, itera = 0;
    FILE *archivo;

    archivo = fopen("Stock.db", "rb");//Abre el archivo Stock unicamente para lectura de datos en binario
    d_producto imp;
    
    if (archivo == NULL)
    {
      printf("Ha ocurrido un error en la apertura del stock");//Mensaje de error en caso de no existir el archivo
    }
    else
    {
      fread(&imp, sizeof(d_producto), 1, archivo);//Lee archivo
      
        while(!feof(archivo)&&!ferror(archivo))/*Un bucle que no va a terminar hasta que se encuentre 
                                                con el final del archivo o algún tipo de error*/
        {
          printf("\nProducto: %s", imp.nombre);
          printf("\nCodigo: %d", imp.codigo);
          printf("\nExistencias: %d", imp.unidades);
          printf("\nPrecio: %.2f", imp.precio);
          printf("\n_________________________________");
          fread(&imp, sizeof(d_producto), 1, archivo);
        }
      fclose(archivo);//Cierra el archivo
    }
    continuar();
}
void modificarPrecio() 
{
  system("cls");
  int producto=0, existe=0;//Variable inicializadas en 0 para evitar problemas
  char a;
  FILE *archivo;
  d_producto modifx;
  archivo=fopen("Stock.db", "r+b");//Apertura que permite leer como escribir, en caso de no exister crea el archivo
  if(archivo==NULL)
  {
    printf("\nHa ocurrido un error al abrir el archivo Stock.db");//Mensaje de error
  }
  else
  {
    printf("\nCual es el codigo del producto a modificar?");//Mensaje para indicar al usuario que escribir
    scanf("%d", &producto);
    fread(&modifx, sizeof(d_producto), 1, archivo);//lectura del archivo en el struck anteriormente creado
      while(!feof(archivo))
      {
        if(producto==modifx.codigo)//Condicional en caso de que el codigo coincida con algun producto del stock
        {
          printf("\nProducto: %s", modifx.nombre);
          printf("\nCodigo: %d", modifx.codigo);
          printf("\nExistencias: %d", modifx.unidades);
          printf("\nPrecio: %.2f", modifx.precio);
          printf("\n_________________________________");
          printf("\nIngrese el nuevo precio del producto\n");
          scanf("%f", &modifx.precio); 
          int n = ftell(archivo) - sizeof(d_producto);//Obtengo la posicion en la que inicia todo el stuck correspondiente al codigo del producto
          fseek(archivo, n, SEEK_SET);//Me posiciono en el inicio del struck
          fwrite(&modifx, sizeof(d_producto), 1, archivo);//Lo reescribo
          existe = 1;//Altero una variable para evitar un mensaje de error
          break;
        }
        fread(&modifx, sizeof(d_producto), 1, archivo);//en caso de no coincidir el primer codigo, continue hasta que llegue al final del archivo
      }
    if(existe==0)//Condicional con mensaje de error
    {
      printf("\nNo se encontro ningun producto que conincida con el codigo ingresado");//Mensaje de error
    }  
    fclose(archivo);
    continuar();
  }
}
void modificarNombre()
{
  system("cls");
  int  codigo, existe=0;
  char a, producto[100];
  FILE *archivo;
  d_producto modifx;
  archivo=fopen("Stock.db", "r+b");
  if(archivo==NULL)
  {
    printf("\nHa ocurrido un error al abrir el archivo Stock.db");
  }
  else
  {
    printf("\nCual es el codigo del producto a modificar?");
    scanf("%d", &codigo);

    fread(&modifx, sizeof(d_producto), 1, archivo);
      while(!feof(archivo) && !ferror(archivo))
      {
        if(codigo==modifx.codigo)
        {
          printf("\nProducto: %s", modifx.nombre);
          printf("\nCodigo: %d", modifx.codigo);
          printf("\nExistencias: %d", modifx.unidades);
          printf("\nPrecio: %.2f", modifx.precio);
          printf("\n_________________________________");
          printf("\nIngres el el nuevo nombre del producto\n");
          fflush(stdin);//Limpia el buffer para evitar problemas con el gets
          gets(modifx.nombre);
          int n = ftell(archivo) - sizeof(d_producto);
          fseek(archivo, n, SEEK_SET);
          fwrite(&modifx, sizeof(d_producto), 1, archivo);
          existe=1;
          break; 
        }
        fread(&modifx, sizeof(d_producto), 1, archivo);
      }
    if(existe==0)
    {
      printf("\nNo se encontro ningun producto que conincida con el codigo ingresado");    
    }  
    fclose(archivo);
    continuar();
  }
  
}
void modificarCantidad()
{
  system("cls");
  int producto, existe = 0;
  char a;
  FILE *archivo;
  d_producto modifx;
  archivo=fopen("Stock.db", "r+b");
  if(archivo==NULL)
  {
    printf("\nHa ocurrido un error al abrir el archivo Stock.db");
  }
  else
  {
    printf("\nCual es el codigo del producto a modificar?");
    scanf("%d", &producto);
    fread(&modifx, sizeof(d_producto), 1, archivo);
      while(!feof(archivo) && !ferror(archivo))
      {
        if(producto==modifx.codigo)
        {
          printf("\nProducto: %s", modifx.nombre);
          printf("\nCodigo: %d", modifx.codigo);
          printf("\nExistencias: %d", modifx.unidades);
          printf("\nPrecio: %.2f", modifx.precio);
          printf("\n_________________________________");
          printf("\nIngrese la cantidad de existencias del producto?\n");
          scanf("%d", &producto); 
          modifx.unidades=producto;
          int n = ftell(archivo) - sizeof(d_producto);
          fseek(archivo, n, SEEK_SET);
          fwrite(&modifx, sizeof(d_producto), 1, archivo);
          printf("\nSe ha modificado con exito el producto."); 
          existe=1;
          break;     
        }
        fread(&modifx, sizeof(d_producto), 1, archivo);
      }
    if(existe==0)
    {
      printf("\nNo se encontro ningun producto que conincida con el codigo ingresado");   
    }  
    fclose(archivo);
    continuar();
  }
}
void modificarCodigo()
{
  system("cls");
  int producto=0, existe=0;
  char a;
  FILE *archivo;
  d_producto modifx;
  archivo=fopen("Stock.db", "r+b");
  if(archivo==NULL)
  {
    printf("\nHa ocurrido un error al abrir el archivo Stock.db");
  }
  else
  {
    printf("\nCual es el codigo del producto a modificar?");
    scanf("%d", &producto);
    fread(&modifx, sizeof(d_producto), 1, archivo);
      while(!feof(archivo) && !ferror(archivo))
      {
        if(producto==modifx.codigo)
        {
          printf("\nProducto: %s", modifx.nombre);
          printf("\nCodigo: %d", modifx.codigo);
          printf("\nExistencias: %d", modifx.unidades);
          printf("\nPrecio: %.2f", modifx.precio);
          printf("\n_________________________________");
          printf("\nIngrese el nuevo codigo del producto\n");
          scanf("%d", &producto); 
          modifx.codigo=producto;
          int n = ftell(archivo) - sizeof(d_producto);
          fseek(archivo, n, SEEK_SET);
          fwrite(&modifx, sizeof(d_producto), 1, archivo);
          printf("\nSe ha modificado con éxito el producto.");  
          existe=1; 
          break;     
        }
        fread(&modifx, sizeof(d_producto), 1, archivo);
      }
      if(existe==0)
        {
          printf("\nNo se encontro ningun producto que conincida con el codigo ingresado");    
        }  
    fclose(archivo);
    continuar();
  }
}

void vaciaStock()
{
  system("cls");
  
  if (remove("Stock.db") == 0)//Elimina el archivo "Stock.db"
  {
    printf("\nSu Stock ha sido reestablecido");//Mensaje en caso de operacion exitosa
  }
  else
  {
    printf("\nNo se ha podido vaciar el stock");//Mensaje de error
  }
  continuar();
}

void menuModificar()
{
  system("cls");
  int op1;
   do
  {
    system("cls");
    printf("\nBienvenido al sub-menu de modificar productos");
    printf("\nDigite segun sus necesidades:");
    printf("\n____________________________________________________________________");
    printf("\n1 - Si desea modificar el precio de un producto");
    printf("\n2 - Si desea modificar el nombre de un producto");
    printf("\n3 - Si desea modificar la cantidad de existencias de un producto");
    printf("\n4 - Si desea modificar el codigo de un producto");
    printf("\n5 - Si desea volver al submenu de productos\n");
    scanf("%d", &op1);
    switch (op1)
    {
    case 1:
      modificarPrecio();
      break;
    
    case 2:
      modificarNombre();
      break;

    case 3:
      modificarCantidad();
      break;

    case 4:
      modificarCodigo();
      break;

    case 5:
      break;
    
    default:
      printf("\nDigite un valor correspondiente a las opciones brindadas");//Mensaje en caso de error con el input
      break;
    }
  } while (op1 != 5);
}
#include <stdio.h>

#include <stdlib.h>

#include <string.h>





#define MAX 80

#define ARCHIVO_USUARIOS "usuarios.dat"

#define TECLA_ENTER 13

#define TECLA_BACKSPACE 8

#define LONGITUD 5

#define MAX_INTENTOS 3



/* Estructura de cuentas de usuario */

struct usuario {

char nombre[MAX];

char password[MAX];

};



typedef struct usuario Usuario;



/* Funciones de men� */

void menuInicial();

void menuListarUsuarios();

void menuRegistrarUsuario();

void menuIniciarSesion();

void menuSistema();



/* Funciones que manipulan el archivo de usuarios */

char insertarUsuario(Usuario usuario);

char existeUsuario(char nombreUsuario[], Usuario *usuario);

Usuario *obtenerUsuarios(int *);

char logear(char nombreUsuario[], char password[]);



int leerLinea(char *cad, int n);

void leerClave(char *password);



char linea[MAX];

int main() {

menuInicial();

return 0;

}



void menuInicial() {

char repite = 1;

int opcion = -1;



do {

system("cls");

printf("\n\t\t\tMENU INICIAL\n");

printf("\t\t\t============\n");

printf("\n\t\t[1]. Ver usuarios registrados\n");

printf("\t\t[2]. Registrar usuario nuevo\n");

printf("\t\t[3]. Ingresar al sistema\n");

printf("\t\t[0]. Salir\n");

printf("\n\t\tIngrese su opcion: [ ]\b\b");

leerLinea(linea, MAX);

sscanf(linea, "%d", &opcion);



switch (opcion) {

case 1:

menuListarUsuarios();

break;



case 2:

menuRegistrarUsuario();

break;



case 3:

menuIniciarSesion();

break;




 


case 0:

repite = 0;

break;

}



} while (repite == 1);

}



void menuRegistrarUsuario() {

Usuario usuario;

char nombreUsuario[MAX];

char respuesta[MAX];

char repite = 1;



do {

system("cls");

printf("\n\t\t\tREGISTRAR USUARIO\n");

printf("\t\t\t=================\n");

printf("\n\tIngrese nombre de usuario: ");

leerLinea(linea, MAX);

sscanf(linea, "%s", nombreUsuario);



/* Se verifica que el nombre de usuario no exista */

if (!existeUsuario(nombreUsuario, &usuario)) {

strcpy(usuario.nombre, nombreUsuario);



printf("\tIngrese la clave: ");

leerLinea(usuario.password, MAX);



/* Se inserta el usuario en el archivo de usuarios */

if (insertarUsuario(usuario)) {

printf("\n\tEl usuario fue registrado satisfactoriamente!\n");



} else {

printf("\n\tOcurrio un error al registrar el usuario\n");

printf("\nInt�ntelo mas tarde\n");

}

} else {

printf("\n\tEl usuario \"%s\" ya ha sido registrado previamente\n", usuario.nombre);

printf("\tNo puede registrar dos usuarios con el mismo nombre de usuario.\n");

}



printf("\n\tDesea seguir registrando usuarios? [S/N]: ");

leerLinea(respuesta, MAX);



if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {

repite = 0;

}



} while (repite == 1);

}



void menuListarUsuarios() {

int numeroUsuarios = 0;

Usuario *usuarios;

int i;



system("cls");

usuarios = obtenerUsuarios(&numeroUsuarios); /* Retorna un vector din�mico de usuarios */



if (numeroUsuarios == 0) {

printf("\n\tNo existe ningun usuario registrado!\n");



} else {

printf("\n\t\t ==> LISTADO DE USUARIOS REGISTRADOS <==\n");

printf(" ------------------------------------------------------------------------------\n");

printf("%10s%25s%25s\n", "#", "NOMBRE", "PASSWORD");

printf(" ------------------------------------------------------------------------------\n");



/* Se recorre el vector din�mico de productos */

for (i = 0; i < numeroUsuarios; i++) {

printf("%10d%25s%25s\n", (i + 1), usuarios[i].nombre, usuarios[i].password);

}

printf(" ------------------------------------------------------------------------------\n");

}



// Se libera la memoria asignada al vector din�mico

free(usuarios);

usuarios = NULL;

getchar();

}



void menuIniciarSesion() {

char nombreUsuario[MAX];

char password[MAX];

int intento = 0;

int loginExitoso = 0;



do {

system("cls");

printf("\n\t\t\tINGRESAR AL SISTEMA\n");

printf("\t\t\t===================\n");



printf("\n\t\tUSUARIO: ");

leerLinea(linea, MAX);

sscanf(linea, "%s", nombreUsuario);



printf("\t\tCLAVE: ");

leerClave(password);



if (logear(nombreUsuario, password)) {

loginExitoso = 1;

} else {

printf("\n\n\t\tUsuario y/o password incorrectos");

intento++;

getchar();

}

} while (intento < MAX_INTENTOS && loginExitoso == 0);



if (loginExitoso == 1) {

menuSistema();



} else {

printf("\n\tHa sobrepasado el numero maximo de intentos permitidos\n");

getchar();

}

}



void menuSistema() {

system("cls");

printf("\n ======================================================================\n");

printf("\t\t\t BIENVENIDO AL SISTEMA\n");

printf("\t\t Aqui va la descripcion de tu sistema\n");

printf("\t\t Copyright 2021 | Algoritmos y Algo mas\n");

printf(" ======================================================================\n");



printf("\n\t\tAqui va todo el contenido de tu sistema ;)");

/** 

* Escribe aqu� el resto 

* de todo tu c�digo

* ....

* ....

* ....

* ....

* ....

*/



getchar();

}



/* Retorna 1 si se registr� el usuario en el archivo correctamente */

char insertarUsuario(Usuario usuario) {

FILE *archivo;

char insercion = 0;



/* Abre el archivo en modo de a�adidura, para agregar datos al final. Si no existe es creado*/

archivo = fopen(ARCHIVO_USUARIOS, "ab");



if (archivo == NULL) {

insercion = 0;



} else {

/* Registra el struct usuario en el archivo */

fwrite(&usuario, sizeof(usuario), 1, archivo);

insercion = 1;



/* Cierra el archivo */

fclose(archivo);

}



return insercion;

}



/* Retorna 1 si existe el nombre de usuario. Retorna el usuario buscado si existe */

char existeUsuario(char nombreUsuario[], Usuario* usuario) {

FILE *archivo;

char existe;



/* Abre el archivo en modo de lectura */

archivo = fopen(ARCHIVO_USUARIOS, "rb");



if (archivo == NULL) {

existe = 0;



} else {

existe = 0;



/* Lee secuencialmente del archivo de usuarios */

fread(&(*usuario), sizeof(*usuario), 1, archivo);

while (!feof(archivo)) {

if (strcmp((*usuario).nombre, nombreUsuario) == 0) {

/* Encuentra un usuario del archivo con el nombre de usuario buscado */

existe = 1;

break;

}



fread(&(*usuario), sizeof(*usuario), 1, archivo);

}



/* Cierra el archivo*/

fclose(archivo);

}



return existe;

}



Usuario *obtenerUsuarios(int *n) {

FILE *archivo;

Usuario usuario;

Usuario *usuarios; /* Vector din�mico de usuarios */

int i;



/* Abre el archivo en modo lectura */

archivo = fopen(ARCHIVO_USUARIOS, "rb");



if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */

*n = 0; /* No se pudo abrir. Se considera n = 0 */

usuarios = NULL;



} else {



fseek(archivo, 0, SEEK_END); /* Posiciona el cursor al final del archivo */

*n = ftell(archivo) / sizeof(Usuario); /* # de usuarios almacenados en el archivo. (# de registros) */

usuarios = (Usuario *)malloc((*n) * sizeof(Usuario)); /* Se asigna memoria para todos los usuarios almacenados en el archivo */



/* Se recorre el archivo secuencialmente */

fseek(archivo, 0, SEEK_SET); /* Posiciona el cursor al principio del archivo */

fread(&usuario, sizeof(usuario), 1, archivo);

i = 0;

while (!feof(archivo)) {

usuarios[i++] = usuario;

fread(&usuario, sizeof(usuario), 1, archivo);

}



/* Cierra el archivo */

fclose(archivo);

}



return usuarios;

}



/* Retorna 1 o 0 si el usuario y password son correctos para un usuario en particular */

char logear(char nombreUsuario[], char password[]) {

FILE *archivo;

char logeoExitoso;

Usuario usuario;



/* Abre el archivo en modo de lectura */

archivo = fopen(ARCHIVO_USUARIOS, "rb");



if (archivo == NULL) {

logeoExitoso = 0;



} else {

logeoExitoso = 0;



/* Lee secuencialmente del archivo de usuarios */

fread(&usuario, sizeof(usuario), 1, archivo);

while (!feof(archivo)) {

if (strcmp(usuario.nombre, nombreUsuario) == 0 && strcmp(usuario.password, password) == 0) {

/* Encuentra un usuario del archivo con el nombre de usuario y password buscado */

logeoExitoso = 1;

break;

}



fread(&usuario, sizeof(usuario), 1, archivo);

}



/* Cierra el archivo*/

fclose(archivo);

}



return logeoExitoso;

}



int leerLinea(char *cad, int n)

{

int i, c;



/* 1 COMPROBACI�N DE DATOS INICIALES EN EL BUFFER */

c = getchar();

if (c == EOF) {

cad[0] = '\0';

return 0;

}



if (c == '\n') {

i = 0;

} else {

cad[0] = c;

i = 1;

}



/* 2. LECTURA DE LA CADENA */

for (; i < n - 1 && (c = getchar()) != EOF && c != '\n'; i++) {

cad[i] = c;

}

cad[i] = '\0';



/*3. LIMPIEZA DEL BUFFER */ 

if (c != '\n' && c != EOF) /* es un caracter */

while ((c = getchar()) != '\n' && c != EOF);



return 1;

}



void leerClave(char *password) {

char caracter;

int i = 0;



while (caracter = getch()) {

if (caracter == TECLA_ENTER) {

password[i] = '\0';

break;



break;



} else if (caracter == TECLA_BACKSPACE) {

if (i > 0) {

i--;

printf("\b \b");

}



} else {

if (i < MAX) {

printf("*");

password[i] = caracter;

i++;

}

}

}

}  























