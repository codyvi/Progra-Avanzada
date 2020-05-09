#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void main() {
	char dirStr[]="C:\\Users\\David\\Documents\\PruebaProgra\\Temp";
	char dirFileStr[]="C:\\Users\\David\\Documents\\PruebaProgra\\Temp\\Algo1.txt";
	char dirFileStr2[]="C:\\Users\\David\\Documents\\PruebaProgra\\Temp\\Algo2.txt";
	HANDLE changeNotifHandle;
	HANDLE fileHandle;
	char chr = 0;
	DWORD waitResult;
	int flag=0;
	FILETIME lastWriteTime,t1,t2,t3;
	DWORD lastError;

	//Asegurar tiempos de facto para el archivo
	lastWriteTime.dwHighDateTime=0;	//Asignar los 32bits HIGH
	lastWriteTime.dwLowDateTime=0;	//Asignar los 32bits LOW
	//Abrir un "handle" con el archivo para obtener (inicialmente) el tiempo de ultima escritura
	fileHandle=CreateFile(dirFileStr,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
	//Si el 
	if (fileHandle!=INVALID_HANDLE_VALUE) {
		if(GetFileTime(fileHandle,&t1,&t2,&t3))
			memcpy(&lastWriteTime,&t3,sizeof(FILETIME));
		CloseHandle(fileHandle);
	} else {
		lastError=GetLastError();
		if (lastError==ERROR_FILE_NOT_FOUND)
			return;	//Archivo no localizado, quizas lo borraron ... terminar el programa
		//Otra posibilidad del error es que el archivo este abierto y LOCKED ...
		// ... habr� que decidir como proceder (terminar el programa tambi�n o ciclarse esperando)
		// ... pero esto no lo vamos a hacer aqu� simplemente tomamos valores de tiempo en ceros.
	}
	while (chr!=27) {
		if (!flag)
			changeNotifHandle=FindFirstChangeNotification(dirStr,FALSE,FILE_NOTIFY_CHANGE_LAST_WRITE);
		else
			FindNextChangeNotification(changeNotifHandle);
		waitResult = WaitForSingleObject(changeNotifHandle,500);	//Esperar hasta 500 mseg.
		flag=1;
		switch(waitResult) {
			case WAIT_OBJECT_0:
					printf("Cambio algun archivo\n");
					Sleep(50);	//Dar un tiempo para evitar el "LOCK" cuando se esta grabando el archivo
					fileHandle=CreateFile(dirFileStr,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
					if (fileHandle!=INVALID_HANDLE_VALUE) {
						if(GetFileTime(fileHandle,&t1,&t2,&t3)) {
							//printf("Time: %ld, %ld\n",t3.dwHighDateTime,t3.dwLowDateTime);
							if ((t3.dwHighDateTime!=lastWriteTime.dwHighDateTime)||(t3.dwLowDateTime!=lastWriteTime.dwLowDateTime)) {
								printf("El archivo cambio\n");
								memcpy(&lastWriteTime,&t3,sizeof(FILETIME));
								//unlink(dirFileStr2);
								CopyFile(dirFileStr,dirFileStr2,FALSE);
							} else {
								printf("El archivo NO cambio\n");
							}
						}
						CloseHandle(fileHandle);
					} else {
						lastError=GetLastError();
						if (lastError == ERROR_SHARING_VIOLATION)	//�Ups!, que mala suerte el archivo cambio y esta LOCKED
							printf("El archivo cambio!\n");
						else if (lastError == ERROR_FILE_NOT_FOUND) {
							printf("Borraron el achivo ... que hacemos?\n");
							return;		//Por lo pronto finalizar este programa
						} else
							printf("INVALID_HANDLE_VALUE! ... %ld\n",lastError);
					}
					break;
			case WAIT_TIMEOUT:
					printf(".");
					break;
			default:
					printf("ERROR!!!\n");
					break;
		}
		if (kbhit())
			chr=getch();
	}
	FindCloseChangeNotification(changeNotifHandle);
	printf("Listo\n");
}