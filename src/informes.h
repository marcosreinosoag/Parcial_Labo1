/*
 * informes.h
 *
 *  Created on: 30 abr. 2021
 *      Author: marco
 */

#ifndef INFORMES_H_
#define INFORMES_H_
#define QTY_COMPRA 1000


typedef struct{
	char colores [QTY_CARACTERESCOLOR];
	int isEmpty;
}Color;

int informes_colorInit(Color * pArrays, int limiteColor);
int informes_colorRepetido(Color *pArrayColor,int limiteColor,char* colorAbuscar);
int informes_contarComprasPendientesRef(Compra *pArrayCompra,int limiteCompra,int *contadorComprasPendientes);
int informes_colorDeBarbijoMasComprado(Compra *pArrayCompra,int limiteCompra,Color *pArrayColor,int limiteColor);
int informes_contadorComprasporColor(Compra *pArrayCompra,int limiteCompra,char* colorAbuscar,int *contadorColor);
int informes_agregarColor(Color* pArrayColor,int limiteColor,char* colorAagregar);
int informes_agregarColorAlArray(Compra *pArrayCompra,int limiteCompra,Color *pArrayColor,int limiteColor);
int cliente_baja (Cliente * pArraysCliente, int limiteCliente,Compra *arrayCompra,int limiteCompra);
int informe_precioPorUnidadMasBajo(Compra *pArrayCompra,int limiteCompra);
int informe_unidadPrecio(Compra *pArrayCompra,int limiteCompra,int precioTotal,int cantidad,int *precioPorUnidad);
int informes_menuConsulas(Compra * pArrayCompra, int limiteCompra, Cliente * pArrayCliente , int limiteCliente,Color *pArrayColor,int limiteColor);
#endif /* INFORMES_H_ */
