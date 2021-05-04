/*
 * cliente.c
 *
 *  Created on: 29 abr. 2021
 *      Author: marco
 */
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "utn.h"
#include "cliente.h"

static int cliente_generarNuevoId (void);

/** \brief Inicializa el array de clientes con espacios vacios
*
 * \param Valor Cliente *arrayClientes es el puntero al array de clientes
 * \param Valor limiteCliente es el tamaño del array de clientes
 * \return Devuelve 0 si no hubo errores y -1 si hubo errores
 *
 */

int cliente_init(Cliente * pArrays, int limiteCliente)
{
	int retorno = -1;
	if (pArrays != NULL && limiteCliente >0){
		for (int i = 0; i<limiteCliente; i++ )
		{
			pArrays[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}

/** \brief Realiza el alta de clientes
 *
 * \param Valor Cliente *arrayClientes es el puntero al array de clientes
 * \param Valor limiteArrayClientes es el tamaño del array de clientes
 * \return Devuelve 0 si no hubo errores y -1 si hubo errores
 *
 */

int cliente_alta(Cliente *arrayClientes,int limiteArrayClientes)
{
	int retorno=-1;
	int indice;
	Cliente bufferClientes;
	if(arrayClientes!=NULL && limiteArrayClientes>0 )
	{
		if(cliente_buscarLibreRef(arrayClientes,limiteArrayClientes,&indice)==0)
		{
			if(utn_getNombre("\nINGRESE NOMBRE: ", "\nERROR!!!!! REINGRESE EL NOMBRE: ",bufferClientes.nombre,3,LONG_NOMBRE)==0 &&
				utn_getNombre("\nINGRESE APELLIDO: ","\n ERROR!!!!!! REINGRESE EL APELLIDO: ",bufferClientes.apellido,3, LONG_APELLIDO)==0 &&
				utn_getCuit("\nINGRESE CUIT: ", "\ERROR!!!!! REINGRESE CUIT: ",bufferClientes.cuit, 3, LONG_CUIT)==0)
			{
				//bufferAlumno.isEmpty=FALSE;
				arrayClientes[indice]=bufferClientes;
				arrayClientes[indice].isEmpty=FALSE;
				arrayClientes[indice].idCliente=cliente_generarNuevoId();
				printf("\n/////////////////////////////////////////////////////////ALTA REALIZADA CORRECTAMENTE////////////////////////////////////////////////////////////////////\n"
						"\///////////////////////////////////////////Nombre: %s -Apellido: %s - Cuit %s -ID Cliente: %d //////////////////////////////////////////////////////////\n"
						,arrayClientes[indice].nombre ,arrayClientes[indice].apellido , arrayClientes[indice].cuit, arrayClientes[indice].idCliente);
				retorno = 0;
			}
			else
			{
				printf("Error!!!!");
			}
		}
		else
		{
			printf("\n No quedan espacios libres");
		}
	}
	return retorno;
}

/** \brief Realiza la modificacion de clientes
 *
 * \param Valor Cliente *arrayClientes es el puntero al array de clientes
 * \param Valor limiteCliente es el tamaño del array de clientes
 * \return Devuelve 0 si no hubo errores y -1 si hubo errores
 *
 */
int cliente_modificar (Cliente * pArrays, int limiteCliente)
{
	int retorno = -1;
	int idBuscar;
	int indiceAModificar;
	Cliente bufferCliente;

	if (pArrays != NULL && limiteCliente>0)
	{
		cliente_imprimir(pArrays, limiteCliente);

		if(utn_getEntero("\nINGRESE EL ID QUE DESEA MODIFICAR:","\nERROR REINGRESE ID!!!!!",&idBuscar,3,9999,0)==0)
		{
			if(cliente_buscarIndicePorIdRef(pArrays,limiteCliente,idBuscar,&indiceAModificar) == 0)
			{
				bufferCliente = pArrays[indiceAModificar];

				if (utn_getNombre("\nINGRESE NUEVO NOMBRE","ERROR!!!REINGRESE NOMBRE",bufferCliente.nombre,3,LONG_NOMBRE) == 0 &&
					utn_getNombre("\nINGRESE NUEVO APELLIDO","ERROR!!!REINGRESE APELLIDO",bufferCliente.apellido,3,LONG_NOMBRE) == 0 &&
					utn_getCuit("INGRESE NUEVO CUIT","ERROR!!! REINGRESE CUIT", bufferCliente.cuit, 3, LONG_NOMBRE) == 0)
					{
						pArrays[indiceAModificar] = bufferCliente;
						retorno = 0;
					}
			}
			else
			{
				printf("ERROR!!!!ID NO ENCONTRADO!!!!!!!!");
			}
		}

	}
	return retorno;
}

/** \brief Imprime los clientes
 *
 * \param Valor Cliente *arrayClientes es el puntero al array de clientes
 * \param Valor limiteCliente es el tamaño del array de clientes
 * \return Devuelve 0 si no hubo errores y -1 si hubo errores
 *
 */
int cliente_imprimir (Cliente * pArrays , int limiteCliente)
{
	int retorno = -1;
	if (pArrays != NULL && limiteCliente >0){
		for (int i=0 ; i<limiteCliente ; i++)
		{
			if(pArrays[i].isEmpty == FALSE)
			{
				printf("\nNombre: %s - Apellido: %s - Cuit %s - ID %d",pArrays[i].nombre,pArrays[i].apellido, pArrays[i].cuit , pArrays[i].idCliente);
			}
		}
		retorno = 0;
	}
return retorno;
}

/** \brief Imprime los clientes por id
 *
 * \param Valor Cliente *arrayClientes es el puntero al array de clientes
 * \param Valor limiteCliente es el tamaño del array de clientes
 * \param Valor id es el id a buscar
 * \param Valor *mensaje es el puntero al mensaje que se va a presentar
 * \return Devuelve 0 si no hubo errores y -1 si hubo errores
 *
 */
int cliente_imprimirClientePorID (Cliente * pArrayCliente , int limitCliente, int id,char*mensaje)
{
	int retorno =-1;
		if(pArrayCliente!= NULL && limitCliente > 0 && pArrayCliente != NULL && limitCliente>0)
		{
			for(int i = 0; i<limitCliente; i++)
			{
				if (pArrayCliente[i].idCliente == id)
				{
					retorno = 0;
					printf("\n %s %s - %s -Cuit: %s -ID:%d ",mensaje,pArrayCliente[i].nombre,pArrayCliente[i].apellido, pArrayCliente[i].cuit,pArrayCliente[i].idCliente);
				}
			}
		}

	return retorno;
}

/** \brief Busca el indice por el id y devuelve por referencia el indice
 *
 * \param Valor Cliente *arrayClientes es el puntero al array de clientes
 * \param Valor limiteCliente es el tamaño del array de clientes
 * \param Valor idBuscar es el id que se va a buscar
 * \param Valor * pIndice es el puntero al indice encontrado
 * \return Devuelve 0 si no hubo errores y -1 si hubo errores
 *
 */

int cliente_buscarIndicePorIdRef (Cliente * pArrays, int limiteCliente,int idBuscar, int * pIndice)
{
	int retorno = -1;
	int i ;
		if (pArrays != NULL && limiteCliente >0 && idBuscar >= 0)
		{
				for ( i = 0; i<limiteCliente; i++)
				{
					if(pArrays[i].isEmpty == FALSE &&
					   pArrays[i].idCliente == idBuscar)
					{
					*pIndice= i;
					retorno = 0;
					break;
					}
				}
		}
		else
		{
			printf("ERRORR!!!!!!!!!!!!");
		}
	return retorno;
}

/** \brief Busca el en el array cliente un lugar libre y devuelve el indice por referencia
 *
 * \param Valor Cliente *arrayClientes es el puntero al array de clientes
 * \param Valor limiteCliente es el tamaño del array de clientes
 * \param Valor * pindex es el puntero al indice encontrado
 * \return Devuelve 0 si no hubo errores y -1 si hubo errores
 *
 */

int cliente_buscarLibreRef(Cliente pArrayCliente[],int limiteCliente, int *pindex)
{
	int retorno=-1;
	int i;
	if(pArrayCliente !=NULL && limiteCliente>0 && pindex!=NULL)
	{
		for(i = 0;i<limiteCliente;i++)
		{
			if(pArrayCliente[i].isEmpty==TRUE)
			{
				*pindex=i;
				retorno=0;
				break;
			}
		}
	}
	return retorno;
}

/** \brief Busca el indice por el id
 *
 * \param Valor Cliente *arrayClientes es el puntero al array de clientes
 * \param Valor limiteCliente es el tamaño del array de clientes
 * \param Valor idBuscar es el id que se va a buscar
 * \return Devuelve 0 si no hubo errores y -1 si hubo errores
 *
 */
int cliente_buscarIndicePorId (Cliente * pArrays, int limiteCliente,int idBuscar)
{
	int retorno = -1;
	int i ;
		if (pArrays != NULL && limiteCliente >0 && idBuscar >= 0)
		{
				for ( i = 0; i<limiteCliente; i++)
				{
					if(pArrays[i].isEmpty == FALSE &&
					   pArrays[i].idCliente == idBuscar)
					{
					retorno = i;
					break;
					}
				}
		}
		else
		{
			printf("ERROR!!!!!! ID NO ENCONTRADO");
		}
	return retorno;
}

/** \brief Genera un id para asociarlo al cliente
 */

static int cliente_generarNuevoId (void)
{
	static int id = 0;
	id = id+1;
	return id;
}
