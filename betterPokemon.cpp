#include "betterPokemon.h"

using namespace std;

void usage() {
    printf("betterPokemon -f config.ini");
}

static char filename[100];

/*
 * size is the order
 */
pokemon** createPokemonMap(int size) {
    if (size <= 0) {
        cout<<" Bad arguments to createPokemonMap, size=" << size << endl;
        return NULL;
    }
    pokemon **map = (pokemon**)malloc(size * sizeof(pokemon*));
    for (int i = 0; i < size; i++) {
        map[i] = (pokemon*)malloc(size * sizeof(pokemon));
        for (int j = 0; j < size; j++) {
            map[i][j].x 	= -1;
            map[i][j].y 	= -1;
            map[i][j].type 	= -1;
            map[i][j].wall 	= -1;
            map[i][j].entity= -1;
        }
    }
    return map;
}
bool isAWall(pokemon *p) {
    return (p->wall == WALL);
}
void showPokeObject (pokemon *p) {
    if (p == NULL) return;
    // cout<<"x="<<p->x<<" y="<<p->y<<endl;
    if (p->wall == WALL) {
        cout<<"wall"<<endl;
        return;
    }
    if (p->type == e_pokemon) {
        cout<<"Pokemon "<< getPokemonString(p->entity) << " Value=" << p->entity <<"; ";
    } else if (p->type == e_pokeystop) {
        cout<<"Pokestop "<< p->entity;
    }
}
void showMap (pokemon** map, int size) {
    if (size <= 0) {
        cout<<" Bad arguments to show, size=" << size << endl;
        return;
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout<<endl<<"Poke Object at "<< i <<", " <<j <<endl;
            showPokeObject(&map[i][j]);
        }
    }
}
void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
void setPokemon(pokemon** map, int t, int x, int y) {
    map[x][y].type 		= e_pokemon;
    map[x][y].entity 	= t;
    map[x][y].x			= x;
    map[x][y].y			= y;
    map[x][y].wall		= NO_WALL;
}
void setPokestop(pokemon** map, int t, int x, int y) {
    map[x][y].type 		= e_pokeystop;
    map[x][y].entity 	= t;
    map[x][y].x			= x;
    map[x][y].y			= y;
    map[x][y].wall		= NO_WALL;
}
void setWall (pokemon** map, int x, int y) {
    map[x][y].type 		= -1;
    map[x][y].entity 	= -1;
    map[x][y].x			= x;
    map[x][y].y			= y;
    map[x][y].wall		= WALL;
}
pokemon ** processPokemons(char *filename, int &squareMatrixSize) {
    FILE * fp;
    ssize_t read;
    char * line = NULL;
    size_t len = 0;
    squareMatrixSize = 0;
    pokemon **pokemonMap = NULL;

    /*ofstream myfile (filename);
    if (myfile.is_open())
    {
        myfile << "mapsize=5\n";
        myfile << "pokemon=6\n";
        myfile << "0,4 3\n";
        myfile << "1,2 5\n";
        myfile << "2,0 6\n";
        myfile << "3,2 9\n";
        myfile << "3,4 4\n";
        myfile << "4,0 1\n";
        myfile << "pokeystops=5\n";
        myfile << "0,2 4\n";
        myfile << "1,4 6\n";
        myfile << "2,2 2\n";
        myfile << "3,0 3\n";
        myfile << "4,2 1\n";
        myfile << "wallcells=5\n";
        myfile << "1,1\n";
        myfile << "2,1\n";
        myfile << "3,1\n";
        myfile << "1,3\n";
        myfile << "2,3\n";
        myfile.close();
    }*/

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("\nFile read failure; file=%s", filename);
        exit(EXIT_FAILURE);
    }
    while ((read = getline(&line, &len, fp)) != -1) {
        char *p = strtok(line, "=");
        string s = p;
        if (p != NULL && s == "mapsize") {
            p = strtok(NULL, "=");
            squareMatrixSize = atoi(p);
            pokemonMap = createPokemonMap(squareMatrixSize);
            // showMap(pokemonMap, squareMatrixSize);
        } else if (p != NULL && s == "pokemon") {
            p = strtok(NULL, "=");
            int numberOfPokemons = atoi(p);
            cout << "numberOfPokemons = " << numberOfPokemons <<endl;
            for (int i = 0; i < numberOfPokemons; i++) {
                read = getline(&line, &len, fp);
                string lineStr = line;
                vector<string> pokeStr = split(lineStr, ' ');
                string poketype = pokeStr[1];
                vector<string> pokelocationStr = split(pokeStr[0], ',');
                setPokemon(pokemonMap, stoi(poketype), stoi(pokelocationStr[0]), stoi(pokelocationStr[1]));
            }
        } else if (p != NULL && s == "pokeystops") {
            p = strtok(NULL, "=");
            int numberOfPokestops = atoi(p);
            cout << "numberOfPokestops = " << numberOfPokestops <<endl;
            for (int i = 0; i < numberOfPokestops; i++) {
                read = getline(&line, &len, fp);
                string lineStr = line;
                vector<string> pokeStr = split(lineStr, ' ');
                string numberOfPokeBalls = pokeStr[1];
                vector<string> pokelocationStr = split(pokeStr[0], ',');
                setPokestop(pokemonMap, stoi(numberOfPokeBalls), stoi(pokelocationStr[0]), stoi(pokelocationStr[1]));
            }
        } else if (p != NULL && s == "wallcells") {
            p = strtok(NULL, "=");
            int numberOfWalls = atoi(p);
            cout << "numberOfWalls = " << numberOfWalls <<endl;
            for (int i = 0; i < numberOfWalls; i++) {
                read = getline(&line, &len, fp);
                string lineStr = line;
                vector<string> splitStr = split(lineStr, ',');
                setWall(pokemonMap, stoi(splitStr[0]), stoi(splitStr[1]));
            }
        }
    }
    return pokemonMap;
}

