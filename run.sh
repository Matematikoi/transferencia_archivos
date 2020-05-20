g++ code/transferir_archivos.cpp -o binaries/transferir.bin
echo "Archivos" > resultados

for prefijo in k m 
do 
	for valor in 1 10 100
	do
		(time  ./binaries/transferir.bin $valor $prefijo ) > out 2> tiempo
		echo -n "$valor$prefijo " >>resultados
		cat tiempo | sed -n 2p | sed 's/\t/ /g' | sed 's/,/./g' | cut -d ' ' -f 2 >> resultados
	done
done


echo "memoria_compartida" >> resultados

g++ code/memoria_compartida.cpp -o binaries/memoria.bin
./binaries/memoria.bin 100 m 
for prefijo in k m 
do 
	for valor in 1 10 100
	do
		(time  ./binaries/memoria.bin $valor $prefijo ) > out 2> tiempo
		echo -n "$valor$prefijo " >>resultados
		cat tiempo | sed -n 2p | sed 's/\t/ /g' | sed 's/,/./g' | cut -d ' ' -f 2 >> resultados
	done
done
