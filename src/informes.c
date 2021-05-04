/*
 * informes.c
 *
 *  Created on: 30 abr. 2021
 *      Author: marco
 */
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "utn.h"
#include "cliente.h"
#include "compra.h"
#include "informes.h"




/** \brief Inicializa el array de Color con espacios vacios
*
 * \param Valor Color *pArrays es el puntero al array de Color
 * \param Valor limiteColor es el tamaño del array de Color
 * \return Devuelve 0 si no hubo errores y -1 si hubo errores
 *
 */

int informes_colorInit(Color * pArrays, int limiteColor)
{
	int retorno = -1;
	if (pArrays != NULL && limiteColor >0){
		for (int i = 0; i<limiteColor; i++ )
		{
			pArrays[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}
int informe_unidadPrecio(Compra *pArrayCompra,int limiteCompra,int precioTotal,int cantidad,int *precioPorUnidad)
{
	int retorno=-1;
	int total;
	if(pArrayCompra!=NULL && limiteCompra>0)
	{
		if(cantidad!=0)
		{
			total = precioTotal/cantidad;
			*precioPorUnidad = total;
			retorno=0;
		}
	}

	return retorno;
}
int informes_colorRepetido(Color *pArrayColor,int limiteColor,char* colorAbuscar)
{
	int flagEncontrado=-1;
	int i;
	for(i=0;i<limiteColor;i++)
	{
		if(strncmp(pArrayColor[i].colores,colorAbuscar,QTY_CARACTERESCOLOR)==0)
		{
			flagEncontrado=0;
			break;
		}
	}
	return flagEncontrado;
}

int informes_agregarColor(Color* pArrayColor,int limiteColor,char* colorAagregar)
{
	int retorno=-1;
	int i;
	for(i=0;i<limiteColor;i++)
	{
		strncpy(pArrayColor[i].colores,colorAagregar,QTY_CARACTERESCOLOR);
		pArrayColor[i].isEmpty=FALSE;
		retorno=0;
	}
	return retorno;
}

int informes_agregarColorAlArray(Compra *pArrayCompra,int limiteCompra,Color *pArrayColor,int limiteColor)
{
	int retorno=-1;
	int i;
	char colorAbuscar[QTY_CARACTERESCOLOR];
	if(pArrayCompra!=NULL && limiteCompra>0 && pArrayColor!=NULL && limiteColor>0)
	{
		for(i=0;i<limiteCompra;i++)
		{
			strncpy(colorAbuscar,pArrayCompra[i].color,QTY_CARACTERESCOLOR);
			if(informes_colorRepetido(pArrayColor,limiteColor,colorAbuscar)==0)
			{
				informes_agregarColor(pArrayColor, limiteColor, colorAbuscar);
			}
		}
	}

	return retorno;
}
int informes_contadorComprasporColor(Compra *pArrayCompra,int limiteCompra,char* colorAbuscar,int *contadorColor)
{
	int contador=0;
	int retorno=-1;
	int i;
	for(i=0;i<limiteCompra;i++)
	{
		if(strncmp(pArrayCompra[i].color,colorAbuscar,QTY_CARACTERESCOLOR)==0)
		{
			contador++;
			retorno=0;
		}
	}
	*contadorColor=contador;
	return retorno;
}

int informes_colorDeBarbijoMasComprado(Compra *pArrayCompra,int limiteCompra,Color *pArrayColor,int limiteColor)
{
	int retorno=-1;
	int i;
	char colorAbuscar[QTY_CARACTERESCOLOR];
	int contadorColor;
	int contadorMax;
	char colorMasComprado[QTY_CARACTERESCOLOR];
	if(pArrayCompra!=NULL && limiteCompra>0 && pArrayColor!=NULL && limiteColor>0)
	{
		for(i=0;i<limiteCompra;i++)
		{
			strncpy(colorAbuscar,pArrayCompra[i].color,QTY_CARACTERESCOLOR);
			if(pArrayColor[i].isEmpty==FALSE && informes_contadorComprasporColor(pArrayCompra,limiteCompra,colorAbuscar,&contadorColor)==0)
			{
				if(i==0 || contadorColor>contadorMax)
				{
					contadorMax = contadorColor;
					strncpy(colorMasComprado,pArrayColor[i].colores,QTY_CARACTERESCOLOR);
					retorno=0;
				}
			}
		}
		printf("El barbijo mas comprado es el %s",colorMasComprado);
	}

	return retorno;
}

int informe_precioPorUnidadMasBajo(Compra *pArrayCompra,int limiteCompra)
{
	int retorno=-1;
	int precioMinPorUnidad;
	int resultadoPrecioPorUnidad;
	int i=0;
	if(pArrayCompra!=NULL && limiteCompra>0)
	{
		for(i=0;i<limiteCompra;i++)
		{
			if(pArrayCompra[i].isEmpty == FALSE && pArrayCompra[i].estadoCompra==COBRADO &&
			informe_unidadPrecio(pArrayCompra, limiteCompra,pArrayCompra[i].ImporteTotal,pArrayCompra[i].cantidadBarbijos,&resultadoPrecioPorUnidad)==0)
			{
				resultadoPrecioPorUnidad=pArrayCompra[i].ImporteTotal/pArrayCompra[i].cantidadBarbijos;
				if(i==0 || resultadoPrecioPorUnidad<precioMinPorUnidad)
				{
					precioMinPorUnidad = resultadoPrecioPorUnidad;

					retorno=0;
				}
			}
		}
		printf("El precio mas bajo por unidad es: %d y corresponde a la compra Id %d, con un importe total de: %d y una cantidad de %d unidades.",precioMinPorUnidad,pArrayCompra[i].idCompra,pArrayCompra[i].ImporteTotal,pArrayCompra[i].cantidadBarbijos);
	}
return retorno;
}

/** \brief Informa cuantas Compras estan Pendientes y devuelve el resultado por referencia
*
** \param valor Compra *pArrayCompra es el puntero al array de Compra
* \param valor limiteCompra es el tamaño del array de Compra
* \param valor contadorCompraPendientes devuelve la cantidad de Compras Pendientes
* \return Devuelve 0 si no hubo errores y -1 si hubo errores
*
*/

int informes_contarComprasPendientesRef(Compra *pArrayCompra,int limiteCompra,int *contadorComprasPendientes)
{
	int retorno=-1;
	int contador=0;
	for(int i = 0; i<limiteCompra; i++)
	{
		if (pArrayCompra[i].estadoCompra == PAGO_PENDIENTE &&
			pArrayCompra[i].isEmpty==FALSE)
		{
			contador++;
			retorno=0;
		}
	}
	*contadorComprasPendientes=contador;
	return retorno;
}

int informes_menuConsulas(Compra * pArrayCompra, int limiteCompra, Cliente * pArrayCliente , int limiteCliente,Color *pArrayColor,int limiteColor)
{
	int retorno=-1;
	char opcionMenu;
	int contadorComprasPendientes;

	if (pArrayCompra != NULL && limiteCompra >0 && pArrayCliente!=NULL && limiteCliente>0)
	{
		do
		{
			if(utn_getChar("\n|///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////|"
					         "\n|/////INGRESE: a) Color de barbijo mas que se compro mas veces.///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////|"
					         "\n|//////////////b) Cantidad de compras pendientes.//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////|"
					         "\n|//////////////c) Compra con “precio por unidad” mas bajo//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////|"
					        "\n|///////////////d) Salir/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////|",
							 "\n\n*|////////////////////////////////////////////////////////ERROR!!! LETRA MAL INGRESADA!!!!////////////////////////////////////////////////////////////////////////////////|*",
							 &opcionMenu,3)==0)
			{
				switch(opcionMenu)
				{
					case  'a':
						if(informes_colorDeBarbijoMasComprado(pArrayCompra,limiteCompra,pArrayColor,limiteColor)==0)
					    {
							retorno=0;
						}
						else
						{
							printf("No hay clientes con avisos");
						}
						break;
					case 'b':
						if(informes_contarComprasPendientesRef(pArrayCompra,limiteCompra,&contadorComprasPendientes)==0)
						{
							printf("La cantidad de compras pendientes es: %d",contadorComprasPendientes);
							retorno=0;
						}
						else
						{
							printf("No hay compras pendientes");
						}
						break;
					case 'c':
						if(informe_precioPorUnidadMasBajo(pArrayCompra,limiteCompra)==0)
						{
							retorno=0;
						}
						else
						{
							printf("\n No Compras cargadas");
						}
						break;
					case 'd':

						break;

				}
				retorno= 0;
			}
		}while(opcionMenu !='d');
	}
	return retorno;
}