void printPath(int pathNumber, deque<pair<int,int>> *path, pokemon **pokemonMap) {
    if (path->empty()) return;
    std::deque<pair<int,int>>::iterator it = path->begin();
    cout << "Path " << pathNumber << ":";
    static int bestPokeValue;
    static int bestPokePath;
    deque<pokemon*> pokeyMonStash;
    deque<pokemon*> pokeBallStash;
    while (it != path->end())
    {
        std::cout << " (" << (*it).first << ", " << (*it).second << ")";
        pokemon* obj = &pokemonMap[(*it).first][(*it).second];
        if (obj->type == e_pokemon)
            pokeyMonStash.push_back(obj);
        else if (obj->type == e_pokeystop)
            pokeBallStash.push_back(obj);
        it++;
    }
    cout << endl;
    int pokemonSum = 0;
    cout << "\tPokemons collected = ";
    std::deque<pokemon*>::iterator pokeymonIT = pokeyMonStash.begin();
    while (pokeymonIT != pokeyMonStash.end())
    {
        showPokeObject(*pokeymonIT);
        pokemonSum += (*pokeymonIT)->entity;
        pokeymonIT++;
    }
    cout << endl << "\tPokemons value = " << pokemonSum;
    cout << endl << "\tPokeballs collected = ";
    int pokeyballs = 0;
    std::deque<pokemon*>::iterator pokeBallIT = pokeBallStash.begin();
    while (pokeBallIT != pokeBallStash.end())
    {
        pokeyballs += (*pokeBallIT)->entity;
        pokeBallIT++;
    }
    cout << pokeyballs << endl;
    cout << "\tTotal Poke value for path " <<pathNumber << " = " << pokeyballs + pokemonSum << endl;
    if ((pokeyballs + pokemonSum) > bestPokeValue) {
        bestPokeValue = (pokeyballs + pokemonSum);
        bestPokePath = pathNumber;
    }
    cout << "\tBest Path so far = Path " <<bestPokePath << ", with value = " << bestPokeValue << endl << endl;

}
void caluclatePathsInternal (pokemon **pokemonMap, int size, int **visited, pair<int, int> start, pair <int,int> destination, deque<pair<int,int>> *path) {

    static unsigned pathNumber;
    if (start.first >= size || start.second >= size) return;
    if (start == destination) {
        pathNumber++;
        path->push_back(make_pair(start.first,start.second));
        printPath(pathNumber, path, pokemonMap);
        path->pop_back();
        visited[start.first][start.second] = 0;
        return;
    }
    // try to go to the right and bottom
    if (isAWall(&pokemonMap[start.first][start.second])) {
        // this is a wall return;
        return;
    }
    visited[start.first][start.second] = 1;
    path->push_back(make_pair(start.first,start.second));
    caluclatePathsInternal (pokemonMap, size, visited, make_pair(start.first+1, start.second), destination, path);
    caluclatePathsInternal (pokemonMap, size, visited, make_pair(start.first, start.second+1), destination, path);
    path->pop_back();
    visited[start.first][start.second] = 0;
}

void calculatepaths (pokemon **pokemonMap, int size, pair<int, int> start, pair <int,int> destination) {
    cout << "Traveling from location: (" << start.first << ", " << start.second <<") to: (" << destination.first << ", " << destination.second <<")" <<endl;
    int **visitedMatrix = (int**)malloc(size * sizeof(int*));
    deque<pair<int,int>> path;
    for (int i = 0; i < size; i++) {
        visitedMatrix[i] = (int*)malloc(size * sizeof(int));
        for (int j = 0; j < size; ++j) {
            visitedMatrix[i][j] = 0;
        }
    }
    caluclatePathsInternal(pokemonMap, size, visitedMatrix, start, destination, &path);
    for (int i = 0; i < size; i++) {
        delete visitedMatrix[i];
    }
    delete visitedMatrix;
}

int main(int argc, char **argv) {
    char c;
    while ((c = getopt(argc, argv, "f:")) != EOF) {
        switch (c) {
            case 'f': /* Generate summary info for the autograder */
                memset(filename, '\0', 100);
                strcpy(filename, optarg);
                break;
            default:
                usage();
                exit(1);
        }
    }
    int mapsize = 0;
    pokemon **pokemonMap = processPokemons(filename, mapsize);

    // Uncomment this to show map
    // showMap(pokemonMap, mapsize);

    calculatepaths(pokemonMap, mapsize, make_pair(0,0), make_pair(mapsize-1, mapsize-1));

    // cleanupn
    for (int i = 0; i < mapsize; i++) {
        delete pokemonMap[i];
    }
    delete pokemonMap;
    return 0;
}
