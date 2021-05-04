/*
 * compra.c
 *
 *  Created on: 29 abr. 2021
 *      Author: marco
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "utn.h"
#include "compra.h"


static int compra_generarNuevoId (void);

/** \brief Realiza el alta de Compras
 *
 * \param Valor Compra *arrayCompra es el puntero al array de Compra
 * \param Valor limiteArrayCompra es el tamaño del array de Compra
 * \param Valor Cliente *arrayCompra es el puntero al array de clientes
 * \param Valor limiteArrayClientes es el tamaño del array de clientes
 * \return Devuelve 0 si no hubo errores y -1 si hubo errores
 *
 */
int compra_alta(Compra *arrayCompra,int limiteCompra, Cliente *pArrayClientes,int limiteCliente)
{
	int retorno=-1;
	int indice;
	char estadoCompra[28];
	Compra bufferCompra;
	if(arrayCompra!=NULL && limiteCompra>0 )
	{
		if(compra_buscarLibreRef(arrayCompra,limiteCompra,&indice)==0)
		{
			cliente_imprimir(pArrayClientes,limiteCliente);
			if(utn_getEntero("\nINGRESE ID DEL CLIENTE: ","\nERROR!!!!! REINGRESE ID: ",&bufferCompra.idCliente,3,99999999,0)==0 &&
				cliente_buscarIndicePorId(pArrayClientes,limiteCliente,bufferCompra.idCliente) != -1 &&
				utn_getEntero("\nINGRESE LA CANTIDAD DE BARBIJOS: ","\nERROR!!!!! REINGRESE CANTIDAD DE BARBIJOS: ",&bufferCompra.cantidadBarbijos,3,99999999,0)==0 &&
				utn_getTexto("INGRESE LA DIRECCION DE ENTREGA","ERRORRRR!!!!!!!!!!!! REINGRESE LA DIRECCION DE ENTREGA",bufferCompra.textoDireccionEntrega,3,QTY_CARACTERESENTREGA) &&
				utn_getTexto("INGRESE EL COLOR","ERRORRRR!!!!!!!!!!!! REINGRESE EL COLOR",bufferCompra.color,3,QTY_CARACTERESCOLOR)==0 &&
				utn_getEntero("ingrese el importe total: ","Error!!!! Reingrese el importe total: ", &bufferCompra.ImporteTotal, 3, 99999999, 0)==0)
			{
				bufferCompra.isEmpty=FALSE;
				arrayCompra[indice]=bufferCompra;
				arrayCompra[indice].isEmpty=FALSE;
				arrayCompra[indice].idCompra=compra_generarNuevoId();
				arrayCompra[indice].estadoCompra= PAGO_PENDIENTE;
				if(arrayCompra[indice].estadoCompra==PAGO_PENDIENTE)
				{
					strncpy(estadoCompra,"Pendiente de cobrar",28);
				}
				else
				{
					strncpy(estadoCompra,"Cobrada",28);
				}
				printf("\n ////////////////////////////////////////////////////////////COMPRA REALIZADA CORRECTAMENTE////////////////////////////////////////////////////////////////////////////////////\n"
						"                                        ID CLIENTE: %d - CANTIDAD DE BABIJOS: %d - COLOR %s-ESTADO DE LA PUBLICACION: %s -ID AVISO: %d                       \n"
						"////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n"
						,arrayCompra[indice].idCliente ,arrayCompra[indice].cantidadBarbijos , arrayCompra[indice].color,estadoCompra,arrayCompra[indice].idCompra);
				retorno = 0;
			}
			else
			{
				printf("ERROR!!!!!!!!!!!! ID NO ENCONTRADO");
			}
		}
		else
		{
			printf("\n NO QUEDAN ESPACIOS LIBRES");
		}
	}
	return retorno;
}

