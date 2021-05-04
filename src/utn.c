/*
 * utn.c
 *
 *  Created on: 10 oct. 2020
 *      Author: marco
 */
#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include<string.h>


static int myGets(char *cadena, int longitud);
static int getInt(int* pResultado);
static int esNumerica(char* cadena);
static int getFloat(float* pResultado);
static int esFloat(char* cadena);


static int myGets(char *cadena, int longitud)
{
	if(cadena!=NULL && longitud>0 && fgets (cadena, longitud, stdin)==cadena)
	{
		fflush(stdin);
		if(cadena[strlen(cadena)-1]=='\n')
		{
			cadena[strlen (cadena) - 1] = '\0';
		}
		return 0;

	}
	return -1;
}

static int esNumerica(char* cadena)
{
	int i=0;
	int retorno=0;
	if(cadena !=NULL && strlen(cadena)>0)
	{
		while(cadena[i]!= '\0')
		{
			if(cadena[i]<'0'|| cadena [i]>'9')
			{
				retorno=-1;
				break;
			}
			i++;
		}
	}
	return retorno;
}
static int getInt(int* pResultado)
{
	int retorno=-1;
	char buffer[LIMITE_BUFFER_STRING];
	if(pResultado!=NULL)
	{
		if (myGets(buffer,sizeof(buffer))==0 && esNumerica(buffer)==0)
		{
			*pResultado=atoi(buffer);
			retorno=0;
		}
	}
	return retorno;
}



/**
 * \brief Solicita un numero entero al usuario
 * \param Valor  mensaje, se guarda el mensaje que va a ser leido por el usuario
 * \param Valor  mensajeError, se guarda el mesaje de error que va a ser leido por el usuario
 * \param Valor  pResultado, puntero al espacio de memoria donde se dejara el valor obtenido.
 * \param Valor  reintentos, cantidad de oportunidades para ingresar el dato.
 * \param Valor	 maximo, se guarda el valor maximo para establecerlo como limite de lo que se va a ingresar
 * \param Valor  minimo, se guarda el valor minimo para establecerlo como limite de lo que se va a ingresar
 * \return Devuelve si hubo error o no
 *
 */

int utn_getEntero(char* mensaje, char* mensajeError, int* pResultado,int reintentos,int maximo,int minimo)
{
	int retorno=-1;
	int bufferInt;
	if(mensaje != NULL && mensajeError != NULL && pResultado!= NULL && reintentos >= 0 && maximo >= minimo)
	{
		while(reintentos>0)
		{
			reintentos--;
			printf("%s",mensaje);
			if(getInt(&bufferInt)==0)
			{
				if(bufferInt>=minimo && bufferInt<=maximo)
				{
					*pResultado = bufferInt;
					retorno=0;
					break;
				}
			}
			printf("%s",mensajeError);
		}
	}
	return retorno;
}

static int esFloat(char* cadena)
{
	int i=0;
	int retorno=0;
	int contadorPuntos=0;
	if(cadena !=NULL && strlen(cadena)>0)
	{
		while(cadena[i]!= '\0')
		{
			if(cadena[i]<'0'|| cadena [i]>'9')
			{
				if(cadena[i] == '.' && contadorPuntos ==0)
				{
					contadorPuntos++;
					retorno=0;
				}
				else
				{
					retorno=-1;
					break;
				}
			}
			i++;
		}
	}
	return retorno;
}

static int getFloat(float* pResultado)
{
	int retorno=-1;
	char buffer[LIMITE_BUFFER_STRING];
	if(pResultado!=NULL)
	{
		if (myGets(buffer,sizeof(buffer))==0 && esFloat(buffer)==0)
		{
			*pResultado=atof(buffer);
			retorno=0;
		}
	}
	return retorno;
}

int utn_getfloat(char* mensaje, char* mensajeError, float* pResultado,int reintentos,int maximo,int minimo)
{
	int retorno=-1;
	float bufferInt;
	if(mensaje != NULL && mensajeError != NULL && pResultado!= NULL && reintentos >= 0 && maximo >= minimo)
	{
		while(reintentos>0)
		{
			reintentos--;
			printf("%s",mensaje);
			if(getFloat(&bufferInt)==0)
			{
				if(bufferInt>=minimo && bufferInt<=maximo)
				{
					*pResultado = bufferInt;
					retorno=0;
					break;
				}
			}
			printf("%s",mensajeError);
		}
	}
	return retorno;
}


/**
 * \brief 	Verifica una cadena recibida como parametro para determinar si es un nombre valido
 * \param char* cadena, Cadena a analizar
 * \param int limite, indica la cantidad de letras maxima de la cadena
 * \return (0) Indicar que no es un nombre valido / (1) Indica que que es un nombre valido
 *
 */
int esUnNombreValido(char* cadena,int limite)
{
	int respuesta = 1;

	for(int i=0; i<=limite && cadena[i] != '\0';i++)
	{
		if(	(cadena[i] < 'A' || cadena[i] > 'Z') &&
			(cadena[i] < 'a' || cadena[i] > 'z'))
		{
			respuesta = 0;
			break;
		}
	}
	return respuesta;
}

