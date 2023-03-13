#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	
	//Conector para acceder al servidor de bases de datos
	
	MYSQL *conn;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int i;
	int j;
	int err;
	int id;
	int idJ;
	int idP;
	char usuario [30];
	char contrasena [30];
	char consulta [80];
	char ids [3];
	char idJs [3];
	char idPs [3];
	char fechaHora [50];
	int duracion;
	char ganador [50];
	char duraciones [3];
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al establecer la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//inicializar la conexion, indicando nuestras claves de acceso
	// al servidor de bases de datos (user,pass)
	
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "JUEGO", 0, NULL, 0);
	if (conn==NULL)
	{
		printf ("Error al establecer la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	// ahora vamos a crear la base de datos, que se llamara JUEGO
	// primero la borramos si es que ya existe
	
	mysql_query(conn, "drop database if exists JUEGO;"); 
	err=mysql_query(conn, "create database JUEGO;");
	if (err!=0) {
		printf ("Error al crear la base de datos %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	
	// creamos las 3 tablas que definen la entidad JUEGO: 
	err=mysql_query(conn,
					"CREATE TABLE JUGADORES (ID int not null primary key, USUARIO VARCHAR(30), CONTRASENA VARCHAR (30) not null primary key");
	err=mysql_query(conn,
					"CREATE TABLE PARTIDAS (ID int not null primary key, FECHA_HORA VARCHAR(50), DURACION int, GANADOR VARCHAR (50)");
	err=mysql_query(conn,				
					"CREATE TABLE PARTICIPACION (ID_J INT, ID_P INT, FOREIGN KEY (ID_J) REFERENCES JUGADORES (ID), FOREIGN KEY (ID_P) REFERENCES PARTIDAS (ID)");
	
	if (err!=0)
	{
		printf ("Error al definir la tabla %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	
	//Introduciremos en la base de datos 4 personas cuyos datos pedimos al usuario
	for (i=0; i<4; i++) {
		printf ("Escribe ID, usuario y contraseña, separados por un blanco\n");
		err = scanf ("%d %s %s", &id, usuario, contrasena);
		if (err!=3) {
			printf ("Error al introducir los datos \n");
			exit (1);
		}
	}
	
	
	// INSERT INTO JUGADORES VALUES (id, 'usuario', 'contraseña'); 
	strcpy (consulta, "INSERT INTO JUGADORES VALUES ('");
	
	//convertimos id en un string y lo concatenamos 
	sprintf(ids, "%d", id);
	strcat (consulta, ids); 
	strcat (consulta, ");");
	//concatenamos el usuario 
	strcat (consulta, usuario); 
	strcat (consulta, "','");
	//concatenamos la contraseña
	strcat (consulta, contrasena); 
	strcat (consulta, "','");
	
	
	printf("consulta = %s\n", consulta);
	// Ahora ya podemos realizar la insercion 
	err = mysql_query(conn, consulta);
	if (err!=0) {
		printf ("Error al introducir datos la base %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//Introduciremos en la base de datos los datos de la tabla partidas cuyos datos pedimos al usuario
	for (i=0; i<4; i++) {
		printf ("Escribe el ID, fecha_hora, duracion y el ganador, separados por un blanco\n");
		err = scanf ("%d %s %d %s", &id, fechaHora, &duracion, ganador);
		if (err!=3) {
			printf ("Error al introducir los datos \n");
			exit (1);
		}
	}
	
	// INSERT INTO PARTIDAS VALUES (id, 'fechaHora', duracion, 'ganador'); 
	strcpy (consulta, "INSERT INTO PARTIDAS VALUES ('");
	
	//convertimos id en un string y lo concatenamos 
	sprintf(ids, "%d", id);
	strcat (consulta, ids); 
	strcat (consulta, ");");
	//concatenamos la fechaHora 
	strcat (consulta, fechaHora); 
	strcat (consulta, "','");
	//convertimos duracion en un string y lo concatenamos 
	sprintf(duraciones, "%d", duracion);
	strcat (consulta, duraciones); 
	strcat (consulta, ");");
	//concatenamos el ganador 
	strcat (consulta, ganador); 
	strcat (consulta, "','");
	
	
	printf("consulta = %s\n", consulta);
	// Ahora ya podemos realizar la insercion 
	err = mysql_query(conn, consulta);
	if (err!=0) {
		printf ("Error al introducir datos la base %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	
	//Introduciremos en la base de datos los datos de la tabla participacion, 
	//cuyos datos pedimos al usuario
	for (i=0; i<8; i++) {
		printf ("Escribe el ID_J, ID_P separados por un blanco\n");
		err = scanf ("%d %d", &idJ, &idP);
		if (err!=7) {
			printf ("Error al introducir los datos \n");
			exit (1);
		}
	}
	
	// INSERT INTO PARTICIPACION VALUES (idJ, idP); 
	strcpy (consulta, "INSERT INTO PARTICIPACION VALUES ('");
	
	//convertimos id en un string y lo concatenamos 
	sprintf(idJs, "%d", idJ);
	strcat (consulta, idJs); 
	strcat (consulta, ");");
	
	//convertimos duracion en un string y lo concatenamos 
	sprintf(idPs, "%d", idP);
	strcat (consulta, idPs); 
	strcat (consulta, ");");
	
	printf("consulta = %s\n", consulta);
	// Ahora ya podemos realizar la insercion 
	err = mysql_query(conn, consulta);
	if (err!=0) {
		printf ("Error al introducir datos la base %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	
	
	// Consulta SQL para obtener el nï¿ºmero de partidas ganadas por un jugador llamado 'MOHAMED'
	err=mysql_query (conn, "SELECT PARTIDAS.GANADOR FROM (PARTIDAS, JUGADORES, PARTICIPACION) WHERE PARTIDAS.GANADOR='MOHAMED' && JUGADORES.ID=PARTICIPACION.ID_J && PARTIDAS.ID=PARTICIPACION.ID_P");
	if (err!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//recogemos el resultado de la consulta
	resultado = mysql_store_result (conn);
	// El resultado es una estructura matricial en la que cada
	// fila contiene los datos de una persona y sucesivas
	// columnas contienen cada uno de los datos de la persona
	// recorremos una a una cada fila del resultado
	// ahora obtenemos la siguiente fila
	row = mysql_fetch_row (resultado);
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		while (row !=NULL)
	{
			// la columnas 0 contiene el nombre del jugador
			printf ("MOHAMED: %s\n",
					row[4]);
			// obtenemos la siguiente fila
			row = mysql_fetch_row (resultado);
	}
		mysql_close (conn);
		
		
}

