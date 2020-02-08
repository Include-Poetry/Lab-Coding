# Activity wheel analyzer

Programa auxiliar en el análisis del conteo de vueltas en ruedas. Especialmente programado para la estudiante de maestría *Teresa Belem Mares Barbosa* desde el 10/06/2017.

## Sobre la función del programa

El programa determina la cantidad de vueltas que un ratón dio en una rueda por cada hora, a partir de una determinada fecha y hora establecidas por el programa de registro. Los datos se convierten del horario civil (normal) a un horario en que las 08:00hrs son la hora 00:00.

## Sobre los archivos de entrada

El programa espera analizar una estructura de carpetas como:

    [Fecha]/RatonX/RuedaY.txt

en donde [Fecha] tiene el formato: DiaMesAño como 31122017 y donde X y Y son números enteros.
Este archivo ejecutable debe estar en la misma carpeta en donde estén las carpetas de fecha.

## Sobre los datos de los archivos

El programa espera leer en los archivos algo como: 

    SEXO:
    EDAD:
    TRMT:
    CEPA:
    1 08:00:00 03-17-2017 100

Las primeras cuatro líneas no tienen ningún espacio (` `) A partir de quinta línea todas siguen el mismo formato donde cada línea tiene cuatro atributos variables, y cada uno es:
`1` -> Un número entero
`08:00:00` -> Hora en reloj de 24 horas a dos dígitos por parte
`03-17-2017` -> Fecha con formato Mes-Día-Año a 2, 2 y 4 dígitos
`100` -> Un número entero

## Cómo citar este programa

Si utilizas este programa exitosamente en tu investigación, por favor cítalo utilizando el formato:

> Velázquez R. (2018). Activity wheel analyzer (v0.2.1) [Computer software]. Retrieved from https://github.com/Include-Poetry/Lab-Coding/tree/master/Activity-wheel-analyzer