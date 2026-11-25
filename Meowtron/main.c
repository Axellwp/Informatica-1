#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>
#include <time.h>
const char *api_cat = "https://meowfacts.herokuapp.com/?lang=esp";
struct memory {
  char *response;
  size_t size;
};
static size_t cb(char *data, size_t size, size_t nmemb, void *clientp)
{
  size_t realsize = size * nmemb;
  struct memory *mem = clientp;
  char *ptr = realloc(mem->response, mem->size + realsize + 1);
  if(!ptr)
    return 0;  /* out of memory */
  mem->response = ptr;
  memcpy(&(mem->response[mem->size]), data, realsize);
  mem->size += realsize;
  mem->response[mem->size] = 0;
  return realsize;
}
void leer_token(char *token);
void leer_archivo(long *ult_up);
void obt_id(char *token);
void obt_msj(char *token, long *ult_up);
void enviar_msj(char *token, char *nombre, long char_id, char *mensaje);
void guardar_registro(char *nombre, char *mensaje);
	int main(void){
  char token[100] = {0};
  leer_token(token);
  long ult_up;
  obt_id(token);
  leer_archivo(&ult_up);
while(1){
  obt_msj(token, &ult_up);
 sleep(2);
}
}
void leer_token(char *p){
	FILE *token = fopen("token.txt", "r");
	if (token == NULL){
	printf("Error al abrir el TOKEN");
		exit(1);}
	fgets(p,100,token);
	p[strcspn(p, "\n")] = '\0';
	fclose(token);
}
void obt_id(char *token){
	long up_id;
	char url_tg[200];
	CURLcode res;
	snprintf(url_tg, sizeof(url_tg),"https://api.telegram.org/bot%s/getUpdates",token);
	CURL *curl = curl_easy_init();
	struct memory chunk = {0};
  	if(curl) {
    		curl_easy_setopt(curl, CURLOPT_URL, url_tg);
    		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
    		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		res = curl_easy_perform(curl);
	if(res != CURLE_OK || chunk.response == NULL){
    		free(chunk.response);
    		curl_easy_cleanup(curl);
    		return;
}
		if(res != 0)
			printf("Error de codigo%d\n", res);
		curl_easy_cleanup(curl);}
	char *p = strstr(chunk.response, "\"update_id\"");
	if (p == NULL){
		free(chunk.response);
		return;}
	while ( p != NULL){
		p = strchr(p,':');
		p++;
		up_id = atol(p);
		p = strstr(p, "\"update_id\"");}
	FILE *id = fopen("registro.txt", "w");
	if(id == NULL){
		printf("Error al guardar el registro");
		exit(1);}
	fprintf(id,"%ld",up_id);
	fclose(id);
	free(chunk.response);
}
void leer_archivo(long *up){
	FILE *id = fopen("registro.txt","r");
	if(id == NULL){
	 	printf("No existe el registro");
		exit(1);}
	fscanf(id,"%ld",up);
	fclose(id);
}
void obt_msj(char *token, long *ult_up){
    char url_tg[250];
    snprintf(url_tg, sizeof(url_tg),
        "https://api.telegram.org/bot%s/getUpdates?offset=%ld",
        token, *ult_up + 1);
    CURL *curl = curl_easy_init();
    struct memory chunk = {0};
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, url_tg);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);
        curl_easy_perform(curl);
        if(chunk.response == NULL){
            curl_easy_cleanup(curl);
            return;
        }
        char *u = strstr(chunk.response, "\"update_id\"");
        while(u != NULL){
            u = strchr(u, ':') + 1;
            long id = atol(u);
            char *p = strstr(u, "\"message\"");
            if(p == NULL)
                break;
	    char *chat = strstr(p, "\"chat\"");
            char nombre[100];
            char *p_nombre = strstr(chat, "\"first_name\"");
            p_nombre = strchr(p_nombre, ':') + 1;
            while(*p_nombre == ' ')
                p_nombre++;
            p_nombre++;
            char *fin = strchr(p_nombre, '"');
            int largo = fin - p_nombre;
            strncpy(nombre, p_nombre, largo);
            nombre[largo] = '\0';
            char *id_chat = strstr(chat, "\"id\"");
            id_chat = strchr(id_chat, ':') + 1;
            long chat_id = atol(id_chat);
            char *texto = strstr(id_chat, "\"text\"");
            texto = strchr(texto, ':') + 1;
            while(*texto == ' ')
                texto++;
            texto++;
            fin = strchr(texto, '"');
            int largo_texto = fin - texto;
            char mensaje[500];
            strncpy(mensaje, texto, largo_texto);
            mensaje[largo_texto] = '\0';
	    guardar_registro(nombre, mensaje);
            enviar_msj(token, nombre, chat_id, mensaje);
            *ult_up = id;
            u = strstr(fin + 1, "\"update_id\"");
        }
        FILE *archivo = fopen("registro.txt", "w");
        fprintf(archivo, "%ld", *ult_up);
        fclose(archivo);
        free(chunk.response);
        curl_easy_cleanup(curl);
    }
}

void enviar_msj(char *token, char *nombre, long chat_id, char *mensaje){
    char respuesta[500] = {0};
    CURL *curl = curl_easy_init();
    struct memory chunk = {0};
    if(strcasestr(mensaje, "Hola") != NULL || strcasecmp(mensaje,"/start") == 0){
        snprintf(respuesta, sizeof(respuesta), "Miowla, %s! para obtener un dato escribe /gato", nombre);
    }
    else if(strcasecmp(mensaje, "Adios") == 0 || strcasecmp(mensaje,"Chau") == 0){
        snprintf(respuesta, sizeof(respuesta), "I'll be back.. Miau");
    }
    else if(strcasecmp(mensaje, "/gato") == 0){
        curl_easy_setopt(curl, CURLOPT_URL, api_cat);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);
        curl_easy_perform(curl);
        char *p = strstr(chunk.response, "\"data\"");
        p = strchr(p, ':') + 1;
        while(*p == ' ' || *p == '[' || *p == '"')
            p++;
        char *fin = strchr(p, '"');
        int largo = fin - p;
        strncpy(respuesta, p, largo);
        respuesta[largo] = '\0';
        free(chunk.response);
        chunk.response = NULL;
        chunk.size = 0;
    }
char *respuesta_url = curl_easy_escape(curl, respuesta, 0);
	char url_tg[1000];
    snprintf(url_tg, sizeof(url_tg),"https://api.telegram.org/bot%s/sendMessage?chat_id=%ld&text=%s",token, chat_id, respuesta_url);
    curl_easy_setopt(curl, CURLOPT_URL, url_tg);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);
    curl_easy_perform(curl);
    curl_free(respuesta_url);
    guardar_registro("BOT", respuesta);
    free(chunk.response);
    curl_easy_cleanup(curl);
}
void guardar_registro(char *nombre, char *mensaje){
	FILE *historial = fopen("historial.txt", "a");
	time_t ahora = time(NULL);
	struct tm *fecha = localtime(&ahora);
	char hora[10];
	strftime(hora, sizeof(hora), "%H:%M:%S", fecha); 
	fprintf(historial, "%s | %s ° %s\n", hora,nombre, mensaje);
        fclose(historial);

}

