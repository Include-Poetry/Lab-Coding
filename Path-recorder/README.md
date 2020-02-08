# Path recorder

Este programa está diseñado con la intención de que sea una forma computacional y manualmente sencilla de cuantificar y dibujar de forma confiable la distancia que se mueve un objetivo en un video estático. Originalmente pensado para cuantificar la distancia que recorre una rata en pruebas de conducta como [Open Field Maze](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC4354627/ "OFT en NCBI") y [Three Chamber Sociability test](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3197404/ "TCS en NCBI") pero se puede utilizar en prácticamente cualquier video. También se genera un dibujo vectorial del recorrido del animal en el espacio donde se encuentra.

## Cómo utilizarlo

Para realizar el análisis de un video, hay que tener en cuenta que es necesario que una persona esté viendo y siguiendo al animal con el mouse, este programa **no** realiza un análisis automático. Lo que hay que hacer es ver el video y seguir al animal con el apuntador, al finalizar se puede obtener la distancia recorrida y el dibujo del camino correspondiente.

Es necesario que el video esté en formato `.mp4` web compatible, para que el navegador web pueda reproducirlo. El video a analizar debe estar dentro de la carpeta `vids` El siguiente punto es que se necesita conocer el tamaño exacto y real de un elemento en el video, ya sea un lado de la caja donde está el animal o alguna marca dedicada para este propósito. El objetivo es darle al programa una equivalencia del tamaño de un objeto que sí conocemos para que en base a esta referencia se realice el factor de conversión para la distancia total recorrida.

Los pasos para comenzar el análisis se pueden ver como:

0. Ejecutar la herramienta abriendo el archivo `index.html` en Mozilla Firefox
1. Abrir el video en la opción "Examinar..." del lado izquierdo de la pantalla
2. Ubicar el video que se analizará en la carpeta `vids`
3. Cuando el video cargue en el centro de la pantalla entonces se procede a realizar una línea con el mouse que sea del tamaño de la referencia que hemos designado, sea un lado de la caja o una marca particular.
4. En el centro de la pantalla y en la parte inferior, se debe indicar en el recuadro `Equivalence (cm)` el tamaño en centímetros de la referencia, la misma que acabamos de marcar en la pantalla.
5. Ahora se presiona el botón `Set reference`. En el lado inferior derecho de la pantalla en el recuadro de `Log` debe aparecer un factor de conversión debajo del nombre del video que vamos a procesar. La línea de referencia que hemos puesto antes debe de borrarse.
6. Ahora podemos reproducir el video y cuando el animal se ubique en el punto de partida comenzar a seguirlo con el mouse. Es importante mencionar que la línea se continúa dibujando mientras se mantenga el click presionado. Se puede soltar el click y reanudar, esto no altera el resultado final.
7. Cuando se termine de hacer el seguimiento se debe presionar el botón `Measure`. En el `Log` aparecerá la distancia total recorrida.
8. Para salvar el dibujo vectorial del recorrido hay que presionar el botón `Save path` que está del lado izquierdo de la pantalla. El archivo se descargará donde el usuario indique, como cualquier otro archivo que se descargue.

Es importante mencionar que la referencia siempre se debe marcar al inicio de cada video. El programa tiene algunas opciones para facilitar el registro de los videos, por ejemplo se puede modificar la velocidad de reproducción, para esto hay que utilizar el cuadro `Playblack speed (factor)`, lo que se ingresa aquí es el factor de velocidad, el `1` es la reproducción normal, si se ingresa un `2` el video irá al doble de la velocidad, un `0.5` irá a la mitad de la velocidad.

También se puede modificar el color y grosor de la linea. Desde luego que el grosor de la línea no cambia la longitud de la misma ni afecta el resultado. En un solo dibujo se pueden realizar tantas líneas de diferentes colores como se desee. 

El botón de `clear` borra todo el dibujo realizado.

## Cómo funciona el programa

El programa lo que hace es utilizar la librería de [Fabric.js](https://github.com/fabricjs/fabric.js/tree/master "Fabric.js | Github") para realizar el dibujo y poder cambiar cosas como el color de la línea, el grosor y la exportación de la imagen vectorial. El programa genera el dibujo vectorial y con la propiedad de los objetos tipo `path` llamada `.getTotalLength()` se obtiene el tamaño de cada línea dibujada. De ahí en fuera solamente es un proceso de conversión del tamaño de referencia con el tamaño total del recorrido.

Este programa no tiene *gran ciencia*, sin embargo es bastante eficiente y facilita horas de trabajo y mucho dinero que podría gastarse en programas especializados y automáticos. Pero otra vez, los resultados son bastante buenos y sencillos.

Modificar la velocidad de reproducción, cargar el video, descargar la imagen y todo eso es realizado gracias a las herramientas comunes de JavaScript. El diseño es un simple CSS3 y está montado utilizando HTML5 como esqueleto.

## Consideraciones para esta versión

Esta versión es apta para utilizarse y realizar registros, sin embargo es poco versátil en cuanto a los navegadores en los que se puede usar, principalmente por la forma en la que se disponen los botones de reproducción del video en diferentes navegadores. Como mencionaba, las mediciones realizadas son buenas y se pueden utilizar pero hay *poca compatibilidad* y el diseño también es un tanto burdo todavía, por esto la herramienta actualmente está en calidad de *beta*.

Se debe correr esta herramienta en Mozilla Firefox. Se ha probado en Firefox Quantum 67.04 (32bits) y funciona sin problemas. No olvidar que los videos tienen que estar dentro de la carpeta `vids` y que el archivo `index.html` debe ir siempre junto a la carpeta `src`.

## Recomendaciones

Para una buena medición es recomendable mantener un *error* constante, realizar el trazo de la referencia no necesariamente tiene que ser perfecto pero sí lo más recto posible. Todo el recorrido se somete al mismo error humano si lo realiza la misma persona.

También recomiendo que antes de guardar el dibujo vectorial y después de obtener la distancia total, se marque con algún color único y distintivo la referencia, para que si después ese dibujo se procesa de otra forma sea sencillo llevar la referencia consigo. 

## Cómo citar este programa

Si utilizas este programa exitosamente en tu investigación, por favor cítalo utilizando el formato:

> Velázquez R. (2019). Path recorder (v0.1-alpha) [Computer software]. Retrieved from https://github.com/Include-Poetry/Lab-Coding/tree/master/Path-recorder

## Créditos

Esta herramienta y su idea principal tiene como autor a Ricardo Velázquez Contreras y fue desarrollado para el **Laboratorio de Neurobiología de la Conducta y Cognición** de la **Facultad de Medicina, UASLP**.

> Made with <3 by rivel_co

***Más sobre el desarrollador en:*** [Github](https://github.com/Include-Poetry/ "rivel_co").