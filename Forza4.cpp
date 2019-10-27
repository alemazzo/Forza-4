#include <iostream>
using namespace std;

class Player{
    public:
        string name;
        int wins = 0;
        Player(){};
};

class Forza4{

    private:

        Player players[2];
        bool turno = 0;
        int field[6][7];
        int moves = 0;

        void print(){

            cout << endl << "Field : " << endl;

            for(int i = 0; i < 6; i++){

                cout << "|";

                for(int j = 0; j < 7; j++){
                    int n = this->field[i][j];                    
                    if(n==0) cout << " ";
                    if(n==1) cout << "X";
                    if(n==2) cout << "0";
                    cout << '|';
                }

                cout << endl;
            }

            cout << endl;
        }

        int get_colonna(){

            int c;
            string str;

            while(true){

                try{
                    cout << "Inserisci colonna [1-7] : ";
                    cin >> str;
                    c = stoi(str);
                    if(c >= 1 && c <= 7) break;
                }catch(...){}
                cout << "Errore inserimento" << endl;
            }

            return c-1;
        }

        void start(){

            for(int i=0;i<6;i++){
                cout << "----------";
                for(int j=0;j<7;j++){
                    this->field[i][j] = 0;
                }
            }
            cout << endl;
            cout << "Players : " << endl;
            cout << this->players[0].name << " - " << this->players[0].wins << " wins" << endl;
            cout << this->players[1].name << " - " << this->players[1].wins << " wins" << endl;

            this->play();

        }

        void play(){
            this->moves++;
            this->print();
            int c;
            bool free;
            do{

                cout << "Turno di : " << this->players[this->turno].name << endl;
                c = this->get_colonna();
                free = false;
                for(int i = 5;i >= 0; i--){
                    if(this->field[i][c] == 0){
                        this->field[i][c] = (this->turno + 1);
                        free = true;
                        break;
                    }
                }
                if(!free) cout << endl << "Colonna completamente occupata - Ritenta" << endl;

            }while(!free);

            if(!this->check_win()){
                if(this->moves == 42){
                    cout << endl << "! It's a draw !" << endl;
                    this->print();
                    
                    string replay;
                    cout << "Do you wanna play again? (y/n) : ";
                    cin >> replay;
                    if(replay != "y") return;
                    else this->start();
                }else this->turno = !this->turno;
            }
            
            else{

                this->players[this->turno].wins++;
                cout << endl << "! The winner is " << this->players[this->turno].name << " ! " << endl;
                this->print();
                
                string replay;
                cout << "Do you wanna play again? (y/n) : ";
                cin >> replay;
                if(replay != "y") return;
                else this->start();
            }
            
            this->play();
        }   
        


        bool check_win(){
            
            //righe
            for(int i = 0;i < 6;i++){

                for(int j = 0;j < 4;j++){

                    bool four = true;

                    for(int z = 1; z < 4; z++){

                        if(this->field[i][j+z] != 0){
                            if(this->field[i][j+z] != this->field[i][j+z-1]) four = false;
                        }else{
                            four = false;
                        }
                    }
                    if(four) return true;
                }
            }

            //colonne
            for(int i = 0;i < 7;i++){

                for(int j = 0;j < 3;j++){

                    bool four = true;

                    for(int z = 1; z < 4; z++){

                        if(this->field[j+z][i] != 0){
                            if(this->field[j+z][i] != this->field[j+z-1][i]) four = false;
                        }else{
                            four = false;
                        }
                    }
                    if(four) return true;
                }
            }

            

            //diagonali
            
            for(int r = 0; r < 6; r++){
                
                for(int c = 0; c < 7; c++){                    
                    //alto sx
                    if(c >= 3 && r >= 3){
                        bool four = true;
                        for(int x = r-1, y = c-1; x > (r-4) && four; x--,y--){
                            int n = this->field[x][y];
                            if(n == 0 || n != this->field[x+1][y+1]) four = false;
                        }
                        if(four) return true;
                    }
                    
                    //alto dx
                    if(c <= 4 && r >= 3){
                        bool four = true;
                        for(int x = r-1, y = c+1; x > (r-4) && four; x--,y++){
                            int n = this->field[x][y];
                            if(n == 0 || n != this->field[x+1][y-1]) four = false;
                        }
                        if(four) return true;
                    }
                }
            }
            return false;          
        }
        
        
    public:
        Forza4(){

            cout << "Welcome in C++ 4-in-a-row game;" << endl;

            cout << "Insert the first player's name : ";
            cin >> players[0].name;

            cout << "Insert the second player's name : ";
            cin >> players[1].name;

            this->start();
        }
};

int main(){
    
    Forza4 *f = new Forza4();
    
    return 1;
}