/**
 * \brief Solicita un nombre al usuario
 * \param Valor  mensaje, se guarda el mensaje que va a ser leido por el usuario
 * \param Valor  mensajeError, se guarda el mesaje de error que va a ser leido por el usuario
 * \param Valor  pResultado, puntero al espacio de memoria donde se dejara el valor obtenido.
 * \param Valor  reintentos, cantidad de oportunidades para ingresar el dato.
 * \param Valor  limite, indica la cantidad de letras maxima del nombre
 * \return Devuelve si hubo error o no
 *
 */

int utn_getNombre(char* mensaje, char* mensajeError, char* pResultado,int reintentos, int limite)
{
char bufferString[LIMITE_BUFFER_STRING];
	int retorno = -1;

	if(mensaje != NULL && mensajeError != NULL && pResultado != NULL && reintentos >= 0 && limite > 0)
	{
		do
		{
			printf("%s",mensaje);
			if( myGets(bufferString,LIMITE_BUFFER_STRING) == 0 &&
				strnlen(bufferString,sizeof(bufferString)-1)<= limite &&
				esUnNombreValido(bufferString,limite) != 0 ) //verdadero
			{
				retorno = 0;
				strncpy(pResultado,bufferString,limite);
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

/**
 * \brief Solicita un nombre al usuario
 * \param Valor  mensaje, se guarda el mensaje que va a ser leido por el usuario
 * \param Valor  mensajeError, se guarda el mesaje de error que va a ser leido por el usuario
 * \param Valor  pResultado, puntero al espacio de memoria donde se dejara el valor obtenido.
 * \param Valor  reintentos, cantidad de oportunidades para ingresar el dato.
 * \param Valor  limite, indica la cantidad de letras maxima del nombre
 * \return Devuelve si hubo error o no
 *
 */

int utn_getTexto(char* mensaje, char* mensajeError, char* pResultado,int reintentos, int limite)
{
char bufferString[LIMITE_BUFFER_STRING];
	int retorno = -1;

	if(mensaje != NULL && mensajeError != NULL && pResultado != NULL && reintentos >= 0 && limite > 0)
	{
		do
		{
			printf("%s",mensaje);
			if( myGets(bufferString,LIMITE_BUFFER_STRING) == 0 &&
				strnlen(bufferString,sizeof(bufferString)-1)<= limite)
			{
				retorno = 0;
				strncpy(pResultado,bufferString,limite);
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}
/**
 * \brief 	Verifica una cadena recibida como parametro para determinar si es un nombre valido
 * \param char* cadena, Cadena a analizar
 * \param int limite, indica la cantidad de letras maxima de la cadena
 * \return (0) Indicar que no es un nombre valido / (1) Indica que que es un nombre valido
 *
 */
int esUnCuitValido(char* cadena,int limite)
{
	int respuesta = 1;

	for(int i=0; i<=limite && cadena[i] != '\0';i++)
	{
		if(	(cadena[i] < '0' || cadena[i] > '9') &&
			(cadena[i] != '-' ))
		{
			respuesta = 0;
			break;
		}
	}
	return respuesta;
}

/**
 * \brief Solicita el cuit al usuario
 * \param Valor *mensaje, se guarda el mensaje que va a ser leido por el usuario
 * \param Valor *mensajeError, se guarda el mesaje de error que va a ser leido por el usuario
 * \param Valor *pResultado, puntero al espacio de memoria donde se dejara el valor obtenido.
 * \param Valor reintentos, cantidad de oportunidades para ingresar el dato.
 * \param Valor limite, indica la cantidad de letras maxima del nombre
 * \return Devuelve si hubo error o no
 *
 */
int utn_getCuit(char* mensaje, char* mensajeError, char* pResultado,int reintentos, int limite)
{
	char bufferString[LIMITE_BUFFER_STRING];
		int retorno = -1;

		if(mensaje != NULL && mensajeError != NULL && pResultado != NULL && reintentos >= 0 && limite > 0)
		{
			do
			{
				printf("%s",mensaje);
				if( myGets(bufferString,LIMITE_BUFFER_STRING) == 0 &&
					strnlen(bufferString,sizeof(bufferString)-1)<= limite &&
					esUnCuitValido(bufferString,limite) != 0 ) //verdadero
				{
					retorno = 0;
					strncpy(pResultado,bufferString,limite);
					break;
				}
				else
				{
					printf("%s",mensajeError);
					reintentos--;
				}
			}while(reintentos >= 0);
		}
	return retorno;
}


int utn_getChar(char *mensaje, char * mensajeError,char *pResultado,int reintentos)
{
	char bufferString[LIMITE_BUFFER_STRING];
	int retorno = -1;

	if(mensaje != NULL && mensajeError != NULL && pResultado != NULL && reintentos >= 0)
	{
		do
		{
			printf("%s",mensaje);
			if( myGets(bufferString,LIMITE_BUFFER_STRING) == 0 &&
				strnlen(bufferString,sizeof(bufferString)-1)== 1) //verdadero
			{
				retorno = 0;
				strncpy(pResultado,bufferString,1);
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}






