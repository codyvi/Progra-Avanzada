// Programa para instalar un programa con estructa de servicio
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <winsvc.h>

#define MAXSERVICIOSPORPANTALLA	10

char nombreServicio[512];
char nombreDisplay[512];
char pathServicio[512];


SC_HANDLE manejadorServicios;		//Descriptor del manejador de servicios
SC_HANDLE nuevoServicio;

ENUM_SERVICE_STATUS *ptrDatosServicios,*ptrAuxDatosServicios;
int srvIndx;
int bytesRequeridos;
int contadorServicios;
int contadorServiciosEnPantalla;

void main(void) {
	char chr=0;

	if (manejadorServicios=OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS)) {
		srvIndx=0;
		while (chr!=27) {
			printf("\nOPERACIONES:\n  1)Visualizar servicios instalados\n  2)Instalar un servicio\n  3)Borrar un servicio\n<ESC> Terminar\nSeleccion==>");
			chr=getch();
			switch(chr) {
				case '1':	//Visualizar servicios
						ptrDatosServicios=NULL;
						EnumServicesStatus(manejadorServicios,SERVICE_WIN32,		//Obtner la cantidad de byes que se requerirán para guardar los datos
															  SERVICE_STATE_ALL,NULL,0,
															  &bytesRequeridos,&contadorServicios,&srvIndx);
						ptrDatosServicios=malloc(bytesRequeridos);
						EnumServicesStatus(manejadorServicios,SERVICE_WIN32,
															  SERVICE_STATE_ALL,ptrDatosServicios,bytesRequeridos,
															  &bytesRequeridos,&contadorServicios,&srvIndx);
						ptrAuxDatosServicios=ptrDatosServicios;
						if (contadorServicios!=0) {	//¿Hay algo que mostrar?
							printf("\n------------------------------------------------------------------------\n");
							srvIndx=0;
							chr=0;
							while (chr!=27) {
								contadorServiciosEnPantalla=0;
								while((contadorServiciosEnPantalla<MAXSERVICIOSPORPANTALLA)&&(srvIndx<contadorServicios)) {
									printf("%d) Servicio (Nombre) --> %s\n",srvIndx,ptrAuxDatosServicios->lpServiceName);
									printf("    ....... (Display) -> %s\n",ptrAuxDatosServicios->lpDisplayName);
									contadorServiciosEnPantalla++;
									ptrAuxDatosServicios++;
									srvIndx++;
								}
	
								if (srvIndx>=contadorServicios) {
									printf("Lista completa ... presione cualquier tecla para continuar\n");
									chr=27;		//Forzar salida
									getch();	//Esperar cualquier caracter
								} else {
									printf("\nPresione cualquier tecla para continuar, <ESC> para salir\n");
									chr=getch();
								}
							}
							if (ptrDatosServicios!=NULL)
								free(ptrDatosServicios);
							chr=0;	//Evitar propagar el valor de chr hacia el ciclo principal
						}
						break;
				case '2':	//Instalar un servicio
						printf("Cual sera el nombre del servicio: ");
						scanf("%s",nombreServicio);
						printf("Con que nombre desea visualizar el servicio en pantalla: ");
						scanf("%s",nombreDisplay);
						printf("Cual es el \"path\" para ubicar el archivo ejecutable:\n   ");
						scanf("%s",pathServicio);

						if((nuevoServicio=CreateService(manejadorServicios,nombreServicio,nombreDisplay,
														SERVICE_ALL_ACCESS,SERVICE_WIN32_OWN_PROCESS,
														SERVICE_AUTO_START,SERVICE_ERROR_NORMAL,
														pathServicio,NULL,NULL,NULL,NULL,NULL))==NULL)	//Error?
							printf("(%d) Error al crear el servicio %s\n",GetLastError(),nombreServicio);
						else
							printf("Servicio %s creado!!!\n",nombreServicio);
						break;
				case '3':	//Borrar un servicio
						printf("Cual es el nombre del servicio que desea eliminar: ");
						scanf("%s",nombreServicio);
						if(!(DeleteService(OpenService(manejadorServicios,nombreServicio,DELETE))))	//Error?
							printf("(%d) Error al eliminar el servicio %s\n",GetLastError(),nombreServicio);
						else
							printf("Servicio %s eliminado!!!\n",nombreServicio);
						break;
			}
		}
		CloseServiceHandle(manejadorServicios);
	}
}