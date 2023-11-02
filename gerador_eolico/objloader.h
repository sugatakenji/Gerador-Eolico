// A função loadobj serve para carregar os vetores de um arquivo obj. Ela não é muito eficiente no uso de memória, já que //carrega todos os vetores de uma malha na memoria. Além dos vetores das malhas, a função carrega os vetores normais e o mapemamento de textura
// A função recebe obrigatoriamente os seguintees parametros loadobj(filename, ponteiro vetores, ponteiros das normais, ponteiros do mapeamento )
//
//



struct point3{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct point2{
    GLfloat x;
    GLfloat y;
};

void loadObj(const char *fname,std::vector<point3> & out_vertex,std::vector<point3> & out_normal, std::vector<point2> &
out_uv)
{
	FILE *fp;//manipulador do arquivo .obj
	int read;//flag que sinaliza a quantidade de variaveis lidas do arquivo
	fp=fopen(fname,"r");
	if (!fp) 
	{
		printf("Nao foi possivel abrir o arquivo %s\n", fname);
	  exit(1);
	}
	//essa parte do codigo salvara os array contendo os vetores e as faces
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices; // 3 vetores com os indices dos vertices
	std::vector< point3 > temp_vertices;//vetor com os vertices das faces
	std::vector< point2 > temp_uvs;//vetor com os vertices de mapeamento de textura
	std::vector< point3 > temp_normals; // vetor com as normais 
	//lendo o arquivo
	while(!(feof(fp))){
		char lineHeader[128]; //variavel que guardara temporariamente as  palavras lidas 
		read = fscanf(fp, "%s", lineHeader); //le a primeira palavra do arquivos
        //A partir de agora iremos ler cada tipo de vertice do arquivo
		if(strcmp(lineHeader, "v") == 0){ 
			point3 vertex;
		    fscanf(fp, "%f %f %f\n", &vertex.x,&vertex.y,&vertex.z);
            temp_vertices.push_back(vertex);    
		}else if (strcmp(lineHeader, "vt") == 0){
            point2 uv;
            fscanf(fp, "%f %f \n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        }else if (strcmp(lineHeader, "vn") == 0){
            point3 normal;
            fscanf(fp, "%f %f %f \n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }else if (strcmp(lineHeader,"f" ) == 0){
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1] , &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);    
            normalIndices.push_back(normalIndex[1]);    
            normalIndices.push_back(normalIndex[2]);
        }    
    }  
    for(int i = 0; i < vertexIndices.size(); i++){
          unsigned int vertexIndex = vertexIndices[i];
          printf("vertex indices : %d\n", vertexIndex);
          point3 vertex = temp_vertices[vertexIndex - 1];
          out_vertex.push_back(vertex);//saida vertex
     }
     for(int i = 0; i < normalIndices.size(); i++){
          unsigned int normalIndex = normalIndices[i];
          printf("normal indices : %d\n", normalIndex);
          point3 normal = temp_normals[normalIndex - 1];
          out_normal.push_back(normal);//saida vertex
     } 
     for(int i = 0; i < uvIndices.size(); i++){
          unsigned int uvIndex = uvIndices[i];
          printf("uv indices : %d\n", uvIndex);
          point2 uv = temp_uvs[uvIndex - 1];
          out_uv.push_back(uv);//saida vertex
     }      
	fclose(fp);
}