int compra_bajaClienteYcompra (Cliente * pArraysCliente, int limiteCliente,Compra *arrayCompra,int limiteCompra)
{
	int retorno = -1;
	int idABorrar;
	int indiceABorrarCliente;
	int confirmacion;

	if (pArraysCliente != NULL && limiteCliente>0 && arrayCompra !=NULL && limiteCompra>0)
	{
		cliente_imprimir(pArraysCliente, limiteCliente);
		if(utn_getEntero("\nINGRESE EL ID QUE DESEA BORRAR: ","\nERROR!!!!! ID MAL INGRESADO!!",&idABorrar,3,9999,0)==0)
		{
			if(cliente_buscarIndicePorIdRef(pArraysCliente, limiteCliente,idABorrar,&indiceABorrarCliente)== 0 &&
				compra_imprimirCompraPorIDCliente(arrayCompra,limiteCompra,idABorrar)==0)
				{
					utn_getEntero("¿DESEA CONTINUAR LA BAJA DEL CLIENTE? 1(SI) 2(NO)", "ERROR!!!!!!!EL REGISTRO SERA ELIMINADO¿DESEA CONTINUAR LA BAJA DEL CLIENTE? 1(SI) 2(NO) ",&confirmacion,3, 2, 1);
					if(confirmacion)
					{
					compra_bajaPorIdCliente(arrayCompra,limiteCompra,indiceABorrarCliente);
					pArraysCliente[indiceABorrarCliente].isEmpty=TRUE;
					}
				}
				else
				if(cliente_buscarIndicePorIdRef(pArraysCliente, limiteCliente,idABorrar,&indiceABorrarCliente)== 0 )
				{
					utn_getEntero("¿DESEA CONTINUAR LA BAJA DEL CLIENTE? 1(SI) 2(NO)", "ERROR!!!!!!!EL REGISTRO SERA ELIMINADO¿DESEA CONTINUAR? ",&confirmacion,3, 2, 1);
					if(confirmacion==1)
					{
					pArraysCliente[indiceABorrarCliente].isEmpty=TRUE;
					}
				}
		}
	}
	return retorno;
}

/** \brief Realiza el cambio de estado en la Compra de pendiente a cobrada
*
* \param Valor Cliente * pArrayCliente es el puntero al array de Clientes
* \param Valor limitCliente es el tamaño del array de clientes
* \param valor Compra *arrayCompra es el puntero al array de Compra
* \param valor limiteCompra es el tamaño del array de Compra
* \return Devuelve 0 si no hubo errores y -1 si hubo errores
*
*/

int compra_pagarCompra (Cliente * pArrayCliente, int limiteCliente,Compra *arrayCompra,int limiteCompra)
{
	int retorno = -1;
	int idCompra;
	int indiceCliente;
	int pIndice;
	int confirmacionReanudar;

	if (pArrayCliente != NULL && limiteCliente >0 && arrayCompra!=NULL && limiteCompra>0)
	{
		if(compra_imprimir(arrayCompra, limiteCompra)==0 && utn_getEntero("\n INGRESE EL ID DE LA COMPRA QUE DESEA PAGAR: ","\nERROR!!!!! ID NO ENCONTRADO",&idCompra,3,9999,0)==0 &&
			compra_buscarIndicePorIdRef(arrayCompra,limiteCompra,idCompra,&indiceCliente)==0)
		{
			cliente_buscarIndicePorIdRef (pArrayCliente,QTY_CLIENTES,arrayCompra[indiceCliente].idCliente,&pIndice);
			printf("\nID CLIENTE: %d - NOMBRE: %s - APELLIDO %s - CUIT %s",pArrayCliente[pIndice].idCliente,pArrayCliente[pIndice].nombre, pArrayCliente[pIndice].apellido , pArrayCliente[pIndice].cuit);
			utn_getEntero("ATENCION!!! LA COMPRA CAMBIARA AL ESTADO: COBRADO ¿DESEA CONTINUAR? 1(SI) 2(NO)", "ERROR REINGRESE EL NUMERO!!!! EL AVISO SERA REACTIVADO¿DESEA CONTINUAR? ",&confirmacionReanudar,3, 2, 1);
			if(confirmacionReanudar)
			{
				arrayCompra[indiceCliente].estadoCompra= COBRADO;
			}
			else
			{
				printf("Usted esta volviendo al menu");
			}
		}
	}
	return retorno;
}



/** \brief Realiza el cambio de estado en la Compra de cobrada a pendiente
*
* \param Valor Cliente * pArrayCliente es el puntero al array de Clientes
* \param Valor limitCliente es el tamaño del array de clientes
* \param valor Compra *arrayCompra es el puntero al array de Compra
* \param valor limiteCompra es el tamaño del array de Compra
* \return Devuelve 0 si no hubo errores y -1 si hubo errores
*
*/

