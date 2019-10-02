#include <cstdio>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct formula{
	int row = 0, col = 0;
	//char *form = nullptr;
	char form[100000];
	formula(int _row, int _col, char *_form){
		//printf("This form: %s\n", _form);
		row = _row;
		col = _col;
		//form = _form;
		strcpy(form,_form);
	}

	/*~formula(){
		printf("%s\n","Calling Destructor FORMULA");
	}*/
};

struct spreadhsheet{
	int rows = 0, cols = 0;
	int **arr_spread = nullptr;
	vector<formula> formulas_vec;

	spreadhsheet(int _rows, int _cols){
		rows = _rows;
		cols = _cols;
		arr_spread = new int *[rows];
		//printf("%s\n", "Constructor called");
		for(int i=0; i<rows; ++i){
			arr_spread[i] = new int[cols];
		}
	}

	void input_values(){
		int value = 0;
		//char *str_value = nullptr;
		char str_value[100000];
		size_t n;
		for(int i=0; i<rows; ++i){
			for(int j=0; j<cols; ++j){
				/*if(i == 1 && j == 1){
					printf("fffxread Formula: %s \n",formulas_vec[j-1].form);
				}*/
				//scanf("%d",&value);
				scanf("%99999s", str_value);
				//printf("Ingresaste: %s\n",str_value);
				if(str_value[0] == '='){
					//printf("Guardar formula: %s\n",str_value);
					formula f1(i,j,str_value);
					//printf("Struct : %s\n",str_value);
					formulas_vec.push_back(f1);
					//printf("read Formula: %s \n",formulas_vec[j].form);
					arr_spread[i][j] = 0;
				}
				else{
					arr_spread[i][j] = atoi(str_value);
				}
				//printf("Ingresaste: %s\n",str_value);
				//arr_spread[i][j] = value;
			}
		}
		//printf("xxxxread Formula: %s \n",formulas_vec[1].form);
	}

	void print_formulas(){
		printf("%s\n", "-- Print Vector of formulas --");
		for(auto f1 : formulas_vec){
			printf("Formula: %s - En Fila: %d - En columna: %d \n", f1.form, f1.row, f1.col);
		}
		/*for(auto it = formulas_vec.begin(); it != formulas_vec.end(); ++it){
			printf("%s\n", (*it).form);
		}*/
	}

	void read_linea_form(char *form, vector<string> &expresion_vec){
		string cel_name = "";
		for(int i=1;i<100000; ++i){
			if(form[i] == ' ') break;
			if(form[i] == '+'){
				//printf("\n");
				// Update 
				expresion_vec.push_back(cel_name);
				//printf("%s\n",cel_name.c_str());
				// Reset
				cel_name="";
				continue;
			}
			//printf("%c", form[i]);
			cel_name += form[i];
		}
		expresion_vec.push_back(cel_name);	// Update the last cell
		//printf("%s\n",cel_name.c_str());
	}

	void get_celda_index(const string celda, int &x, int &y){
		int exponent = 0;
		for(int i=0; i<celda.size(); ++i){
			if(int(celda[i]) >= 65){
				exponent++;
			}
			else break;
		}
		x = stoi(celda.substr(exponent)) - 1;
		int index_celda = 0;
		for(int i=exponent-1; i>=0; --i){
			y += (int(celda[index_celda]) - 64) * pow(26,i);
			index_celda++;
		}
	}

	void calculate_celda(const int x, const int y, const formula f1){
		arr_spread[f1.row][f1.col] += arr_spread[x][y];
	}

	void execute_formula(){
		//printf("%s\n", "-- Execute cell formulas --");
		for(auto f1 : formulas_vec){
			//printf("Formula: %s - En Fila: %d - En columna: %d \n", f1.form, f1.row, f1.col);
			vector<string> expresion_vec;
			read_linea_form(f1.form, expresion_vec);
			for(auto celda : expresion_vec){
				int x = 0, y = -1;
				get_celda_index(celda, x, y);
				//printf("X: %d - Y: %d \n",x,y);
				calculate_celda(x,y,f1);
			}
		}
	}

	void print_spreadsheet(){
		//printf("%s\n", "-- Print spreadhsheet --");
		for(int i=0; i<rows; ++i){
			for(int j=0; j<cols; ++j){
				printf("%d ", arr_spread[i][j]);
			}
			printf("\n");
		}
	}

	int get_column(){
		return 0;
	}

	~spreadhsheet(){
		//printf("%s\n", "Destructor called");
		for(int i=0; i<rows; ++i){
			delete[] arr_spread[i];
		}
		delete[] arr_spread;
	}

};

int main(){
	int num_spreadsheet = 0;
	int cols = 0 , rows = 0;
	scanf("%d",&num_spreadsheet);
	for(int i=0; i<num_spreadsheet; ++i){
		scanf("%d %d",&cols, &rows);
		spreadhsheet sp(rows, cols);
		sp.input_values();
		//sp.print_formulas();
		sp.execute_formula();
		sp.print_spreadsheet();
	}

	return 0;
}