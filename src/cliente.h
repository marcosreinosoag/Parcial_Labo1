/*
 * cliente.h
 *
 *  Created on: 29 abr. 2021
 *      Author: marco
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_
#define LONG_NOMBRE 80
#define LONG_APELLIDO 80
#define LONG_CUIT 80
#define TRUE 1
#define FALSE 0


typedef struct{
	char nombre [LONG_NOMBRE];
	char apellido[LONG_NOMBRE];
	char cuit [LONG_CUIT];
	int isEmpty;
	int idCliente;
}Cliente;

int cliente_init(Cliente * pArrays, int limiteCliente);
int cliente_alta(Cliente *arrayClientes,int limiteArrayClientes);
int cliente_buscarLibreRef(Cliente pArrayCliente[],int limiteCliente, int *pindex);
int cliente_modificar (Cliente * pArrays, int limiteCliente);
int cliente_buscarIndicePorIdRef (Cliente * pArrays, int limiteCliente,int idBuscar, int * pIndice);
int cliente_imprimir (Cliente * pArrays , int limiteCliente);
int cliente_imprimirClientePorID (Cliente * pArrayCliente , int limitCliente, int id,char*mensaje);
int cliente_buscarIndicePorId (Cliente * pArrays, int limiteCliente,int idBuscar);


#endif /* CLIENTE_H_ */
