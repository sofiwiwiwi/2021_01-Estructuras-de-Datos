Instrucciónes de Compilación

Para correr la tarea se debe correr el siguente comando en la carpeta Tarea3:
    g++ main.cpp -Wall -o <nombre-ejecutable>

Y para la posterior ejecución se debe, en la misma carpeta utilizar el siguiente comando:
    ./<nombre-ejecutable>

El resultado esperado se encontrará en el archivo boletas.txt en la carpeta Tarea3.

Para mayor claridad acerca de cómo funciona el macro de la tarea, continuar leyendo.


Explicación:

El código se divide de la siguiente manera:
    * main
    * productHashTable
        - hpp
        - cpp
    * saleHashTable
        - hpp
        - cpp
    * productCounter
        - hpp
        - cpp

productHashTable se encarga de almacenar todos los productos, saleHashTable se encarga de almacenar las ofertas.

En productCounter es donde ocurre la magia. Al existir productos equivalentes, llamaremos a estos "grupos", productCounter es una tabla de Hash que se encarga de almacenar un grupo y la cantidad de productos del grupo que se han comprado.
Al almacenarlos, la key es el código de algún producto del grupo (el primero que se compra), y el value es la cantidad de productos de este grupo que se han comprado.
Para insertar un producto en esta tabla se inserta la oferta a la que pertenece este producto ya que esta es la que contiene sus productos equivalentes. Si el producto, o alguno de los productos equivalentes es una key válida entonces al value de esa key se le sumará uno, y si ninguno de estos está en la tabla haremos un nuevo grupo y la cantidad será 1.
Finalmente, para calcular el descuento total que debe ser aplicado vamos por cada uno de los grupos (recorrer la tabla de hashing), ver la cantidad de productos dentro del grupo y compararlo con la cantidad de productos necesarios para que se le descuente X al valor total.
