#include <iostream>
#include <cstring>
using namespace std;
bool** adjMatrix;
bool** adjMatrix2;

////1. ve 2.graf icin matris olusturma adimlari
class Graph {
public:
    int numVertices;

    explicit Graph(int numVertices) {
        this->numVertices = numVertices;
        adjMatrix = new bool*[numVertices];
        for (int i = 0; i < numVertices; i++) {
            adjMatrix[i] = new bool[numVertices];
            for (int j = 0; j < numVertices; j++)
                adjMatrix[i][j] = false;
        }
    }

    static void addEdge(int i, int j) {
        adjMatrix[i][j] = true;
        adjMatrix[j][i] = true;
    }

    void toString() {
        for (int i = 0; i < numVertices; i++) {
            cout << i << " : ";
            for (int j = 0; j < numVertices; j++)
                cout << adjMatrix[i][j] << " ";
            cout << "\n";
        }
    }

    ~Graph() {
        for (int i = 0; i < numVertices; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;
    }
};

class Graph2{
public:
    int numVertices;

    explicit Graph2(int numVertices) {
        this->numVertices = numVertices;
        adjMatrix2 = new bool*[numVertices];
        for (int i = 0; i < numVertices; i++) {
            adjMatrix2[i] = new bool[numVertices];
            for (int j = 0; j < numVertices; j++)
                adjMatrix2[i][j] = false;
        }
    }
    void addEdge2(int i, int j) {
        adjMatrix2[i][j] = true;
        adjMatrix2[j][i] = true;
    }

    void toString2() {
        for (int i = 0; i < numVertices; i++) {
            cout << i << " : ";
            for (int j = 0; j < numVertices; j++)
                cout << adjMatrix2[i][j] << " ";
            cout << "\n";
        }
    }

    ~Graph2() {
        for (int i = 0; i < numVertices; i++)
            delete[] adjMatrix2[i];
        delete[] adjMatrix2;
    }
};

////tum pathleri bulabilmek icin DFS algoritmasi kullanildi
void DFS(bool** graph, bool marked[], int n, int vert, int start, int &count, int V){
    marked[vert] = true;

    if (n == 0) {
        marked[vert] = false;
        if (graph[vert][start]){
            count++;
            return;
        }
        else
            return;
    }
    for (int i = 0; i < V; i++)
        if (!marked[i] && graph[vert][i])
            DFS(graph, marked, n-1, i, start, count, V);
    marked[vert] = false;
}

////pathleri bulmak icin countCycles function
int countCycles(bool** graph, int n, int V){
    bool marked[V];
    memset(marked, 0, sizeof(marked));
    int count = 0;

    for (int i = 0; i < V - (n - 1); i++){
        DFS(graph, marked, n-1, i, i, count, V);
        marked[i] = true;
    }

    return count/2;
}

////dugumlerin derecelerini sayar
int countDegree(int e1, int e2){
    int counter;
    int counter2;

    int counterArr[e1],counterArr2[e2];
    for(int i = 0; i<e1 ; i++){
        counter = 0;
        counter2 = 0;
        for(int j = 0; j<e1; j++){
            if(adjMatrix[i][j] == 1){
                counter++;
            }
            if(adjMatrix2[i][j] == 1){
                counter2++;
            }
        }
        counterArr[i] = counter;
        counterArr2[i] = counter2;
    }

    int degreeCounter = 0;
    for(int i = 0; i<e2; i++){
        if(counterArr[i]==counterArr2[i]){
            degreeCounter++;
        }
    }
    return degreeCounter;
}

////tum pathlerin uzunluklarini diziye atar ve iki dizi ayni ise "true" dondurur
bool samePaths(int e1, int e2, int v){
    int maxLength = 0;

    if(v%2 != 0){
        maxLength = v*(v-1)/2;
    }
    else{
        maxLength = v*(v-2)/2;
    }

    int path[maxLength];
    int path2[maxLength];
    
    ////burada tum olasi yol uzunluklarini diziye uzunluklarina gore kaydediyoruz. 
    /// ornegin 2 uzunlugundaki yollarin sayisini 2.indekse kaydediyoruz. en sonda ise bu indeksleri karsilastirarak
    ////esitliklerini kontrol ediyoruz. tum uzunluklardaki yollar esitse 4.kural saglaniyor demektir.
    for(int i = 1; i<=maxLength; i++){
        path[i] = countCycles(adjMatrix,i, v);
        path2[i] = countCycles(adjMatrix2,i, v);
    }

    int pathCounter = 0;

    for(int i = 1; i<=maxLength ; i++){
        if(path[i] == path2[i]){
            pathCounter++;
        }
    }

    if(pathCounter == maxLength){
        return true;
    }

    return false;
}

int main() {
    int v1, v2, e1, e2;

    ////dugum ve baglanti bilgileri
    cout<<"number of V and E for graph 1: ";
    cin>>v1>>e1;

    cout<<"number of V and E for graph 2: ";
    cin>>v2>>e2;

    ////graflar gerekli sartlari sagliyorsa komsuluk matrisleri olusturulur
    if(v1==v2 && e1==e2){//rule 1 -> dugum sayilari esit
                         //rule 2 -> baglanti sayilari esit
        int a,b;

        Graph g(v1);
        for(int i = 0; i<e1; i++){
            cin>>a>>b;
            g.addEdge(a, b);
        }
        cout<<"\n";
        Graph2 g2(v2);
        for(int i = 0; i<e2; i++){
            cin>>a>>b;
            g2.addEdge2(a, b);
        }

        ////matrixleri ekrana yazdirma
        cout<<"adj matrix for graph 1:\n";
        g.toString();

        cout<<"\n";

        cout<<"adj matrix for graph 2:\n";
        g2.toString2();

        ////matrixlerin node derecelerini bulma ve karsilastirma
        if(countDegree(e1,e2) == e2 && samePaths(e1,e2,v2)){//rule 3 -> her dugum esit dereceye sahip
                                                               //rule 4 -> her iki grafin da tüm dugumlerinin path'leri esit uzunlukta
            cout<<"\n! these graphs are isomorphic.";
        }


        ////sartlar saglanmiyorsa izomorfizm yoktur
        else{
            cout<<"\n! these graphs are not isomorphic.";
        }
    }

    ////sartlar saglanmiyorsa izomorfizm yoktur
    else{
        cout<<"\n! these graphs are not isomorphic.";
    }
}