int compra_cancelarCompra (Cliente * pArrayCliente, int limiteCliente,Compra *arrayCompra,int limiteCompra)
{
	int retorno = -1;
	int idCompra;
	int indiceCliente;
	int pIndice;
	int confirmacionReanudar;

	if (pArrayCliente != NULL && limiteCliente >0 && arrayCompra!=NULL && limiteCompra>0)
	{
		if(compra_imprimir(arrayCompra, limiteCompra)==0 && utn_getEntero("\n INGRESE EL ID DE LA COMPRA QUE DESEA PAGAR: ","\nERROR!!!!! ID NO ENCONTRADO",&idCompra,3,9999,0)==0 &&
			compra_buscarIndicePorIdRef(arrayCompra,limiteCompra,idCompra,&indiceCliente)==0)
		{
			cliente_buscarIndicePorIdRef (pArrayCliente,QTY_CLIENTES,arrayCompra[indiceCliente].idCliente,&pIndice);
			printf("\nID CLIENTE: %d - NOMBRE: %s - APELLIDO %s - CUIT %s",pArrayCliente[pIndice].idCliente,pArrayCliente[pIndice].nombre, pArrayCliente[pIndice].apellido , pArrayCliente[pIndice].cuit);
			utn_getEntero("ATENCION!!! LA COMPRA CAMBIARA AL ESTADO: PENDIENTE DE COBRAR ¿DESEA CONTINUAR? 1(SI) 2(NO)", "ERROR REINGRESE EL NUMERO!!!! EL AVISO SERA REACTIVADO¿DESEA CONTINUAR? ",&confirmacionReanudar,3, 2, 1);
			if(confirmacionReanudar)
			{
				arrayCompra[indiceCliente].estadoCompra= PAGO_PENDIENTE;
			}
			else
			{
				printf("Usted esta volviendo al menu");
			}
		}
	}
	return retorno;
}



/** \brief Busca el indice por ID de la Compra y devuelve el indice de la Compra por referencia
*
* \param valor Compra * pArrayCompra es el puntero al array de Compra
* \param valor limiteCompra es el tamaño del array de Compra
* \param idBuscar es el id a buscar
* \param devuelve el puntero que devuelve el indice de la compra
* \return Devuelve 0 si no hubo errores y -1 si hubo errores
*
*/
int compra_buscarIndicePorIdRef(Compra * pArrayCompra, int limiteCompra,int idBuscar, int * pIndice)
{
	int retorno = -1;
	int i ;
		if (pArrayCompra != NULL && limiteCompra >0 && idBuscar >= 0)
		{
				for ( i = 0; i<limiteCompra; i++)
				{
					if(pArrayCompra[i].isEmpty == FALSE &&
					   pArrayCompra[i].idCompra == idBuscar)
					{
					*pIndice= i;
					retorno = 0;
					break;
					}
				}
		}
		else
		{
			printf("ERROR!!! ID NO ENCONTRADO!!!!!!!!!!!!");
		}
	return retorno;
}
/** \brief Imprime una lista de clientes con todos sus datos junto con la cantidad de Compras activos.
*
 * \param valor Compra * pArrayCompra es el puntero al array de Compra
 * \param valor limiteCompra es el tamaño del array de Compra
 * \param Valor Cliente *pArrayClientes es el puntero al array de Clientes
 * \param Valor limiteCliente es el tamaño del array de clientes
 *
 * \return Devuelve 0 si no hubo errores y -1 si hubo errores
 *
 */
int compra_imprimirCompraYcliente(Compra * pArrayCompra, int limiteCompra, Cliente * pArrayCliente , int limiteCliente)
{
	int retorno = -1;
	int comprasDelCliente;

	if (pArrayCompra != NULL && limiteCompra >0 && pArrayCliente!=NULL && limiteCliente>0)
	{
			for (int i=0 ; i<limiteCliente ; i++)
			{
				if(pArrayCliente[i].isEmpty == FALSE)
				{
					compra_contadorCompraPorCliente(pArrayCompra,limiteCompra,pArrayCliente[i].idCliente,&comprasDelCliente);
					printf("\nNombre: %s - Apellido: %s - Cuit: %s - ID: %d "
							"\n Compras realizadas: %d",pArrayCliente[i].nombre,pArrayCliente[i].apellido, pArrayCliente[i].cuit , pArrayCliente[i].idCliente,comprasDelCliente);
				}
			}
		retorno = 0;
	}
	return retorno;
}

/** \brief Desarrolla la suma total de Compra realizados por el cliente y devuelve la suma por referencia
*
* \param valor Compra *arrayCompra es el puntero al array de Aviso
* \param valor limitCompra es el tamaño del array de Compra
* \param valor idCliente recibe el id del cliente para realizar la suma de los avisos
* \param valor *comprasDelCliente devuelve la suma total de Compras realizadas por el cliente
* \return Devuelve 0 si no hubo errores y -1 si hubo errores
*
*/

int compra_contadorCompraPorCliente(Compra *arrayCompra,int limitCompra,int idCliente,int *comprasDelCliente)
{
	int retorno =-1;
	int contadorCompra=0;
	int i;
		if(arrayCompra != NULL && limitCompra > 0)
		{
			for(i = 0; i<limitCompra; i++)
			{
				if (arrayCompra[i].idCliente == idCliente &&
						arrayCompra[i].isEmpty==FALSE)
				{
					contadorCompra++;
					retorno = 0;
				}
			}
		}
	*comprasDelCliente=contadorCompra;
 return retorno;
}

