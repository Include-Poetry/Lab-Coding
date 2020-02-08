# Epigenetics mini-tools

Este programa ha sido diseñado como una herramienta de apoyo y de forma temporal para resolver pequeñas necesidades en la creación de *oligos* o *primers*.

El programa se basa en analizar secuencias de nucleótidos de DNA, por lo que se espera que cada cadena se componga de los siguiente posibles caracteres:

- a ó A -> Adenina
- g ó G -> Guanina
- c ó C -> Citosina
- t ó T -> Timina

## Uso de cada función:

### Calcular un TM estándar

Al recibir una secuencia de nucleótidos se calcula el valor de TM utilizando las siguientes conversiones: `A = T = 2` y `C = G = 4`.

La función devuelve el resultado de sumar todas las conversiones de nucleótidos. Este es el algoritmo que se ha usado manualmente al crear *oligos*, aquí se respeta el mismo principio, pero se automatiza y acelera. De esta manera una cadena como `AGTCTAGATAC` regresa un **TM** igual a **30**.

### Generar cadena reverso-complementaria

Dada una secuencia de nucleótidos la función devuelve la cadena reverso complementaria según los apareamientos canónicos de Watson-Crick. Por ejemplo, la cadena `AGTCTAGATAC` se convierte a `GTATCTAGACT`

### Generar cadena reversa

Se devuelve la cadena reversa a la cadena ingresada. Por ejemplo, la cadena `AGTCTAGATAC` se convierte a `CATAGATCTGA`

### Generar cadena complementaria

La función devuelve la cadena complementaria según los apareamientos canónicos de Watson-Crick.Por ejemplo, la cadena `AGTCTAGATAC` se convierte a `TCAGATCTATG`.

### Buscador de oligos

Dada una secuencia de nucleótidos la función devuelve todos los posibles oligos o primers que se pueden obtener de esa entrada en función de los siguientes parámetros:

- **TM**: Número entero positivo, la TM que deberán tener los oligos. Por ejemplo 60
- **Tamaño mínimo**: Tamaño mínimo del oligo, por ejemplo 20
- **Tamaño máximo**: Tamaño máximo del oligo, por ejemplo 25
- **Grado de libertad**: Indica la cantidad máxima de nucleótidos que pueden haber antes de la primera isla CyG del oligo. Una entrada de **1** regresaría un oligo como `XCGXXXXXXXXXXXXXXXX`, donde `X` puede ser cualquier nucleótido.
- **Dirección del oligo**: Indica la dirección del oligo en base a la isla CyG que se busca. Se deberá indicar con un valor numérico el sentido de la búsqueda:
    - 1  -> *Downstream*: Encuentra oligos como `CGXXXXXXXXXXXXXXXXXXXX`
    - 0  -> *Doble*: Encuentra oligos como `CGXXXXXXXXXXXXXXXXXXGC`
    - -1 -> *Upstream*: Encuentra oligos como `XXXXXXXXXXXXXXXXXXXXGC`

Al finalizar puedes guardar los resultados de la búsqueda en un archivo de texto que se genera en la misma carpeta de donde se ejecutó el programa. No se recomiendan cadenas con más de 4000 caracteres en esta versión, por las limitaciones nativas en la entrada por la consola de Windows.

## Cómo citar este programa

Si utilizas este programa exitosamente en tu investigación, por favor cítalo utilizando el formato:

> Velázquez R. (2017). Epigenetics mini-tools (v0.1) [Computer software]. Retrieved from https://github.com/Include-Poetry/Lab-Coding/tree/master/Epigenetics-mini-tools


> Elaborada por mero amor al arte.

> *¿Quieres aprender a desarrollar herramientas como esta?* No hay momento como ahora, comienza a aprender en [Include Poetry división informática](https://www.include-poetry.com/Code/ "Include Poetry"), sitio realizado por el mismo autor de este programa.