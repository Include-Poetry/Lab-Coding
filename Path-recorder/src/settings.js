/*
Code writen by rivel_co (Ricardo Velázquez Contreras)
Original idea by rivel_co
Further reference: github.com/Include-Poetry
*/

$(document).ready(function() {
	var canvas;
	var referenceValue = 0;
	var fileName = 'myPath';
	var finalLength = 0;

	$('#selected-file').change(function(){
		// Seleccionamos el archivo de video a analizar
		var name = document.getElementById('selected-file');
		// Extraemos el nombre del video
    	fileName = name.files.item(0).name;
    	// Actualizamos el nombre del título de la página
    	$('#current-title').html(fileName);
    	// Reemplazamos en el video tag poniendo como fuente la ubicación del archivo (.mp4)
    	// Nótese que la ubicación del video está fina en la carpeta "vids" con formato .mp4
    	$("#vid").html('<source src="vids/' + fileName + '" type="video/mp4"></source>' );
    	// Actualizamos el log agregando que se está analizando un nuevo video
    	$('#meassuresLog').append(" -- " + fileName + " --<br>");
    	$("#meassuresLog").scrollTop($("#meassuresLog")[0].scrollHeight);
	});

	$('#frf-value').change(function(){
		// Velocidad de reproducción del video
		// Le asignamos al video la velocidad que indica en #frf-value
		document.querySelector('video').playbackRate = this.value;
	});

	$('#drawing-color').change(function() {
		// Color del trazo
		canvas.freeDrawingBrush.color = this.value;
	});

	$('#drawing-line-width').change(function() {
		// Ancho del trazo
		canvas.freeDrawingBrush.width = parseInt(this.value, 10) || 1;
	});

	$('#clear-canvas').click(function(event) {
		// Limpiamos el canvas
		canvas.clear();
	});

	$('#measure-length').click(function(event) {
		console.log("  --- Meassure here ---");
		// Inicializamos la variable de valor final
		finalLength = 0;
		// Obtenemos el svg del canvas
		var svg = canvas.toSVG({suppressPreamble: true});
		// Lo metemos en un elemento temporal, para poder recuperar los path
		$('#tempContainer').html(svg);
		// Por cada path tomamos su tamaño y acumulamos
		$('path').each(function(e){
			var myPath = this.getTotalLength();
			finalLength += myPath;
			console.log('RAW length: ' + myPath);
		});
		// Lo registramos en el log para el usuario ya convertido según la referencia
		$('#meassuresLog').append("Total length: " + finalLength/referenceValue + "cm<br>");
		$("#meassuresLog").scrollTop($("#meassuresLog")[0].scrollHeight);
		// Registramos en el log del navegador
		console.log("File: " + fileName);
		console.log("RAW total length: " + finalLength);
		console.log("Converted total length: " + finalLength/referenceValue);
	});

	$('#set-reference').click(function(event) {
		console.log("  --- Reference here ---");
		// El valor de referencia se inicializa siempre a 0 porque es acumulable
		referenceValue = 0;
		// Obtenemos el svg del canvas
		var svg = canvas.toSVG({suppressPreamble: true});
		// Lo metemos en un elemento temporal, para poder recuperar los path
		$('#tempContainer').html(svg);
		// Por cada path tomamos su tamaño y acumulamos
		$('path').each(function(e){
			var myPath = this.getTotalLength();
			referenceValue += myPath;
			console.log('RAW reference: ' + myPath);
		});
		// Realizamos la conversión de la referencia
		var inputRef = $('#reference-line').val();
		referenceValue /= inputRef;
		$('#meassuresLog').append(referenceValue + "u = 1cm<br>");
		$("#meassuresLog").scrollTop($("#meassuresLog")[0].scrollHeight);
		console.log("Converted reference: " + referenceValue);
		// Borramos el svg del temporal y limpiamos el canvas
		$('#tempContainer').html('');
		canvas.clear();
	});
	
    $('#download-canvas').click(function(event){
    	// Generamos el dibujo a guardar
       	var svg = canvas.toSVG({suppressPreamble: true});
		// Lo metemos como link en una etiqueta
		var a      = document.createElement('a');
		a.href     = 'data:image/svg+xml;utf8,' + svg;
		a.download =  fileName + '.svg';
		a.target   = '_blank';
		// Accionamos la descarga y borramos la etiqueta de link
		document.body.appendChild(a); a.click(); document.body.removeChild(a);
    });

	$(function () {
		// Creamos un nuevo elemento para dibujar sobre el canvas
	    canvas = window._canvas = new fabric.Canvas('canvas');
	    // El mismo tamaño que la ventana de video
	    canvas.setHeight(440);
		canvas.setWidth(853);
		// Se configura todo como default
	    canvas.isDrawingMode = true;
	    canvas.freeDrawingBrush.color = "black";
	    canvas.freeDrawingBrush.width = parseInt($('#drawing-line-width').value, 10) || 1;
	    // Listo para dibujar
	    canvas.renderAll();
	    // Cargamos los valores iniciales de trazo y reproducción
	    document.querySelector('video').playbackRate = $('#frf-value').val();
	    canvas.freeDrawingBrush.color = $('#drawing-color').val();
	    canvas.freeDrawingBrush.width = parseInt($('#drawing-line-width').val(), 10) || 1;
	});
});