/** \brief Imprime los Compra publicados
*
* \param valor Compra * pArrayCompra es el puntero al array de Compra
* \param valor limiteCompra es el tamaño del array de Compra
* \return Devuelve 0 si no hubo errores y -1 si hubo errores
*
*/
int compra_imprimir (Compra * pArrayCompra , int limiteCompra)
{
	int retorno = -1;
	int i;
	char estadoCompra[20];
	if (pArrayCompra != NULL && limiteCompra >0)
	{
		for (i=0 ; i<limiteCompra ; i++)
		{
			if(pArrayCompra[i].isEmpty == FALSE)
			{
				if(pArrayCompra[i].estadoCompra == PAGO_PENDIENTE)
				{
					strncpy(estadoCompra,"PAGO PENDIENTE",20);
				}
				else
				{
					strncpy(estadoCompra,"COBRADA",20);
				}
				printf("\n ID Compra %d - Estado de la compra: %s - Cantidad de barbijos: %d - Direccion de entrega %s - Color: %s - ID de cliente: %d ",pArrayCompra[i].idCompra, estadoCompra, pArrayCompra[i].cantidadBarbijos, pArrayCompra[i].textoDireccionEntrega, pArrayCompra[i].color,pArrayCompra[i].idCliente);
			}
			else{
				printf("Usted llego al limite de compra disponible");
			}
		}
		retorno = 0;
	}
return retorno;
}


/** \brief Busca un espacio vacio en el array de Compra y devuelve el indice por referencia
*
* \param valor Aviso *pArrayCompra es el puntero al array de Compra
* \param valor limiteCompra es el tamaño del array de Compra
* \param valor *pindex es el indice de la compra vacia
* \return Devuelve 0 si no hubo errores y -1 si hubo errores
*
*/


int compra_buscarLibreRef(Compra pArrayCompra[],int limiteCompra, int *pindex)
{
	int retorno=-1;
	int i;
	if(pArrayCompra !=NULL && limiteCompra>0 && pindex!=NULL)
	{
		for(i = 0;i<limiteCompra;i++)
		{
			if(pArrayCompra[i].isEmpty==TRUE)
			{
				*pindex=i;
				retorno=0;
				break;
			}
		}
	}
	return retorno;
}

/** \brief Inicializa el array de compras con espacios vacios
*
 * \param Valor Compra *pArrayCompra es el puntero al array de clientes
 * \param Valor limiteCompra es el tamaño del array de clientes
 * \return Devuelve 0 si no hubo errores y -1 si hubo errores
 *
 */

int compra_init(Compra * pArrayCompra, int limiteCompra)
{
	int retorno = -1;
	if (pArrayCompra != NULL && limiteCompra >0)
	{
		for (int i = 0; i<limiteCompra; i++ )
		{
			pArrayCompra[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}

/** \brief Imprime Compras por ID
*
* \param valor Compra * pArrayCompra es el puntero al array de Compra
* \param valor limiteCompra es el tamaño del array de Compra
* \param valor id es el id del cliente que sera asociado con la compra
* \return Devuelve 0 si no hubo errores y -1 si hubo errores *************
*
*/

int compra_imprimirCompraPorIDCliente (Compra * pArrayCompra, int limiteCompra, int id)
{
	int retorno =-1;
		if(pArrayCompra != NULL && limiteCompra > 0 )
		{
			for(int i = 0; i<limiteCompra; i++)
			{
				if (pArrayCompra[i].idCliente == id)
				{
					retorno = 0;
					printf("\n ID CLIENTE: %d - ID COMPRA: %d -CANTIDAD DE BARBIJOS COMPRADOS %d ",pArrayCompra[i].idCliente,pArrayCompra[i].idCompra,pArrayCompra[i].cantidadBarbijos);
				}
			}
		}

	return retorno;
}

/** \brief Realiza la baja de la compra por el id de cliente
*
* \param valor Compra * pArrayCompra es el puntero al array de Compra
* \param valor limiteCompra es el tamaño del array de Compra
* \param valor idCliente es el id del cliente que se va a asociar con la compra
* \return Devuelve 0 si no hubo errores y -1 si hubo errores
*
*/
int compra_bajaPorIdCliente(Compra * pArrayCompra, int limiteCompra,int idCliente)
{
	int retorno =-1;
	if(pArrayCompra != NULL && limiteCompra > 0)
	{
		for(int i = 0; i<limiteCompra; i++)
		{
			if (pArrayCompra[i].idCliente == idCliente)
			{
				pArrayCompra[i].isEmpty=TRUE;
				retorno = 0;
			}
		}
	}
	return retorno;
}

/** \brief Genera un id para asociarlo a la Compra
 */

static int compra_generarNuevoId (void)
{
	static int id = 0;
	id = id+1;
	return id;
}
