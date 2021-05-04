/*
 ============================================================================
 Name        : ParcialLab_1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "cliente.h"
#include "compra.h"
#include "informes.h"

int main(void) {
	setbuf(stdout,NULL);
	int opcionMenu;
	Color arrayColor[QTY_COMPRA];
	informes_colorInit(arrayColor,QTY_COMPRA);
	Cliente arrayCliente[QTY_CLIENTES];
	Compra arrayCompra[QTY_COMPRA];
	cliente_init(arrayCliente, QTY_CLIENTES);
	compra_init(arrayCompra,QTY_COMPRA);

	do
	{
			if(utn_getEntero("\n|////////////////////////////////////////////////////////////////BIENVENIDO!!!!!!!!!!!!!!!!!!///////////////////////////////////////////////////////|\n"
					   "|///////1)-Cargar Cliente//////////////2)-Modificar Cliente//////////////3)-Dar de baja un Cliente////////4)-Realizar una Compra///////////////|"
					 "\n|///////5)-Pagar compra//////////6)-Cancelar compra ////////////7)-Imprimir Clientes/////////////8)-Realizar Informes/////////////////////|"
					 "\n|/////////////////////////////////////////////////////////////////9)-Salir//////////////////////////////////////////////////////////////////////////|\n",
					 "\n|///////////////////////////////////////Error!!!! Reingrese numero!!!///////////////////////////////////////////////////////////////////////////////|",
					 &opcionMenu,3,9,1)==0)
			{
				switch(opcionMenu)
				{
				case 1:
					cliente_alta(arrayCliente, QTY_CLIENTES);
					break;
				case 2:
					cliente_modificar (arrayCliente,QTY_CLIENTES);
					break;
				case 3:
					compra_bajaClienteYcompra(arrayCliente,QTY_CLIENTES,arrayCompra,QTY_COMPRA);
					break;
				case 4:
					compra_alta(arrayCompra, QTY_COMPRA, arrayCliente, QTY_CLIENTES);
					break;
				case 5:
					compra_pagarCompra(arrayCliente, QTY_CLIENTES, arrayCompra, QTY_COMPRA);
					break;
				case 6:
					compra_cancelarCompra(arrayCliente, QTY_CLIENTES, arrayCompra, QTY_COMPRA);
					break;
				case 7:
					compra_imprimirCompraYcliente(arrayCompra, QTY_COMPRA, arrayCliente, QTY_CLIENTES);
					break;
				case 8:
					informes_menuConsulas(arrayCompra,QTY_COMPRA,arrayCliente,QTY_CLIENTES,arrayColor,QTY_COMPRA);
					break;
				}
			}
	}while(opcionMenu !=9);
}
