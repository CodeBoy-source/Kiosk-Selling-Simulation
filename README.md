# Simulación de ventas en quiosco.
Un establecimiento (por ejemplo un quiosco de periódicos) se abastece diariamente de un
cierto producto, y necesita decidir cuántas unidades de ese producto pedir cada día. Este valor,
s, se fija en un contrato a largo plazo con el proveedor (y una vez fijado no puede cambiarse).
El establecimiento obtiene una ganancia de x euros por cada unidad vendida, con un costo de
y euros por cada unidad comprada. La demanda D (o sea, el número de unidades del producto
que se solicitan cada día) varía diariamente, pero se ha estudiado que se ajusta a una determinada
distribución de probabilidad P (D = d), que se detallará después. Se desea encontrar el
valor óptimo de s, donde el criterio de optimalidad es maximizar la ganancia esperada.

Se estudia el comportamiento del establecimiento para diversas funciones
de demanda D. Luego se estudio que pasaría si introducimos una política
de devolución de ítems no vendidos.

Por último, se utiliza métodos y mejoras para generadores de datos e las
implicaciones que existe con el uso de cada uno de ellos.

Existen 4 archivos principales:
1. `main` que ejecuta la simulación trivial.
2. `modf` que ejecuta la simulación con la política de devolución.
3. `gen` que calcula la amplitud de cada generador explicado en el pdf.
4. `perf` que estudia las diferentes mejores propuestas.
