/*
 * compra.h
 *
 *  Created on: 29 abr. 2021
 *      Author: marco
 */

#ifndef COMPRA_H_
#define COMPRA_H_
#define QTY_CLIENTES 100
#define QTY_COMPRA 1000
#define COBRADO 1
#define PAGO_PENDIENTE 0
#define QTY_CARACTERESCOLOR 40
#define QTY_CARACTERESENTREGA 32
#include "cliente.h"

typedef struct{
	int idCompra;
	int idCliente;
	int cantidadBarbijos;
	char textoDireccionEntrega [QTY_CARACTERESENTREGA];
	char color [QTY_CARACTERESCOLOR];
	int ImporteTotal;
	int estadoCompra;
	int isEmpty;
}Compra;

int compra_alta(Compra *arrayCompra,int limiteCompra, Cliente *pArrayClientes,int limiteCliente);
int compra_init(Compra * pArrayCompra, int limiteCompra);
int compra_imprimirCompraPorIDCliente (Compra * pArrayCompra, int limiteCompra, int id);
int compra_pagarCompra (Cliente * pArrayCliente, int limiteCliente,Compra *arrayCompra,int limiteCompra);
int compra_cancelarCompra (Cliente * pArrayCliente, int limiteCliente,Compra *arrayCompra,int limiteCompra);
int compra_imprimirCompraYcliente(Compra * pArrayCompra, int limiteCompra, Cliente * pArrayCliente , int limiteCliente);
int compra_bajaClienteYcompra (Cliente * pArraysCliente, int limiteCliente,Compra *arrayCompra,int limiteCompra);
int compra_contadorCompraPorCliente(Compra *arrayCompra,int limitCompra,int idCliente,int *comprasDelCliente);
int compra_bajaPorIdCliente(Compra * pArrayCompra, int limiteCompra,int idCliente);
int compra_imprimir (Compra * pArrayCompra , int limiteCompra);
int compra_buscarIndicePorIdRef(Compra * pArrayCompra, int limiteCompra,int idBuscar, int * pIndice);
int compra_buscarLibreRef(Compra pArrayCompra[],int limiteCompra, int *pindex);


#endif /* COMPRA_H_ */
